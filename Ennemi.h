#ifndef ARME_H
#define ARME_H

#include <string>

class Arme {
protected: // personne appart les classe qui herite de arme 
    std::string nom;
    int puissance;
    float portee; // la distance a laquelle l'arme peut toucher une cible (le rapport avec la hitbox est que si la 
    // distance entre le personnage et la cible est inferieur ou egale a la portee de l'arme alors l'attaque touche la cible)

public:
    Arme() : nom(""), puissance(0), portee(0.0f) {}// constructeur par defaut de l'arme, on peut aussi faire un constructeur qui prend en parametre les valeurs des attributs pour les initialiser directement.
    Arme(const std::string& nom, int puissance, float portee)
        : nom(nom), puissance(puissance), portee(portee) {}// constructeur qui prend en parametre les valeurs des attributs pour les initialiser directement.

  //  virtual ~Arme() {} 

    std::string getNom() const;
    int getPuissance() const;
    float getPortee() const; 
    void testerArme(); // declaration de la fonction de test de la classe Arme, la definition de cette fonction se trouve dans le fichier Arme.cpp
};

#endif