#ifndef _jeu_h_
#define _jeu_h_

 const int largeur = 25;
 const int hauteur = 25;
 char grille [largeur][hauteur];
 char nouvelle_grille[largeur][hauteur];
 void initialiser_grille();
 void afficher_separateur();
 void afficher_grille();
 int compter_voisins ( int x , int y);
 void appliquer_regles();
 void ajout_cellule();
 void afficher_statistiques();
 void definir_vitesse();
 #endif