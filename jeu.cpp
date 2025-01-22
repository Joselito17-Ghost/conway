#include<iostream>
#include<ctime>
#include<cstdlib>
#include<unistd.h>
#include<windows.h>

    const int largeur = 10;
    const int hauteur = 10;
 //\033[31m" << "1 vs 1" << "\033[37m"
  
// tableau 2D pour stocker l'etat des cellules 
   int grille [largeur][hauteur];
   int nouvelle_grille[largeur][hauteur];


// fonction pour initialiser la grille
   void initialiser_grille()
   {
     for(int i = 0 ; i < largeur ; i++)
     {
        for(int j = 0 ; j < hauteur ; j++)
        {
            grille[i][j] = rand() %3;
        }
     }
   }
// fonction pour compter les voisins vivants d'une cellule
   int compter_voisins ( int x , int y)
   {
     int voisin = 0;
     for( int i = -1 ; i <=1 ; i++)
     {
      for( int j = -1 ; j <=1 ; j++)
      {
        if( i == 0 && j == 0) continue;
        int xvoisin = ( x + i + largeur) % largeur;
        int yvoisin = ( y + j + hauteur) % hauteur;
        if (grille[xvoisin][yvoisin] == 1) voisin++;
      }
     }
     return voisin;
   }
// fonction pour appliquer les regles du jeu de la vie
   void appliquer_regles()
   {
      int nouvelle_grille [largeur][hauteur];
      for (int i = 0 ; i < largeur ; i++)
      {
         for (int j = 0 ; j < hauteur ; j++)
         {
            int voisins = compter_voisins(i,j);
            if (grille[i][j] == 1)
            {
               nouvelle_grille[i][j] = (voisins == 2 || voisins == 3)? 1 : 0;
            } else {
               nouvelle_grille[i][j] = (voisins == 3)? 1 : 0;
              }  
        }
      }
   
   for (int i = 0 ; i < largeur ; i++)
    {
      for(int j = 0 ; j < hauteur ; j++)
      {
         grille[i][j] = nouvelle_grille[i][j];
      }
    }
   }
   
// fonction pour afficher la grille 
   void afficher_grille()
   {
    for (int j = 0 ; j < largeur ; j++)
    {
      for (int i = 0 ; i < hauteur ; i++)
      {
        if( i != 0)
        {
         if (grille [j][i] == 1)
         {
            std::cout <<"#|";
         }else if (grille [j][i] == 2){
            std::cout <<" |";
         }else{
            std::cout <<".|";
         }
        }
        else
        {
         if (grille [j][i] == 1)
         {
            std::cout <<"|#|";
         }else if (grille [j][i] == 2){
            std::cout <<"| |";
         }else{
            std::cout <<"|.|";
         }
        }
      }
      std::cout << std::endl;
    }  
   }
// fonction pour ajouter une cellule
void ajout_cellule()
{
   bool ajout = false;
   int i ,j;
   while(!ajout)
   {
    std::cout<<"selectioner une colonne"<< std::endl;
    std::cin >> j;
    std::cout<<"selectioner une ranger"<< std::endl;
    std::cin >> i;
    if(grille[i][j] == 2) 
    {
      grille[i][j] = 1;
      ajout = true;
    }
    else
    {
      std::cout << "case occuper" << std::endl;
    }
   }
}

// fonction pour compter l'evolution des cellules
   int compter_evolution( int grille[largeur][hauteur] ,int nouvelle_grille[largeur][hauteur])
   {
      int evolution = 0;
   for (int i = 0 ; i < largeur ; i++)
    {
      for(int j = 0 ; j < hauteur ; j++)
      {
       if (grille [j][i] != nouvelle_grille[i][j])
       {
         evolution++;
       }
      }
   }
   return evolution;
   }
   int main()
   {
      int b,evol;
      std::cin >> b;
      srand (time(0));
      initialiser_grille();
      while(true)
      {
         afficher_grille();
         ajout_cellule();
         appliquer_regles();
         evol = compter_evolution( grille , nouvelle_grille);
         
      }
      return 0;
   }