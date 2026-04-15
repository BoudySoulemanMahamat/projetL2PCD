#include "Jeu.h"
#include <iostream>


bool Jeu::init() {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "[Jeu] SDL_Init erreur : "
                  << SDL_GetError() << "\n";
        return false;
    }

    if (TTF_Init() != 0) {
        std::cerr << "[Jeu] TTF_Init erreur : "
                  << TTF_GetError() << "\n";
        SDL_Quit();
        return false;
    }

    fenetre = SDL_CreateWindow(
        "Les Gardiens de la Nuit",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_SHOWN);

    if (!fenetre) {
        std::cerr << "[Jeu] Fenetre erreur : "
                  << SDL_GetError() << "\n";
        TTF_Quit(); SDL_Quit();
        return false;
    }

    rendu = SDL_CreateRenderer(fenetre, -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC);

    if (!rendu) {
        std::cerr << "[Jeu] Renderer erreur : "
                  << SDL_GetError() << "\n";
        SDL_DestroyWindow(fenetre);
        TTF_Quit(); SDL_Quit();
        return false;
    }

    renderer = new Renderer2D(rendu);
    renderer->chargerPolices();

    niveau.charger("data/niveau1_terrain.csv",
                   "data/niveau1_objets.csv");

    std::cout << "[Jeu] init() OK\n";
    enCours = true;
    return true;
}

void Jeu::gererEvenement() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        if (event.type == SDL_QUIT) {
            enCours = false;
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {

                case SDLK_ESCAPE:
                    enCours = false;
                    break;

                case SDLK_LEFT:
                    niveau.getPersonnage()->deplacer(-5, 0);
                    break;

                case SDLK_RIGHT:
                    niveau.getPersonnage()->deplacer(5, 0);
                    break;

                case SDLK_UP:
                case SDLK_SPACE:
                    niveau.getPersonnage()->sauter();
                    break;

                case SDLK_a:
                    for (auto& ennemi : niveau.getEnnemis()) {
                        if (ennemi->Estvivant()) {
                            niveau.getPersonnage()->attaquer(*ennemi);
                            break;
                        }
                    }
                    break;

                case SDLK_s:
                    for (auto& ennemi : niveau.getEnnemis()) {
                        if (ennemi->Estvivant()) {
                            niveau.getPersonnage()->assassiner(*ennemi);
                            break;
                        }
                    }
                    break;
            }
        }
    }
}

void Jeu::mettreAJour() {
    niveau.update();

    // Sécurité — vérifier que le personnage existe
    Personnage* p = niveau.getPersonnage();
    if (p == nullptr) return;

    // Collision sol — convertir pixels en cases
    Tilemap& terrain = niveau.getTerrainMap();
    int col = (int)p->getPosition().x / 32;
    int lig = ((int)p->getPosition().y + 48) / 32; // +48 = bas du personnage
    if (terrain.estSolide(col, lig)) {
        float yBloque = (float)(lig * 32 - 48);
        p->setPosition(Vecteur2D(p->getPosition().x, yBloque));
    }

    // Vérifier fin de partie — joueur mort
    if (!p->Estvivant()) {
        enCours = false;
        return;
    }

    // Vérifier fin de partie — tous ennemis morts
    bool tousMorts = true;
    for (auto& ennemi : niveau.getEnnemis()) {
        if (ennemi->Estvivant()) {
            tousMorts = false;
            break;
        }
    }
    if (tousMorts) enCours = false;
}

void Jeu::render() {
    if (niveau.getPersonnage() == nullptr) return;

    renderer->effacer();

    renderer->dessinerTilemap(niveau.getTerrainMap(), 32);

    renderer->dessinerPersonnage(
        *niveau.getPersonnage(), 32);
    // on dessine les ennemis avant le personnage pour que le personnage soit au dessus des ennemis
    // for (auto& ennemi : niveau.getEnnemis()) {
    //     renderer->dessinerEnnemi(*ennemi, 32);
    // }

    if (!niveau.getEnnemis().empty()) {
        renderer->dessinerHUD(
            *niveau.getPersonnage(),
            *niveau.getEnnemis().front());
    }

    renderer->dessinerControles();
    renderer->afficher();
}