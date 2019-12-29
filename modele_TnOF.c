#include "modele_TnOF.h"
/*********************** IMPLEMENTATION DU MODELE *****************************/
/************************** OUVERTURE_i *************************************/
void Ouvrir_i (TnOF *fichier,char nomfich[20],char mode[])//ouvre le fichier index
{ char n[] = "n";//mode n pour nouveau fichier
  char a[] = "a";//mode a pour fichier deja existant
    if (!stricmp ( mode, n ))//le fichier n'existe pas
    {
        fichier->fi = fopen(nomfich,"wb+");//ouvrir un nouveau fichier index
        strcpy(fichier->entete_i.nom_i,nomfich);//enregistre le nom du fichier index
        fichier->entete_i.nb_bloc= NIL;//initialiser le champs 1  de l'entete à 0
        fichier->entete_i.nb_elem= NIL;//initialiser le champs 2 de l'entete à 0
        fwrite(&(fichier->entete_i),sizeof(S_i_entete),1,fichier->fi);//enregistre l'entete dans le fichier
    }
    else
    {
        if (!stricmp ( mode, a ))//le mode est ancien c'est a dire le fichier existe
        {

          fichier->fi=fopen(nomfich,"rb+");//ouvrir le fichier index en mode lecture binaire
          if (fichier->fi==NULL)//le fichier n'existe pas
            printf("\n\t\t<<Le fichier n'existe pas...>>");//si erreur d'ouverture
          else //recuperer le contenu de l'entete dans la variable entete
         {
             strcpy(fichier->entete_i.nom_i,nomfich);//enregistre le nom du fichier index
             fread(&(fichier->entete_i),sizeof(S_i_entete),1,fichier->fi);//lire l'entete
         }
        }
        else// ni "a" ni "n"
            printf("le mode est errone.");
    }
}
/******************************** FERMITURE_i **********************************/
void fermer_i (TnOF *fichier)//fermer un fichier index
{
    fseek(fichier->fi, 0, SEEK_SET);
    fwrite(&(fichier->entete_i),sizeof(S_i_entete),1,fichier->fi);//on enregistre les modifications effectuées sur l'entete
    fclose(fichier->fi);//on ferme le fichier index
}
/********************************* liredir_i ****************************/
void liredir_i(TnOF *fichier,int i,S_i_bloc *buf)//lecture directe du contenu de fichier du i dans le buf
{   rewind(fichier->fi);
    fseek(fichier->fi,sizeof(S_i_entete)+(i-1)*sizeof(S_i_bloc),SEEK_SET);//se positionner à la place exacte
    fread(buf,sizeof(S_i_bloc),1,fichier->fi);//lecture
}
/******************************* ecriredir_i ***************************/
void ecriredir_i(TnOF *fichier,int i,S_i_bloc *buf)//ecriture directe du contenu de buf dans le fichier dans le bloc numero i
{   rewind(fichier->fi);
    fseek(fichier->fi,sizeof(S_i_entete)+(i-1)*sizeof(S_i_bloc),SEEK_SET);//se positionner à la place exacte
    fwrite(buf,sizeof(S_i_bloc),1,fichier->fi);//ecriture
}
/******************************* allouerbloc_i **************************/
void allouerbloc_i(TnOF *fich,S_i_bloc *buf)//alloue un nouveau bloc
{
    int i;//indice de tableau
    S_element_i elem;//sert de variable de transition pour la reinitialisation du buf
    elem.cle=0;//initialise cle a 0
    elem.pos_bloc=0;//initialise position dans bloc a 0
    elem.adr_bloc=0;//initialise adresse du bloc a 0
    buf->nelem =0;//initialisation du nombre d'element du bloc à 0
  for(i=0;i<b;i++)
  {
      buf->t_i[i]= elem;//initialiser tous les champs de l'element i du tableau à 0
  }
  ecriredir(fich,entete_i(fich,1)+1,buf);//enregistre le nouveau bloc
  aff_entete_i(fich,1,entete_i(fich,1)+1);//initialise le nombre de blocs alloues
}
/******************************* entete_i ********************************/
int entete_i(TnOF *fichier,int entier )//retourner la caracteristique de numero "entier" dans val
{
    int val;//valeur retourner en sorti
    switch(entier)
  {
      case 1:val=fichier->entete_i.nb_bloc; break;//nombre de bloc alloues
      case 2:val=fichier->entete_i.nb_elem; break;//nombre d'elements inseres
      default: printf("\n LE NUMERO N'EXISTE PAS");
  }
  return val;//retourne la valeur de la caracteristique demande
}
/*********************************** AFF_entete_i *******************************/
void aff_entete_i(TnOF *fichier,int entier,int val)//affecter à la caracteristique num entier la valeur val
{
  switch(entier)
  {
      case 1:fichier->entete_i.nb_bloc=val; break;//affecte au nombre de bloc alloues val
      case 2:fichier->entete_i.nb_elem=val; break;//affecte au nombre d'elements inseres val
      default: printf("\n\t\t<<Le numero est errone>>");
  }
}
/********************************** Allouer table d'index **************************/
void alloue_tab_i(struct S_Table **tete_table)//alloue dynamiquement les enregistrements de la table d'index
{
    struct S_Table *q, *sauv;//pointeurs vers un enregistrement de table index
    q = malloc(sizeof(struct S_Table));//allocation d'un nouvelle enregistrement
    q->suiv = NIL;//initialise son suivant a nil
    sauv = (*tete_table);//enregistrer la tete de la table
    if (sauv == NIL)//table d'index est vide
    {
        (*tete_table) = q;//initialise la tete vers l'enregistrement alloue
    }
    else//table non vide
    {
        while (sauv->suiv != NIL)//se positionne a la fin de la table d'index
        {
            sauv = sauv->suiv ;//aller a la fin de la table
        }
        sauv->suiv = q;//chaine le dernier element de la table d'index avec l'element q'on vien d'alloue
    }
}
