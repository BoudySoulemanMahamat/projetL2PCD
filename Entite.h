#ifndef __ENNEMI_H
#define __ENNEMI_H
#include "Entite.h"
#include <string>


class Ennemi : public Entite {
    private:
        std::string nom;
        int malusDegats;
    
    public:
        Ennemi() : Entite(), nom("ennemi"), malusDegats(0) {
            pv = 20;
            pvMax = 20;
        }
        /** \brief Modifie le nom de l'ennemi
         *  \param n Le nouveau nom de l'ennemi
         */
        std::string setNom(std::string n);

        /** \brief Modifie le malus de dégâts de l'ennemi
         *  \param m Le nouveau malus de dégâts de l'ennemi
         */
        int setMalusDegats(int m);
        /** \brief Renvoie le nom de l'ennemi
         *  \return Le nom de l'ennemi
         */
        std::string getNom() const;
        /** \brief Renvoie le malus de dégâts de l'ennemi
         *  \return Le malus de dégâts de l'ennemi
         */
        int getMalusDegats() const; 

        void infligerDegats(Entite& cible);
        /** \brief Attaque une cible
         *  \param cible La cible à attaquer
         */
        void attaquer(Entite& cible);

};
#endif