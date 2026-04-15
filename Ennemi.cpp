#include <iostream>
#include <cassert>
#include "Arme.h"
using namespace std;

std::string Arme::getNom()       const { 
    return nom; }
    
int Arme::getPuissance() const { 
    return puissance; }

float Arme::getPortee() const {
     return portee; }
    
void Arme::testerArme() {
    Arme a("Arc", 15, 5.0f);
    assert(a.getNom() == "Arc");
    assert(a.getPuissance() == 15);
    assert(a.getPortee() == 5.0f);
    std::cout << "Test de la classe Arme bien passé" << std::endl;
}