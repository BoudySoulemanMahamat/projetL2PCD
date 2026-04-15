#ifndef VECTEUR2D_H
#define VECTEUR2D_H
/** @brief Structure représentant un vecteur en 2D une position, soit une vitesse.*/

struct Vecteur2D { 
    float x; 
    
    float y;    
///** @brief Constructeur pour initialiser les composantes du vecteur. */
    
    Vecteur2D(float x = 0, float y = 0) : x(x), y(y) {}

    /** @brief Surcharge de l'opérateur + pour l'addition de vecteurs. */
  
    Vecteur2D operator+(const Vecteur2D& vec) const;   

/** @brief Surcharge de l'opérateur * pour la multiplication d'un vecteur par un scalaire. */
   
    Vecteur2D operator*(float s) const;
   
    ///** @brief Méthode pour calculer la longueur du vecteur. */
     float longueur() const;
};

#endif // VECTEUR2D_H
//dans le .h on declare juste les fonction et les structures, dans le .cpp on implemente les fonctions.