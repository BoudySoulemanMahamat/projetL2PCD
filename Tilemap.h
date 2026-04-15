#include "Vecteur2D.h"
#include "Rect.h"
#include "Entite.h"
#include "Arme.h"
#include "Epee.h"
#include "Personnage.h"
#include "Ennemi.h"

#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

// ─────────────────────────────────────────────
//  Compteurs globaux
// ─────────────────────────────────────────────
static int total  = 0;
static int passed = 0;

// Macro de test — affiche OK ou FAIL sans crasher
#define TEST(nom, condition)                                        \
    do {                                                            \
        total++;                                                    \
        if (condition) {                                            \
            passed++;                                              \
            cout << "[OK]   " << nom << endl;                      \
        } else {                                                    \
            cout << "[FAIL] " << nom << endl;                      \
        }                                                           \
    } while(0)

// Comparaison float avec tolérance
bool approx(float a, float b, float eps = 0.001f) {
    return fabs(a - b) < eps;
}

// ═════════════════════════════════════════════
//  1. VECTEUR2D
// ═════════════════════════════════════════════
void tester_Vecteur2D() {
    cout << "\n── Vecteur2D ──────────────────────────\n";

    // Construction
    Vecteur2D a(2.0f, 3.0f);
    TEST("Vecteur2D : constructeur x", a.x == 2.0f);
    TEST("Vecteur2D : constructeur y", a.y == 3.0f);

    // Constructeur par défaut
    Vecteur2D zero;
    TEST("Vecteur2D : constructeur defaut x=0", zero.x == 0.0f);
    TEST("Vecteur2D : constructeur defaut y=0", zero.y == 0.0f);

    // operator+
    Vecteur2D b(1.0f, 1.0f);
    Vecteur2D c = a + b;
    TEST("Vecteur2D : operator+ x", c.x == 3.0f);
    TEST("Vecteur2D : operator+ y", c.y == 4.0f);

    // operator*
    Vecteur2D d = a * 2.0f;
    TEST("Vecteur2D : operator* x", d.x == 4.0f);
    TEST("Vecteur2D : operator* y", d.y == 6.0f);

    // operator* par 0
    Vecteur2D e = a * 0.0f;
    TEST("Vecteur2D : operator* par 0", e.x == 0.0f && e.y == 0.0f);

    // longueur
    Vecteur2D v(3.0f, 4.0f);
    TEST("Vecteur2D : longueur (3,4) = 5", approx(v.longueur(), 5.0f));

    Vecteur2D v2(0.0f, 0.0f);
    TEST("Vecteur2D : longueur vecteur nul = 0", approx(v2.longueur(), 0.0f));

    // Régression : addition neutre
    Vecteur2D f = a + zero;
    TEST("REGRESSION : a + zero == a", f.x == a.x && f.y == a.y);

    // Régression : multiplication par 1
    Vecteur2D g = a * 1.0f;
    TEST("REGRESSION : a * 1 == a", g.x == a.x && g.y == a.y);
}

// ═════════════════════════════════════════════
//  2. RECT
// ═════════════════════════════════════════════
void tester_Rect() {
    cout << "\n── Rect ────────────────────────────────\n";

    Rect r(Vecteur2D(10.0f, 20.0f), 32.0f, 64.0f);
    TEST("Rect : position x", r.position.x == 10.0f);
    TEST("Rect : position y", r.position.y == 20.0f);
    TEST("Rect : width",      r.width  == 32.0f);
    TEST("Rect : height",     r.height == 64.0f);

    // Rect à l'origine
    Rect r2(Vecteur2D(0.0f, 0.0f), 1.0f, 1.0f);
    TEST("Rect : position origine", r2.position.x == 0.0f && r2.position.y == 0.0f);

    // Régression : dimensions non nulles
    TEST("REGRESSION : width > 0",  r.width  > 0.0f);
    TEST("REGRESSION : height > 0", r.height > 0.0f);
}

