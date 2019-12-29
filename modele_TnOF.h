#ifndef MODELE_TNOF_H_INCLUDED
#define MODELE_TNOF_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#define b 5// Le nombre d’articles existants dans le bloc
#define NIL 0//Adresse null
/*************************DECLARATION DES STRUCTURES*****************************/
/***************** structure de l'entete index ******************/
typedef struct
{
    int nb_bloc;//Le nombre de blocs alloués
    int nb_elem;//Le nombre d’éléments existants
    char nom_i[FILENAME_MAX];//nom du fichier index
}S_i_entete;
/***************** structure des elements index *************************/
typedef struct
{
    int cle;//La clé de l’étudiant
    int adr_bloc;//L’adresse du bloc dans le fichier de données ou se trouve l’article
    int pos_bloc;//La position dans le bloc
}S_element_i;
/********************* structure des blocs index ************************/
typedef struct
{
    int nelem;//Le nombre d’éléments existants dans le bloc
    S_element_i t_i[b];//Tableau d'elements
}S_i_bloc;
/*************** structure de fichier TnOF *****************************/
typedef struct
{
    FILE *fi;//Le fichier
    S_i_entete entete_i;//L'entete du fichier
}TnOF;
/************************* Table d'index ******************************/
typedef struct S_Table
{
    S_element_i elem;//enregistrement d'elements
    struct S_Table *suiv;//pointe l'element suivant de la table d'index
};
/********************** ENTETE DES MODULES *****************************/
void Ouvrir_i (TnOF *fichier,char nomfich[20],char mode[]);//ouvre le fichier index
void fermer_i (TnOF *fichier);//ferme le fichier index
void liredir_i(TnOF *fichier,int i,S_i_bloc *buf);//lecture directe du contenu de fichier du i dans le buf
void ecriredir_i(TnOF *fichier,int i,S_i_bloc *buf);//ecriture directe du contenu de buf dans le fichier dans le bloc numero i
void allouerbloc_i(TnOF *fich,S_i_bloc *buf);//alloue un nouveau bloc dans le fichier index
int entete_i(TnOF *fichier,int entier );//retourner la caracteristique de numero "entier" dans val
void aff_entete_i(TnOF *fichier,int entier,int val);//affecter à la caracteristique num entier la valeur val
void alloue_tab_i(struct S_Table **tete_table);//alloue dynamiquement les enregistrements de la table d'index
#endif // MODELE_TNOF_H_INCLUDED
