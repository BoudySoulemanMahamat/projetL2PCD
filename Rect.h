#ifndef PERSONNAGE_H
#define PERSONNAGE_H
#include "Entite.h"
#include "Arme.h"
#include <string>

class Personnage : public Entite {

    private:

    std::string pseudo;
    Arme armeEquipe;
    Vecteur2D velocite;         
    bool estAuSol = true;       
    const float gravite = 900.0; // force de gravité pour le saut
    const float force = -15.0; // force de saut initiale (valeur négative pour aller vers le haut)
    public:
Personnage() : Entite(), pseudo("joueur1"), armeEquipe("Epée", 10, 1.5f) {
    pv = 50;
    pvMax = 100;
    velocite = Vecteur2D(0, 0); // vitesse initiale nulle

}

    /** @brief Définit le pseudo du personnage
     *  @param p Le nouveau pseudo   */

    void setPseudo(std::string p);

    /** @brief Fait sauter le personnage
     */

    void sauter();


    
    void update(float deltaTime); // mise à jour de la position et de la physique du personnage


/** @brief Attaque une entité
     *  @param cible L'entité à attaquer
     */
    void attaquer(Entite& cible);
    /** @brief Assassine une entité
     *  @param cible L'entité à assassiner
     */

     
    void assassiner(Entite& cible);
};
#endif