// ═════════════════════════════════════════════
//  3. ENTITE
// ═════════════════════════════════════════════
void tester_Entite() {
    cout << "\n── Entite ──────────────────────────────\n";

    Entite e;

    // État initial
    TEST("Entite : pv initial > 0",     e.getPv() > 0);
    TEST("Entite : pvMax initial > 0",  e.getPvMax() > 0);
    TEST("Entite : position initiale x=0", e.getPosition().x == 0.0f);
    TEST("Entite : position initiale y=0", e.getPosition().y == 0.0f);
    TEST("Entite : Estvivant au depart",   e.Estvivant());

    // subirDegats partiel
    e.setPv(50);
    e.subirDegats(10);
    TEST("Entite : subirDegats partiel (50-10=40)", e.getPv() == 40);
    TEST("Entite : toujours vivant apres degats partiels", e.Estvivant());

    // subirDegats fatal
    e.subirDegats(100);
    TEST("Entite : subirDegats fatal -> pv=0", e.getPv() == 0);
    TEST("Entite : Estvivant=false apres mort", !e.Estvivant());

    // Régression : pv ne descend pas sous 0
    e.subirDegats(999);
    TEST("REGRESSION : pv ne descend pas sous 0", e.getPv() == 0);

    // deplacer
    e.setPosition(Vecteur2D(0.0f, 0.0f));
    e.deplacer(5, 3);
    TEST("Entite : deplacer x", e.getPosition().x == 5.0f);
    TEST("Entite : deplacer y", e.getPosition().y == 3.0f);

    // deplacer deux fois (régression cumul)
    e.deplacer(2, 0);
    TEST("REGRESSION : deplacer cumule x", e.getPosition().x == 7.0f);

    // hitbox suit la position
    Rect hb = e.getHitbox();
    TEST("Entite : hitbox suit position x", hb.position.x == e.getPosition().x);
    TEST("Entite : hitbox suit position y", hb.position.y == e.getPosition().y);

    // distance
    Entite e2;
    e.setPosition(Vecteur2D(0.0f, 0.0f));
    e2.setPosition(Vecteur2D(3.0f, 4.0f));
    TEST("Entite : distance (3,4) = 5", approx(e.distance(e2), 5.0f));

    // distance identique dans les deux sens (régression symétrie)
    TEST("REGRESSION : distance symetrique", approx(e.distance(e2), e2.distance(e)));

    // distance avec soi-même
    TEST("REGRESSION : distance avec soi-meme = 0", approx(e.distance(e), 0.0f));

    // setPv / setPvMax
    e.setPv(30);
    TEST("Entite : setPv", e.getPv() == 30);
    e.setPvMax(100);
    TEST("Entite : setPvMax", e.getPvMax() == 100);

    // setVitesse
    e.setVitesse(Vecteur2D(2.0f, 0.0f));
    TEST("Entite : setVitesse x", e.getVitesse().x == 2.0f);
}

// ═════════════════════════════════════════════
//  4. ARME + EPEE
// ═════════════════════════════════════════════
void tester_Arme() {
    cout << "\n── Arme / Epee ─────────────────────────\n";

    Epee epee;
    TEST("Epee : nom",       epee.getNom() == "Epee");
    TEST("Epee : puissance", epee.getPuissance() == 10);
    TEST("Epee : portee",    approx(epee.getPortee(), 1.0f));

    // utiliser
    int pv = 30;
    epee.utiliser(pv);
    TEST("Epee : utiliser reduit pv (30-10=20)", pv == 20);

    // utiliser plusieurs fois (régression cumul)
    epee.utiliser(pv);
    TEST("REGRESSION : Epee utiliser 2x (20-10=10)", pv == 10);

    // utiliser jusqu'à 0
    epee.utiliser(pv);
    TEST("Epee : utiliser -> pv=0", pv == 0);

    // Régression : puissance positive
    TEST("REGRESSION : puissance > 0", epee.getPuissance() > 0);
    TEST("REGRESSION : portee > 0",    epee.getPortee() > 0.0f);
}

