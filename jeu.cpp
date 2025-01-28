#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

const int largeur = 25;
const int hauteur = 25;

// Caractères pour les cellules vivantes, mortes et les cases vides
const char cellule_Vivante = '#';
const char cellule_Morte = '.';
const char cellule_Vide = ' ';

// Tableau 2D pour stocker l'état des cellules
int grille[largeur][hauteur];
int nouvelle_grille[largeur][hauteur];

// Fonction pour initialiser la grille avec des cellules aléatoires
void initialiser_grille() 
{
    for (int i = 0; i < largeur; i++) 
    {
        for (int j = 0; j < hauteur; j++) 
        {
            grille[i][j] = rand() % 3; // 0, 1 ou 2
        }
    }
}

// Fonction pour compter les voisins vivants d'une cellule
int compter_voisins(int x, int y) 
{
    int voisins = 0;
    for (int i = -1; i <= 1; i++) 
    {
        for (int j = -1; j <= 1; j++) 
        {
            if (i == 0 && j == 0) continue;
            int xvoisin = (x + i + largeur) % largeur; // Grille torique
            int yvoisin = (y + j + hauteur) % hauteur;
            if (grille[xvoisin][yvoisin] == 1) voisins++;
        }
    }
    return voisins;
}

// Fonction pour appliquer les règles du jeu de la vie
void appliquer_regles() 
{
    for (int i = 0; i < largeur; i++) 
    {
        for (int j = 0; j < hauteur; j++) 
        {
            int voisins = compter_voisins(i, j);
            if (grille[i][j] == 1) 
            {
                nouvelle_grille[i][j] = (voisins == 2 || voisins == 3) ? 1 : 0;
            } else {
                nouvelle_grille[i][j] = (voisins == 3) ? 1 : 0;
            }
        }
    }

    // Mettre à jour la grille actuelle avec la nouvelle grille
    for (int i = 0; i < largeur; i++) 
    {
        for (int j = 0; j < hauteur; j++) 
        {
            grille[i][j] = nouvelle_grille[i][j];
        }
    }
}

// Fonction pour afficher la grille
void afficher_grille() 
{
    for (int j = 0; j < largeur; j++) 
    {
        for (int i = 0; i < hauteur; i++) 
        {
            if (i != 0) {
                if (grille[j][i] == 1) 
                {
                    std::cout << "#|";
                } else if (grille[j][i] == 2) 
                {
                    std::cout << " |";
                } else {
                    std::cout << ".|";
                }
            } else {
                if (grille[j][i] == 1) 
                {
                    std::cout << "|#|";
                } else if (grille[j][i] == 2) 
                {
                    std::cout << "| |";
                } else {
                    std::cout << "|.|";
                }
            }
        }
        std::cout << std::endl;
    }
}

// Fonction pour ajouter des cellules
void ajout_cellules() 
{
    char continuer = 'o';
    int i, j;
    while (continuer == 'o' || continuer == 'O') 
    {
        std::cout << "Sélectionnez une colonne (0 à " << largeur - 1 << "): ";
        std::cin >> j;
        std::cout << "Sélectionnez une rangée (0 à " << hauteur - 1 << "): ";
        std::cin >> i;
        if (i >= 0 && i < largeur && j >= 0 && j < hauteur && grille[i][j] == 2) 
        {
            grille[i][j] = 1;
        } else {
            std::cout << "Case occupée ou invalide. Essayez encore.\n";
        }
        std::cout << "Voulez-vous ajouter une autre cellule ? (o/n) : ";
        std::cin >> continuer;
    }
}

// Fonction pour afficher les statistiques des cellules
void afficher_statistiques() 
{
    int vivantes = 0, mortes = 0, vides = 0;
    for (int i = 0; i < largeur; i++) 
    {
        for (int j = 0; j < hauteur; j++) 
        {
            if (grille[i][j] == 1) 
            {
                vivantes++;
            } else if (grille[i][j] == 0) 
            {
                mortes++;
            } else {
                vides++;
            }
        }
    }
    std::cout << "Cellules vivantes: " << vivantes << std::endl;
    std::cout << "Cellules mortes: " << mortes << std::endl;
    std::cout << "Cellules vides: " << vides << std::endl;
}

// Fonction pour vérifier si le jeu est terminé
bool est_jeu_termine() 
{
    for (int i = 0; i < largeur; i++) 
    {
        for (int j = 0; j < hauteur; j++) 
        {
            if (grille[i][j] == 1) 
            {
                return false;
            }
        }
    }
    return true;
}

// Fonction pour définir la vitesse d'exécution (pause entre les cycles)
void definir_vitesse() 
{
    int vitesse;
    std::cout << "Choisissez la vitesse d'exécution (en millisecondes, ex: 500): ";
    std::cin >> vitesse;
    usleep(vitesse * 1000); // Convertir millisecondes en microsecondes
}

// Fonction pour gérer le jeu
void lancer_jeu() 
{
    initialiser_grille();
    while (true) 
    {
        afficher_grille();
        ajout_cellules();
        appliquer_regles();
        afficher_statistiques();
        if (est_jeu_termine()) 
        {
            std::cout << "Le jeu est terminé : il n'y a plus de cellules vivantes." << std::endl;
            break;
        }
        definir_vitesse(); // Pause entre les générations
    }
}

// Fonction principale
int main() 
{
    srand(time(0));
    while (true) 
    {
        lancer_jeu();
    }
    return 0;
}
