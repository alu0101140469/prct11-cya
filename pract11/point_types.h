/**
 * @file point_types.h
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @brief Tipos básicos para la práctica EMST (puntos, arcos, vectores...).
 *
 * Define tipos (point, arc, weigthed_arc, colecciones) y operadores de
 * entrada/salida para puntos y vectores de puntos.
 */

#pragma once

#include <iostream>
#include <utility>
#include <vector>
#include <set>

#define MAX_SZ 3
#define MAX_PREC 0

namespace CyA
{
    typedef std::pair<double, double> point;

    typedef std::pair<point, point> line;
    typedef std::vector<point> point_vector;

    typedef std::pair<point, point> arc;
    typedef std::pair<double, arc> weigthed_arc;
    typedef std::vector<weigthed_arc> arc_vector;

    typedef std::set<point> point_collection;

    typedef std::vector<arc> tree;
}

/**
 * @brief Formatea e imprime un vector de puntos (primero imprime tamaño).
 * @param os flujo de salida
 * @param ps vector de puntos
 * @return flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const CyA::point_vector& ps);

/**
 * @brief Formatea e imprime un punto (par ordenado).
 * @param os flujo de salida
 * @param ps punto a imprimir
 * @return flujo de salida
 */
std::ostream& operator<<(std::ostream& os, const CyA::point& ps);

/**
 * @brief Lee desde un flujo un vector de puntos (formato: n \n p1x p1y \n ...).
 * @param is flujo de entrada
 * @param ps vector de puntos a rellenar
 * @return flujo de entrada
 */
std::istream& operator>>(std::istream& is, CyA::point_vector& ps);

/**
 * @brief Lee desde un flujo un punto (dos double).
 * @param is flujo de entrada
 * @param ps punto a rellenar
 * @return flujo de entrada
 */
std::istream& operator>>(std::istream& is, CyA::point& ps);
