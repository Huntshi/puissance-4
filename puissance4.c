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
const char DROITE = 'd';                // touche de déplacement
const char GAUCHE = 'q';                // touche de déplacement 
const char ESPACE = ' ';

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
    char vainqueur;
    vainqueur = INCONNU;
    /* int ligne,colonne; */
    Grille g;

    initGrille(g);
    
    afficher(g, PION_A, COLONNE_DEBUT);

    choisirColonne(g, PION_A, COLONNE_DEBUT);

    /*
    while(( vainqueur == INCONNU ) && (!grillePleine(g)))
    {
        jouer(g, PION_A, &ligne, &colonne);
        afficher(g, PION_B, COLONNE_DEBUT);
        if(estVainqueur(g, ligne, colonne))
        {
            vainqueur = PION_A;
        }else if (!grillePleine(g))
        {
            jouer(g, PION_B, &ligne, &colonne);
            afficher(g, PION_A, COLONNE_DEBUT);
            if(estVainqueur(g, ligne, colonne))
            {
                vainqueur = PION_B;
            }
        }
    }*/

    finDePartie(vainqueur);

    return EXIT_SUCCESS;
}

void initGrille(Grille g)
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

void afficher(Grille g, char pion, int colonne)
{
    int i;
    int j;

    printf("Le numéro de la colonne est : %d\n", colonne);
    printf("C'est au tour du joueur 1 %c", pion);

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

bool grillePleine(Grille g)
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

void jouer(Grille g, char pion, int *ligne, int *colonne)
{
    
    
    do
    {   
        
        initGrille(g);
        afficher(g, pion, *colonne);
        *colonne = choisirColonne(g, pion, *colonne);
        *ligne = trouverLigne(g, *colonne);
        

    }while(*ligne != -1);
    
}

int choisirColonne(Grille g, char pion, int colonne)
{
    afficher(g, pion, colonne);
    char saisie;
    int colonneChoisi;

        printf("Choisissez une colonne : \n");
        scanf("%c", &saisie);

    do
    {   

        printf("Choisissez une colonne : \n");
        scanf("%c", &saisie);

        if((saisie == GAUCHE) && (colonneChoisi <= 7))
        {
            colonneChoisi = colonneChoisi -1;
        }else if ((saisie == DROITE) && (colonneChoisi >= 0))
        {
            colonneChoisi = colonneChoisi +1;
        }else if (saisie == ESPACE)
        {
            return colonneChoisi;
        }

        afficher(g, pion, colonne);
    
        
        
    }while((saisie != GAUCHE) || (saisie != DROITE) || (saisie == ESPACE));

    return colonneChoisi;
}

int trouverLigne(Grille g, int colonne)
{
    int i;
    i = NBLIG;
    int trouverLigne;
    trouverLigne = -1;
    
    while((i>0) && (trouverLigne == -1))
    {
        if(g[i][colonne] == VIDE)
        {
            trouverLigne = i;
        }
        i--;
    }
    return trouverLigne;
}

bool estVainqueur(Grille g, int ligne, int colonne)
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

    if(compdd == 4)
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

     if(compdg == 4)
    {
        victoire = true;
    }
}

void finDePartie(char pion)
{
    char vainqueur;

    if(vainqueur == INCONNU)
    {
        printf("Il y a une égalité " );
    }else if(vainqueur == PION_A)
    {
        printf("Le vainqueur est le joueur 1");
    }else if(vainqueur == PION_B)
    {
        printf("Le vainqueur est le joueur 2");
    }else
    {
        printf("Erreur de saisie ");
    }
    
} 

