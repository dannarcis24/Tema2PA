#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TIPURILE DE STRUCT
//          (tip, lista inlantuita, coada)
typedef struct{
    char *nume_echipa;
    float punctaj;
    unsigned int pozitie;
} Team;

typedef struct a{
    Team *echipa;
    struct a *next;
} TeamList;

typedef struct b{
    TeamList *first, *last;
} Queue;

// APELURILE PENTRU FUNCTII DE LISTE INLANTUITE
//          (creare, adaugare, stergere)
Team* createTeam();
TeamList* createTeamList();
void addTeam(TeamList**, Team*);
void delTeamList(TeamList**);

// APELURILE PENTRU FUNCTII DE GESTIONAREA UNEI COZI
//          (creare, adaugare, stergere)
Queue* createQueue();
void enQueue(Queue *q, TeamList*);
Team* deQueue(Queue *q);
void delQueue(Queue **q);