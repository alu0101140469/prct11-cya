/**
 * @file sub_tree.cc
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @brief Implementación de sub_tree.
 */

#include "sub_tree.h"

#include <iomanip>
#include <cmath>

#include <algorithm>
#include <utility>

namespace EMST
{
    /**
     * @brief Constructor: inicializa contenedores y coste a 0.0
     */
    sub_tree::sub_tree(void) : arcs_(),
                               points_(),
                               cost_(0.0)
    {
    }

    /**
     * @brief Destructor vacío (no necesita limpieza explícita).
     */
    sub_tree::~sub_tree(void)
    {
    }

    /**
     * @brief Añade un arco al sub-árbol.
     * @param a arco a añadir
     */
    void sub_tree::add_arc(const CyA::arc &a)
    {
        // Añadir el arco a la lista interna de arcos
        arcs_.push_back(a);

        // Añadir los puntos del arco al conjunto de puntos
        points_.insert(a.first);
        points_.insert(a.second);
    }

    /**
     * @brief Añade un punto aislado al sub-árbol.
     * @param p punto a añadir
     */
    void sub_tree::add_point(const CyA::point &p)
    {
        // Insertar el punto en la colección (set)
        points_.insert(p);
    }

    /**
     * @brief Indica si el sub-árbol contiene el punto.
     * @param p punto a comprobar
     * @return true si contiene, false en caso contrario
     */
    bool sub_tree::contains(const CyA::point &p) const
    {
        // Buscar en el set (log n)
        return points_.find(p) != points_.end();
    }

    /**
     * @brief Fusiona el sub-árbol actual con otro sub-árbol pasado por parámetro.
     * @param st sub-árbol que se añadirá
     * @param a arco ponderado que une ambos sub-árboles
     */
    void sub_tree::merge(const sub_tree &st, const CyA::weigthed_arc &a)
    {
        // Añadir todos los arcos del subárbol recibido
        arcs_.insert(arcs_.end(), st.arcs_.begin(), st.arcs_.end());
        // Añadir el arco que une ambos subárboles
        arcs_.push_back(a.second);

        // Unir las colecciones de puntos
        points_.insert(st.points_.begin(), st.points_.end());

        // Actualizar coste, con coste propio + coste del subárbol pasado + peso del arco que los une
        cost_ += a.first + st.get_cost();
    }
}
