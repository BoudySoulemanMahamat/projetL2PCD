#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <climits>
#include <iostream>
#include <string>
#include "../noyau/Personnage.h"
#include "../noyau/Ennemi.h"

// ─────────────────────────────────────────────
//  Constantes
// ─────────────────────────────────────────────
const int LARGEUR_FENETRE = 1280;
const int HAUTEUR_FENETRE = 720;
const int TAILLE_JOUEUR   = 48;
const int TAILLE_ENNEMI   = 48;
const int SOL_Y           = 500;

// ─────────────────────────────────────────────
//  Dessiner un rectangle rempli
// ─────────────────────────────────────────────
void dessinerRect(SDL_Renderer* rendu, int x, int y, int w, int h,
                  Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(rendu, r, g, b, 255);
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(rendu, &rect);
}

// ─────────────────────────────────────────────
//  Afficher du texte à l'écran
// ─────────────────────────────────────────────
void dessinerTexte(SDL_Renderer* rendu, TTF_Font* police,
                   const std::string& texte, int x, int y,
                   Uint8 r, Uint8 g, Uint8 b) {
    SDL_Color couleur = { r, g, b, 255 };
    SDL_Surface* surface = TTF_RenderUTF8_Solid(police, texte.c_str(), couleur);
    if (!surface) return;
    SDL_Texture* texture = SDL_CreateTextureFromSurface(rendu, surface);
    SDL_Rect dst = { x, y, surface->w, surface->h };
    SDL_RenderCopy(rendu, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}

// ─────────────────────────────────────────────
//  Barre de vie
// ─────────────────────────────────────────────
void dessinerBarreVie(SDL_Renderer* rendu, int x, int y,
                      int pv, int pvMax) {
    int largeurMax = 80;
    int largeurActuelle = (pvMax > 0) ? (pv * largeurMax / pvMax) : 0;

    dessinerRect(rendu, x, y, largeurMax, 10, 80, 80, 80);
    dessinerRect(rendu, x, y, largeurActuelle, 10, 50, 200, 50);
    SDL_SetRenderDrawColor(rendu, 200, 200, 200, 255);
    SDL_Rect contour = { x, y, largeurMax, 10 };
    SDL_RenderDrawRect(rendu, &contour);
}

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────
int main() {

    // ── Init SDL ──────────────────────────────
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init erreur: " << SDL_GetError() << "\n";
        return 1;
    }
    if (TTF_Init() != 0) {
        std::cerr << "TTF_Init erreur: " << TTF_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    // ── Fenêtre + Renderer ────────────────────
    SDL_Window* fenetre = SDL_CreateWindow(
        "Les Gardiens de la Nuit",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        LARGEUR_FENETRE, HAUTEUR_FENETRE,
        SDL_WINDOW_SHOWN
    );
    if (!fenetre) {
        std::cerr << "Fenetre erreur: " << SDL_GetError() << "\n";
        TTF_Quit(); SDL_Quit();
        return 1;
    }

    SDL_Renderer* rendu = SDL_CreateRenderer(fenetre, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!rendu) {
        std::cerr << "Renderer erreur: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(fenetre);
        TTF_Quit(); SDL_Quit();
        return 1;
    }

    // ── Police ───────────────────────────────
    TTF_Font* police = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 18);
    TTF_Font* policeGrande = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 28);
    if (!police || !policeGrande)
        std::cerr << "Police erreur: " << TTF_GetError() << "\n";

    // ── Objets du noyau ───────────────────────
    Personnage joueur;
    joueur.setPseudo("Gardien");
    joueur.setPosition(Vecteur2D(200.0f, (float)(SOL_Y - TAILLE_JOUEUR)));

    Ennemi ennemi;
    ennemi.setPosition(Vecteur2D(900.0f, (float)(SOL_Y - TAILLE_ENNEMI)));

    std::cout << "[SDL] Fenetre ouverte\n";
    std::cout << "[SDL] Joueur PV=" << joueur.getPv() << "\n";
    std::cout << "[SDL] Ennemi PV=" << ennemi.getPv() << "\n";

    // ── DeltaTime ─────────────────────────────
    Uint32 dernierTemps = SDL_GetTicks();  // ← ajout

    // ── Boucle principale ─────────────────────
    bool enCours = true;
    while (enCours) {

        // ── DeltaTime calcul ──────────────────
        Uint32 maintenant = SDL_GetTicks();
        float deltaTime = (maintenant - dernierTemps) / 1000.f;  // en secondes
        dernierTemps = maintenant;

        // 1. Gérer les événements
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) enCours = false;

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {

                    case SDLK_LEFT:
                        joueur.deplacer(-10, 0);
                        break;

                    case SDLK_RIGHT:
                        joueur.deplacer(10, 0);
                        break;

                    case SDLK_UP:
                        joueur.sauter();  
                        break;

                    case SDLK_SPACE:
                        joueur.attaquer(ennemi);
                        std::cout << "[SDL] Attaque ! Ennemi PV="
                                  << ennemi.getPv() << "\n";
                        break;

                    case SDLK_a:
                        joueur.assassiner(ennemi);
                        std::cout << "[SDL] Assassinat ! Ennemi PV="
                                  << ennemi.getPv() << "\n";
                        break;

                    case SDLK_ESCAPE:
                        enCours = false;
                        break;
                }
            }
        }

        // 2. Mettre à jour
        joueur.update(deltaTime);  // ← appelé chaque frame ici

        // Garder le joueur dans la fenêtre horizontalement
        Vecteur2D pos = joueur.getPosition();
        if (pos.x < 0) pos.x = 0;
        if (pos.x > LARGEUR_FENETRE - TAILLE_JOUEUR)
            pos.x = LARGEUR_FENETRE - TAILLE_JOUEUR;
        joueur.setPosition(pos);

        // Si l'ennemi est mort — victoire (attendre une touche avant de fermer)
        bool partieTerminee = !ennemi.Estvivant() || !joueur.Estvivant();

        // 3. Rendu
        SDL_SetRenderDrawColor(rendu, 20, 20, 30, 255);
        SDL_RenderClear(rendu);

        // Sol
        dessinerRect(rendu, 0, SOL_Y, LARGEUR_FENETRE, HAUTEUR_FENETRE - SOL_Y, 60, 60, 60);

        // Joueur
        dessinerRect(rendu,
            (int)joueur.getPosition().x,
            (int)joueur.getPosition().y,
            TAILLE_JOUEUR, TAILLE_JOUEUR,
            50, 100, 220);

        // Ennemi
        if (ennemi.Estvivant()) {
            dessinerRect(rendu,
                (int)ennemi.getPosition().x,
                (int)ennemi.getPosition().y,
                TAILLE_ENNEMI, TAILLE_ENNEMI,
                200, 50, 50);
        }

        // Barres de vie
        dessinerBarreVie(rendu,
            (int)joueur.getPosition().x,
            (int)joueur.getPosition().y - 16,
            joueur.getPv(), joueur.getPvMax());

        if (ennemi.Estvivant()) {
            dessinerBarreVie(rendu,
                (int)ennemi.getPosition().x,
                (int)ennemi.getPosition().y - 16,
                ennemi.getPv(), ennemi.getPvMax());
        }

        // Textes
        if (police && policeGrande) {

            dessinerTexte(rendu, policeGrande,
                "Les Gardiens de la Nuit", 400, 20, 220, 200, 100);

            dessinerTexte(rendu, police,
                "JOUEUR",
                (int)joueur.getPosition().x,
                (int)joueur.getPosition().y + 52,
                150, 180, 255);

            if (ennemi.Estvivant()) {
                dessinerTexte(rendu, police,
                    "ENNEMI",
                    (int)ennemi.getPosition().x,
                    (int)ennemi.getPosition().y + 52,
                    255, 150, 150);
            }

            dessinerTexte(rendu, police,
                "PV: " + std::to_string(joueur.getPv()) + "/" + std::to_string(joueur.getPvMax()),
                20, 20, 255, 255, 255);

            dessinerTexte(rendu, police,
                "PV ennemi: " + std::to_string(ennemi.getPv()) + "/" + std::to_string(ennemi.getPvMax()),
                20, 50, 255, 180, 180);

            dessinerTexte(rendu, police,
                "← → : deplacer   ESPACE : attaquer   A : assassiner   ESC : quitter   UP : sauter",
                200, HAUTEUR_FENETRE - 40, 180, 180, 180);

            float dist = joueur.distance(ennemi);
            dessinerTexte(rendu, police,
                "Distance ennemi: " + std::to_string((int)dist),
                20, 80, 200, 200, 100);

            // Message victoire / game over
            if (!ennemi.Estvivant()) {
                dessinerTexte(rendu, policeGrande,
                    "VICTOIRE !", 520, 300, 50, 255, 50);
                dessinerTexte(rendu, police,
                    "Appuyez sur ENTREE ou ESC pour quitter", 380, 360, 200, 200, 200);
            }
            if (!joueur.Estvivant()) {
                dessinerTexte(rendu, policeGrande,
                    "GAME OVER", 500, 300, 255, 50, 50);
                dessinerTexte(rendu, police,
                    "Appuyez sur ENTREE ou ESC pour quitter", 380, 360, 200, 200, 200);
            }
        }

        // Quitter seulement si partie terminée ET touche pressée
        if (partieTerminee) {
            SDL_RenderPresent(rendu);
            SDL_Event waitEvent;
            bool attente = true;
            while (attente) {
                while (SDL_PollEvent(&waitEvent)) {
                    if (waitEvent.type == SDL_QUIT) { attente = false; enCours = false; }
                    if (waitEvent.type == SDL_KEYDOWN &&
                        (waitEvent.key.keysym.sym == SDLK_RETURN ||
                         waitEvent.key.keysym.sym == SDLK_ESCAPE)) {
                        attente = false; enCours = false;
                    }
                }
                SDL_Delay(16);
            }
            continue;
        }

        SDL_RenderPresent(rendu);
        SDL_Delay(16);
    }

    // ── Nettoyage ─────────────────────────────
    std::cout << "Fin — PV joueur=" << joueur.getPv()
              << " PV ennemi=" << ennemi.getPv() << "\n";

    if (police)       TTF_CloseFont(police);
    if (policeGrande) TTF_CloseFont(policeGrande);
    SDL_DestroyRenderer(rendu);
    SDL_DestroyWindow(fenetre);
    TTF_Quit();
    SDL_Quit();

    return 0;
}