#include "Renderer2D.h"
#include <iostream>
// Constructeur — reçoit le renderer SDL déjà créé par Jeu
// on initialise les polices à nullptr (pas encore chargées)
Renderer2D::Renderer2D(SDL_Renderer* rendu)
    : rendu(rendu), police(nullptr), policeGrande(nullptr) {}

// Destructeur — ferme les polices pour éviter les fuites mémoire
Renderer2D::~Renderer2D() {
    if (police)       TTF_CloseFont(police);
    if (policeGrande) TTF_CloseFont(policeGrande);
}

bool Renderer2D::chargerPolices() {
    police = TTF_OpenFont(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        16);
    policeGrande = TTF_OpenFont(
        "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf",
        28);

    if (!police || !policeGrande) {
        std::cerr << "[Renderer2D] Police erreur : "
                  << TTF_GetError() << "\n";
        return false;
    }
    return true;
}

void Renderer2D::dessinerRect(int x, int y, int w, int h,
                               Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(rendu, r, g, b, 255);
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderFillRect(rendu, &rect);
}


void Renderer2D::dessinerTexte(const std::string& texte,
                                int x, int y,
                                Uint8 r, Uint8 g, Uint8 b) {
    if (!police) return;

    SDL_Color couleur = { r, g, b, 255 };

    // Étape 1 — créer une image du texte en RAM
    SDL_Surface* surf = TTF_RenderUTF8_Solid(
        police, texte.c_str(), couleur);
    if (!surf) return;

    // Étape 2 — envoyer l'image sur le GPU
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rendu, surf);

    // Étape 3 — afficher à la position (x,y)
    SDL_Rect dst = { x, y, surf->w, surf->h };
    SDL_RenderCopy(rendu, tex, nullptr, &dst);

    // Étape 4 — libérer la mémoire
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}


void Renderer2D::dessinerBarreVie(int x, int y,
                                   int pv, int pvMax) {
    int largeurMax  = 60;
    int largeurActu = (pvMax > 0) ? (pv * largeurMax / pvMax) : 0;

    dessinerRect(x, y, largeurMax,  8, 60, 60, 60);  // fond gris
    dessinerRect(x, y, largeurActu, 8, 50, 200, 50); // barre verte

    // contour blanc
    SDL_SetRenderDrawColor(rendu, 180, 180, 180, 255);
    SDL_Rect c = { x, y, largeurMax, 8 };
    SDL_RenderDrawRect(rendu, &c);
}


void Renderer2D::dessinerTilemap(const Tilemap& map,
                                  int tailleTuile) {
    for (int lig = 0; lig < map.getHauteur(); lig++) {
        for (int col = 0; col < map.getLargeur(); col++) {
            int val = map.getTuile(col, lig);
            int x   = col * tailleTuile;
            int y   = lig * tailleTuile;

            if (val == 1) {
                // Sol — gris foncé
                dessinerRect(x, y, tailleTuile, tailleTuile,
                             80, 80, 90);
                // Bordure claire en haut
                dessinerRect(x, y, tailleTuile, 3,
                             120, 120, 130);

            } else if (val == 2) {
                // Plateforme — marron
                dessinerRect(x, y, tailleTuile, tailleTuile,
                             120, 80, 40);
                // Bordure claire en haut
                dessinerRect(x, y, tailleTuile, 3,
                             180, 130, 70);
            }
            // val == 0 → vide, on ne dessine rien
        }
    }
}
// <<<<<<< HEAD



// void Renderer2D::dessinerPersonnage(const Personnage& p, int taille) {
//     int x = (int)p.getPosition().x;
//     int y = (int)p.getPosition().y;

//     dessinerRect(x, y, taille, taille, 50, 100, 220); // bleu
//     dessinerBarreVie(x, y - 12, p.getPv(), p.getPvMax());
//     dessinerTexte("JOUEUR", x, y + taille + 2, 150, 180, 255);
// }
// =======
// >>>>>>> 36b4a70c77116f74b5a9fe5615b89b77e45067ad


void Renderer2D::dessinerEnnemi(const Ennemi& e,
                                 int taille) {
    if (!e.Estvivant()) return; // ne dessine pas si mort

    int x = (int)e.getPosition().x;
    int y = (int)e.getPosition().y;

    dessinerRect(x, y, taille, taille, 200, 50, 50); // rouge
    dessinerBarreVie(x, y - 12, e.getPv(), e.getPvMax());
    dessinerTexte("ENNEMI", x, y + taille + 2, 255, 150, 150);
}

void Renderer2D::dessinerHUD(const Personnage& joueur,
                               const Ennemi& ennemi) {
    dessinerTexte(
        "PV: " + std::to_string(joueur.getPv())
        + "/" + std::to_string(joueur.getPvMax()),
        10, 10, 255, 255, 255);

    dessinerTexte(
        "PV ennemi: " + std::to_string(ennemi.getPv())
        + "/" + std::to_string(ennemi.getPvMax()),
        10, 32, 255, 160, 160);

    dessinerTexte(
        "Distance: "
        + std::to_string((int)joueur.distance(ennemi)),
        10, 54, 200, 200, 100);
}

void Renderer2D::dessinerControles() {
    dessinerTexte(
        "← → : deplacer   HAUT : sauter   "
        "A : attaquer   S : assassiner   ESC : quitter",
        10, 692, 160, 160, 160);
}

void Renderer2D::dessinerVictoire() {
    if (!policeGrande) return;
    SDL_Color c = { 50, 255, 50, 255 };
    SDL_Surface* surf = TTF_RenderUTF8_Solid(
        policeGrande, "VICTOIRE !", c);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rendu, surf);
    SDL_Rect dst = { 560, 300, surf->w, surf->h };
    SDL_RenderCopy(rendu, tex, nullptr, &dst);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}

void Renderer2D::dessinerGameOver() {
    if (!policeGrande) return;
    SDL_Color c = { 255, 50, 50, 255 };
    SDL_Surface* surf = TTF_RenderUTF8_Solid(
        policeGrande, "GAME OVER", c);
    if (!surf) return;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rendu, surf);
    SDL_Rect dst = { 540, 300, surf->w, surf->h };
    SDL_RenderCopy(rendu, tex, nullptr, &dst);
    SDL_DestroyTexture(tex);
    SDL_FreeSurface(surf);
}


void Renderer2D::effacer() {
    // Fond bleu très foncé (ciel de nuit)
    SDL_SetRenderDrawColor(rendu, 15, 15, 25, 255);
    SDL_RenderClear(rendu);
}

void Renderer2D::afficher() {
    SDL_RenderPresent(rendu);
}

void Renderer2D::dessinerPersonnage(const Personnage& p, int taille) {
    int x = (int)p.getPosition().x;
    int y = (int)p.getPosition().y;

    dessinerRect(x, y, taille, taille, 50, 100, 220); // bleu
    dessinerBarreVie(x, y - 12, p.getPv(), p.getPvMax());
    dessinerTexte("JOUEUR", x, y + taille + 2, 150, 180, 255);
}