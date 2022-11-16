#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

typedef enum {
    False,True
}Boolean;

int position_machine[2]={-1};
int DEPTH=0;

int evaluation_position(char color, char **position_jeu);
int minimax(char **position_jeu, char color, int depth, int alpha, int beta, Boolean player);
liste *coup_possible(char color,char **position_jeu);
char **inverser(char color,char **position_jeu,int *tab_pion_capte);
char **position_initial();
void vider_tab(char **tab);

int main()
{
    char **position_jeu=position_initial();
    int m;
    scanf("%d",&DEPTH);
    m=minimax(position_jeu,'N',DEPTH,-64,64,True);
    printf(" %c%d : %d",'A'+position_machine[1],position_machine[0]+1,m);
    return 0;
}

int evaluation_position(char color, char **position_jeu)
{
    int i,j,N=0,B=0;
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
            if (position_jeu[i][j]=='N')
                N++;
            else if (position_jeu[i][j]=='B')
                B++;
        }
    }
    if (color=='N')
        return N-B;
    return B-N;
}

int minimax(char **position_jeu, char color, int depth, int alpha, int beta, Boolean player)
{
    char pion=(player)?color:(color=='N')?'B':'N';
    liste *L=coup_possible(pion,position_jeu);
    int eval;
    if ( depth==0 || L->taille==0 )
    {
        eval=evaluation_position(color,position_jeu);
        vider_liste(L);
        supprimer_liste(L);
        vider_tab(position_jeu);
        return eval;
    }
    if (player)
    {
        int max_eval=-65,i;
        char **nv_position_jeu;
        cellule *element=L->first;
        for (i=0;i<L->taille;i++)
        {
            nv_position_jeu=inverser(pion,position_jeu,element->tab_pion_capte);
            eval=minimax(nv_position_jeu, color, depth-1, alpha, beta, False);
            if (eval>max_eval)
            {
                max_eval=eval;
                if (depth==DEPTH)
                {
                    position_machine[0]=element->tab_pion_capte[0];
                    position_machine[1]=element->tab_pion_capte[1];
                }
            }
            if (eval>alpha)
                alpha=eval;
            if (beta<=alpha)
                break;
            element=element->next;
        }
        vider_liste(L);
        supprimer_liste(L);
        vider_tab(position_jeu);
        return max_eval;
    }
    int min_eval=64,i;
    char **nv_position_jeu;
    cellule *element=L->first;
    for (i=0;i<L->taille;i++)
    {
        nv_position_jeu=inverser(pion,position_jeu,element->tab_pion_capte);
        eval=minimax(nv_position_jeu, color, depth-1, alpha, beta, True);
        if (eval<min_eval)
            min_eval=eval;
        if (eval<beta)
            beta=eval;
        if (beta<=alpha)
            break;
        element=element->next;
    }
    vider_liste(L);
    supprimer_liste(L);
    vider_tab(position_jeu);
    return min_eval;
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

char **inverser(char color,char **position_jeu,int *tab_pion_capte)
{
    int i,j,n;
    char **nv_position_jeu=(char**)malloc(8*sizeof(char*));
    for (i=0;i<8;i++)
        nv_position_jeu[i]=(char*)malloc(8*sizeof(char));
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            nv_position_jeu[i][j]=position_jeu[i][j];
    nv_position_jeu[tab_pion_capte[0]][tab_pion_capte[1]]=color;
    j=tab_pion_capte[1];
    for (n=0;n<tab_pion_capte[3];n++)  // à droite
    {
        j++;
        nv_position_jeu[tab_pion_capte[0]][j]=color;
    }
    i=tab_pion_capte[0];
    j=tab_pion_capte[1];
    for (n=0;n<tab_pion_capte[4];n++)  // en haut à droite
    {
        i--;
        j++;
        nv_position_jeu[i][j]=color;
    }
    i=tab_pion_capte[0];
    for (n=0;n<tab_pion_capte[5];n++)  // en haut
    {
        i--;
        nv_position_jeu[i][tab_pion_capte[1]]=color;
    }
    i=tab_pion_capte[0];
    j=tab_pion_capte[1];
    for (n=0;n<tab_pion_capte[6];n++)  // en haut à gauche
    {
        i--;
        j--;
        nv_position_jeu[i][j]=color;
    }
    j=tab_pion_capte[1];
    for (n=0;n<tab_pion_capte[7];n++)  // à gauche
    {
        j--;
        nv_position_jeu[tab_pion_capte[0]][j]=color;
    }
    i=tab_pion_capte[0];
    j=tab_pion_capte[1];
    for (n=0;n<tab_pion_capte[8];n++)  // en bas à gauche
    {
        i++;
        j--;
        nv_position_jeu[i][j]=color;
    }
    i=tab_pion_capte[0];
    for (n=0;n<tab_pion_capte[9];n++)  // en bas
    {
        i++;
        nv_position_jeu[i][tab_pion_capte[1]]=color;
    }
    i=tab_pion_capte[0];
    j=tab_pion_capte[1];
    for (n=0;n<tab_pion_capte[10];n++)  // en bas à droite
    {
        i++;
        j++;
        nv_position_jeu[i][j]=color;
    }
    return nv_position_jeu;
}

char **position_initial()
{
    int i,j;
    char **tab=(char**)malloc(8*sizeof(char*));
    for (i=0;i<8;i++)
        tab[i]=(char*)malloc(8*sizeof(char));
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            tab[i][j]='V';
    tab[3][3]='B';
    tab[3][4]='N';
    tab[4][3]='N';
    tab[4][4]='B';
    return tab;
}

void vider_tab(char **tab)
{
    int i;
    for (i=0;i<8;i++)
        free(tab[i]);
    free(tab);
}