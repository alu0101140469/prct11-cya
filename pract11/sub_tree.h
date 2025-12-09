/**
 * @file sub_tree.h
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @brief Declaración de la clase sub_tree usada por Kruskal (subárboles).
 *
 * Implementa una estructura que contiene arcos, puntos contenidos y coste.
 */

#pragma once

#include <iostream>
#include <cmath>

#include "point_types.h"

namespace EMST
{
    /**
     * @class sub_tree
     * @brief Representa un sub-árbol: contiene arcos, puntos y coste acumulado.
     *
     * Métodos públicos permiten añadir arcos/puntos, comprobar pertenencia
     * y fusionar con otro sub-árbol mediante un arco ponderado.
     */
    class sub_tree
    {
    private:
        CyA::tree arcs_;
        CyA::point_collection points_;
        double cost_;

    public:
        /**
         * @brief Constructor por defecto.
         */
        sub_tree(void);

        /**
         * @brief Destructor.
         */
        ~sub_tree(void);

        /**
         * @brief Añade un arco (con sus puntos) al sub-árbol.
         * @param a arco a añadir
         */
        void add_arc(const CyA::arc &a);

        /**
         * @brief Añade un punto aislado al sub-árbol.
         * @param p punto a añadir
         */
        void add_point(const CyA::point &p);

        /**
         * @brief Indica si el sub-árbol contiene el punto.
         * @param p punto a comprobar
         * @return true si contiene, false en caso contrario
         */
        bool contains(const CyA::point &p) const;

        /**
         * @brief Fusiona el sub-árbol actual con otro sub-árbol pasado por referencia,
         *        mediante el arco ponderado a.
         * @param st sub-árbol que se añadirá
         * @param a arco ponderado que une ambos sub-árboles
         */
        void merge(const sub_tree &st, const CyA::weigthed_arc &a);

        /**
         * @brief Devuelve los arcos del sub-árbol.
         * @return referencia constante al vector de arcos
         */
        inline const CyA::tree& get_arcs(void) const { return arcs_; }

        /**
         * @brief Devuelve el coste acumulado del sub-árbol.
         * @return coste (double)
         */
        inline double get_cost(void) const { return cost_; }
    };

    typedef std::vector<sub_tree> sub_tree_vector;
}
