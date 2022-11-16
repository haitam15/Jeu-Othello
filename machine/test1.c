#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "liste.h"

char **position_initial();
void vider_tab(char **tab);
void couleur(char couleur);
void plateau(char **position_jeu);
void lire(char *text,int n);
int lire_chiffre(char *ch,int n);
int joueur_joueur(int *position,char color);
liste *coup_possible(char color,char **position_jeu);
char **inverser(char color,char **position_jeu,int *tab_pion_capte);
char **jouer_coup(char color,char **position_jeu,liste *L);
int nbr_pion(char **position_jeu,char color);

int main()
{
    system("mode 122,40");
    SetConsoleTitle("Othello");
    int N,B;
    char **position_jeu=position_initial();
    liste *L=NULL;
    plateau(position_jeu);
    do{
        L=coup_possible('N',position_jeu);
        N=L->taille;
        if (N!=0)
        {
            printf("\n");
            afficher_liste(L);
            printf("%d \n",nbr_pion(position_jeu,'N')-nbr_pion(position_jeu,'B'));
            position_jeu=jouer_coup('N',position_jeu,L);
        }
        vider_liste(L);
        supprimer_liste(L);
        L=coup_possible('B',position_jeu);
        B=L->taille;
        if (B!=0)
        {
            printf("\n");
            afficher_liste(L);
            printf("%d \n",nbr_pion(position_jeu,'N')-nbr_pion(position_jeu,'B'));
            position_jeu=jouer_coup('B',position_jeu,L);
        }
        vider_liste(L);
        supprimer_liste(L);
    }while( N!=0 || B!=0 );
    system("pause");
    vider_tab(position_jeu);
    return 0;
}

int nbr_pion(char **position_jeu,char color)
{
    int i,j,s=0;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            if (position_jeu[i][j]==color)
                s++;
    return s;
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

void plateau(char **position_jeu)
{
    int i,j,k;
    couleur('D');
    printf("\n\t\t\t  ");
    for (i=0;i<8;i++)
        printf("    %c   ",'A'+i);
    printf("\n");
    for (i=0;i<8;i++)
    {
        printf("\n\t\t\t   ");
        couleur('V');
        for (j=0;j<8;j++)
            {
                printf("       ");
                if (j!=7)
                    printf("|");
            }
        couleur('N');
        printf(".\n\t\t\t");
        couleur('D');
        printf("%d  ",i+1);
        couleur('V');
        for (k=0;k<2;k++)
        {
            for (j=0;j<8;j++)
            {
                printf("  ");
                couleur(position_jeu[i][j]);
                printf("   ");
                couleur('V');
                printf("  ");
                if (j!=7)
                    printf("|");
            }
            couleur('N');
            printf(".\n\t\t\t   ");
            couleur('V');
        }
        for (j=0;j<8;j++)
            {
                if (i!=7)
                    printf("_______");
                else
                    printf("       ");
                if (j!=7)
                    printf("|");
            }
        couleur('N');
        printf(".");
    }
    couleur('D');
    printf("\n");
}

void couleur(char couleur)
{
    switch(couleur)
    {
        case 'N' :
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
            break;
        case 'B' :
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
            break;
        case 'V' :
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),47);
            break;
        case 'D' :
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            break;
        default :
            break;
    }
}

void lire(char *text,int n)
{
    int i=0;
    fgets(text,n,stdin);
    while (i<n-1)
    {
        if (text[i]=='\n')
        {
            text[i]='\0';
            return;
        }
        i++;
    }
    char c;
    do
    {
        scanf("%c",&c);
    }while(c!='\n');
}

int lire_chiffre(char *ch,int n)
{
    int i=1,digit=0;
    while( ch[i]==' ' && i<n )
        i++;
    if ( '1'<=ch[i] && ch[i]<='9' )
        digit=(int)(ch[i]-'0');
    return digit;
}

int joueur_joueur(int *position,char color)
{
    char txt[10],col;
    int line,player=(color=='N')?1:2;
    printf("Joueur %d : ",player);
    lire(txt,10);
    col=txt[0];
    if ( 'a'<=col && col<='z' )
        col='A'+(col-'a');
    if ( 'A'<=col && col<='H' )
    {
        line=lire_chiffre(txt,10);
        if (line!=0)
        {
            position[0]=line-1;
            position[1]=(int)(col-'A');
            return 0;
        }
        printf("ligne invalide !");
        return 1;
    }
    printf("colone invalide !");
    return 2;
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

char **jouer_coup(char color,char **position_jeu,liste *L)
{
    int position[2]={0},i,n=0;
    char **nv_position_jeu=NULL;
    joueur_joueur(position,color);
    cellule *element=L->first;
    for (i=0;i<L->taille;i++)
    {
        if ( element->tab_pion_capte[0]==position[0] && element->tab_pion_capte[1]==position[1] )
        {
            n++;
            break;
        }
        element=element->next;
    }
    while(n==0)
    {
        printf("coup impossible ! ");
        joueur_joueur(position,color);
        element=L->first;
        for (i=0;i<L->taille;i++)
        {
            if ( element->tab_pion_capte[0]==position[0] && element->tab_pion_capte[1]==position[1] )
            {
                n++;
                break;
            }
            element=element->next;
        }
    }
    nv_position_jeu=inverser(color,position_jeu,element->tab_pion_capte);
    vider_tab(position_jeu);
    system("cls");
    plateau(nv_position_jeu);
    return nv_position_jeu;
}