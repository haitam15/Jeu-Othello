#include <stdio.h>
#include <stdlib.h>

int N_coup_possible[8][8][9];
int B_coup_possible[8][8][9];

int coup_possible(char color,char position_jeu[8][8]);
void afficher3D(int tab_coup_possible[8][8][9]);
void afficher2D(char tab[8][8]);

int main()
{
    int i,j,n;
    int N_nbr_coup_possible;
    int B_nbr_coup_possible;
    char position_jeu[8][8];
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
            {
                if ( (i==3 && j==3) || (i==4 && j==4) )
                    position_jeu[i][j]='B';
                else if ( (i==3 && j==4) || (i==4 && j==3) )
                    position_jeu[i][j]='N';
                else
                    position_jeu[i][j]='V';
            }
    }
    //afficher2D(position_jeu);
    printf("%d\n",coup_possible('N',position_jeu));
    afficher3D(N_coup_possible);
    return 0;
}

int coup_possible(char color,char position_jeu[8][8])
{
    char pion=color,adverse=(color=='N')?'B':'N';
    int i,j,k,l,nbr_coup_possible=0,a,b,c,d,e,f,g,h,nbr_pion_capte=0;
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
            if (position_jeu[i][j]!='V')
                nbr_pion_capte=0;
            else
            {
                a=0;  //  à droite
                l=j+1;
                while( position_jeu[i][l]==adverse && l<7 )
                {
                    a++;
                    l++;
                }
                if (position_jeu[i][l]!=pion)
                    a=0;
                b=0;  //  en haut à droite
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
                c=0;  //  en haut
                k=i-1;
                while( position_jeu[k][j]==adverse && k>0 )
                {
                    c++;
                    k--;
                }
                if (position_jeu[k][j]!=pion)
                    c=0;
                d=0;  //  en haut à gauche
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
                e=0;  //  à gauche
                l=j-1;
                while( position_jeu[i][l]==adverse && l>0 )
                {
                    e++;
                    l--;
                }
                if (position_jeu[i][l]!=pion)
                    e=0;
                f=0;  //  en bas à gauche
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
                g=0;  //  en bas
                k=i+1;
                while( position_jeu[k][j]==adverse && k<7 )
                {
                    g++;
                    k++;
                }
                if (position_jeu[k][j]!=pion)
                    g=0;
                h=0;  //  en bas à droite
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
                nbr_pion_capte=a+b+c+d+e+f+g+h;
                if (nbr_pion_capte!=0)
                {
                    nbr_coup_possible++;
                    if (color=='N')
                    {
                        N_coup_possible[i][j][1]=a;
                        N_coup_possible[i][j][2]=b;
                        N_coup_possible[i][j][3]=c;
                        N_coup_possible[i][j][4]=d;
                        N_coup_possible[i][j][5]=e;
                        N_coup_possible[i][j][6]=f;
                        N_coup_possible[i][j][7]=g;
                        N_coup_possible[i][j][8]=h;
                    }
                    else
                    {
                        B_coup_possible[i][j][1]=a;
                        B_coup_possible[i][j][2]=b;
                        B_coup_possible[i][j][3]=c;
                        B_coup_possible[i][j][4]=d;
                        B_coup_possible[i][j][5]=e;
                        B_coup_possible[i][j][6]=f;
                        B_coup_possible[i][j][7]=g;
                        B_coup_possible[i][j][8]=h;
                    }
                    
                }
            }
            N_coup_possible[i][j][0]=nbr_pion_capte;
            B_coup_possible[i][j][0]=nbr_pion_capte;
        }
    }
    return nbr_coup_possible;
}

void afficher3D(int tab_coup_possible[8][8][9])
{
    int i,j,k;
    for (i=0;i<8;i++) {
        printf("\n");
        for (j=0;j<8;j++) {
            for (k=0;k<9;k++)
                printf(" %d",tab_coup_possible[i][j][k]);
            printf("  ");
        }
    }
}

void afficher2D(char tab[8][8])
{
    int i,j;
    for (i=0;i<8;i++)
    {
        printf("\n");
        for (j=0;j<8;j++)
            printf("  %c",tab[i][j]);
    }
}