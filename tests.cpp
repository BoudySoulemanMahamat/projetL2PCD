#include "Rect.h"

Rect::Rect(const Vecteur2D& pos, float w, float h)
    : position(pos), width(w), height(h) {};
    // cosntructeur vide pour initialiser les attributs de la classe rect, on peut aussi faire un constructeur qui prend en parametre les valeurs des attributs pour les initialiser directement.