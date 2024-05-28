#include "tasks.h"

int wins(int *matrice, int poz) // se calculeaza numarul de victorii echipei de pe pozitia poz
{
    int suma = 0;
    for(register int i = 0; i < 32; i++) // matrice[i * 32 + j] = matrice[i][j]
        suma += matrice[i * 32 + poz];
    return suma;
}

float power(float numar, int putere)
{
    float p = 1.;
    for(register int i = 0; i < putere; i++)
        p *= numar;
    return p;
}

void pointsTeam(List *lista_echipe, int *matrice_turneu) // se modifica punctajele conform formulei
{
    for(register List *p = lista_echipe; p; p = p->next)
    {
        int numar_victorii = wins(matrice_turneu, ((Team*)p->val)->pozitie);
        ((Team*)p->val)->punctaj = 0.15*power(2-0.15, numar_victorii)/(64.+power(2-0.15, 6)*(0.15-1));
    }
}
