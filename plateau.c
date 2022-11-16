#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void couleur(char couleur);
void plateau(char position_jeu[][8]);

int main()
{
    char position_jeu[8][8],i,j;
    system("mode 122,40");
    SetConsoleTitle("Othello");
    //system("couleur 4f");
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
    couleur('D');
    plateau(position_jeu);
    couleur('D');
    printf("\n\n");
    scanf("%c",&i);
    return 0;
}

void plateau(char position_jeu[][8])
{
    int i,j,k;
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