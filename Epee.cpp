#include "Entite.h"
#include <cmath>
#include <cassert>
#include <iostream>
using namespace std;

// constructeur par defaut de l'entite// le destructeur par defaut est automatiquement genere par le compilateur, on peut aussi faire un constructeur qui prend en parametre les valeurs des attributs pour les initialiser directement.
Entite::Entite() : hitbox (Vecteur2D(0,0),32, 32) {
    pv = 50;
    pvMax = 50;
    position = Vecteur2D(0, 0);
    vitesse = Vecteur2D(0, 0);
}

Rect Entite::getHitbox() const {
    return hitbox;
}

bool Entite::Estvivant() const {
    return pv > 0;
}

float Entite::distance(const Entite& autre) const {
    float dx = position.x - autre.position.x;
    float dy = position.y - autre.position.y;
    return sqrt(dx * dx + dy * dy);
}

void Entite::deplacer(int x, int y) {
    position.x += x;
    position.y += y;
    hitbox.position = position;
}

void Entite::subirDegats(int degats) {
    pv -= degats;
    if (pv <= 0) {
        pv = 0;
        cout << "L'entite est morte." << endl;
    }
}

void Entite::setPv(int newPv) {
    pv = newPv;
}

void Entite::setPvMax(int newPvMax) {
    pvMax = newPvMax;
}

void Entite::setPosition(Vecteur2D newPosition) {
    position = newPosition;
}

void Entite::setVitesse(Vecteur2D newVitesse) {
    vitesse = newVitesse;
}

void testEntite() {
    Entite e1;
    Entite e2;

  
    e1.setPosition(Vecteur2D(0, 0));
    e2.setPosition(Vecteur2D(3, 4));
    float d = e1.distance(e2);
    assert(d == 5.0f);
    cout << "Distance e1-e2 : " << d << " (attendu : 5)" << endl;

 
    e1.deplacer(1, 1);
    assert(e1.getPosition().x == 1 && e1.getPosition().y == 1);
    cout << "Position apres deplacement : "
         << e1.getPosition().x << " " << e1.getPosition().y
         << " (attendu : 1 1)" << endl;

    e1.setPv(50);
    e1.subirDegats(10);
    assert(e1.getPv() == 40);
    cout << "PV apres 10 degats : " << e1.getPv() << " (attendu : 40)" << endl;

    e1.subirDegats(40);
    assert(e1.getPv() == 0);
    cout << "V apres degats fatals : " << e1.getPv() << " (attendu : 0)" << endl;

    
    Entite e;
    assert(e.getPv() == 50);
    assert(e.getPvMax() == 50);
    assert(e.getPosition().x == 0 && e.getPosition().y == 0);
    assert(e.getVitesse().x == 0 && e.getVitesse().y == 0);
    cout << "Test de la classe Entite bien passé" << endl;

}

