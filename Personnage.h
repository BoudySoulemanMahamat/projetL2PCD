#ifndef NIVEAU_H
#define NIVEAU_H

#include "Tilemap.h"
#include "Personnage.h"
#include "Ennemi.h"
#include <vector>
#include <string>

class Niveau {
private:
    Tilemap terrainMap;
    Tilemap objetsMap;
    Personnage* personnage;
    std::vector<Ennemi*> ennemis;//un tableau d'ennemis pour stocker les ennemis ;;;
public:
    Niveau();
    ~Niveau();
    void charger(const std::string& fichierTerrain, const std::string& fichierObjets);
    void update();
    // Getters
    Personnage* getPersonnage();
    std::vector<Ennemi*>& getEnnemis();
    Tilemap& getTerrainMap();// pour accéder à la map de terrain depuis le niveau, afin de vérifier les collisions et les interactions avec le sol

};

#endif