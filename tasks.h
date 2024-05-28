#include "structs.h"

// APELUL PENTRU FUNCTIA DE COSTRUIRE A UNUI SIR
char* readString(FILE*);

// APELURI PENTRU FUNCTII GESTIONAREA ECHIPELOR
//          (citire, verificare, turnir, afisare, calculare punctaj)
List* dataInput(char*);
List* whoWIns(List*, List*);
void match(Queue*, Queue*, int, int*);
int* tournamentMatrix(List*, Queue**);
void writeMatrix(int*, char*);
void pointsTeam(List*, int*);

// APELURI PENTRU FUNCTII DE DIVERSE CALCULE
int wins(int*, int);
float power(float, int);