// ═════════════════════════════════════════════
//  5. PERSONNAGE
// ═════════════════════════════════════════════
void tester_Personnage() {
    cout << "\n── Personnage ──────────────────────────\n";

    Personnage p;

    // État initial
    TEST("Personnage : pv initial > 0",    p.getPv() > 0);
    TEST("Personnage : Estvivant au depart", p.Estvivant());

    // setPseudo
    p.setPseudo("Hissein");

    // attaquer — l'ennemi subit des dégâts si à portée
    Ennemi ennemi;
    int pvAvant = ennemi.getPv();
    p.setPosition(Vecteur2D(0.0f, 0.0f));
    ennemi.setPosition(Vecteur2D(0.5f, 0.0f)); // distance < portee (1.0)
    p.attaquer(ennemi);
    TEST("Personnage : attaquer reduit pv ennemi", ennemi.getPv() < pvAvant);

    // attaquer hors portée — pas de dégâts
    Ennemi ennemi2;
    int pvAvant2 = ennemi2.getPv();
    p.setPosition(Vecteur2D(0.0f, 0.0f));
    ennemi2.setPosition(Vecteur2D(100.0f, 0.0f)); // hors portée
    p.attaquer(ennemi2);
    TEST("Personnage : attaquer hors portee = pas de degats", ennemi2.getPv() == pvAvant2);

    // assassiner — met pv à 0
    Ennemi ennemi3;
    p.setPosition(Vecteur2D(0.0f, 0.0f));
    ennemi3.setPosition(Vecteur2D(0.5f, 0.0f));
    p.assassiner(ennemi3);
    TEST("Personnage : assassiner -> pv=0", ennemi3.getPv() == 0);
    TEST("Personnage : assassiner -> Estvivant=false", !ennemi3.Estvivant());

    // Régression : le personnage ne se blesse pas en attaquant
    int pvJoueurAvant = p.getPv();
    Ennemi ennemi4;
    p.setPosition(Vecteur2D(0.0f, 0.0f));
    ennemi4.setPosition(Vecteur2D(0.5f, 0.0f));
    p.attaquer(ennemi4);
    TEST("REGRESSION : attaquer ne blesse pas le joueur", p.getPv() == pvJoueurAvant);

    // sauter — position y change
    float yAvant = p.getPosition().y;
    p.sauter();
    TEST("Personnage : sauter modifie position y", p.getPosition().y != yAvant);
}

// ═════════════════════════════════════════════
//  6. ENNEMI
// ═════════════════════════════════════════════
void tester_Ennemi() {
    cout << "\n── Ennemi ──────────────────────────────\n";

    Ennemi e;

    // État initial
    TEST("Ennemi : pv initial > 0",     e.getPv() > 0);
    TEST("Ennemi : Estvivant au depart", e.Estvivant());

    // infligerDegats
    Personnage p;
    int pvAvant = p.getPv();
    e.infligerDegats(p);
    TEST("Ennemi : infligerDegats reduit pv joueur", p.getPv() <= pvAvant);

    // attaquer
    Personnage p2;
    int pvAvant2 = p2.getPv();
    e.attaquer(p2);
    TEST("Ennemi : attaquer reduit pv joueur", p2.getPv() < pvAvant2);

    // Ennemi peut mourir
    e.subirDegats(9999);
    TEST("Ennemi : peut mourir", !e.Estvivant());

    // Régression : pv ennemi ne descend pas sous 0
    TEST("REGRESSION : pv ennemi >= 0", e.getPv() >= 0);
}

// ═════════════════════════════════════════════
//  MAIN
// ═════════════════════════════════════════════
int main() {
    cout << "╔══════════════════════════════════════════╗\n";
    cout << "║  Les Gardiens de la Nuit — Tests noyau   ║\n";
    cout << "╚══════════════════════════════════════════╝\n";

    tester_Vecteur2D();
    tester_Rect();
    tester_Entite();
    tester_Arme();
    tester_Personnage();
    tester_Ennemi();

    cout << "\n══════════════════════════════════════════\n";
    cout << "  Résultat : " << passed << " / " << total << " tests passés\n";

    if (passed == total) {
        cout << "   Tous les tests sont passés !\n";
        return 0;
    } else {
        cout << "   " << (total - passed) << " test(s) échoué(s) !\n";
        return 1; // code erreur → utile pour CI/GitLab
    }
}