/**
 * @file main.cc
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @brief Programa principal. Lee puntos desde stdin, calcula EMST y escribe por stdout.
 *
 * Uso:
 *   ./emst # lee desde stdin y escribe aristas + coste a stdout
 *   ./emst < input1.txt > output1.txt # introducir puntos desde fichero y guardar salida en fichero
 *   ./emst -d output1.dot < input1.txt  # genera fichero DOT para visualización
 *   ./neato output1.dot -Tpdf -o salida.pdf # generar PDF con DOT
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

#include "point_types.h"
#include "point_set.h"

using namespace std;
using namespace EMST;

/**
 * @brief Genera un fichero DOT con el conjunto de puntos y las aristas del árbol.
 * @param filename nombre del fichero DOT a crear
 * @param ps conjunto de puntos (original)
 * @param tree aristas del EMST
 */
static void generate_dot(const string &filename,
                         const CyA::point_vector &ps,
                         const CyA::tree &tree)
{
    ofstream ofs(filename.c_str());

    if (!ofs)
    {
        cerr << "ERROR: no se puede abrir fichero DOT para escritura: " << filename << endl;
        return;
    }

    // Cabecera del grafo
    ofs << "graph{ " << endl << endl;

    // Imprimimos cada punto con su índice y posición pos="x,y!"
    for (size_t i = 0; i < ps.size(); ++i)
    {
        const CyA::point &p = ps[i];

        // Ejemplo: 0 [pos = "68,-21!"]
        ofs << " " << i << " [pos = \"" << p.first << "," << p.second << "!\"]" << endl;
    }

    ofs << endl;

    // Función auxiliar para encontrar el índice (posición) de un punto en el vector ps
    // Para cada arco del árbol escribimos indices de nodos
    // Necesitamos buscar el índice de cada punto en ps
    auto find_index = [&](const CyA::point &p) -> int {
        for (size_t k = 0; k < ps.size(); ++k)
        {
            if (ps[k] == p)
            {
                return static_cast<int>(k);
            }
        }
        return -1;
    };

    // Para cada arco del EMST escribir la conexión i -- j
    for (const CyA::arc &a : tree)
    {
        int i = find_index(a.first);
        int j = find_index(a.second);

        // Si ambos índices válidos, escribir la arista en el DOT
        if (i >= 0 && j >= 0)
        {
            ofs << " " << i << " -- " << j << endl;
        }
    }

    ofs << "}" << endl;

    ofs.close();
}

int main(int argc, char *argv[])
{
    // Parseo simple de argumentos: -d fichero.dot
    string dot_file;
    for (int i = 1; i < argc; ++i)
    {
        string arg(argv[i]);
        if (arg == "-d" && i + 1 < argc)
        {
            dot_file = argv[++i];
        }
        else if (arg == "-h" || arg == "--help")
        {
            cout << "Uso: " << argv[0] << " [-d fichero.dot]" << endl;
            return 0;
        }
        else
        {
            cerr << "Argumento desconocido: " << arg << endl;
            cout << "Uso: " << argv[0] << " [-d fichero.dot]" << endl;
            return 1;
        }
    }

    // Leer puntos desde stdin
    CyA::point_vector points;
    if (!(cin >> points))
    {
        cerr << "ERROR: lectura de puntos fallida." << endl;
        return 1;
    }

    // Construir point_set y calcular EMST
    point_set ps(points);
    ps.EMST();

    // Si se solicitó, generar fichero DOT para visualización
    if (!dot_file.empty())
    {
        generate_dot(dot_file, points, ps.get_tree());
    }

    // Escribimos el árbol y coste a stdout
    ps.write_tree(cout);

    return 0;
}
