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
    void *val;
    struct a *next;
} List;

typedef struct{
    void *first, *last;
} Queue;

// APELURILE PENTRU FUNCTII DE LISTE INLANTUITE
//          (creare, adaugare, stergere)
Team* createTeam();
List* createList();
void addElem(List**, Team*);
void delList(List**);

// APELURILE PENTRU FUNCTII DE GESTIONAREA UNEI COZI
//          (creare, adaugare, stergere)
Queue* createQueue();
void enQueue(Queue *q, List*);
List* deQueue(Queue *q);
void delQueue(Queue **q);
