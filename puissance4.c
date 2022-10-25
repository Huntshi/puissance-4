/** 
 * @brief programme du puissance 4
 * @author Timéo Tribotté
 * @groupe 1E1
 * @version 1.0
 * @date 25/10/2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


#define NBLIG 6   // constante des lignes de la grille
#define NBCOL 7  // constante des colonnes de la grille


const char PION_A = 'X';
const char PION_B = 'O';
const char VIDE = ' ';
const char INCONNU = ' ';
const int COLONNE_DEBUT = NBCOL/2;   // postionnement au milieu de la grille

typedef char Grille = tab[NBLIG-1] [NBCOL-1]; 
/**
* \typedef grille
* \brief Type tableau de caractère NBLIG-1 et NBCOL-1
*
* Le type char Grille permet de définir la grille de jeu 
* et de pouvoir la réutilisé dans laa suite du programme 
*/ 

void initGrille(*g);
void afficher(g, char pion, int colonne);
void grillePleine(g);
void jouer(*g, char pion, int *ligne, int *colonne);
void choisirColonne(g, char pion, int colonne);
void trouverLigne(g, int colonne);
void estVainqueur(g, int ligne, int colonne);
void finDePartie(char pion);



/**
* \fn int main()
* \brief Programme principal.
* \return Vainqueur de la partie, (PION_A ou PION_B).
* 
* Le programme principal effectue une partie de puissance 4 à deux joueurs.
*/

int main()
{
    char vainqueur[15];
    int ligne,colonne;
    Grille g;

    initGrille(*g);
    vainqueur = INCONNU;
    afficher(g, PION_A, COLONNE_DEBUT);

    while(( vainqueur == INCONNU ) && (!grillePleine(g)))
    {
        jouer(*g, PION_A, *ligne, *colonne);
        afficher(g, PION_B, COLONNE_DEBUT);
        if(estVainqueur(g, ligne, colonne))
        {
            vainqueur = PION_A;
        }else if (!grillePleine(g))
        {
            jouer(*g, PION_B, *ligne *colonne);
            afficher(g, PION_A, COLONNE_DEBUT);
            if(estVainqueur(g, ligne, colonne))
            {
                vainqueur = PION_B;
            }
        }
    }
    finDePartie(vainqueur);
}