#include "Epee.h"   // ← guillemets, pas < >
#include <cassert>
#include <iostream>

void Epee::testerEpee() {   // ← Epee:: obligatoire
    Epee e;
    Entite cible;
    int pvInitial = cible.getPv();
    e.utiliser(cible);
    assert(cible.getPv() == pvInitial - e.getPuissance());
    std::cout << "Test de la classe Epee bien passé" << std::endl;
}   //  pas de ; après }