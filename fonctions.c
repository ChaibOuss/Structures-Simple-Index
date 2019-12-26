#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "fonctions.h"
#define b 5// Le nombre d’articles existants dans le bloc
#define NIL 0//Adresse null

/*********************** IMPLEMENTATION DU MODELE *****************************/

/*********************************** CHARGEMENT DU FICHIER *******************************/
void charg_fich (LnOF *fich,S_bloc *buf)//Le chargement du fichier de données de façon aleatoire
{
    int  N_bloc =1;
    int Art =0;
    int n,i,j;
 printf("LE NOMBRE D'ARTICLES : ");
 scanf("%d",&n);//lecture du nombre d'articles à charger
 int tab[n],x,trouv,taille;
 aff_entete(fich,1,0);//reinitialiser l'adresse du premier bloc à NIL
 aff_entete(fich,2,0);//reinitialiser l'adresse du dernier bloc à NIL
 aff_entete(fich,3,0);//reinitialiser le nombre d'articles inseres à NIL
 aff_entete(fich,4,0);//reinitialiser le nombre d'articles supprimes à NIL
 aff_entete(fich,5,0);//reinitialiser l'adresse du premier bloc de la liste des blocs vide à NIL

 if (n != 0)
 {
     allouerbloc(fich,buf);//initialise un buffer si liste blocs vide est vide sinon recuppere un bloc de liste vide et fait les chainement necessaire
   for(i=0;i<n;i++)//chargement de n articles
  {
     if((buf->Nb_article) == b)//le bloc est plein
     {
         ecriredir(fich,N_bloc,buf);//enregistrer le bloc dans le fichier
         allouerbloc(fich,buf);//allouer un autre bloc vide
         N_bloc++;//incrementer le nombre de bloc
         Art = 0;//reinitialiser le nombre d'articles à 0
     }

     buf->Nb_article++;//incrementer le nombre d'articles dans le bloc
     trouv = 1;//initialiser trouv à 1 pour qu'il entre dans la boucle
     while (trouv)//tant que trouv est vrai
     {
         trouv =0;//reinitialiser à non trouv
        x = rand()%1000000;
        for(j=0;j<i;j++)//on teste x avec tous les articles inseres avant
        {
            if(x == tab[j])//x existe deja
                trouv =1;//trouv reçoit 1 pour sortir de la boucle et avoir une autre valeur
        }
     }
     buf->t[Art].matricule = x;//inseres le matricule
     taille = rand()%19;//initialiser une taille aleatoire pour le nom
     for (j=0;j<taille;j++)//remplire le champs nom aleatoirement
     {
        x = 'A' + rand() % ('z' - 'a' + 1) + (rand() % 2) * ('a' - 'A');//generer un caractere aleatoire de l'alphabet
        buf->t[Art].nom[j]= x ;//remplire la chaine nom comme si c'etais un tableau de caractere
     }
     buf->t[Art].nom[j] = '\0';//le dernier caractere du nom
      buf->t[Art].efface =0;//initialiser le champ efface à 0
      Art++;//incrementer le nombre d'article
      aff_entete(fich,3,entete(fich,3)+1);//reinitialiser le nombre d'article inseres
 }
 ecriredir(fich,N_bloc,buf);//enregistrer le dernier bloc
 printf("\nLE CHARGEMENT A BIEN ETAIT EFFECTUE\n");
 }
 else printf("\nLE FICHIER EST VIDE \n");
}

