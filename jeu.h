#ifndef _jeu_h_
#define _jeu_h_

 const int largeur = 10;
 const int hauteur = 10;
 int grille [largeur][hauteur];
 int nouvelle_grille[largeur][hauteur];
 void initialiser_grille();
 int compter_voisins ( int x , int y);
 void appliquer_regles();
 void appliquer_regles();
 void afficher_grille();
 void ajout_cellule();
 int compter_evolution( int grille[largeur][hauteur] ,int nouvelle_grille[largeur][hauteur]);
 #endif