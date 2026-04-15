#ifndef EPEE_H
#define EPEE_H
#include "Arme.h"
#include "Entite.h"

class Epee : public Arme {
public:
    Epee() : Arme("Epee", 10, 1) {}

    void utiliser(Entite& cible) {
        cible.subirDegats(puissance);
    }

    void testerEpee();  // ← déclaration seulement, définition dans le .cpp
};

#endif