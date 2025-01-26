#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h> // Pour usleep (compatible UNIX)
#include <thread>
#include <chrono>

// Dimensions de la grille
const int largeur = 25;
const int hauteur = 25;

// Caractères pour les cellules vivantes, mortes et les cases vides
const char cellule_Vivante = '#';
const char cellule_Morte = '.';
const char cellule_Vide = ' ';

// Tableau 2D pour stocker l'état des cellules
char grille[largeur][hauteur];
char nouvelle_grille[largeur][hauteur];

// Fonction pour initialiser la grille avec des cellules aléatoires
void initialiser_grille() {
    for (int i = 0; i < largeur; i++) {
        for (int j = 0; j < hauteur; j++) {
            int rand_val = rand() % 3; // 0, 1 ou 2
            if (rand_val == 0) {
                grille[i][j] = cellule_Morte; // Cellule morte
            } else if (rand_val == 1) {
                grille[i][j] = cellule_Vivante; // Cellule vivante
            } else {
                grille[i][j] = cellule_Vide; // Cellule vide
            }
        }
    }
}

// Fonction pour afficher une ligne de séparation pour la grille
void afficher_separateur() {
    for (int i = 0; i < hauteur; i++) {
        std::cout << "--";
    }
    std::cout << "-" << std::endl;
}

// Fonction pour afficher la grille
void afficher_grille() {
    afficher_separateur();
    for (int i = 0; i < largeur; i++) {
        for (int j = 0; j < hauteur; j++) {
            std::cout << grille[i][j] << " ";
        }
        std::cout << std::endl;
    }
    afficher_separateur();
    std::cout << std::endl;
}

// Fonction pour compter les voisins vivants d'une cellule
int compter_voisins(int x, int y) {
    int voisins = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Ignorer la cellule elle-même
            int xvoisin = (x + i + largeur) % largeur; // Grille torique
            int yvoisin = (y + j + hauteur) % hauteur;
            if (grille[xvoisin][yvoisin] == cellule_Vivante) 
            {
                voisins++;
            }
        }
    }
    return voisins;
}

// Fonction pour appliquer les règles du jeu de la vie
void appliquer_regles() {
    for (int i = 0; i < largeur; i++) {
        for (int j = 0; j < hauteur; j++) {
            int voisins = compter_voisins(i, j);
            if (grille[i][j] == cellule_Vivante) {
                nouvelle_grille[i][j] = (voisins == 2 || voisins == 3) ? cellule_Vivante : cellule_Morte;
            } else if (grille[i][j] == cellule_Morte) {
                nouvelle_grille[i][j] = (voisins == 3) ? cellule_Vivante : cellule_Morte;
            } else {
                nouvelle_grille[i][j] = cellule_Vide; // Les cases vides restent vides
            }
        }
    }

    // Mettre à jour la grille actuelle avec la nouvelle grille
    for (int i = 0; i < largeur; i++) {
        for (int j = 0; j < hauteur; j++) {
            grille[i][j] = nouvelle_grille[i][j];
        }
    }
}

// Fonction pour ajouter une cellule
void ajout_cellule() {
    bool ajout = false;
    int i, j;
    while (!ajout) {
        std::cout << "Sélectionnez une colonne (0 à " << largeur - 1 << "): ";
        std::cin >> j;
        std::cout << "Sélectionnez une rangée (0 à " << hauteur - 1 << "): ";
        std::cin >> i;

        if (i >= 0 && i < largeur && j >= 0 && j < hauteur && grille[i][j] == cellule_Vide) {
            grille[i][j] = cellule_Vivante;
            ajout = true;
        } else {
            std::cout << "Case occupée ou invalide. Essayez encore.\n";
        }
    }
}

// Fonction pour afficher les statistiques des cellules
void afficher_statistiques() {
    int vivantes = 0, mortes = 0, vides = 0;
    for (int i = 0; i < largeur; i++) {
        for (int j = 0; j < hauteur; j++) {
            if (grille[i][j] == cellule_Vivante) {
                vivantes++;
            } else if (grille[i][j] == cellule_Morte) {
                mortes++;
            } else if (grille[i][j] == cellule_Vide) {
                vides++;
            }
        }
    }
    std::cout << "Cellules vivantes: " << vivantes << std::endl;
    std::cout << "Cellules mortes: " << mortes << std::endl;
    std::cout << "Cellules vides: " << vides << std::endl;
}

// Fonction pour vérifier si le jeu est terminé
bool est_jeu_termine() {
    for (int i = 0; i < largeur; i++) {
        for (int j = 0; j < hauteur; j++) {
            if (grille[i][j] == cellule_Vivante) {
                return false;
            }
        }
    }
    return true;
}

// Fonction pour définir la vitesse d'exécution (pause entre les cycles)
void definir_vitesse() {
    int vitesse;
    std::cout << "Choisissez la vitesse d'exécution (en millisecondes, ex: 500): ";
    std::cin >> vitesse;
    std::this_thread::sleep_for(std::chrono::milliseconds(vitesse));
}





// Fonction principale
int main() {
    srand(time(0)); // Initialiser le générateur de nombres aléatoires
    initialiser_grille();

    while (true) {
        afficher_grille();
        afficher_statistiques();

        if (est_jeu_termine()) {
            std::cout << "Le jeu est terminé : il n'y a plus de cellules vivantes." << std::endl;
            break;
        }

        ajout_cellule(); // Ajouter une cellule manuellement
        appliquer_regles(); // Passer à la génération suivante
        definir_vitesse(); // Pause entre les générations
    }

    return 0;
}