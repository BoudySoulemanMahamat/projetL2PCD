#include "Niveau.h"
//#include "Tilemap.h"
#include <iostream>

Niveau::Niveau() : personnage(nullptr) {
}
void Niveau::charger(const std::string& fichierTerrain, const std::string& fichierObjets) {
    (void)fichierTerrain;
    (void)fichierObjets;

    // initialisation du personnage au début du niveau
    personnage = new Personnage();
    ennemis.push_back(new Ennemi()); // le new ajoute un ennemi à la liste des ennemis, on peut en ajouter autant que nécessaire
}

void Niveau::update() {
    if (personnage == nullptr) return;

    

    for (Ennemi* e : ennemis) {
        // mise à jour de chaque ennemi (IA, déplacement...)
        // e->update() si la méthode existe

        // combat si l'ennemi est en vie et à portée du personnage
        if (e->Estvivant() && personnage->distance(*e) <= 1.0f) {
            personnage->attaquer(*e);  // vérifie le nom exact de attaquer()
        }
    }

    // suppression propre des ennemis morts pour libérer la mémoire
    for (auto it = ennemis.begin(); it != ennemis.end(); ) {
        if (!(*it)->Estvivant()) {
            delete *it;
            it = ennemis.erase(it);  // erase retourne l'itérateur suivant valide
        } else {
            ++it;
        }
    }
}

// Getters qu'on peut utiliser dans le jeu. pour accéder au personnage et aux ennemis du niveau je viens à jour pour permettre au jeu de gérer les interactions entre le personnage et les ennemis, comme les attaques et les déplacements.
Personnage* Niveau::getPersonnage() {
    return personnage;
}

std::vector<Ennemi*>& Niveau::getEnnemis() {
    return ennemis;
}
Tilemap& Niveau::getTerrainMap() {
    return terrainMap;
}
