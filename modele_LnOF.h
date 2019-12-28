#ifndef MODEL_LNOF_H_INCLUDED
#define MODEL_LNOF_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#define b 5// Le nombre d’articles existants dans le bloc
#define NIL 0//Adresse null
/*************************DECLARATION DES STRUCTURES*****************************/
/**************structure de l'entete***************/
typedef struct
{   int pre_bloc;//l'adresse du premier bloc
    int der_bloc;//l'adresse du dernier bloc
    int Nb_art_inser;//Le nombre d’articles insérer
    int Nb_art_supp;//Le nombre d’articles supprimer logiquement
    int pre_bloc_vide;//L’adresse du premier bloc de la liste des blocs vides
    char nom_fich [FILENAME_MAX];//Le nom du fichier
}S_entete;

/******************* structure d'article *********************/
typedef struct
{   int matricule;//la clé
    int efface;//le champs effacé
    char nom[20];//le nom de l'étudiant
}S_Article;

/******************* structure de bloc ************************/
typedef struct
{S_Article t [b];//tableau d'article
int Nb_article;//le nombre d'article dans le tableau
int suiv;//l'adresse du prochain bloc
int prec;//l'adresse du bloc precedent
}S_bloc;

/************structure de fichier LnOF**************/
typedef struct
{   FILE *f;//Le fichier
    S_entete entete;//L'entete du fichier
}LnOF;
/********************** ENTETE DES MODULES *****************************/
void Ouvrir (LnOF *fichier,char nomfich[20],char mode[]);//ouvre le fichier
void fermer (LnOF *fichier);//fermer un fichier
void liredir(LnOF *fichier,int i,S_bloc *buf);//lecture directe du contenu de fichier du i dans le buf
void ecriredir(LnOF *fichier,int i,S_bloc *buf);//ecriture directe du contenu de buf dans le fichier dans le bloc numero i
void allouerbloc(LnOF *fichier,S_bloc *buf);//initialise un buffer si liste blocs vide est vide sinon recuppere un bloc de liste vide et fait les chainement necessaire
void liber_bloc(LnOF *fichier,int adr);//chaine le bloc avec liste bloc vide et fais les chainement necessaire
int entete( LnOF *fichier,int entier );//retourner l'entier dans val
void aff_entete(LnOF *fichier,int entier,int val);//affecter à l'entete val dans la position entier


#endif // MODEL_LNOF_H_INCLUDED
