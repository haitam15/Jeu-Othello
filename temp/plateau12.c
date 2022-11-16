#include <stdio.h>

void plateau(char pion[8][8]);

int main()
{
    int i,j;
    char pion[8][8];
    for (i=0;i<8;i++)
        for (j=0;j<8;j++)
            pion[i][j]=' ';
    plateau(pion);
    printf("\n");
    scanf("%c",&i);
    return 0;
}

void plateau(char pion[8][8])
{
    int i,j,k,l;
    for (i=0;i<8;i++)
        printf(" _____");
    for (k=0;k<8;k++)
    {
        for (i=0;i<3;i++)
        {
            printf("\n");
            printf("|");
            for (l=0;l<8;l++)
            {
                for (j=0;j<5;j++)
                {
                    switch (i)
                    {
                    case 0:
                        printf(" ");
                        break;
                    case 1:
                        if (j==2)
                            printf("%c",pion[k][l]);
                        else
                            printf(" ");
                        break;
                    case 2:
                        printf("_");
                            break;
                    default:
                        break;
                    }
                }
                printf("|");
            }
        }
    }
}