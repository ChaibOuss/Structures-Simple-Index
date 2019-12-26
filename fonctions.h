#ifndef FONCTIONS_H_INCLUDED
#define FONCTIONS_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "modele_LnOF.h"
#include "modele_TnOF.h"
#define b 5// Le nombre d’articles existants dans le bloc
#define NIL 0//Adresse null


/********************** ENTETE DES MODULES *****************************/
void inser(LnOF *fich,int cle,char nom [20]);//insertion d’un article non existant
void decal(LnOF *fich,int adr,int pos);//Decale les valeurs d'un tableau apartir de pos
void supprim(LnOF *fich,int cle);//Supprime l'article de matricule cle si il existe
void charg_fich (LnOF *fich,S_bloc *buf);//Le chargement du fichier de données de façon aleatoire
void recherche(LnOF *fich,int cle,int *adr,int *pos,int *lect,int *trouv);//La recherche d’une clé donnée dans le fichier
void reorganis(LnOF *fich);//elimine tous les articles supprimes en creant un nouveau fichier
void affichage(LnOF *fich);//L’affichage du contenu de chaque bloc du fichier de données ainsi que l’affichage de l’entête du fichier

/****************************** PARTIE 2 INDEX ***************************/

void charge_i(TnOF *fich_i,struct S_Table *tete_table);//Le chargement du fichier index en memoire gentrale
void sauvegarde_i (TnOF *fich_i,struct S_Table *tete_table);//sauvegarder la table d'index dans fichier index
void charg_initial_i (LnOF *fich,TnOF *fich_i,S_bloc *buf,struct S_Table **tete_table);//Le chargement du fichier de données avec index de façon aleatoire
void recherche_i(LnOF *fich,int cle,struct S_Table *tete_table,int *trouv);//La recherche d’une clé donnée dans le fichier avec index
void inser_i(LnOF *fich,TnOF *fich_i,struct S_Table **tete_table,int cle,char nom[20]);//insertion d’un article non existant avec index
void affich_tab(struct S_Table *tete_table);//affiche la table d'index



#endif // FONCTIONS_H_INCLUDED
