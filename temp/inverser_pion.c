#include <stdio.h>
#include <stdlib.h>

int N_coup_possible[8][8][9];
int B_coup_possible[8][8][9];

void inverser(char color,int *position,char position_jeu[8][8]);

int main()
{
    int i,j,position[2]={3,4};
    char position_jeu[8][8];
    return 0;
}

void inverser(char color,int *position,char position_jeu[8][8])
{
    int i,j,n;
    int a=(color=='N')?N_coup_possible[position[0]][position[1]][1]:B_coup_possible[position[0]][position[1]][1];
    int b=(color=='N')?N_coup_possible[position[0]][position[1]][2]:B_coup_possible[position[0]][position[1]][2];
    int c=(color=='N')?N_coup_possible[position[0]][position[1]][3]:B_coup_possible[position[0]][position[1]][3];
    int d=(color=='N')?N_coup_possible[position[0]][position[1]][4]:B_coup_possible[position[0]][position[1]][4];
    int e=(color=='N')?N_coup_possible[position[0]][position[1]][5]:B_coup_possible[position[0]][position[1]][5];
    int f=(color=='N')?N_coup_possible[position[0]][position[1]][6]:B_coup_possible[position[0]][position[1]][6];
    int g=(color=='N')?N_coup_possible[position[0]][position[1]][7]:B_coup_possible[position[0]][position[1]][7];
    int h=(color=='N')?N_coup_possible[position[0]][position[1]][8]:B_coup_possible[position[0]][position[1]][8];
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