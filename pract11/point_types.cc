/**
 * @file point_types.cc
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @brief Implementación de operadores de entrada/salida para puntos y vectores.
 */

#include "point_types.h"

#include <iomanip>

/**
 * @brief Imprime un vector de puntos, primero el número de puntos y después cada punto en línea.
 * @param os flujo de salida
 * @param ps vector de puntos
 * @return referencia al flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps)
{
    // Imprime tamaño y un salto
    os << ps.size() << std::endl;

    // Imprime cada punto en nueva línea usando el operador << de puntos
    for (const CyA::point &p : ps)
    {
        os << p << std::endl;
    }

    return os;
}

/**
 * @brief Imprime un punto en formato "x\t y" con anchura y precisión definidas.
 * @param os flujo de salida
 * @param p punto a imprimir
 * @return referencia al flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const CyA::point& p)
{
    // Formatear con setw y setprecision para reproducibilidad en la salida
    os << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC)
       << p.first << "\t" << std::setw(MAX_SZ) << std::fixed << std::setprecision(MAX_PREC)
       << p.second;

    return os;
}

/**
 * @brief Lee un vector de puntos desde el flujo: lee n y luego n puntos.
 * @param is flujo de entrada
 * @param ps vector de puntos a rellenar
 * @return referencia al flujo de entrada
 */
std::istream& operator>>(std::istream& is, CyA::point_vector& ps)
{
    int n;
    // Leer el número de puntos
    is >> n;

    ps.clear();

    // Leer n puntos y se añaden al vector
    for (int i = 0; i < n; ++i)
    {
        CyA::point p;
        is >> p;

        ps.push_back(p);
    }

    return is;
}

/**
 * @brief Lee dos double desde el flujo y los asigna a p.first y p.second.
 * @param is flujo de entrada
 * @param p punto a rellenar
 * @return referencia al flujo de entrada
 */
std::istream& operator>>(std::istream& is, CyA::point& p)
{
    // Lectura simple de dos valores double
    is >> p.first >> p.second;

    return is;
}
