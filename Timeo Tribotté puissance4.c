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

#define NBLIG 6
/**
*   /def NBLIG
*   /brief constante du nombre de ligne de la grille de jeu
*/

#define NBCOL 7  
/**
*   /def NBCOL
*   /brief constante du nombre de colonne de la grille de jeu
*/


const char PION_A = 'X';
/**
*   /def PION_A
*   /brief constante qui represente le caractère 'X', utilisé comme pion
*/

const char PION_B = 'O';
/**
*   /def PION_B
*   /brief constante qui represente le caractère 'O', utilisé comme pion
*/

const char VIDE = ' ';
/**
*   /def VIDE
*   /brief constante qui represente le caractère espace qui sera ajouté à chaque case de la grille de jeu
*/

const char INCONNU = ' ';
/**
*   /def INCONNU
*   /brief constante qui assigne un vainqueur qui n'est pas un dès deux joueurs
*/

const int COLONNE_DEBUT = NBCOL/2;
/**
*   /def COLONNE_DEBUT
*   /brief constante qui represente l'emplacement du pion au debut de chaque tour, ici sur la colonne 3 au milieu
*/

const char DROITE = 'd';
/**
*   /def DROITE
*   /brief constante qui represente la touche de déplacement pour aller à droite
*/

const char GAUCHE = 'q';
/**
*   /def GAUCHE
*   /brief constante qui represente la touche de déplacement pour aller à gauche
*/

const char ESPACE = ' ';
/**
*   /def ESPACE
*   /brief constante qui represente la touche d'insertion du pion
*/

const int COMPTEURV = 4;
/**
*   /def COMPTEURV
*   /brief constante qui represente un compteur afin de vérifier si 4 pions sont alignés dans la fonction estVainqueur
*   /see cette constante est utilisé uniquement dans la fonction estVainqueur
*/

typedef char Grille[NBLIG][NBCOL]; 
/**
* \typedef grille
* \brief Type tableau de caractère NBLIG-1 et NBCOL-1
*
* Le type char Grille permet de définir la grille de jeu 
* et de pouvoir la réutilisé dans la suite du programme 
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
/**
*   /fn void initGrille(Grille g) 
*   /brief Procedure qui initialise les cases de la grille à un espace.
*   /param  grille de jeu g.
*/

void afficher(Grille g, char pion, int colonne)                 
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
/**
*   /fn void afficher(Grille g, char pion, int colonne) 
*   /brief Procedure qui affiche la grille avec le pion centré en haut de la grille.
*   /param  grille de jeu g, un pion et la colonne.
*/

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
/**
*   /fn bool grillePleine(Grille g) 
*   /brief Fonction qui vérifie si la grille est remplie de pion.
*   /param  grille de jeu g.
*   /return true si la grille est pleine et false sinon. 
*/

void jouer(Grille g, char pion, int *ligne, int *colonne)                       
{
    *colonne = COLONNE_DEBUT;

    do
    {
        *colonne = choisirColonne(g, pion, COLONNE_DEBUT);
        *ligne = trouverLigne(g, *colonne);
    } while (*ligne == -1);

    g[*ligne][*colonne] = pion;
}
/**
*   /fn void jouer(Grille g, char pion, int *ligne, int *colonne)
*   /brief Procédure qui prend en paramètre la colonne et la ligne pour insérer le pion.
*   /param  grille de jeu g, un pion, la ligne disponible et la colonne choisi.
*/

int choisirColonne(Grille g, char pion, int colonne)                    
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
/**
*   /fn int choisirColonne(Grille g, char pion, int colonne) 
*   /brief Fonction qui permet de choisir la colonne ou l'on souhaite insérer le pion en se déplacant.
*   /param  grille de jeu g, un pion, et la colonne;
*   /return la colonne choisie.
*/
   
int trouverLigne(Grille g, int colonne)
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
/**                           
*   /fn int trouverLigne(Grille g, int colonne) 
*   /brief Procédure qui vérifie si les cases de la colonne choisie sont déja prises ou pas, ligne par ligne.
*   /param  grille de jeu g, et la colonne choisie.
*   /return -1 si la ligne est pleine ou le numero de la ligne sinon.
*/

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
/**                           
*   /fn bool estVainqueur(Grille g, int ligne, int colonne) 
*   /brief Fonction qui retourne le vainqueur en fonction des alignements des pions.
*   /param  grille de jeu g, les ligne et les colonnes.
*   /return true si il y a un alignement de 4 pions et false sinon.
*/

void finDePartie(char pion, char prenomA[15], char prenomB[15])                         
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
/**
*   /fn void finDePartie(char pion, char prenomA[15], char prenomB[15]) 
*   /brief Procedure qui affiche le résultat de la partie.
*   /param  grille de jeu g, le prenom du joueur A et le prenom du joueur B.
*/

