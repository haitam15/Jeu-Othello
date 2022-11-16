#include <stdio.h>
#include <stdlib.h>

void plateau(char tab[][8]);

int main()
{
    char tab[8][8],i,j;
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            tab[i][j]=' ';
    plateau(tab);
    printf("\n");
    scanf("%c",&i);
    return 0;
}

void plateau(char tab[][8])
{
    int i,j;
    for (i=0;i<8;i++)
        printf(" _____");
    for (i=0;i<8;i++)
    {
        printf("\n|");
        for (j=0;j<8;j++)
            printf("     |");
        printf("\n|");
        for (j=0;j<8;j++)
            printf("  %c  |",tab[i][j]);
        printf("\n|");
        for (j=0;j<8;j++)
            printf("_____|");
    }
}