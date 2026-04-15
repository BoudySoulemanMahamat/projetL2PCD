#ifndef TILEMAP_H
#define TILEMAP_H

#include <vector>
#include <string>

class Tilemap {
private:
    std::vector<std::vector<int>> map;// les donnees de  viennent de la lecture du csv, chaque entier représente un type de tuile (0 = vide, 1 = sol, 2= position par deaut du personage )
    int largeur;
    int hauteur;
// le choix dun tableau 2D & l'utilisation de vector permet
//  une gestion dynamique de la taille de la map, facilitant le chargement de différentes tailles de niveaux sans se soucier de la mémoire allouée
public:
    Tilemap() : map(), largeur(0), hauteur(0) {}

    void chargerCSV(const std::string& nomFichier); // pour charger dans map les donner du csv
    
    int getTuile(int x, int y) const;
    bool estSolide(int x, int y) const;
    int getLargeur() const;
    int getHauteur() const;
    void testRegressionMap() const; // méthode de test pour vérifier le chargement correct de la map
};

#endif