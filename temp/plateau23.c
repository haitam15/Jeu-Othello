#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void color(char color);
void plateau(char tab[][8]);

int main()
{
    char tab[8][8],i,j;
    system("mode 122,40");
    SetConsoleTitle("Othello");
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            {
                if ( (i==3 && j==3) || (i==4 && j==4) )
                    tab[i][j]='B';
                else if ( (i==3 && j==4) || (i==4 && j==3) )
                    tab[i][j]='N';
                else
                    tab[i][j]='V';
            }
    printf("\n");
    plateau(tab);
    color('D');
    printf("\n");
    scanf("%c",&i);
    return 0;
}

void plateau(char tab[][8])
{
    int i,j,k;
    printf("   ");
    for (i=0;i<8;i++)
        printf(" _______");
    for (i=0;i<8;i++)
    {
        printf("\n   ");
        color('V');
        printf("|");
        for (j=0;j<8;j++)
            printf("       |");
        color('N');
        printf(".\n   ");
        color('V');
        printf("|");
        for (k=0;k<2;k++)
        {
            for (j=0;j<8;j++)
            {
                printf("  ");
                color(tab[i][j]);
                printf("   ");
                color('V');
                printf("  |");
            }
            color('N');
            printf(".\n   ");
            color('V');
            printf("|");
        }
        for (j=0;j<8;j++)
            printf("_______|");
        color('N');
        printf(".");
    }
}

void color(char color)
{
    switch(color)
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
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
            break;
        default :
            break;
    }
}