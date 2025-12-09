/**
 * @file point_set.h
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @brief Declaración de la clase point_set que implementa EMST por Kruskal.
 */

#pragma once

#include <vector>
#include <string>
#include <ostream>

#include "point_types.h"
#include "sub_tree.h"

namespace EMST
{
    typedef std::vector<sub_tree> forest;

    /**
     * @class point_set
     * @brief Conjunto de puntos con la capacidad de calcular su EMST (Kruskal adaptado).
     *
     * Hereda de CyA::point_vector para representar el conjunto de puntos.
     */
    class point_set : public CyA::point_vector
    {
    private:
        CyA::tree emst_;

    public:
        /**
         * @brief Construye un point_set a partir de un vector de puntos.
         * @param points vector de puntos inicial
         */
        explicit point_set(const CyA::point_vector &points);

        /**
         * @brief Destructor.
         */
        ~point_set(void);

        /**
         * @brief Ejecuta el algoritmo EMST (Kruskal) y guarda el árbol en emst_.
         */
        void EMST(void);

        /**
         * @brief Escribe el árbol (lista de arcos) en el flujo dado.
         * @param os flujo de salida
         */
        void write_tree(std::ostream &os) const;

        /**
         * @brief Escribe el conjunto de puntos en el flujo dado (uso auxiliar).
         * @param os flujo de salida
         */
        void write(std::ostream &os) const;

        /**
         * @brief Devuelve el árbol (EMST) calculado.
         * @return referencia constante al vector de arcos que forman el EMST
         */
        inline const CyA::tree& get_tree(void) const { return emst_; }

        /**
         * @brief Devuelve los puntos originales.
         * @return referencia constante al vector de puntos
         */
        inline const CyA::point_vector& get_points(void) const { return *this; }

        /**
         * @brief Devuelve el coste del EMST.
         * @return coste total (double)
         */
        inline const double get_cost(void) const { return compute_cost(); }

    private:
        /**
         * @brief Calcula el vector de aristas ponderadas (todas las parejas de puntos).
         * @param av vector a rellenar con pares (peso, arco)
         */
        void compute_arc_vector(CyA::arc_vector &av) const;

        /**
         * @brief Encuentra los índices i, j en el bosque st donde están los extremos del arco a.
         * @param st bosque actual
         * @param a arco (sin peso) cuyos extremos vamos a localizar
         * @param i índice del sub-árbol que contiene a.first (salida)
         * @param j índice del sub-árbol que contiene a.second (salida)
         */
        void find_incident_subtrees(const forest& st, const CyA::arc &a, int& i, int& j) const;

        /**
         * @brief Fusiona en st los sub-árboles i y j usando el arco a (y su peso).
         * @param st bosque (se modifica)
         * @param a arco que une los subárboles
         * @param i índice del primer sub-árbol
         * @param j índice del segundo sub-árbol
         * @param weight peso del arco (distancia euclídea)
         */
        void merge_subtrees(forest& st, const CyA::arc &a, int i, int j, double weight) const;

        /**
         * @brief Calcula el coste total del árbol almacenado en emst_.
         * @return coste total (double)
         */
        double compute_cost(void) const;

        /**
         * @brief Calcula la distancia euclídea entre los extremos del arco a.
         * @param a arco con dos puntos
         * @return distancia euclídea (double)
         */
        double euclidean_distance(const CyA::arc& a) const;
    };
}
