#include <stdio.h>
#include <stdlib.h>
#include "fonctions.h"
#include "modele_TnOF.h"
#include "modele_LnOF.h"
extern int cpt;//compteur d'acces memoire pour calculer les couts
/******************************* MENU ***************************************/
void main()
{
/*************************** PARTIE DECLARATION ********************************/
 srand(time(NULL));//Modifie la «graine» utilisée par le « générateur de nombres pseudo-aléatoires » de rand. Par défaut, cette graine a la valeur 1.
int choix1,choix2,matricule,adresse,position,nb_lect,trouv,quitter1,quitter2,cout,commit_test;
commit_test = 0;
char nom[20];
LnOF *fich_donne=malloc(sizeof(LnOF));//cree le fichier de donnees de la partie 1
LnOF *fich_donne2=malloc(sizeof(LnOF));//cree le fichier de donnees de la partie index
TnOF *fich_index =malloc(sizeof(TnOF));//cree le fichier index
S_i_bloc *bloc =malloc(sizeof(S_i_bloc));//allouer un buffer pour fichier index
S_bloc * buf =malloc(sizeof(S_bloc));//allouer un buffer pour fichier de donnees
struct S_Table *tete_table = NIL;//initialiser la tete de la table d'index a NIL
    Ouvrir(fich_donne,"donnees","n");//ouvrir le fichier de donnees en mode nouveau
    Ouvrir(fich_donne2,"donnees2","n");//ouvrir le fichier de donnees en mode nouveau
    Ouvrir_i(fich_index,"index","n");//ouvrir le fichier index en mode nouveau
quitter1 = 0;//initialiser la condition de sorti du menu principal a 1
while (!quitter1)//tant que non quitte
{
    printf("\n---------------------------------- MENU PRINCIPAL ---------------------------\n");
        printf("1 - FICHIER DE DONNEES.\n");
        printf("2 - FICHIER INDEX.\n");
        printf("3 - CAMPARAISON ET COUT.\n");
        printf("4 - QUITTER.\n");
    printf("-------> ");
        scanf("%d",&choix1);//lire le choix
    printf("-----------------------------------------------------------------------------\n");
    switch(choix1)
   {
/************************************* PARTIE 1 ************************************/
    case 1 :
        system("cls");
        quitter2 = 0;
        while (!quitter2)
        {
            printf("\n---------------------------------- MANIPULATION DES FICHIERS DE DONNEES -----------------------------------\n");
                printf("1 - CHARGER LE FICHIER DE DONNEES.\n");
                printf("2 - RECHERCHER UNE CLE.\n");
                printf("3 - INSERER UN ARTICLE.\n");
                printf("4 - SUPPRIMER UN ARTICLE.\n");
                printf("5 - AFFICHER LE CONTENUE DU FICHIER DE DONNEES.\n");
                printf("6 - REORGANISER LE FICHIER.\n");
                printf("7 - MENU PRINCIPAL.\n");
            printf("-------> ");
                scanf("%d",&choix2);
            printf("-----------------------------------------------------------------------------\n");
            switch (choix2)
            {
                case 1 ://charger le fichier
                    system("cls");
                    charg_fich(fich_donne,buf);
                    break;
                case 2 ://recherche d'une cle
                    system("cls");
                    printf("\nLE MATRICULE DE L'ETUDIANT RECHERCHER : ");
                    scanf("%d",&matricule);
                    recherche(fich_donne,matricule,&adresse,&position,&nb_lect,&trouv);
                    break;
                case 3 ://insertion d'un article
                    system("cls");
                    printf("\nLE NOM DE L'ETUDIANT : ");
                    scanf("%s",&nom);
                    printf("\nLE MATRICULE DE L'ETUDIANT : ");
                    scanf("%d",&matricule);
                    inser(fich_donne,matricule,nom);
                    break;
                case 4 ://suppretion d'un article
                    system("cls");
                    printf("\nLE MATRICULE DE L'ETUDIANT A SUPPRIMER :");
                    scanf("%d",&matricule);
                    supprim(fich_donne,matricule);
                    break;
                case 5 ://affichage
                    system("cls");
                    affichage(fich_donne);
                    system("pause");
                    system("cls");
                    break;
                case 6 ://reorganisation
                    system("cls");
                    reorganis(fich_donne);
                    break;
                case 7 ://menu principale
                    quitter2 = 1;
                    system("cls");
            }
        }
        break;

/********************************* PARTIE INDEX ***************************************/
    case 2 :
        system("cls");
        quitter2 = 0;
        while (!quitter2)
        {
            printf("\n----------------------------------- MENU INDEX ------------------------------\n");
                printf("1 - CHARGER LE FICHIER INDEX EN MEMOIRE.\n");
                printf("2 - SAUVEGARDER LA TABLE INDEX DANS LE FICHIER INDEX.\n");
                printf("3 - CHARGEMENT INITIAL AVEC INDEX.\n");
                printf("4 - RECHERCHER UNE CLE AVEC INDEX.\n");
                printf("5 - INSERER UN ARTICLE AVEC INDEX.\n");
                printf("6 - AFFICHER LE FICHIER DE DONNEES RELIE A L'INDEX.\n");
                printf("7 - AFFICHER LA TABLE D'INDEX.\n");
                printf("8 - MENU PRINCIPAL.\n");
            printf("-------> ");
                scanf("%d",&choix2);
            printf("-----------------------------------------------------------------------------\n");
            switch (choix2)
            {
                case 1 ://charger le fichier index en ram
                    system("cls");
                    charge_i(fich_index,tete_table);
                    break;
                case 2 ://sauvegarder la table d'index dans le fichier index
                    system("cls");
                    sauvegarde_i(fich_index,tete_table);
                    break;
                case 3 ://chargement initial avec index
                    system("cls");
                    charg_initial_i(fich_donne2,fich_index,buf,&tete_table);
                    break;
                case 4 ://recherche avec index
                    system("cls");
                    printf("\nLE MATRICULE DE L'ETUDIANT : ");
                    scanf("%d",&matricule);
                    recherche_i(fich_donne2,matricule,tete_table,&trouv);
                    break;
                case 5 ://insertion avec index
                    system("cls");
                    printf("\nLE NOM DE L'ETUDIANT : ");
                    scanf("%s",&nom);
                    printf("\nLE MATRICULE DE L'ETUDIANT : ");
                    scanf("%d",&matricule);
                    inser_i(fich_donne2,fich_index,&tete_table,matricule,nom);
                    break;
                case 6 ://affichage du fichier de donnees
                    system("cls");
                    affichage(fich_donne2);
                    system("pause");
                    system("cls");
                    break;
                case 7 ://affichage de la table d'index
                    system("cls");
                    affich_tab(tete_table);
                    system("pause");
                    system("cls");
                    break;
                case 8 ://retourner au menu principal
                    quitter2 = 1;
                    system("cls");
            }
        }
        break;
/****************************** PARTIE COMPARAISON ***********************************/
    case 3 :
        system("cls");
         quitter2 = 0;
        while (!quitter2)
        {
            printf("\n----------------------------------- MENU DES COUTS ------------------------------\n");
                printf("(IMPORTANT : LES FICHIERS DE COMPARAISON SONT CEUX DE LA DEXIEME PARTIE DONC TOUTE MODIFICATION SERA ENREGISTRE)\n");
                printf("1 - LA COMPARAISON DES RECHERCHES.\n");
                printf("2 - LA COMPARAISON DES INSERTIONS.\n");
                printf("3 - LA SUPPRESSION (NON INDEX).\n");
                printf("4 - MENU PRINCIPAL.\n");
            printf("-------> ");
                scanf("%d",&choix2);
            printf("-----------------------------------------------------------------------------\n");
            switch (choix2)
            {
                case 1 ://le cout des recherches (comparaison)
                    cpt = 0;
                    printf("\nENTREZ UN MATRICULE : ");
                    scanf("%d",&matricule);
                    recherche(fich_donne2,matricule,&adresse,&position,&nb_lect,&trouv);
                    cout = cpt;
                    cpt = 0;
                    recherche_i(fich_index,matricule,tete_table,&trouv);
                    system("cls");
                    printf("\nLE COUT SANS INDEX : %d",cout);
                    printf("\nLE COUT AVEC INDEX : %d",cpt);
                    break;
                case 2 ://le cout des insertions
                    cpt = 0;
                    inser(fich_donne2,16,"alger");
                    cout = cpt;
                    cpt = 0;
                    inser_i(fich_donne2,fich_index,&tete_table,02,"chlef");
                    system("cls");
                    printf("\nLE COUT SANS INDEX : %d",cout);
                    printf("\nLE COUT AVEC INDEX : %d",cpt);
                    break;
                case 3 ://le cout de la suppretion
                    system("cls");
                    cpt = 0;
                    printf("\nENTREZ LE MATRICULE DE L'ETUDIANT A SUPPRIMER  :");
                    scanf("%d",&matricule);
                    supprim(fich_donne2,matricule);
                    system("cls");
                    printf("\nLE COUT SANS INDEX : %d",cpt);
                    break;
                case 4 :
                    quitter2 = 1;
                    system("cls");
            }
        }
        break;
    case 4 ://sortir du menu principal
        quitter1 = 1;
   }
}
    fermer_i(fich_index);//fermer le fichier index
    fermer(fich_donne);//fermer le fichier de donnees de la premiere partie
    fermer(fich_donne2);//fermer le fichier de donnees de la partie index
    return 0;
}
