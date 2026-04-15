#include "Personnage.h"
#include "Entite.h"
#include "Ennemi.h"
#include <iostream>

void Personnage::setPseudo(std::string p){
    pseudo = p;
}

   void Personnage::sauter() {
    if (estAuSol) {
        velocite.y = -400.f;
        estAuSol = false;
    }
}

void Personnage::update(float deltaTime) {
    velocite.y += 900.f * deltaTime;

    Vecteur2D pos = getPosition();
    pos.y += velocite.y * deltaTime;
    setPosition(pos);

    // SOL_Y - TAILLE_JOUEUR = 500 - 48 = 452
    if (pos.y >= 452.f) {
        pos.y = 452.f;        // ← était 500.f
        setPosition(pos);
        velocite.y = 0;
        estAuSol = true;
    }
}
void Personnage::attaquer(Entite& cible) {
    if (distance(cible) <= armeEquipe.getPortee()) {
        cible.subirDegats(armeEquipe.getPuissance());
    }
}

void Personnage::assassiner(Entite& cible) {
    if (distance(cible) <= armeEquipe.getPortee()) {
        cible.setPv(0);
    }
}