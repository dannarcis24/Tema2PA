#include "tasks.h"

void errorInput(int argc, char *argv[])
{
    if(argc != 4)
    {
        printf("datele de intrare trebuie sa fie la numar de trei fisiere: primul de intrare si ultimele doua de iesire\n");
        exit(1);
    }
    if(!strstr(argv[1], ".in"))
    {
        printf("primul fisier trebuie sa fie Input.in\n");
        exit(1);
    }
    if(!strstr(argv[2], ".out") || !strstr(argv[2], "Graf"))
    {
        printf("al doilea fisier trebuie sa fie OutputGraf.out\n");
        exit(1);
    }
    if(!strstr(argv[3], ".out") || !strstr(argv[3], "Scor"))
    {
        printf("al treilea fisier trebuie sa fie OutputScor.out\n");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    errorInput(argc, argv);

    List *lista_echipe = dataInput(argv[1]);
    Queue *lista_invinsi = NULL; // coada va fi folosita pentru afisarea la cerinta 2
    int *matrice_turneu = tournamentMatrix(lista_echipe, &lista_invinsi);
    writeMatrix(matrice_turneu, argv[2]);
    pointsTeam(lista_echipe, matrice_turneu);
    writeQueue(lista_invinsi, argv[3]);

    free(matrice_turneu);
    delQueue(&lista_invinsi);
    delList(&lista_echipe);
    return 0;
}
