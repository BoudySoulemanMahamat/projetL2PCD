#ifndef JEU_H
#define JEU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "Renderer2D.h"
#include "Niveau.h"

class Jeu {
private:
    SDL_Window*   fenetre;
    SDL_Renderer* rendu;
    Niveau        niveau;
    Renderer2D*   renderer;
    bool          enCours;

public:
    Jeu();
    ~Jeu();

    /** @brief Initialise la fenetre SDL et charge le niveau */
    bool init();

    /** @brief Lance la boucle principale */
    void run();

private:
    /** @brief Lit les evenements clavier SDL */
    void gererEvenement();

    /** @brief Met a jour la logique du jeu */
    void mettreAJour();

    /** @brief Dessine tout a l'ecran */
    void render();
    
};

#endif