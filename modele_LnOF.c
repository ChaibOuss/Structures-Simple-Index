#include "modele_LnOF.h"
int cpt = 0;//compteur d'acces memoire pour calculer les couts
/*********************** IMPLEMENTATION DU MODELE *****************************/
/************************** OUVERTURE *************************************/

void Ouvrir (LnOF *fichier,char nomfich[20],char mode[])
{ char n[] = "n";//mode n pour nouveau fichier
  char a[] = "a";//mode a pour fichier deja existant
if (!stricmp ( mode, n ))//si le fichier n'existe pas
    {

        fichier->f = fopen(nomfich,"wb+");//ouvrir un nouveau fichier
        strcpy(fichier->entete.nom_fich,nomfich);//enregistre le nom du fichier
        fichier->entete.pre_bloc= NIL;//initialiser le champs 1  de l'entete à 0
        fichier->entete.der_bloc= NIL;//initialiser le champs 2 de l'entete à 0
        fichier->entete.Nb_art_inser=0;//initialiser le nombre d'articles inseres à 0
        fichier->entete.Nb_art_supp=0;//initialiser le nombre d'articles supprimes à 0
        fichier->entete.pre_bloc_vide= NIL;//initialiser l'adresse du premier bloc vide à 0
        fwrite(&(fichier->entete),sizeof(S_entete),1,fichier->f);//ecrire l'entete dans le fichier

    }
    else
    {
        if (!stricmp ( mode, a ))//le mode est ancien c'est a dire le fichier existe
        {

          fichier->f=fopen(nomfich,"rb+");//ouvrir le fichier en mode lecture binaire
          if (fichier->f==NULL)//le fichier n'existe pas
            printf("\n\t\t<<Le fichier n'existe pas...>>");//si erreur d'ouverture
          else //recuperer le contenu de l'entete dans la variable entete

         {

             strcpy(fichier->entete.nom_fich,nomfich);//enregistre le nom du fichier
             fread(&(fichier->entete),sizeof(S_entete),1,fichier->f);//lire l'entete

         }
        }
        else
            printf("le mode est errone.");// ni "a" ni "n"
    }

}

/******************************** FERMITURE **********************************/
void fermer (LnOF *fichier)//fermer un fichier
{
    fseek(fichier->f, 0, SEEK_SET);
    fwrite(&(fichier->entete),sizeof(S_entete),1,fichier->f);//on enregistre les modifications effectuées sur l'entete
    fclose(fichier->f);//on ferme le fichier
}
/********************************* liredir ****************************/
void liredir(LnOF *fichier,int i,S_bloc *buf)//lecture directe du contenu de fichier du i dans le buf
{   rewind(fichier->f);
    fseek(fichier->f,sizeof(S_entete)+(i-1)*sizeof(S_bloc),SEEK_SET);//se positionner à la place exacte
    fread(buf,sizeof(S_bloc),1,fichier->f);//lecture
    cpt++;
}

