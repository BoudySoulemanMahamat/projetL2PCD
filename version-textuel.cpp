#include "Vecteur2D.h"
#include <cmath>
Vecteur2D Vecteur2D::operator+(const Vecteur2D& vec) const {
    return {x + vec.x, y + vec.y};
}
Vecteur2D Vecteur2D::operator*(float s) const {
    return {x * s, y * s};
}
float Vecteur2D::longueur() const {
    return sqrt(x * x + y * y);
}       