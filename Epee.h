#ifndef ENTITE_H_
#define ENTITE_H_

#include "Vecteur2D.h"
#include "Rect.h"

class Entite {

protected:
    Vecteur2D position;
    Vecteur2D vitesse;
    Rect hitbox;
    int pv;
    int pvMax;

public:
    Entite();

    // Retourne true si pv > 0 — pas besoin de passer une Entite en parametre
     /** \brief Vérifie si l'entité est vivante
     *  \return true si l'entité est vivante, false sinon
     */
    bool Estvivant() const;
/** \brief Déplace l'entité
     *  \param x La coordonnée x du déplacement
     *  \param y La coordonnée y du déplacement
     */
    void deplacer(int x, int y);
    /** \brief Dessine l'entité à l'écran
     */
    void dessiner();// A implementer plus tard, pour dessiner l'entite a l'ecran

    /** \brief Calcule la distance entre cette entité et une autre
     *  \param autre L'autre entité
     *  \return La distance entre les deux entités
     */
    float distance(const Entite& autre) const;

    // Reduit les pv, met a 0 si on tombe en dessous
    void subirDegats(int degats);

    /** \brief Retourne les points de vie de l'entité
     *  \return Les points de vie de l'entité
     */
    int       getPv()       const { return pv; }
    /** \brief Retourne les points de vie max de l'entité
     *  \return Les points de vie max de l'entité
     */
    int       getPvMax()    const { return pvMax; }
    /** \brief Retourne la hitbox de l'entité
     *  \return La hitbox de l'entité
     */
    Rect      getHitbox()   const;
    /** \brief Retourne la position de l'entité
     *  \return La position de l'entité
     */
    Vecteur2D getPosition() const { return position; }
    /** \brief Retourne la vitesse de l'entité
     *  \return La vitesse de l'entité
     */
    Vecteur2D getVitesse()  const { return vitesse; }

    // Setters pour pouvoir modifier les attributs de l'entite, par exemple, pour les ennemis qui perdent des points de vie en infligeant des degats a distance, on peut utiliser le setter setPv pour reduire les points de vie de l'ennemi en fonction du malus de degats qu'il a, par exemple, si un ennemi inflige 5 points de degats a distance et que son malus de degats est de 2, alors on peut utiliser le setter setPv pour reduire les points de vie de l'ennemi de 2 points, ce qui rendra l'ennemi plus faible au fil du temps s'il utilise beaucoup d'attaques a distance.
    /** \brief Modifie les points de vie de l'entité
     *  \param newPv Les nouveaux points de vie de l'entité
     */
    void setPv(int newPv);
    /** \brief Modifie les points de vie max de l'entité
     *  \param newPvMax Les nouveaux points de vie max de l'entité
     */
    void setPvMax(int newPvMax);
    /** \brief Modifie la position de l'entité
     *  \param newPosition La nouvelle position de l'entité
     */
    void setPosition(Vecteur2D newPosition);
    /** \brief Modifie la vitesse de l'entité
     *  \param newVitesse La nouvelle vitesse de l'entité
     */
    void setVitesse(Vecteur2D newVitesse);
    void test_entite();
};

#endif // ENTITE_H_