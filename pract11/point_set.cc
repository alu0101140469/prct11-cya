/**
 * @file point_set.cc
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @brief Implementación de point_set y algoritmo EMST (Kruskal).
 */

#include "point_set.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>

namespace EMST
{
    /**
     * @brief Constructor: copia el vector de puntos al objeto.
     * @param points vector de puntos de entrada
     */
    point_set::point_set(const CyA::point_vector &points) : CyA::point_vector(points), emst_()
    {
    }

    /**
     * @brief Destructor vacío.
     */
    point_set::~point_set(void)
    {
    }

    /**
     * @brief Calcula la distancia euclídea entre dos puntos (arco).
     * @param a arco con dos puntos
     * @return distancia euclídea (double)
     */
    double point_set::euclidean_distance(const CyA::arc& a) const
    {
        // Calcular desplazamientos en x y y
        const double dx = a.first.first - a.second.first;
        const double dy = a.first.second - a.second.second;

        // Devolver la raíz cuadrada de la suma de cuadrados
        return std::sqrt(dx * dx + dy * dy);
    }

    /**
     * @brief Construye todas las aristas posibles entre pares de puntos y las ordena por peso.
     * @param av vector a rellenar con aristas ponderadas (peso, arco)
     */
    void point_set::compute_arc_vector(CyA::arc_vector &av) const
    {
        // Vaciar el vector de salida
        av.clear();

        // Tamaño del conjunto de puntos
        const int n = static_cast<int>(size());

        // Recorrer pares i<j para generar cada arista una vez
        for (int i = 0; i < n - 1; ++i)
        {
            const CyA::point &p_i = (*this)[i];

            for (int j = i + 1; j < n; ++j)
            {
                const CyA::point &p_j = (*this)[j];

                // Calculardistancia euclídea
                const double dist = euclidean_distance(std::make_pair(p_i, p_j));

                // Añadir par (distancia, arco)
                av.push_back(std::make_pair(dist, std::make_pair(p_i, p_j)));
            }
        }

        // Ordenar por el primer elemento del pair (distancia ascendente)
        std::sort(av.begin(), av.end());
    }

    /**
     * @brief Busca en el vector de sub_trees los subárboles que contienen cada extremo del arco a.
     * @param st bosque actual
     * @param a arco cuyos extremos se buscan
     * @param i referencia para devolver índice del subárbol que contiene a.first
     * @param j referencia para devolver índice del subárbol que contiene a.second
     */
    void point_set::find_incident_subtrees(const forest& st, const CyA::arc &a, int& i, int& j) const
    {
        // Inicializamos a -1 (no encontrados)
        i = -1;
        j = -1;

        const int m = static_cast<int>(st.size());

        // Iterar sobre cada sub_tree buscando los puntos
        for (int idx = 0; idx < m; ++idx)
        {
            // Si aún no se encuentra i y el sub_tree idx contiene a.first, lo asigno
            if (i == -1 && st[idx].contains(a.first))
            {
                i = idx;
            }

            // Si aún no se encuentra j y el sub_tree idx contiene a.second, lo asigno
            if (j == -1 && st[idx].contains(a.second))
            {
                j = idx;
            }

            // Si ambos encontrados, salir del bucle
            if (i != -1 && j != -1)
            {
                break;
            }
        }
    }

    /**
     * @brief Fusiona los sub-árboles i y j en el bosque st usando el arco proporcionado.
     * @param st bosque (se modificará)
     * @param a arco que une ambos sub-árboles
     * @param i índice del primer sub-árbol
     * @param j índice del segundo sub-árbol
     * @param weight peso del arco (distancia euclídea)
     */
    void point_set::merge_subtrees(forest& st, const CyA::arc &a, int i, int j, double weight) const
    {
        // Crear el arco ponderado (peso, arco)
        const CyA::weigthed_arc wa = std::make_pair(weight, a);

        // Si índices iguales, nada que fusionar
        if (i == j)
        {
            return;
        }

        // Para mantener índices válidos al borrar, borramos el índice mayor para no invalidar el menor.
        if (i < j)
        {
            // Fusionar j en i, y borrar j
            st[i].merge(st[j], wa);
            st.erase(st.begin() + j);
        }
        else
        {
            // Fusionar i en j, y borrar i
            st[j].merge(st[i], wa);
            st.erase(st.begin() + i);
        }
    }

    /**
     * @brief Ejecuta Kruskal adaptado para obtener el EMST y almacenarlo en emst_.
     */
    void point_set::EMST(void)
    {
        // Generar el vector de aristas ponderadas entre todos los pares de puntos
        CyA::arc_vector av;
        compute_arc_vector(av);

        // Inicializar el bosque, donde cada punto es un sub-árbol independiente
        forest st;

        // Cada punto comienza como un sub-árbol aislado
        for (const CyA::point &p : *this)
        {
            sub_tree s;
            s.add_point(p); // sub-árbol con un solo vértice

            st.push_back(s);
        }

        // Recorremos aristas por peso creciente (Kruskal)
        for (const CyA::weigthed_arc &a : av)
        {
            int i, j;

            // a.second es el arco (sin peso)
            find_incident_subtrees(st, a.second, i, j);

            // Si no se encuentran índices (i o j = -1), se ignora la arista
            if (i == -1 || j == -1)
            {
                continue;
            }

            // Si pertenecen a sub-árboles distintos, se fusionan
            if (i != j)
            {
                merge_subtrees(st, a.second, i, j, a.first);
            }
        }

        // Tras las fusiones, si existe un único componente se guarda su lista de arcos en emst_
        if (!st.empty())
        {
            emst_ = st[0].get_arcs();
        }
    }

    /**
     * @brief Calcula el coste total del árbol almacenado en emst_ sumando distancias.
     * @return coste total (double)
     */
    double point_set::compute_cost(void) const
    {
        double sum = 0.0;

        // Sumar la distancia euclídea de cada arco del EMST
        for (const CyA::arc &a : emst_)
        {
            sum += euclidean_distance(a);
        }

        return sum;
    }

    /**
     * @brief Imprime el EMST en el flujo en formato "(x1, y1) -> (x2, y2)" y una línea final con el coste.
     * @param os flujo de salida
     */
    void point_set::write_tree(std::ostream &os) const
    {
        // Imprime cada arco en formato: (x, y) -> (x2, y2)
        for (const CyA::arc &a : emst_)
        {
            os << "(";
            os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << a.first.first << ", "
               << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << a.first.second;
            os << ") -> (";
            os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << a.second.first << ", "
               << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC) << a.second.second;
            os << ")" << std::endl;
        }

        // Imprimir el coste total con 2 decimales
        os << std::fixed << std::setprecision(2) << compute_cost() << std::endl;
    }

    /**
     * @brief Escribe el conjunto de puntos (invoca operador<<).
     * @param os flujo de salida
     */
    void point_set::write(std::ostream &os) const
    {
        os << *this;
    }
}
