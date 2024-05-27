#include "tasks.h"

char *readString(FILE *f) //citirea sirurilor se face parcurgand carcter cu caracter fisierul
{
    char c, *sir = (char *)malloc(sizeof(char));
    if (!sir)
    {
        printf("variabilei sir nu i s-a putut aloca memorie\n");
        exit(1);
    }
    int k = 0;
    
    fscanf(f, "%c", &c);
    while (c != '\n')
    {   
        sir[k++] = c;
        fscanf(f, "%c", &c);
        sir = (char *)realloc(sir, sizeof(char) * (k + 1));
        if (!sir)
        {
            printf("variabilei sir nu i s-a putut realoca memorie\n");
            exit(1);
        }

        if(feof(f))
            break;
    }
    sir[k] = '\0';
    if(sir[strlen(sir)-1] == '\r')
    {
        sir[--k] = '\0';
        sir = (char *)realloc(sir, sizeof(char) * (k + 1));
        if (!sir)
        {
            printf("variabilei sir nu i s-a putut realoca memorie\n");
            exit(1);
        }
    }

    return sir;
}

TeamList* dataInput(char *fisier)
{
    FILE *f = fopen(fisier, "rt");
    if(!f)
    {
        printf("nu s-a putut deschide fisierul %s\n", fisier);
        exit(1);
    }

    TeamList *lista_echipe = NULL;
    for(register int i = 0; i < 32 && !feof(f); i++)
    {
        Team *echipa = createTeam();

        fscanf(f, "%f", &echipa->punctaj);
        echipa->pozitie = i;
        fseek(f, 1L, SEEK_CUR);
        echipa->nume_echipa = readString(f);

        addTeam(&lista_echipe, echipa);
    }
    fclose(f);

    return lista_echipe;
}

int** tournamentMatrix(TeamList *lista_echipe)
{
    int **matrice_turneu = (int**)malloc(sizeof(int*) * 32);
    if(!matrice_turneu)
    {
        printf("variabilei matrice turneu nu i s-a putut aloca memorie");
        exit(1);
    }

    for(register int i = 0; i < 32; i++)
        for(register int j = 0; j <= i; j++)
            matrice_turneu[i][j] = 0;

    
}