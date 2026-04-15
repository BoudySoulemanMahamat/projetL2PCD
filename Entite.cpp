#include "Ennemi.h"
#include "Entite.h"
#include <iostream>
#include <cassert>
using namespace std;

void Ennemi::infligerDegats(Entite& cible) {
    cible.subirDegats(malusDegats);
}

void Ennemi::attaquer(Entite& cible) {
    cible.subirDegats(10); // degats de base de l'ennemi
}

std::string Ennemi::getNom() const {
    return nom;
}
int Ennemi::getMalusDegats() const {
    return malusDegats;
}

std::string Ennemi::setNom(std::string n) {
    nom = n;
    return nom;
}
int Ennemi::setMalusDegats(int m) {
    malusDegats = m;
    return malusDegats;
}

void testEnnemi() {
    Ennemi e;
    e.setNom("Gardien");
     assert(e.getNom() == "Gardien");
    std::cout << "Test de la classe Ennemi bien passé" << std::endl;
    e.setMalusDegats(5);
    assert(e.getMalusDegats() == 5);
    std::cout << "Test de la classe Ennemi bien passé" << std::endl;
}