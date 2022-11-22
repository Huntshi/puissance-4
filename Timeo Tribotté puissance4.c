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
#include <string.h>


#define NBLIG 6   // constante des lignes de la grille
#define NBCOL 7  // constante des colonnes de la grille


const char PION_A = 'X';
const char PION_B = 'O';
const char VIDE = ' ';
const char INCONNU = ' ';
const int COLONNE_DEBUT = NBCOL/2;   // postionnement au milieu de la grille
const char DROITE = 'd';                // touche de déplacement à droite
const char GAUCHE = 'q';                // touche de déplacement à gauche
const char ESPACE = ' ';                //touche d'insertion du pion
const int COMPTEURV = 4;

typedef char Grille[NBLIG][NBCOL]; 
/**
* \typedef grille
* \brief Type tableau de caractère NBLIG-1 et NBCOL-1
*
* Le type char Grille permet de définir la grille de jeu 
* et de pouvoir la réutilisé dans laa suite du programme 
*/ 

void initGrille(Grille g);
void afficher(Grille g, char pion, int colonne);
bool grillePleine(Grille g);
void jouer(Grille g, char pion, int *ligne, int *colonne);
int choisirColonne(Grille g, char pion, int colonne);
int trouverLigne(Grille g, int colonne);
bool estVainqueur(Grille g, int ligne, int colonne);
void finDePartie(char pion, char prenomA[15], char prenomB[15]);





/**
* \fn int main()
* \brief Programme principal.
* \return Vainqueur de la partie, (PION_A ou PION_B).
* 
* Le programme principal effectue une partie de puissance 4 à deux joueurs.
*/

int main()
{
    char vainqueur;
    vainqueur = INCONNU;
    int ligne,colonne;
    Grille g;
    char prenomA[15];
    char prenomB[15];

    printf("Quel est le prénom du joueur A :\n");       // les prénoms des joueurs sont demandés
    scanf("%s", prenomA);

    printf("Quel est le prénom du joueur B :\n");
    scanf("%s", prenomB);

    
    initGrille(g);              //on initialise la grille de jeu
    
    afficher(g, PION_A, COLONNE_DEBUT);         //puis on l'affiche avec le pion centré en haut de la grile

    while(( vainqueur == INCONNU ) && (grillePleine(g) == false))       //le vainqueur n'est pas encore connu et la grille de jeu n'est pas remplie
    {
        jouer(g, PION_A, &ligne, &colonne);             //appel de la procedure pour insérer un pion 
        afficher(g, PION_A, COLONNE_DEBUT);
        if(estVainqueur(g, ligne, colonne))             //appel de la procédure qui vérifie le vainqueur
        {
            vainqueur = PION_A;
        }else if (grillePleine(g) == false)
        {
            jouer(g, PION_B, &ligne, &colonne);
            afficher(g, PION_B, COLONNE_DEBUT);
            if(estVainqueur(g, ligne, colonne))
            {
                vainqueur = PION_B;
            }
        }
    }

    finDePartie(vainqueur, prenomA, prenomB);               // appel de la procedure qui affiche le résultat

    return EXIT_SUCCESS;
}

void initGrille(Grille g)           //procedure qui initialise les cases de la grille à un espace
{
    int i;
    int j;
    for(i=0; i<NBLIG; i++)
    {
        for(j=0; j<NBCOL; j++)
        {
           g[i][j] = VIDE;
        }
    }
    
}

void afficher(Grille g, char pion, int colonne)                 // procedure qui affiche la grille avec le pion centré en haut de la grille
{
    int i;
    int j;
    int k;
    system("clear");

    printf("C'est au tour du joueur : '%c'\n", pion);
    
    for(k=0; k<NBCOL; k++)                                  // boucle pour qui affiche les espaces 
    {
        if(k == colonne) {
            printf("  %c  ", pion);
        } else {
            printf("    ");
        }
    }
    printf("\n");


    printf("┌───┬───┬───┬───┬───┬───┬───┐\n");

    for(i=0; i<NBLIG; i++)
    {
        for(j=0; j<NBCOL; j++)
        {
           printf("│ %c ", g[i][j]);
        }
        printf("│\n");

        if(i == NBLIG-1)
        {
            printf("└───┴───┴───┴───┴───┴───┴───┘");
        }else
        {
            printf("├───┼───┼───┼───┼───┼───┼───┤");
        }
        printf("\n");
       
    }
}

bool grillePleine(Grille g)                             // fonction qui vérifie si la grille est remplie de pion 
{
    int i;
    int j;
    bool estPleine = true;

    i=0;
    while(estPleine && i < NBLIG)
    {
        j=0;
        while(estPleine && j < NBCOL)
        {
            if(g[i][j] == VIDE)
            {
                estPleine = false;
            }
            j++;
        }
        i++;
    } 
    return estPleine;
    
}

