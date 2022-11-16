#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <liste.h>

#define W 1100
#define H 619
#define X 433
#define Y 96
#define A 60

#define DEPTH 8

typedef enum {
    False,True
}Boolean;

int position_machine[11]={-1};

int evaluation_position(char color, char **position_jeu);
int minimax(char **position_jeu, char color, int depth, int alpha, int beta, Boolean player);
char **position_initial();
void vider_tab(char **tab);
liste *coup_possible(char color,char **position_jeu);
char **inverser(char color,char **position_jeu,int *tab_pion_capte);
void error(SDL_Window *win);
void afficher_plateau(SDL_Window *win,SDL_Surface *screen,char **position_jeu,char color,int r);
char **jouer_coup(SDL_Window *win,SDL_Surface *screen,char color,char **position_jeu,liste *L,int r,int *c);
char **jouer_machine(SDL_Window *win,SDL_Surface *screen,char color,char **position_jeu,liste *L,int niveau,int r);
int gagnant(char **position_jeu,int r);

int main(int argc,char **argv)
{
    SDL_Window *win=NULL;
    SDL_Surface *screen=NULL,*menu=NULL,*menu1=NULL,*menu2=NULL,*menu3=NULL,*principe=NULL,*principe1=NULL,*principe2=NULL,*principe3=NULL;
    SDL_Surface *jouer=NULL,*jouer1=NULL,*jouer2=NULL,*jouer3=NULL,*difficulte=NULL,*difficulte1=NULL,*difficulte2=NULL,*difficulte3=NULL;
    SDL_Surface *random_box=NULL,*player_tour_win=NULL,*player_tour_lose=NULL,*player1_tour_win=NULL,*player2_tour_win=NULL,*score=NULL;
    SDL_Surface *rejouer=NULL,*rejouer1=NULL,*rejouer2=NULL,*rejouer3=NULL;
    int c=2,niveau=0,winner=0;
    char **position_jeu=NULL;
    liste *L=NULL;
    SDL_Event event;
    srand(time(NULL));
    if (SDL_Init(SDL_INIT_VIDEO)!=0)
        exit(1);
    win=SDL_CreateWindow("Othello",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,W,H,0);
    if (win==NULL)
        error(win);
    screen=SDL_GetWindowSurface(win);
    if (screen==NULL)
        error(win);
    SDL_Rect rect={443,278,193,94};
    while (c)
    {
        if (c==2)
        {
            menu=IMG_Load("..\\image\\menu.png");
            if (menu==NULL)
                error(win);
            SDL_BlitSurface(menu,NULL,screen,NULL);
            SDL_UpdateWindowSurface(win);
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT :
	            c=0;
                break;
            case SDL_MOUSEMOTION :
                if ( 443<=event.motion.x && event.motion.x<=636 )
                {
                    if ( 278<=event.motion.y && event.motion.y<=372 )
                    {
                        menu1=IMG_Load("..\\image\\menu1.png");
                        SDL_Rect rect={443,278,193,94};
                        SDL_BlitSurface(menu1,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=1; //jouer
                                SDL_FreeSurface(menu);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( ! ( 278<=event.motion.y && event.motion.y<=372 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(menu1);
                    }
                    else if ( 372<=event.motion.y && event.motion.y<=466 )
                    {
                        menu2=IMG_Load("..\\image\\menu2.png");
                        SDL_Rect rect={443,372,193,94};
                        SDL_BlitSurface(menu2,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=1; //Regles (jouer)
                                SDL_FreeSurface(menu);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( ! ( 372<=event.motion.y && event.motion.y<=466 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(menu2);
                    }
                    else if ( 466<=event.motion.y && event.motion.y<=571 )
                    {    
                        menu3=IMG_Load("..\\image\\menu3.png");
                        SDL_Rect rect={443,466,193,105};
                        SDL_BlitSurface(menu3,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=0;  //quitter
                                SDL_FreeSurface(menu);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( ! ( 466<=event.motion.y && event.motion.y<=571 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(menu3);
                    }
                }
                break;
            }
            //if (c==2) c=4;
            //SDL_FreeSurface(menu);
        }
        /*if (c==4)
        {
            regles=IMG_Load("..\\image\\regles.png");
            if (regles==NULL)
                error(win);
            SDL_BlitSurface(regles,NULL,screen,NULL);
            SDL_UpdateWindowSurface(win);
            rect.x=x;
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT :
	            c=0;
                break;
            case SDL_MOUSEMOTION :
                if ( <=event.motion.x && event.motion.x<= )
                {
                    if ( <=event.motion.y && event.motion.y<= )
                    {
                            reg1es1=IMG_Load("..\\image\\regles1.png");
                            rect.y=y1;
                            SDL_BlitSurface(regles1,NULL,screen,&rect);
                            SDL_UpdateWindowSurface(win);
                            do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=1; //jouer
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( <=event.motion.y && event.motion.y<= ))
                                break;
                        }while(1);
                        SDL_FreeSurface(regles1);
                    }
                    else if ( <=event.motion.y && event.motion.y<= )
                    {
                        reg1es2=IMG_Load("..\\image\\regles2.png");
                        rect.y=y2;
                        SDL_BlitSurface(regles2,NULL,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=2; //Menu
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( <=event.motion.y && event.motion.y<= ))
                                break;
                        }while(1);
                        SDL_FreeSurface(regles2);
                    }
                    else if ( <=event.motion.y && event.motion.y<= )
                    {    
                        reg1es3=IMG_Load("..\\image\\regles3.png");
                        rect.y=y3;
                        SDL_BlitSurface(regles3,NULL,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=0;  //quitter
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( <=event.motion.y && event.motion.y<= ))
                                break;
                        }while(1);
                        SDL_FreeSurface(regles3);
                    }
                }
                break;
            default:
                break;
            }
            SDL_FreeSurface(regles);
        }*/
        if (c==1)
        {
            //printf("\n 1- Player 1 vs Player 2 \n 2- player 1 vs machine \n 3- Quitter \n");
            jouer=IMG_Load("..\\image\\jouer.png");
            if (jouer==NULL)
                error(win);
            SDL_BlitSurface(jouer,NULL,screen,NULL);
            SDL_UpdateWindowSurface(win);
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT :
	            c=0;
                break;
            case SDL_MOUSEMOTION :
                if ( 555<=event.motion.x && event.motion.x<=1062 && 181<=event.motion.y && event.motion.y<=505 )
                    {
                        jouer1=IMG_Load("..\\image\\jouer1.png");
                        SDL_Rect rect={555,181,507,324};
                        SDL_BlitSurface(jouer1,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=3; //Joeur
                                SDL_FreeSurface(jouer);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 555<=event.motion.x && event.motion.x<=1062 && 181<=event.motion.y && event.motion.y<=505 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(jouer1);
                    }
                if ( 24<=event.motion.x && event.motion.x<=531 && 184<=event.motion.y && event.motion.y<=506 )
                    {
                        jouer2=IMG_Load("..\\image\\jouer2.png");
                        SDL_Rect rect={24,184,507,322};
                        SDL_BlitSurface(jouer2,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=5; //Machine
                                SDL_FreeSurface(jouer);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 24<=event.motion.x && event.motion.x<=531 && 184<=event.motion.y && event.motion.y<=506 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(jouer2);
                    }
                if ( 406<=event.motion.x && event.motion.x<=668 && 478<=event.motion.y && event.motion.y<=612 )
                    {    
                        jouer3=IMG_Load("..\\image\\jouer3.png");
                        SDL_Rect rect={406,478,262,134};
                        SDL_BlitSurface(jouer3,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=0;  //quitter
                                SDL_FreeSurface(jouer);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 406<=event.motion.x && event.motion.x<=668 && 478<=event.motion.y && event.motion.y<=612 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(jouer3);
                    }
                break;
            //SDL_FreeSurface(jouer);
            }
        }
        if (c==5)
        {
            niveau=0;
            difficulte=IMG_Load("..\\image\\difficulte.png");
             if (difficulte==NULL)
                error(win);
            SDL_BlitSurface(difficulte,NULL,screen,NULL);
            SDL_UpdateWindowSurface(win);
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT :
	            c=0;
                break;
            case SDL_MOUSEMOTION :
                if ( 450<=event.motion.x && event.motion.x<=649 && 258<=event.motion.y && event.motion.y<=353 )
                    {
                        difficulte1=IMG_Load("..\\image\\difficulte1.png");
                        SDL_Rect rect={450,258,199,95};
                        SDL_BlitSurface(difficulte1,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                niveau=1; //Facile
                                SDL_FreeSurface(difficulte);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 450<=event.motion.x && event.motion.x<=649 && 258<=event.motion.y && event.motion.y<=353 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(difficulte1);
                    }
                if ( 447<=event.motion.x && event.motion.x<=649 && 371<=event.motion.y && event.motion.y<=467 )
                    {
                        difficulte2=IMG_Load("..\\image\\difficulte2.png");
                        SDL_Rect rect={447,371,199,96};
                        SDL_BlitSurface(difficulte2,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                niveau=2; //Difficile
                                SDL_FreeSurface(difficulte);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 447<=event.motion.x && event.motion.x<=649 && 371<=event.motion.y && event.motion.y<=467 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(difficulte2);
                    }
                if ( 453<=event.motion.x && event.motion.x<=652 && 488<=event.motion.y && event.motion.y<=583 )
                    {
                        difficulte3=IMG_Load("..\\image\\difficulte3.png");
                        SDL_Rect rect={453,488,199,95};
                        SDL_BlitSurface(difficulte3,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=0; //Quitter
                                SDL_FreeSurface(difficulte);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 453<=event.motion.x && event.motion.x<=652 && 488<=event.motion.y && event.motion.y<=583 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(difficulte3);
                    }
                break;
            }
            //SDL_FreeSurface(difficulte);
        }
        if ( c==3 || ( c==5 && niveau!=0 ) )
        {
            int N,B,r=0;
            position_jeu=position_initial();
            random_box=IMG_Load("..\\image\\random_box.png");
            if (random_box==NULL)
                error(win);
            SDL_BlitSurface(random_box,NULL,screen,NULL);
            SDL_UpdateWindowSurface(win);
            do{
                SDL_WaitEvent(&event);
                if (event.type==SDL_QUIT) {
                    c=0;
                    break; }
                else if (event.type==SDL_MOUSEBUTTONDOWN)
                    break;
            }while(1);
            if (c==0) break;
            SDL_FreeSurface(random_box);
            //srand(time(NULL));
            if (c==3)
                r=rand()%2+1;
            else 
                r=rand()%2+3;
            if (r==1)
            {
                player1_tour_win=IMG_Load("..\\image\\player1_tour_win.png");
                if (player1_tour_win==NULL)
                    error(win);
                SDL_BlitSurface(player1_tour_win,NULL,screen,NULL);
                SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                SDL_FreeSurface(player1_tour_win);
            }
            if (r==2)
            {
                player2_tour_win=IMG_Load("..\\image\\player2_tour_win.png");
                if (player2_tour_win==NULL)
                    error(win);
                SDL_BlitSurface(player2_tour_win,NULL,screen,NULL);
                SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                SDL_FreeSurface(player2_tour_win);
            }
            if (r==3)
            {
                player_tour_win=IMG_Load("..\\image\\player_tour_win.png");
                if (player_tour_win==NULL)
                    error(win);
                SDL_BlitSurface(player_tour_win,NULL,screen,NULL);
                SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                SDL_FreeSurface(player_tour_win);
            }
            if (r==4)
            {
                player_tour_lose=IMG_Load("..\\image\\player_tour_lose.png");
                if (player_tour_lose==NULL)
                    error(win);
                SDL_BlitSurface(player_tour_lose,NULL,screen,NULL);
                SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                SDL_FreeSurface(player_tour_lose);
            }
            liste *L=NULL;
            afficher_plateau(win,screen,position_jeu,'N',r);
            do{
                L=coup_possible('N',position_jeu);
                N=L->taille;
                if (N!=0){
                    //afficher(L)
                    if (r==4)
                        position_jeu=jouer_machine(win,screen,'N',position_jeu,L,niveau,r);
                    else {
                        position_jeu=jouer_coup(win,screen,'N',position_jeu,L,r,&c);
                        if (c==0 || c==1 || c==2) 
                            break; }
                vider_liste(L);
                supprimer_liste(L); }
                L=coup_possible('B',position_jeu);
                B=L->taille;
                if (B!=0) {
                    //afficher(L)
                    if (r==3)
                        position_jeu=jouer_machine(win,screen,'B',position_jeu,L,niveau,r);
                   else {
                        position_jeu=jouer_coup(win,screen,'B',position_jeu,L,r,&c);
                        if (c==0 || c==1 || c==2)
                            break; }
                vider_liste(L);
                supprimer_liste(L); }
            }while( N!=0 || B!=0 );
            if (c==0 || c==1 || c==2)
                continue;
            winner=gagnant(position_jeu,r);
            vider_tab(position_jeu);
            if ( c==0 || c==2 || c==1 )            
                continue;
            SDL_Delay(800);
            rejouer=IMG_Load("..\\image\\rejouer.png");
            if (rejouer==NULL)
                error(win);
            switch (winner)
            {
            case 1 :
                score=IMG_Load("..\\image\\player1_win.png");
                SDL_BlitSurface(score,NULL,screen,NULL);
                SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                SDL_BlitSurface(rejouer,NULL,score,NULL);
                break;
            case 2 :
                score=IMG_Load("..\\image\\player2_win.png");
                SDL_BlitSurface(score,NULL,screen,NULL);
                SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                SDL_BlitSurface(rejouer,NULL,score,NULL);
                break;
            case 3 :
                score=IMG_Load("..\\image\\player_win.png");
                SDL_BlitSurface(score,NULL,screen,NULL);
                SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                SDL_BlitSurface(rejouer,NULL,score,NULL);
                break;
            case 4 :
                score=IMG_Load("..\\image\\player_lose.png");
                SDL_BlitSurface(score,NULL,screen,NULL);
                SDL_UpdateWindowSurface(win);
                SDL_Delay(2000);
                SDL_BlitSurface(rejouer,NULL,score,NULL);
                break;
            }
            while(c==3 || c==5) {
            SDL_BlitSurface(score,NULL,screen,NULL);
            SDL_UpdateWindowSurface(win);
            SDL_WaitEvent(&event);
            switch (event.type)
            {
            case SDL_QUIT :
	            c=0;
                break;
            case SDL_MOUSEMOTION :
                if ( 630<=event.motion.x && event.motion.x<=769 && 427<=event.motion.y && event.motion.y<=533 )
                    {
                        rejouer1=IMG_Load("..\\image\\rejouer1.png");
                        SDL_Rect rect={630,427,139,106};
                        SDL_BlitSurface(rejouer1,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=1; //Jouer
                                SDL_FreeSurface(rejouer);
                                SDL_FreeSurface(score);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 630<=event.motion.x && event.motion.x<=769 && 427<=event.motion.y && event.motion.y<=533 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(rejouer1);
                    }
                if ( 473<=event.motion.x && event.motion.x<=611 && 435<=event.motion.y && event.motion.y<=533 )
                    {
                        rejouer2=IMG_Load("..\\image\\rejouer2.png");
                        SDL_Rect rect={473,435,138,98};
                        SDL_BlitSurface(rejouer2,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=2; //Menu
                                SDL_FreeSurface(rejouer);
                                SDL_FreeSurface(score);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 473<=event.motion.x && event.motion.x<=611 && 435<=event.motion.y && event.motion.y<=533 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(rejouer2);
                    }
                if ( 322<=event.motion.x && event.motion.x<=453 && 437<=event.motion.y && event.motion.y<=532 )
                    {    
                        rejouer3=IMG_Load("..\\image\\rejouer3.png");
                        SDL_Rect rect={322,437,131,95};
                        SDL_BlitSurface(rejouer3,&rect,screen,&rect);
                        SDL_UpdateWindowSurface(win);
                        do{
                            if (event.type==SDL_MOUSEBUTTONDOWN)
                            {
                                c=0;  //quitter
                                SDL_FreeSurface(rejouer);
                                SDL_FreeSurface(score);
                                break;
                            }
                            SDL_WaitEvent(&event);
                            if ( !( 322<=event.motion.x && event.motion.x<=453 && 437<=event.motion.y && event.motion.y<=532 ))
                                break;
                        }while(1);
                        SDL_FreeSurface(rejouer3);
                    }
                break;
            //SDL_FreeSurface(rejouer);
            //SDL_FreeSurface(score);
            }}
        }
    }
    SDL_FreeSurface(screen);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void error(SDL_Window *win)
{
    if (win==NULL)
    {
        printf("error window");
        SDL_Quit();
    }
    else
    {
        printf("error surface");
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
}
void afficher_plateau(SDL_Window *win,SDL_Surface *screen,char **position_jeu,char color,int r)
{
    int i,j,k;
    SDL_Surface *white=NULL,*black=NULL,*plateau=NULL;
    if (color=='N')
        plateau=(r==1)?IMG_Load("..\\image\\plateau1.png"):(r==2)?IMG_Load("..\\image\\plateau2.png"):(r==3)?IMG_Load("..\\image\\plateau3.png"):IMG_Load("..\\image\\plateau4.png");
    else
        plateau=(r==1)?IMG_Load("..\\image\\plateau2.png"):(r==2)?IMG_Load("..\\image\\plateau1.png"):(r==3)?IMG_Load("..\\image\\plateau4.png"):IMG_Load("..\\image\\plateau3.png");
    white=IMG_Load("..\\image\\blanc.png");
    black=IMG_Load("..\\image\\noire.png");
    SDL_Rect rect={X,Y,A,A};
    SDL_BlitSurface(plateau,NULL,screen,NULL);
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
            
            rect.x=X+j*A;
            rect.y=Y+i*A;
            if (position_jeu[i][j]=='N')
                SDL_BlitSurface(black,NULL,screen,&rect);
            else if (position_jeu[i][j]=='B')
                SDL_BlitSurface(white,NULL,screen,&rect);
        }
    }
    SDL_UpdateWindowSurface(win);
    //SDL_FreeSurface(plateau);
}

char **jouer_coup(SDL_Window *win,SDL_Surface *screen,char color,char **position_jeu,liste *L,int r,int *c)
{
    int position[2]={0},i,n=0;
    char **nv_position_jeu=NULL,adverse=(color=='N')?'B':'N';
    SDL_Surface *white_poss=NULL,*black_poss=NULL;
    SDL_Rect rect={X,Y,A,A};
    cellule *element=NULL;
    SDL_Event event;
    if (color=='N')
    {
        black_poss=IMG_Load("..\\image\\noire_possible.png");
        element=L->first;
        for (i=0;i<L->taille;i++)
        {
            rect.x=X+element->tab_pion_capte[1]*A;
            rect.y=Y+ element->tab_pion_capte[0]*A;
            SDL_BlitSurface(black_poss,NULL,screen,&rect);
            element=element->next;
        }
        SDL_FreeSurface(black_poss);
    }
    else
    {
        white_poss=IMG_Load("..\\image\\blanc_possible.png");
        element=L->first;
        for (i=0;i<L->taille;i++)
        {
            rect.x=X+element->tab_pion_capte[1]*A;
            rect.y=Y+ element->tab_pion_capte[0]*A;
            SDL_BlitSurface(white_poss,NULL,screen,&rect);
            element=element->next;
        }
        SDL_FreeSurface(white_poss);
    }
    SDL_UpdateWindowSurface(win);
    //SDL_FreeSurface(black_poss);
    //SDL_FreeSurface(white_poss);
    while ( (*c==3 || *c==5) && (n==0) )
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT :
            *c=0;
            break;
        
        case SDL_MOUSEBUTTONUP :
            if ( 992<=event.button.x && event.button.x<=1084 && 247<=event.button.y && event.button.y<=351 )
                *c=2; //Menu
            else if ( 992<=event.button.x && event.button.x<=1084 && 339<=event.button.y && event.button.y<=432 )
                *c=1; //Rejouer
            else if ( 992<=event.button.x && event.button.x<=1084 && 154<=event.button.y && event.button.y<=247 )
                *c=0; //Quitter
            else if ( X<=event.button.x && event.button.x<X+8*A && Y<=event.button.y && event.button.y<Y+8*A )
            {
                position[1]=(((event.button.x)-X)/A);
                position[0]=(((event.button.y)-Y)/A);
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
            break;
        }
    }
    if ( *c==0 || *c==2 || *c==1 )
        return NULL;
    nv_position_jeu=inverser(color,position_jeu,element->tab_pion_capte);
    vider_tab(position_jeu);
    afficher_plateau(win,screen,nv_position_jeu,adverse,r);
    return nv_position_jeu;
}

char **jouer_machine(SDL_Window *win,SDL_Surface *screen,char color,char **position_jeu,liste *L,int niveau,int r)
{
    char **nv_position_jeu=NULL,adverse=(color=='N')?'B':'N';
    if (niveau==1)
    {
        //srand(time(NULL));
        int n=(rand()%(L->taille)),i;
        cellule *element=L->first;
        for (i=0;i<n;i++)
            element=element->next;
        nv_position_jeu=inverser(color,position_jeu,element->tab_pion_capte);
        SDL_Delay(1200);
    }
    else
    {
        minimax(position_jeu,color,DEPTH,-64,64,True);
        nv_position_jeu=inverser(color,position_jeu,position_machine);
        SDL_Delay(500);
    }
    vider_tab(position_jeu);
    afficher_plateau(win,screen,nv_position_jeu,adverse,r);
    return nv_position_jeu;
}

int evaluation_position(char color, char **position_jeu)
{
    int i,j,N=0,B=0;
    for (i=0;i<8;i++)
    {
        for (j=0;j<8;j++)
        {
            if (position_jeu[i][j]=='N')
                N++;
            else if (position_jeu[i][j]=='B')
                B++;
        }
    }
    if (color=='N')
        return N-B;
    return B-N;
}

int minimax(char **position_jeu, char color, int depth, int alpha, int beta, Boolean player)
{
    char pion=(player)?color:(color=='N')?'B':'N';
    liste *L=coup_possible(pion,position_jeu);
    int eval;
    if ( depth==0 || L->taille==0 )
    {
        eval=evaluation_position(color,position_jeu);
        vider_liste(L);
        supprimer_liste(L);
        vider_tab(position_jeu);
        return eval;
    }
    if (player)
    {
        int max_eval=-65,i;
        char **nv_position_jeu;
        cellule *element=L->first;
        for (i=0;i<L->taille;i++)
        {
            nv_position_jeu=inverser(pion,position_jeu,element->tab_pion_capte);
            eval=minimax(nv_position_jeu, color, depth-1, alpha, beta, False);
            if (eval>max_eval)
            {
                max_eval=eval;
                if (depth==DEPTH)
                    for (int j=0;j<11;j++)
                        position_machine[j]=element->tab_pion_capte[j];
            }
            if (eval>alpha)
                alpha=eval;
            if (beta<=alpha)
                break;
            element=element->next;
        }
        vider_liste(L);
        supprimer_liste(L);
        if (depth!=DEPTH)
            vider_tab(position_jeu);
        return max_eval;
    }
    int min_eval=64,i;
    char **nv_position_jeu;
    cellule *element=L->first;
    for (i=0;i<L->taille;i++)
    {
        nv_position_jeu=inverser(pion,position_jeu,element->tab_pion_capte);
        eval=minimax(nv_position_jeu, color, depth-1, alpha, beta, True);
        if (eval<min_eval)
            min_eval=eval;
        if (eval<beta)
            beta=eval;
        if (beta<=alpha)
            break;
        element=element->next;
    }
    vider_liste(L);
    supprimer_liste(L);
    vider_tab(position_jeu);
    return min_eval;
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

int gagnant(char **position_jeu,int r)
{
    int N=0,B=0,i,j;
    for (i=0;i<7;i++)
    {
        for (j=0;j<7;j++)
        {
            if (position_jeu[i][j]=='N')
                N++;
            else if (position_jeu[i][j]=='B')
                B++;
        }
    }
    if (N>B)
        return (r==1)?1:(r==2)?2:(r==3)?3:4;
    else
        return (r==1)?2:(r==2)?1:(r==3)?4:3;
}
