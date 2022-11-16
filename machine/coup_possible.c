#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

liste *coup_possible(char color,char **position_jeu);

int main()
{
    int i,j;
    char **position_jeu=NULL,c;
    liste *L=NULL;
    position_jeu=(char**)malloc(8*sizeof(char*));
    for (i=0;i<8;i++)
        position_jeu[i]=(char*)malloc(8*sizeof(char));
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            {
                if ( (i==3 && j==3) || (i==4 && j==4) )
                    position_jeu[i][j]='B';
                else if ( (i==3 && j==4) || (i==4 && j==3) )
                    position_jeu[i][j]='N';
                else
                    position_jeu[i][j]='V';
            }
    L=coup_possible('N',position_jeu);
    afficher_liste(L);
    vider_liste(L);
    afficher_liste(L);
    supprimer_liste(L);
    for (i=0;i<8;i++)
        free(position_jeu[i]);
    free(position_jeu);
    return 0;
}

liste *coup_possible(char color,char **position_jeu)
{
    char pion=color,adverse=(color=='N')?'B':'N';
    int i,j,k,l,a,b,c,d,e,f,g,h,nbr_pion_capte=0,*tab_pion_capte=NULL;
    liste *L=creer_liste();
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
            if (position_jeu[i][j]=='V')
            {
                a=0;  //  à droite
                if (j<6)
                {
                    l=j+1;
                    while( position_jeu[i][l]==adverse && l<7 )
                    {
                        a++;
                        l++;
                    }
                    if (position_jeu[i][l]!=pion)
                        a=0;
                }
                b=0;  //  en haut à droite
                if ( i>1 && j<6 )
                {
                    k=i-1;
                    l=j+1;
                    while( position_jeu[k][l]==adverse && k>0 && l<7 )
                    {
                        b++;
                        k--;
                        l++;
                    }
                    if (position_jeu[k][l]!=pion)
                        b=0;
                }
                c=0;  //  en haut
                if (i>1)
                {
                    k=i-1;
                    while( position_jeu[k][j]==adverse && k>0 )
                    {
                        c++;
                        k--;
                    }
                    if (position_jeu[k][j]!=pion)
                        c=0;
                }
                d=0;  //  en haut à gauche
                if ( i>1 && j>1 )
                {
                    k=i-1;
                    l=j-1;
                    while( position_jeu[k][l]==adverse && k>0 && l>0 )
                    {
                        d++;
                        k--;
                        l--;
                    }
                    if (position_jeu[k][l]!=pion)
                        d=0;
                }
                e=0;  //  à gauche
                if (j>1)
                {
                    l=j-1;
                    while( position_jeu[i][l]==adverse && l>0 )
                    {
                        e++;
                        l--;
                    }
                    if (position_jeu[i][l]!=pion)
                        e=0;
                }
                f=0;  //  en bas à gauche
                if ( i<6 && j>1 )
                {
                    k=i+1;
                    l=j-1;
                    while( position_jeu[k][l]==adverse && k<7 && l>0 )
                    {
                        f++;
                        k++;
                        l--;
                    }
                    if (position_jeu[k][l]!=pion)
                        f=0;
                }
                g=0;  //  en bas
                if (i<6)
                {
                    k=i+1;
                    while( position_jeu[k][j]==adverse && k<7 )
                    {
                        g++;
                        k++;
                    }
                    if (position_jeu[k][j]!=pion)
                        g=0;
                }
                h=0;  //  en bas à droite
                if ( i<6 && j<6 )
                {
                    k=i+1;
                    l=j+1;
                    while( position_jeu[k][l]==adverse && k<7 && l<7 )
                    {
                        h++;
                        k++;
                        l++;
                    }
                    if (position_jeu[k][l]!=pion)
                        h=0;
                }
                nbr_pion_capte=a+b+c+d+e+f+g+h;
                if (nbr_pion_capte!=0)
                {
                    tab_pion_capte=(int*)malloc(11*sizeof(int));
                    tab_pion_capte[0]=i;
                    tab_pion_capte[1]=j;
                    tab_pion_capte[2]=nbr_pion_capte;
                    tab_pion_capte[3]=a;
                    tab_pion_capte[4]=b;
                    tab_pion_capte[5]=c;
                    tab_pion_capte[6]=d;
                    tab_pion_capte[7]=e;
                    tab_pion_capte[8]=f;
                    tab_pion_capte[9]=g;
                    tab_pion_capte[10]=h;
                    ajouter_fin(L,tab_pion_capte);
                }
            }
        }
    }
    return L;
}