void jouer(Grille g, char pion, int *ligne, int *colonne)                       // procédure qui prend la colonne et la ligne pour insérer le pion
{
    *colonne = COLONNE_DEBUT;

    do
    {
        *colonne = choisirColonne(g, pion, COLONNE_DEBUT);
        *ligne = trouverLigne(g, *colonne);
    } while (*ligne == -1);

    g[*ligne][*colonne] = pion;
}

int choisirColonne(Grille g, char pion, int colonne)                    //procédure qui permet de choisir la colonne en se déplacant
{ 
    char saisie;

    do
    {
        afficher(g, pion, colonne);
        if(saisie == GAUCHE)
        {
            if(colonne -1 >= 0)
            {
                colonne--;
            }else
            {
                printf("Vous ne pouvez pas aller plus loin \n");
            }
            
        }

        if(saisie == DROITE)
        {
            if(colonne +1 <= NBCOL -1)
            {
                colonne++;
            }else 
            {
                printf("Vous ne pouvez pas aller plus loin \n");
            }
            
        }

        if((saisie == ESPACE))
        {
            return colonne;
        }

        scanf("%c", &saisie);
        //while (getchar () != '\n');
    } while (saisie != ESPACE);
    return colonne;
}   
   
int trouverLigne(Grille g, int colonne)                             // procédure qui vérifie si les cases sont déja prises ou pas 
{
    int i;
    for(i=NBLIG; i>=0; i--)
    {
        if(g[i][colonne] == VIDE)
        {
            return i;
        }
    }
    return -1;
}

bool estVainqueur(Grille g, int ligne, int colonne)                         // fonction qui retourne le vainqueur en fonction des alignements des pions
{
    int i;
    int j;
    int comph;
    int compdd;
    int compdg;
    compdg = 1;
    compdd = 1;
    comph = 1;
    i = ligne;
    j = colonne;
    bool victoire;
    victoire = false;

    
    if((g[i][j]) == (g[i][j+1]) && (g[i][j]) == (g[i][j+2]) && (g[i][j]) == (g[i][j+3]))
    {
        victoire = true;
    }

    if((g[i][j]) == (g[i][j-1]) && (g[i][j]) == (g[i][j-2]) && (g[i][j]) == (g[i][j-3]))
    {
        victoire = true;
    }

     
    if((g[i][j]) == (g[i][j+1]) && (g[i][j]) == (g[i][j+2]) && (g[i][j]) == (g[i][j-1]))
    {
        victoire = true;
    }

     
    if((g[i][j]) == (g[i][j+1]) && (g[i][j]) == (g[i][j-1]) && (g[i][j]) == (g[i][j-2]))
    {
        victoire = true;
    }

    if((g[i][j]) == (g[i+1][j]))
    {
        comph++;
        if((g[i][j]) == (g[i+2][j]))
        {
            comph++;
            if((g[i][j]) == (g[i+3][j]))
            {
                comph++;
            }
        }
    }

    if((g[i][j]) == (g[i-1][j]))
    {
        comph++;
        if((g[i][j]) == (g[i-2][j]))
        {
            comph++;
            if((g[i][j]) == (g[i-3][j]))
            {
                comph++;
            }
        }
    }

    if(comph == 4)
    {
        victoire = true;
    }

    if((g[i][j]) == (g[i-1][j-1]))
    {
        compdd++;
        if((g[i][j]) == (g[i-2][j-2]))
        {
            compdd++;
            if((g[i][j]) == (g[i-3][j-3]))
            {
                compdd++;
            }
        }
    }

    if((g[i][j]) == (g[i+1][j+1]))
    {
        compdd++;
        if((g[i][j]) == (g[i+2][j+2]))
        {
            compdd++;
            if((g[i][j]) == (g[i+3][j+3]))
            {
                compdd++;
            }
        }
    }

    if(compdd == COMPTEURV)
    {
        victoire = true;
    }

    if((g[i][j]) == (g[i+1][j-1]))
    {
        compdg++;
        if((g[i][j]) == (g[i+2][j-2]))
        {
            compdg++;
            if((g[i][j]) == (g[i+3][j-3]))
            {
                compdg++;
            }
        }
    }

    if((g[i][j]) == (g[i-1][j+1]))
    {
        compdg++;
        if((g[i][j]) == (g[i-2][j+2]))
        {
            compdg++;
            if((g[i][j]) == (g[i-3][j+3]))
            {
                compdg++;
            }
        }
    }

     if(compdg == COMPTEURV)
    {
        victoire = true;
    }

    return victoire;
}

void finDePartie(char pion, char prenomA[15], char prenomB[15])                         //procedure qui affiche le résultat de la partie 
{

    if(pion == INCONNU)
    {
        printf("Il y a une égalité \n" );
    }else if(pion == PION_A)
    {
        printf("Le vainqueur est %s\n", prenomA);
    }else if(pion == PION_B)
    {
        printf("Le vainqueur est %s\n", prenomB);
    }else
    {
        printf("Erreur de saisie \n");
    }
    
} 