/********************************* RECHERCHE *********************************/
// LE COUT EST O(n) ou n represente le nombre de blocs
void recherche(LnOF *fich,int cle,int *adr,int *pos,int *lect,int *trouv)//La recherche d’une clé donnée dans le fichier
{
    int i,nbloc;
    S_bloc *buf,*sauv;
    if ((entete(fich,1)) == NIL)//l'adresse du premier bloc pointe vers NIL
    {
        printf("LE FICHIER EST VIDE");
        (*trouv)=0;//trouv reçoit faux
    }
    else//le fichier n'est vide
    {
        buf=malloc(sizeof(S_bloc));
        sauv=malloc(sizeof(S_bloc));
        liredir(fich,entete(fich,1),buf);//lecture du premier bloc de la liste
        nbloc=1;//initialiser le nombre de bloc parcouru à 1
        (*trouv) =0;//trouv reçoit faux
        i=0;//initialise le numero de l'article dans le tableau
        while((i<(buf->Nb_article))&&((!(*trouv))))//parcourir le premier bloc
            {
                if (((buf->t[i].matricule)==cle)&&(!(buf->t[i].efface)))//la cle est dans la ieme posotion
                {
                    (*trouv) = 1;//initialise trouv a 1
                    (*adr)=entete(fich,1);//enregistre l'adresse du bloc
                    (*pos)=i;//enregistre la position dans le bloc
                    (*lect)=nbloc;//enregistre le nombre de lecture
                }
                i++;//incremente l'indice du tableau
            }

        while((buf->suiv != NIL)&&(!(*trouv)))//parcourir le reste des blocs
        {
            i=0;//initialise l'indice du tableau a 0
            liredir(fich,buf->suiv,buf);//lecture du bloc suivant
            liredir(fich,buf->prec,sauv);//lecture du bloc precedent
            nbloc++;//incremente le nombre de bloc parcourru
            while((i<(buf->Nb_article))&&((!(*trouv))))//parcourir le tableau
            {
                if (((buf->t[i].matricule)==cle)&&(!(buf->t[i].efface)))//la cle est dans la ieme position
                {
                    (*trouv) = 1;//initialise trouv a 1
                    (*adr)=(sauv->suiv);//enregistre l'adresse du bloc
                    (*pos)=i;//enregistre la position dans le bloc
                    (*lect)=nbloc;//enregistre le nombre de lecture
                }
                i++;//incremente l'indice du tableau

            }
        }
        if (!(*trouv))//la cle n'existe pas
        {
            (*adr)=NIL;//initialise l'adresse du bloc a NIL
            (*pos)=NIL;//initialise la position dans le bloc a NIL
            (*lect)=nbloc;//enregistre le nombre de lecture
            printf("CE MATRICULE N'EXISTE PAS");
        }
        else//la cle existe
        {
            printf("LE NOM DE L'ETUDIANT : %s",buf->t[i-1].nom);
            printf("\nL'ADRESSE DU BLOC : %d",(*adr));
            printf("\nLA POSITION DANS LE BLOC : %d",i-1);
        }
    }
}
/*************************** PERMUT TABLEAU **************************/
void decal(LnOF *fich,int adr,int pos)//decal les elements d'un tableau a partir de la position pos
{
    int i;
    S_bloc buf;
    liredir(fich,adr,&buf);//lecture du bloc
    i = pos;//initialiser i a pose
    while(i<((buf.Nb_article)-1))//parcourir le tableau
    {
        strcpy(buf.t[i].nom,buf.t[i+1].nom);//copie le nom
        (buf.t[i].matricule) = (buf.t[i+1].matricule);//copie le matricule
        i++;//incremente l'indice du tableau
    }
    buf.t[i].efface=1;//initialise le champs efface de l'ancien dernier element a 1
    ecriredir(fich,adr,&buf);//enregistrer dans fichier
}
/*************************** SUPPRESSION *****************************/
// LE COUT EST O(n) ou n represente le nombre de blocs
void supprim(LnOF *fich,int cle)//Supprime l'article de matricule cle si il existe
{
    int adr,pos,lect,trouv;
    S_bloc buf;
    recherche(fich,cle,&adr,&pos,&lect,&trouv);//recuperer les coordonnes de l'element si il existe
    system("cls");
    if (trouv)//le matricule existe
    {
        decal(fich,adr,pos);//decaler le tableau de cette position
        liredir(fich,adr,&buf);//lire le bloc ou se trouve ce matricule
        buf.Nb_article =(buf.Nb_article)-1;//decremente le nombre d'articles dans ce bloc
        ecriredir(fich,adr,&buf);//enregistrer les modifications
        if ((buf.Nb_article)==0)//le bloc devient vide apres cette suppretion
        {
            liber_bloc(fich,adr);//placer le bloc dans la liste des blocs vide avec les chainages adequa
        }
        aff_entete(fich,3,entete(fich,3)-1);//decremente le nombre d'article inserer de l'entete
        aff_entete(fich,4,entete(fich,4)+1);//incremente le nombre d'article supprimer de l'entete
        printf("\nL'ETUDIANT A BIEN ETAIT SUPPRIME");
    }
    else//le matricule n'est pas trouver
    {
        printf("\n CET ARTICLE N'EXISTE PAS\n");
    }
}
/************************ AFFICHAGE *****************************/
void affichage(LnOF *fich)//affichage du contenue du fichier
{
    int adr,i;
    S_bloc buf;
    //Affichage de l'entete du fichier
    printf("\n==========================================================================\n");
    printf("\nL'ENTETE DU FICHIER :   %s                                              \n",fich->entete.nom_fich);
    printf("1.  L'ADRESSE DU PREMIER BLOC :     %d                                    ||\n",entete(fich,1));
    printf("2.  L'ADRESSE DU DERNIER BLOC :     %d                                    ||\n",entete(fich,2));
    printf("3.  LE NOMBRE D'ARTICLES INSERES :     %d                                 ||\n",entete(fich,3));
    printf("4.  LE NOMBRE D'ARTICLES SUPPRIMES :     %d                               ||\n",entete(fich,4));
    printf("5.  L'ADRESSE DU PREMIER BLOC DE LA LISTE VIDES :     %d                  ||\n",entete(fich,5));
    printf("==========================================================================\n");
    liredir(fich,entete(fich,1),&buf);//lecture du premier bloc si existe
    if ((entete(fich,1)) == 0)//le fichier est vide
        printf("\nLE FICHIER EST VIDE\n");
    else//le fichier n'est pas vide
    {
        //Affichage des caracteristique du premier bloc
        printf("==========================================================================\n");
        printf("\nL'ADRESSE DU BLOC : %d \n",entete(fich,1));
        printf("NOMBRE D'ARTICLES EXISTANT : %d\n",buf.Nb_article);
        printf("L'ADRESSE DU BLOC PRECEDENT : %d\n",buf.prec);
        printf("L'ADRESSE DU BLOC SUIVANT : %d\n",buf.suiv);

        for (i=0;i<(buf.Nb_article);i++)//Affiche tous les articles non supprimes les supprimes ont etaient decales
        {
            printf("==========================================================================\n");
            printf("ARTICLE %d\n",i+1);
            printf("NOM DE L'ETUDIANT : %s\n",buf.t[i].nom);
            printf("MATRICULE : %d\n",buf.t[i].matricule);
            printf("==========================================================================\n");
        }
        printf("==========================================================================\n");
        while ((buf.suiv) != NIL)//il existe encore d'autre bloc non vide
        {
            adr = buf.suiv;
            liredir(fich,buf.suiv,&buf);//lecture du bloc suivant
            //Affichage des caracteristique du bloc
            printf("==========================================================================\n");
            printf("\nL'ADRESSE DU BLOC : %d \n",adr);
            printf("NOMBRE D'ARTICLES EXISTANT : %d\n",buf.Nb_article);
            printf("L'ADRESSE DU BLOC PRECEDENT : %d\n",buf.prec);
            printf("L'ADRESSE DU BLOC SUIVANT : %d\n",buf.suiv);
            printf("==========================================================================\n");
            for (i=0;i<(buf.Nb_article);i++)//Affiche tous les articles non supprimes les supprimes ont etaient decales
            {
                printf("==========================================================================\n");
                printf("ARTICLE %d\n",i+1);
                printf("NOM DE L'ETUDIANT : %s\n",buf.t[i].nom);
                printf("MATRICULE : %d\n",buf.t[i].matricule);
                printf("==========================================================================\n");
            }
        }
    }
}
/************************ REORGANISATION ************************/
void reorganis(LnOF *fich)//elimine tous les articles supprimes en creant un nouveau fichier
{
    int i,j,x;
    char nom [20];//pour stocker l'ancient nom
    S_bloc buf_reo,buf_anc;
    LnOF *nef=malloc(sizeof(LnOF));//creer un nouveau fichier
    Ouvrir(nef,"new","n");//ouvrir le nouveau fichier
    if((entete(fich,1))== NIL)//le fichier est vide
    {
        printf("LE FICHIER EST DEJA VIDE");
    }
    else//le fichier n'est pas vide
    {
        liredir(fich,entete(fich,1),&buf_anc);//lecture du premier bloc
        allouerbloc(nef,&buf_reo);//allouer un bloc dans le nouveau fichier
        j = 0;//indice du tableau de l'ancien fichier
        i = 0;//indice du tableau du nouveau fichier
        int cpt =0;//pour compter le nombre d'article ont a copier
      while (cpt < entete(fich,3))//parcourir tous les articles inserer
      {
        if (buf_reo.Nb_article == b )//on a atteint le nombre max d'article dans un bloc
        {
            ecriredir(nef,entete(nef,2),&buf_reo);//enregister le bloc qu'on a remplie
            allouerbloc(nef,&buf_reo);//allouer un nouveau bloc
            i = 0;//reinitialiser l'indice de tableau a 0
        }
            buf_reo.t[i].matricule =buf_anc.t[j].matricule;//copie le matricule
            strcpy(buf_reo.t[i].nom,buf_anc.t[j].nom);//copie le nom
            buf_reo.t[i].efface = 0;//metre le champ efface a 0
            buf_reo.Nb_article ++;//incrementer le nombre d'article dans le bloc
            i++;//incrementer l'indice de tableau
            j++;//incrementer l'indice de tableau
            cpt++;//incrementer le nombre d'article copie
        if (j == buf_anc.Nb_article)//on a parcouru tous les articles du bloc buf_anc
            {
                liredir(fich,buf_anc.suiv,&buf_anc);//lire le prochain bloc
                j = 0;//reinitialiser l'indice du tableau
            }
        }
        ecriredir(nef,entete(nef,2),&buf_reo);//enregistrer le dernier bloc
        printf("\nLE FICHIER A BIEN ETAIT REORGANISE");
    }
        aff_entete(nef,3,entete(fich,3));//enregister le nombre d'article inserer
        aff_entete(nef,4,0);//reinitialiser le nombre d'article supprimer a 0
        strcpy(nom,fich->entete.nom_fich);//copie le nom de l'ancient fichier
        strcpy(nef->entete.nom_fich,nom);//enregister le nom de l'ancient fichier dans l'entete du nouveau
        fermer(nef);//fermer le nouveau fichier
        fermer(fich);//fermer l'ancient fichier
        rename(nom,"ANCIENT");
        rename("new",nom);
        remove("ANCIENT");//supprimer l'ancient fichier
        Ouvrir(fich,nom,"a");//reouvrir le nouveau fichier
}
/************************ INSERTION *****************************/
// LE COUT EST O(n) ou n represente le nombre de blocs
void inser(LnOF *fich,int cle,char nom [20])//insertion d’un article non existant
{
    int adr,pose,lect,trouv;
    S_bloc buf;
    recherche(fich,cle,&adr,&pose,&lect,&trouv);//recherche si cette cle existe deja
    system("cls");
    if (trouv != 0 )//la recherche à trouver un article avec cette cle
        printf("\nCE MATRICULE EXISTE DEJA");
    else//il n'existe pas d'article avec cette cle
    {
        if ((entete(fich,1))== NIL)//le fichier est vide
        {
                allouerbloc(fich,&buf);//cree un nouveau bloc
                buf.t[0].matricule = cle;//charger la cle
                strcpy(buf.t[0].nom,nom);//charger le nom
                buf.t[0].efface = 0;//reinitialiser le champ efface à faux
                buf.Nb_article =1;//initialiser le nombre d'article dans ce bloc à 1
        }
        else//le fichier n'est pas vide
        {
            liredir(fich,entete(fich,2),&buf);//lire le dernier bloc
            if((buf.Nb_article)==b)//le dernier bloc est plein
            {
                allouerbloc(fich,&buf);//allouer un autre bloc
                buf.t[0].matricule = cle;//charger la cle
                strcpy(buf.t[0].nom,nom);//charger le nom
                buf.t[0].efface = 0;//reinitialiser le champ efface à faux
                buf.Nb_article =1;//initialiser le nombre d'article dans ce bloc à 1
            }
            else//il y'a de l'espace dans le dernier bloc
            {
                buf.t[buf.Nb_article].matricule = cle;//charger la cle le premier espace vide du tableau
                strcpy(buf.t[buf.Nb_article].nom,nom);//charger le nom le premier espace vide du tableau
                buf.t[buf.Nb_article].efface = 0;//reinitialiser le champ efface à faux
                buf.Nb_article++;//incrementer le nombre d'articles dans ce bloc
            }
        }
        ecriredir(fich,(entete(fich,2)),&buf);//enregistrer le dernier bloc
        aff_entete(fich,3,entete(fich,3)+1);//incrementer le nombre d'article inserer dans le fichier
        printf("\nL'ETUDIANT A BIEN ETAIT INSCRI");
    }
}
/************************* PARTIE 2 INDEX ***********************************/