/******************************* ecriredir ***************************/
void ecriredir(LnOF *fichier,int i,S_bloc *buf)//ecriture directe du contenu de buf dans le fichier dans le bloc numero i
{   rewind(fichier->f);
    fseek(fichier->f,sizeof(S_entete)+(i-1)*sizeof(S_bloc),SEEK_SET);//se positionner à la place exacte
    fwrite(buf,sizeof(S_bloc),1,fichier->f);//ecriture
    cpt++;
}
/******************************* allouerbloc *************************************/
void allouerbloc(LnOF *fichier,S_bloc *buf)//recuppere un bloc de la liste de bloc vide si il existe sinon initialiser un nouveau
{
  int i,vide,der,adr;
  S_bloc buf_prec,buf_suiv;
  vide = (entete(fichier,5));//adresse du premier bloc vide
  der = entete(fichier,2);//adresse du dernier bloc de la liste
  if (vide != NIL )//il existe aumoin un bloc vide
  {
      adr=vide;//le bloc vide devien le dernier bloc de la liste
      liredir(fichier,adr,buf);//lecture du bloc vide

      if(der != NIL)//le dernier bloc de la liste existe
      {
            if((buf->suiv)!= NIL)//il existe un autre bloc vide
         {
            liredir(fichier,buf->suiv,&buf_suiv);//lecture de ce dexieme bloc vide
            buf_suiv.prec = NIL;//chainnage de son precedent avec NIL
            ecriredir(fichier,buf->suiv,&buf_suiv);//sauvgarde dans le fichier
         }
          liredir(fichier,der,&buf_prec);//lire l'ancient dernier bloc de la liste
          buf_prec.suiv = adr;//chainnage l'ancient dernier bloc avec le bloc vide recupperes
          buf->prec=der;//chainnage du bloc vide recupperes avec l'ancient dernier bloc
          ecriredir(fichier,der,&buf_prec);//enregistres dans le fichier
          aff_entete(fichier,5,buf->suiv);//reinitialisation de l'adresse du premier bloc vide
          aff_entete(fichier,2,adr);//reinitialisation de l'adresee du nouveau dernier bloc

      }
      else//la liste est vide
      {
         if((buf->suiv)!= NIL)//il existe un autre bloc vide
         {
            liredir(fichier,buf->suiv,&buf_suiv);//lecture de ce dexieme bloc vide
            buf_suiv.prec = NIL;//chainnage de son precedent avec NIL
            ecriredir(fichier,buf->suiv,&buf_suiv);//sauvgarde dans le fichier
         }
          aff_entete(fichier,1,vide);//reinitialisation de l'adresee du nouveau premier bloc
          aff_entete(fichier,2,vide);////reinitialisation de l'adresee du nouveau dernier bloc
          aff_entete(fichier,5,buf->suiv);////reinitialisation de l'adresee du premier bloc vide
      }
  }
  else//la liste des blocs vide est vide
  {
      adr =der+1;//affecter l'adresse qui suit le dernier bloc de la liste
      if(der != NIL)//le dernier bloc de la liste existe
      {
          liredir(fichier,der,&buf_prec);////lire l'ancient dernier bloc de la liste
          buf_prec.suiv = der +1;//chainnes l'adresse de son suivant avec le nouveau bloc
          buf->prec=der;////chainnes le nouveau bloc avec l'adresse de l'ancient dernier bloc
          ecriredir(fichier,der,&buf_prec);//enregistres l'ancient dernier bloc dans le fichier
          ecriredir(fichier,der+1,buf);//enregistes le nouveau bloc

      }
      else//la liste est vide
      {
          buf->prec=NIL;//chainnes le nouveau bloc avec NIL
          ecriredir(fichier,adr,buf);//enregister le nouveau bloc
          aff_entete(fichier,1,adr);//reinitialisation de l'adresee du nouveau premier bloc
      }
      aff_entete(fichier,2,der+1);//reinitialisation de l'adresee du nouveau dernier bloc
  }
  (*buf).suiv= NIL;//initialiser le champs suiv à nil
  (*buf).Nb_article=0;//initialiser le nb d'articles à 0
  for(i=0;i<b;i++)
  {
      (*buf).t[i].efface=1;//initialiser tout les champs efface de tableau à vrai
  }
  ecriredir(fichier,adr,buf);//enregistre le dernier bloc
 }
 /******************************* liberer bloc **************************************/
 void liber_bloc(LnOF *fichier,int adr)////chaine le bloc avec liste bloc vide et fais les chainement necessaire
 {
     S_bloc buf_prec,buf_suiv ,*buf;
     buf = malloc(sizeof(S_bloc));
     liredir(fichier,adr,buf);//lecture du bloc à liberer
     if ((buf->suiv) != NIL)//le bloc à liberer n'est pas le dernier bloc
     {
         liredir(fichier,buf->suiv,&buf_suiv);//lecture du bloc qui le suit
          if ((buf->prec) != NIL)//le bloc à liberer n'est pas le premier bloc
         {
             liredir(fichier,buf->prec,&buf_prec);//lecture du bloc qui est avant lui
             buf_prec.suiv = (buf->suiv);//chainnage du bloc qui le precedent avec le bloc qui est apres lui
             buf_suiv.prec = (buf->prec);//chainnage du bloc qui le suit avec le bloc qui le precedent
             ecriredir(fichier,buf->suiv,&buf_suiv);//enregistrer le bloc qui est apres lui dans le fichier
             ecriredir(fichier,buf->prec,&buf_prec);//enregistrer le bloc qui le precedent dans le fichier
         }
         else//le bloc à liberer est le premier bloc de la liste
         {
             aff_entete(fichier,1,buf->suiv);//reinitialisation de l'adresse du premier bloc dans l'entete
             buf_suiv.prec = NIL;//chainnage du bloc qui le suit avec NIL
             ecriredir(fichier,buf->suiv,&buf_suiv);//enregistrer le nouveau premier bloc de la liste
         }
     }
     else//le bloc à liberer est le dernier bloc de la liste
     {
         if ((buf->prec) != NIL)//le bloc à liberer n'est pas le premier bloc
         {
             liredir(fichier,buf->prec,&buf_prec);//lecture du bloc qui est avant lui
             buf_prec.suiv = NIL;//chainnage du bloc qui est avant lui avec NIL
             ecriredir(fichier,buf->prec,&buf_prec);//enregistrer le nouveau dernier bloc
             aff_entete(fichier,2,buf->prec);//enregistrer l'adresse du nouveau dernier bloc
         }
         else//le bloc à liberer est le premier bloc
         {
             aff_entete(fichier,1,NIL);//initialiser l'adresse du premier bloc à NIL
             aff_entete(fichier,2,NIL);//initialiser l'adresse du dernier bloc à NIL
         }
     }
     buf->suiv =entete(fichier,5);//chaines le bloc liberer avec le premier bloc de la liste de bloc vide
     buf->prec = NIL;//chaines son precedent à NIL car c'est le nouveau premier bloc de la liste des blocs vide
     ecriredir(fichier,adr,buf);//enregistrer le nouveau premier bloc de la liste des blocs vide
     if ((entete(fichier,5))!= NIL)//la liste des blocs vide n'etait pas vide
     {
        liredir(fichier,entete(fichier,5),&buf_suiv);//lire l'ancient premier bloc de la liste des blocs vide
        buf_suiv.prec = adr;//chaines l'ancient premier bloc de la liste des blocs vide avec le nouveau
        ecriredir(fichier,entete(fichier,5),&buf_suiv);//enregistrer
     }
     aff_entete(fichier,5,adr);//initialiser la nouvelle adresse du premier bloc vide
 }
 /************************************ ENTETE ***************************************/
