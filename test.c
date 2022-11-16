#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int tab_coup_possible[8][8][9];
char position_jeu[8][8];
int position[2];
char color;

void initialiser_tab();
void couleur(char couleur);
void plateau();
int coup_possible();
void lire(char *text,int n);
int lire_chiffre(char *ch,int n);
int joueur_joueur();
void inverser();
void jouer_coup();

int main()
{
    system("mode 122,40");
    SetConsoleTitle("Othello");
    //system("color 4f");
    int N,B;
    initialiser_tab();
    plateau();
    //system("pause");
    do{
        color='N';
        N=coup_possible();
        if (N!=0)
            jouer_coup();
        color='B';
        B=coup_possible();
        if (B!=0)
            jouer_coup();
    }while( N!=0 || B!=0 );
    system("pause");
    return 0;
}

void initialiser_tab()
{
    int i,j;
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
}

void plateau()
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
    printf("\n");
    couleur('D');
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

int coup_possible()
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
                    tab_coup_possible[i][j][1]=a;
                    tab_coup_possible[i][j][2]=b;
                    tab_coup_possible[i][j][3]=c;
                    tab_coup_possible[i][j][4]=d;
                    tab_coup_possible[i][j][5]=e;
                    tab_coup_possible[i][j][6]=f;
                    tab_coup_possible[i][j][7]=g;
                    tab_coup_possible[i][j][8]=h;
                }
            }
            tab_coup_possible[i][j][0]=nbr_pion_capte;
        }
    }
    return nbr_coup_possible;
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

int joueur_joueur()
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

void inverser()
{
    int i,j,n;
    int a=tab_coup_possible[position[0]][position[1]][1];
    int b=tab_coup_possible[position[0]][position[1]][2];
    int c=tab_coup_possible[position[0]][position[1]][3];
    int d=tab_coup_possible[position[0]][position[1]][4];
    int e=tab_coup_possible[position[0]][position[1]][5];
    int f=tab_coup_possible[position[0]][position[1]][6];
    int g=tab_coup_possible[position[0]][position[1]][7];
    int h=tab_coup_possible[position[0]][position[1]][8];
    j=position[1];
    for (n=0;n<a;n++)  // à droite
    {
        j++;
        position_jeu[position[0]][j]=color;
    }
    i=position[0];
    j=position[1];
    for (n=0;n<b;n++)  // en haut à droite
    {
        i--;
        j++;
        position_jeu[i][j]=color;
    }
    i=position[0];
    for (n=0;n<c;n++)  // en haut
    {
        i--;
        position_jeu[i][position[1]]=color;
    }
    i=position[0];
    j=position[1];
    for (n=0;n<d;n++)  // en haut à gauche
    {
        i--;
        j--;
        position_jeu[i][j]=color;
    }
    j=position[1];
    for (n=0;n<e;n++)  // à gauche
    {
        j--;
        position_jeu[position[0]][j]=color;
    }
    i=position[0];
    j=position[1];
    for (n=0;n<f;n++)  // en bas à gauche
    {
        i++;
        j--;
        position_jeu[i][j]=color;
    }
    i=position[0];
    for (n=0;n<g;n++)  // en bas
    {
        i++;
        position_jeu[i][position[1]]=color;
    }
    i=position[0];
    j=position[1];
    for (n=0;n<h;n++)  // en bas à droite
    {
        i++;
        j++;
        position_jeu[i][j]=color;
    }
}

void jouer_coup()
{
    joueur_joueur();
    while(tab_coup_possible[position[0]][position[1]][0]==0)
    {
        printf("coup impossible ! ");
        joueur_joueur();
    }
    position_jeu[position[0]][position[1]]=color;
    inverser();
    system("cls");
    plateau();
}