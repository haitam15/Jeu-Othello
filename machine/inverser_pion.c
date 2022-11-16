#include <stdio.h>
#include <stdlib.h>

char **inverser(char color,char **position_jeu,int *tab_pion_capte);

int main()
{
    return 0;
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