/********************************** Chargement du fichier index **************************/
void charge_i(TnOF *fich_i,struct S_Table *tete_table)//Le chargement du fichier index en memoire gentrale
{
    int i,j;
    S_i_bloc *buf_i=malloc(sizeof(S_i_bloc));
    struct S_Table *q;
    tete_table = NIL;
    if(entete_i(fich_i,2)!= 0 )//fichier INDEX non vide
    {
        for(i=1;i<=(entete_i(fich_i,1));i++)//repeter pour chaque bloc
        {
            liredir_i(fich_i,i,buf_i);//lire le bloc i
            for(j=0;j<(buf_i->nelem);j++)//repeter pour tous les enregistrement du tableau t_i
            {
                alloue_tab_i(&tete_table);//alloues un nouveau enregistrement vide pour la table d'index
                q = tete_table;
                while (q->suiv != NIL)//se positionne au dernier element de la table
                {
                    q = q->suiv;
                }
                q->elem.adr_bloc = buf_i->t_i[j].adr_bloc;//copie l'adresse du bloc
                q->elem.cle = buf_i->t_i[j].cle;//copie la cle
                q->elem.pos_bloc = buf_i->t_i[j].pos_bloc;//copie la position dans le bloc
            }
        }
        printf("\nLE CHARGEMENT DU FICHIER INDEX EN MEMOIRE CENTRAL A BIEN ETAIT EFFECTUE");
    }
    else//fichier index vide
        printf("\nLE FICHIER INDEX EST VIDE ");
}
/************************* Sauvegarde de la table d'index *************************/
void sauvegarde_i (TnOF *fich_i,struct S_Table *tete_table)//sauvegarder la table d'index dans fichier index
{
    int i,elem;
    struct S_Table *tab ;
    S_i_bloc *buf_i =malloc(sizeof(S_i_bloc));//allouer un buffer
    elem =0;//initialiser l'indice du tableau du bloc a 0
    tab = tete_table;//enregistrer la tete de la table
    if (tab != NIL)//la table d'index n'est pas vide
    {
        allouerbloc_i(fich_i,buf_i);//allouer un bloc pour le fichier index
        while(tab != NIL)//parcourir toute la table
        {
            if((buf_i->nelem)==b)//on a atteint le nombre max d'element dans 1 bloc
            {
                ecriredir_i(fich_i,entete_i(fich_i,1),buf_i);//enregistrer le bloc remplie
                allouerbloc_i(fich_i,buf_i);//allouer un nouveau bloc
                elem=0;//reinitialiser l'indice du tableau a 0
            }
                buf_i->t_i[elem].adr_bloc = tab->elem.adr_bloc;
                buf_i->t_i[elem].cle = tab->elem.cle;
                buf_i->t_i[elem].pos_bloc = tab->elem.pos_bloc;
                elem++;//incrementer l'indice du tableau
                buf_i->nelem++;//incrementer le nombre d'elements dans le bloc
                aff_entete_i(fich_i,2,entete_i(fich_i,2)+1);//incrementer le nombre d'elements inserer
                tab = tab->suiv;//passer a l'element suivant de la table d'index
        }
        ecriredir_i(fich_i,entete_i(fich_i,1),buf_i);//enregister le dernier bloc
        printf("\nLA SAUVEGARDE DANS LE FICHIER INDEX A BIEN ETAIT EFFECTUEE \n");
    }
    else//la table est vide
        printf("\nLA TABLE INDEX EST VIDE");
}
/************************* Chargement initial index ***************************/
void charg_initial_i (LnOF *fich,TnOF *fich_i,S_bloc *buf,struct S_Table **tete_table)//Le chargement du fichier de données avec index de façon aleatoire
{
    int  N_bloc =1;
    int Art =0;
    int n,i,j;
   struct S_Table *q =malloc(sizeof(struct S_Table));
 printf("LE NOMBRE D'ARTICLES : ");
 scanf("%d",&n);//lecture du nombre d'articles à charger
 int tab[n],x,trouv,taille;
 aff_entete(fich,1,0);//reinitialiser l'adresse du premier bloc à NIL
 aff_entete(fich,2,0);//reinitialiser l'adresse du dernier bloc à NIL
 aff_entete(fich,3,0);//reinitialiser le nombre d'articles inseres à NIL
 aff_entete(fich,4,0);//reinitialiser le nombre d'articles supprimes à NIL
 aff_entete(fich,5,0);//reinitialiser l'adresse du premier bloc de la liste des blocs vide à NIL
 (*tete_table) = NIL;
 if (n != 0)
 {
   allouerbloc(fich,buf);//initialise un buffer si liste blocs vide est vide sinon recuppere un bloc de liste vide et fait les chainement necessaire
   for(i=0;i<n;i++)//chargement de n articles
  {
     if((buf->Nb_article) == b)//le bloc est plein
     {
         ecriredir(fich,N_bloc,buf);//enregistrer le bloc dans le fichier
         allouerbloc(fich,buf);//allouer un autre bloc vide
         N_bloc++;//incrementer le nombre de bloc
         Art = 0;//reinitialiser le nombre d'articles à 0
     }
     alloue_tab_i(tete_table);//allouer un enregistrement dans la table d'index
     q = (*tete_table);//enregister la tete de la table d'index
     while (q->suiv != NIL)//se positioner au dernier enregistrement de la table d'index
     {
         q = q->suiv;
     }
     buf->Nb_article++;//incrementer le nombre d'articles dans le bloc
     trouv = 1;//initialiser trouv à 1 pour qu'il entre dans la boucle
     while (trouv)//tant que trouv est vrai
     {
        trouv =0;//reinitialiser à non trouv
        x = rand()%1000000;
        for(j=0;j<i;j++)//on teste x avec tous les articles inseres avant
        {
            if(x == tab[j])//x existe deja
                trouv =1;//trouv reçoit 1 pour sortir de la boucle et avoir une autre valeur
        }
     }
     buf->t[Art].matricule = x;//inseres le matricule dans le bloc
     q->elem.cle = x;//inseres le matricule dans la table
     taille = rand()%19;//initialiser une taille aleatoire pour le nom
     for (j=0;j<taille;j++)//remplire le champs nom aleatoirement
     {
        x = 'A' + rand() % ('z' - 'a' + 1) + (rand() % 2) * ('a' - 'A');//generer un caractere aleatoire de l'alphabet
        buf->t[Art].nom[j]= x ;//remplire la chaine nom comme si c'etais un tableau de caractere
     }
     buf->t[Art].nom[j] = '\0';//le dernier caractere du nom
     q->elem.adr_bloc = N_bloc;//inseres l'adresse du bloc
     q->elem.pos_bloc = Art;//inseres la position dans le bloc
      buf->t[Art].efface =0;//initialiser le champ efface à 0
      Art++;//incrementer le nombre d'article
 }
 ecriredir(fich,N_bloc,buf);//enregistrer le dernier bloc
 aff_entete(fich,3,entete(fich,3)+n);//reinitialiser le nombre d'article inseres
 printf("\nLE CHARGEMENT A BIEN ETAIT EFFECTUE");
 sauvegarde_i(fich_i,*tete_table);////sauvegarder la table d'index dans fichier index
 }
 else printf("\nLE FICHIER EST VIDE \n");
}
/**************************** Recherche index ***************************/
// LE COUT EST O(1) ou n represente le nombre de blocs
void recherche_i(LnOF *fich,int cle,struct S_Table *tete_table,int *trouv)//La recherche d’une clé donnée dans le fichier avec index
{
    S_bloc buf;
    (*trouv)=0;//initialiser trouv a 0
    struct S_Table *q = tete_table;
    while((!(*trouv))&&(q != NIL))//parcourir tous les elements de la table d'index jusqu'a trouver cette cle
    {
        if (q->elem.cle == cle)//la cle est trouver
        {
            (*trouv) =1;//initialiser trouv a 1
        }
        else//passer a l'element suivant
        {
            q = q->suiv;
        }
    }
    if((*trouv))//la cle a ete trouver
    {
        liredir(fich,(q->elem.adr_bloc),&buf);//lecture du bloc ou se trouve la cle
        printf("LE NOM DE L'ETUDIANT : %s \n",buf.t[(q->elem.pos_bloc)].nom);
        printf("\nL'ETUDIANT EST INSERE DANS LE BLOC : %d  A LA POSITION : %d\n",q->elem.adr_bloc,q->elem.pos_bloc);
    }
    else
    {
        printf("\n CETTE CLE N'EXISTE PAS \n");
        (*trouv = 0);
    }
}
/*************************** Insertion index *********************************/
// LE COUT EST O(1) ou n represente le nombre de blocs
void inser_i(LnOF *fich,TnOF *fich_i,struct S_Table **tete_table,int cle,char nom[20])//insertion d’un article non existant avec index
{
    int trouv;
    S_bloc buf;
    struct S_Table *q ;
    recherche_i(fich,cle,*tete_table,&trouv);//recherche si cette cle existe deja
    system("cls");
    if (!(trouv))//la cle n'existe pas
    {
        alloue_tab_i(tete_table);//allouer un enregistrement dans la table d'index
        q = (*tete_table);//enregistrer la tete de la table
         while (q->suiv != NIL)//se positionner au dernier element de la table d'index
        {
            q = q->suiv;
        }
        if ((entete(fich,1))== NIL)//le fichier est vide
        {
            allouerbloc(fich,&buf);//cree un nouveau bloc
        }
            liredir(fich,entete(fich,2),&buf);//lire le dernier bloc
            if((buf.Nb_article)==b)//le dernier bloc est plein
            {
                allouerbloc(fich,&buf);//allouer un autre bloc
            }
            q->elem.cle = cle;//inserer la cle
            q->elem.adr_bloc = entete(fich,2);//inserer l'adresse du bloc
            q->elem.pos_bloc = buf.Nb_article;//inserer la position dans le bloc
            buf.t[buf.Nb_article].matricule = cle;//charger la cle le premier espace vide du tableau
            strcpy(buf.t[buf.Nb_article].nom,nom);//charger le nom le premier espace vide du tableau
            buf.t[buf.Nb_article].efface = 0;//reinitialiser le champ efface à faux
            buf.Nb_article++;//incrementer le nombre d'articles dans ce bloc

        ecriredir(fich,(entete(fich,2)),&buf);//enregistrer le dernier bloc
        aff_entete(fich,3,entete(fich,3)+1);//incrementer le nombre d'article inserer dans le fichier
        printf("\nL'INSERTION A BIEN ETAIT EFFECTUEE");
        sauvegarde_i(fich_i,(*tete_table));//sauvegarder la table d'index dans fichier index
    }
    else
        printf("\nCETTE CLE EXISTE DEJA\n");
}
/*************************** AFFICHAGE DE LA TABLE D'INDEX ***************************/
void affich_tab(struct S_Table *tete_table)//affiche la table d'index
{
    int i = 1;
    struct S_Table *q;
    q = tete_table;
    if (q == NIL)//la table est vide
    {
        printf("\nLA TABLE D'INDEX EST VIDE \n");
    }
    else//il existe au moin un element dans la table
  {
    while (q != NIL)//parcourir la table
    {
        printf("\n===========================================================================\n");
        printf("\nMATRICULE %d : %d",i,q->elem.cle);
        printf("\nADRESSE DU BLOC : %d ",q->elem.adr_bloc);
        printf("\nPOSITION DANS LE BLOC %d : %d",q->elem.adr_bloc,q->elem.pos_bloc);
        printf("\n===========================================================================\n");
        i++;
        q = q->suiv;//passe a l'element suivant
    }
  }
}

