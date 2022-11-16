#include <stdio.h>
#include <stdlib.h>
#define N 5

void lire(char *text,int n);
void lire_entier(int *n);
int lire_chiffre(char *ch,int n);
int joueur_joueur(int *position,char color);

int main()
{
    char text[N];
    int n=-1;
    int position[2];
    /*lire(text,N);
    printf("%s !\n",text);
    printf("%d\n",lire_chiffre(text,N));
    lire_entier(&n);
    printf("%d\n",n);*/
    if (joueur_joueur(position,'N')==0)
        printf("%c %d",'A'+position[1],position[0]+1);
    return 0;
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

void lire_entier(int *n)
{
    char text[N];
    int i=0;
    *n=0;
    lire(text,N);
    while(text[i]!='\0')
    {
        if (text[i]>='0' && text[i]<='9')
            *n=(*n)*10+(int)(text[i]-'0');
        i++;
    }
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

int joueur_joueur(int *position,char color)
{
    char txt[N],col;
    int line,player=(color=='N')?1:2;
    printf("Joueur %d : ",player);
    lire(txt,N);
    col=txt[0];
    if ( 'a'<=col && col<='z' )
        col='A'+(col-'a');
    if ( 'A'<=col && col<='H' )
    {
        line=lire_chiffre(txt,N);
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