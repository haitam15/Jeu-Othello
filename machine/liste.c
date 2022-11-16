#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

liste *creer_liste()
{
    liste *L=malloc(sizeof(liste));
    L->first=NULL;
    L->last=NULL;
    L->taille=0;
    return L;
}

void supprimer_liste(liste *L)
{
    free(L);
}

void ajouter_debut(liste *L,int *tab_pion_capte)
{
    cellule *element=malloc(sizeof(cellule));
    element->tab_pion_capte=tab_pion_capte;
    element->next=L->first;
    element->previous=NULL;
    if (L->taille==0)
        L->last=element;
    else
        L->first->previous=element;
    L->first=element;
    L->taille++;
}

void ajouter_fin(liste *L,int *tab_pion_capte)
{
    cellule *element=malloc(sizeof(cellule));
    element->tab_pion_capte=tab_pion_capte;
    element->next=NULL;
    element->previous=L->last;
    if (L->taille==0)
        L->first=element;
    else
        L->last->next=element;
    L->last=element;
    L->taille++;
}

void supprimer_debut(liste *L)
{
    if (L->taille==0)
        return;
    cellule *element=L->first;
    L->first=L->first->next;
    if (L->taille==1)
        L->last=NULL;
    else
        L->first->previous=NULL;
    free(element->tab_pion_capte);
    free(element);
    L->taille--;
}

void supprimer_fin(liste *L)
{
    if (L->taille==0)
        return;
    cellule *element=L->last;
    L->last=L->last->previous;
    if (L->taille==1)
        L->first=NULL;
    else
        L->last->next=NULL;
    free(element->tab_pion_capte);
    free(element);
    L->taille--;
}

void vider_liste(liste *L)
{
    if (L->taille==0)
        return;
    int i,n=L->taille;
    for (i=0;i<n;i++)
        supprimer_debut(L);
}

void afficher_liste(liste *L)
{
    int i,n=L->taille;
    if (n==0)
        printf("liste vide ! \n");
    else
    {
        cellule *element=L->first;
        printf("( %c%d %d )",'A'+element->tab_pion_capte[1],element->tab_pion_capte[0]+1,element->tab_pion_capte[2]);
        for (i=1;i<n;i++)
        {
            element=element->next;
            printf("  ( %c%d %d )",'A'+element->tab_pion_capte[1],element->tab_pion_capte[0]+1,element->tab_pion_capte[2]);
        }
        printf("\n");
    }
}
