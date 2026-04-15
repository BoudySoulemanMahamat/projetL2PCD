#include "Tilemap.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <cassert>
using namespace std;


void Tilemap::chargerCSV(const std::string& nomFichier) {

    ifstream fichier(nomFichier);

    if (!fichier.is_open()) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << nomFichier << endl;
        return;
    }

    string ligne;
    string valeur;
    string colonne;
    while (getline(fichier, ligne)) { //
        if (ligne.empty()) continue; // ignorer les lignes vides
        vector<int> mapLigne;
        size_t pos = 0;
        while ((pos = ligne.find(',')) != string::npos) {
            valeur = ligne.substr(0, pos);
            mapLigne.push_back(stoi(valeur)); // convertir la valeur en entier et l
            ligne.erase(0, pos + 1);
        }
        // ajouter la dernière valeur après la dernière virgule
        if (!ligne.empty()) {
            mapLigne.push_back(stoi(ligne));
        }
        map.push_back(mapLigne);
    }       

    fichier.close();
    }

int Tilemap::getTuile(int x, int y) const {
    if (x < 0 || x >= largeur || y < 0 || y >= hauteur) {
        cerr << "Erreur : Coordonnées (" << x << ", " << y << ") hors limites" << endl;
        return -1; // ou une valeur par défaut pour indiquer une erreur
    }
    return map[y][x];
}

bool Tilemap::estSolide(int x, int y) const {
    int tuile = getTuile(x, y);
    return tuile == 1; // 1 représente une tuile solide, 0 une tuile non solide
}
int Tilemap::getLargeur() const {
    return largeur;
}
int Tilemap::getHauteur() const {
    return hauteur;
}
 
void Tilemap::testRegressionMap() const {
    //test regression 
   int largeur = 24;
    int hauteur = 16;
    assert(getLargeur() == largeur);
    assert(getHauteur() == hauteur);

        cout << endl;
    }