int entete( LnOF *fichier,int entier )//retourner l'entier dans val
{int val;//valeur retourner en sorti
    switch(entier)
  {
      case 1:val=fichier->entete.pre_bloc; break;//l'adresse du premier bloc
      case 2:val=fichier->entete.der_bloc; break;//l'adresse du dernier bloc
      case 3:val=fichier->entete.Nb_art_inser; break;//le nombre d'articles inserer
      case 4:val=fichier->entete.Nb_art_supp; break;//le nombre d'articles supprimer
      case 5:val=fichier->entete.pre_bloc_vide; break;//l'adresse du premier bloc de la liste des blocs vide
      default: printf("\n LE NUMERO N'EXISTE PAS");
  }
  return val;
}
/*********************************** AFF_entete *******************************/
void aff_entete(LnOF *fichier,int entier,int val)//affecter à la caracteristique num_caract la val
{
  switch(entier)
  {
      case 1:fichier->entete.pre_bloc=val; break;//affecte a l'adresse du premier bloc val
      case 2:fichier->entete.der_bloc=val; break;//affecte a l'adresse du dernier bloc val
      case 3:fichier->entete.Nb_art_inser=val; break;//affecte aux nombre d'articles inserer val
      case 4:fichier->entete.Nb_art_supp=val; break;//affecte aux nombre d'articles supprimer val
      case 5:fichier->entete.pre_bloc_vide=val; break;//affecte a l'adresse du premier bloc de la liste des blocs vide val
      default: printf("\n\t\t<<Le numero est errone>>");
  }
}
