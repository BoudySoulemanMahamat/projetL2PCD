#include "Personnage.h"
#include "Ennemi.h"
#include <iostream>
#include <string>

using namespace std;

// ─────────────────────────────────────────────
//  Affichage de l'état du jeu
// ─────────────────────────────────────────────
void afficherEtat(const Personnage& joueur, const Ennemi& ennemi) {
    cout << "\n╔══════════════════════════════════════╗\n";
    cout << "║  Les Gardiens de la Nuit             ║\n";
    cout << "╠══════════════════════════════════════╣\n";
    cout << "║  Joueur  PV : " << joueur.getPv()
         << " / " << joueur.getPvMax() << "\n";
    cout << "║  Ennemi  PV : " << ennemi.getPv()
         << " / " << ennemi.getPvMax() << "\n";
    cout << "║  Position joueur : ("
         << joueur.getPosition().x << ", "
         << joueur.getPosition().y << ")\n";
    cout << "║  Distance ennemi : "
         << joueur.distance(ennemi) << "                 ║\n";  
    cout << "╚══════════════════════════════════════╝\n";
}

// ─────────────────────────────────────────────
//  Affichage du menu
// ─────────────────────────────────────────────
void afficherMenu() {
    cout << "\n  [a] Attaquer     (combat frontal)\n";
    cout << "  [s] Assassiner   (elimination silencieuse)\n";
    cout << "  [d] Se deplacer  (+1 vers l'ennemi)\n";
    cout << "  [q] Quitter\n";
    cout << "\n> ";
}

// ─────────────────────────────────────────────
//  Boucle principale
// ─────────────────────────────────────────────
int main_textuel() {

    // ── Initialisation ────────────────────────
    cout << "\n=== Initialisation ===\n";

    Personnage joueur;
    joueur.setPseudo("Gardien");
    joueur.setPosition(Vecteur2D(0.0f, 0.0f));

    Ennemi ennemi;
    ennemi.setPosition(Vecteur2D(5.0f, 0.0f));

    cout << "[INIT] Joueur cree — PV=" << joueur.getPv()
         << "  position=(" << joueur.getPosition().x
         << "," << joueur.getPosition().y << ")\n";
    cout << "[INIT] Ennemi cree — PV=" << ennemi.getPv()
         << "  position=(" << ennemi.getPosition().x
         << "," << ennemi.getPosition().y << ")\n";
    cout << "[INIT] Niveau charge — boucle principale demarre\n";

    int tour = 0;
    bool quitter = false;

    // ── Boucle principale ─────────────────────
    while (joueur.Estvivant() && ennemi.Estvivant() && !quitter) {

        tour++;

        // 1. gererEvenements
        cout << "\n[BOUCLE " << tour << "] gererEvenements()\n";
        afficherEtat(joueur, ennemi);
        afficherMenu();

        string commande;
        cin >> commande;

        // 2. mettreAJour
        cout << "[BOUCLE " << tour << "] mettreAJour()\n";

        if (commande == "a") {
    int pvAvant = ennemi.getPv();
    joueur.attaquer(ennemi);

    if (ennemi.getPv() < pvAvant) {
        // L'attaque a touché
        cout << "\n  >>> Attaque frontale reussie !\n";
        cout << "      Ennemi PV=" << ennemi.getPv() << "\n";

        if (ennemi.Estvivant()) {
            cout << "  >>> L'ennemi contre-attaque !\n";
            ennemi.attaquer(joueur);
            cout << "      Joueur PV=" << joueur.getPv() << "\n";
        }
    } else {
        // L'attaque a raté (trop loin)
        cout << "\n  >>> Attaque ratee ! Ennemi trop loin (distance="
             << joueur.distance(ennemi) << ", portee=1)\n";
    }
} else if (commande == "s") {

            float dist = joueur.distance(ennemi);
            cout << "\n  >>> Tentative assassinat (distance=" << dist << ")\n";
            if (dist <= 1.0f) {
                joueur.assassiner(ennemi);
                cout << "      Assassinat reussi ! Ennemi PV=" << ennemi.getPv() << "\n";
            } else {
                cout << "      Trop loin ! Rapprochez-vous d'abord.\n";
            }

        } else if (commande == "d") {

            joueur.deplacer(1, 0);
            cout << "\n  >>> Deplacement → position=("
                 << joueur.getPosition().x << ","
                 << joueur.getPosition().y << ")"
                 << "  distance ennemi=" << joueur.distance(ennemi) << "\n";

        } else if (commande == "q") {
            quitter = true;
        } else {
            cout << "  Commande inconnue. Utilisez a / s / d / q\n";
        }

        // 3. rendu (trace texte)
        cout << "[BOUCLE " << tour << "] rendu() — etat affiche ci-dessus\n";
    }

    // ── Fin ───────────────────────────────────
    cout << "\n[BOUCLE] Fin de la boucle principale\n";
    cout << "══════════════════════════════════════\n";

    if (!joueur.Estvivant())
        cout << "  GAME OVER  — joueur mort au tour " << tour << "\n";
    else if (!ennemi.Estvivant())
        cout << "  VICTOIRE   — ennemi vaincu au tour " << tour << " !\n";
    else
        cout << "  Quitte apres " << tour << " tour(s)\n";

    cout << "  PV joueur restants : " << joueur.getPv() << "\n";
    cout << "══════════════════════════════════════\n";

    return 0;
}