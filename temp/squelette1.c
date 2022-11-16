#include <stdio.h>

int main()
{
    char c='2';
    while (c!='3')
    {
        if (c=='2')
        {
            printf("\n\t Bienvenue Dans le jeu Othello ! \n");
            printf("\n-------------------------------------------------\n");
            printf("\n 1- Jouer \n 2- Principe du jeu \n 3- Quitter \n");
            printf("\n-------------------------------------------------\n");
            scanf("%c",&c);
            scanf("%c");
            while ( c!='1' && c!='2' && c!='3' )
            {
                printf("Taper 1 pour Jouer , 2 pour voir le principe du jeu ou 3 pour quitter ! ");
                scanf("%c",&c);
                scanf("%c");
            }
            if (c=='2') c='4';
        }
        if (c=='4')
        {
            printf("\t\t\t\t Principe du jeu : \n");
            printf("\n--------------------------------------------------------------------------------------------------------\n");
            printf("\n Othello se joue sur un tablier (plateau) unicolore carre de 8x8 cases.\n");
            printf(" Les pions, au nombre de 64, sont reversibles : Une face blanche, et une noire.\n");
            printf(" Chaque joueur a tour de role doit placer une piece a sa couleur sur le tablier.\n");
            printf(" Les pions sont toujours places dans une case adjacente a un pion adverse.\n");
            printf(" De plus, il faut que ce pion finisse d'encadrer une ligne continue de pions \n adverses (ou un seul) qui sont alors captures.\n");
            printf(" Les captures ne retirent pas les pions du tablier, mais on les retourne pour \n qu'ils passent a la couleur de l'attaquant.\n");
            printf(" Peu a peu, le tablier se remplit et la partie prend fin quand le plateau est rempli \n ou que plus aucun joueur ne peut jouer.\n");
            printf(" Le joueur qui possede le plus grand nombre de pions a sa couleur sur le tablier remporte la partie.\n");
            printf("\n--------------------------------------------------------------------------------------------------------\n");
            printf("\n 1- Jouer \n 2- Menu Principal \n 3- Quitter \n");
            scanf("%c",&c);
            scanf("%c");
            while ( c!='1' && c!='2' && c!='3' )
            {
                printf("Taper 1 pour Jouer, 2 pour revenir au menu principal ou 3 quitter ! ");
                scanf("%c",&c);
                scanf("%c");
            }
        }
        if (c=='1')
        {
            printf("\n-------------------------------------------------\n");
            printf("\n 1- Player 1 vs Player 2 \n 2- player 1 vs machine \n 3- Quitter \n");
            printf("\n-------------------------------------------------\n");
            scanf("%c",&c);
            scanf("%c");
            while ( c!='1' && c!='2' && c!='3' )
            {
                printf("Taper 1 pour le mode deux joueurs, 2 pour jouer contre la machine ou 3 pour quitter ! ");
                scanf("%c",&c);
                scanf("%c");
            }
            printf("\n-------------------------------------------------\n");
            if (c!='3')
            {
                if (c=='1')
                    printf("\n Mode deux jouers : Player 1 vs Player 2 \n");
                else
                    printf("\n Mode un jouer : Player 1 vs Machine \n");
                printf("\n-------------------------------------------------\n");
                printf("\n 1- Rejouer \n 2- Menu Principal \n 3- Quitter \n");
                scanf("%c",&c);
                scanf("%c");
                while ( c!='1' && c!='2' && c!='3' )
                {
                    printf("Taper 1 pour Jouer, 2 pour revenir au menu principal ou 3 quitter ! ");
                    scanf("%c",&c);
                    scanf("%c");
                }
            }
        }
    }
    return 0;
}