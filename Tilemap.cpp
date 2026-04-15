#ifndef RECT_H_
#define RECT_H_

#include "Vecteur2D.h"

/** @brief Structure représentant un rectangle défini par sa position (un Vecteur2D), sa taille et sa vitesse. */
struct Rect {
    Vecteur2D position; ///< Position du rectangle
    float width;      ///< Largeur du rectangle
    float height;     ///< Hauteur du rectangle

    // constructeur principal
    Rect(const Vecteur2D& pos, float w, float h);
};

#endif // RECT_H_

