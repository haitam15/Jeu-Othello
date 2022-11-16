#ifndef LIST
#define LIST

typedef struct cellule {
    int *tab_pion_capte;
    struct cellule *next;
    struct cellule *previous;
}cellule;

typedef struct {
    cellule *first;
    cellule *last;
    int taille;
}liste;

liste *creer_liste();
void supprimer_liste(liste *L);
void ajouter_debut(liste *L,int *tab_pion_capte);
void ajouter_fin(liste *L,int *tab_pion_capte);
void supprimer_debut(liste *L);
void supprimer_fin(liste *L);
void vider_liste(liste *L);
void afficher_liste(liste *L);

#endif // LIST
