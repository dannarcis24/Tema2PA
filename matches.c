#include "tasks.h"

char *readString(FILE *f) // citirea sirurilor se face parcurgand carcter cu caracter fisierul
{
    char c, *sir = (char *)malloc(sizeof(char));
    if (!sir)
    {
        printf("variabilei sir nu i s-a putut aloca memorie\n");
        exit(1);
    }
    int k = 0;
    
    fscanf(f, "%c", &c);
    while (c != '\n') // citirea se faca pana la '\n', astfel se retin spatiile din sir
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
    if(sir[strlen(sir)-1] == '\r') // se verifica si sterge caracterul '\r'
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

List* dataInput(char *fisier)
{
    FILE *f = fopen(fisier, "rt");
    if(!f)
    {
        printf("nu s-a putut deschide fisierul %s\n", fisier);
        exit(1);
    }

    List *lista_echipe = NULL;
    for(register int i = 0; i < 32 && !feof(f); i++) // se citesc si introduc in lista cele 32echipe
    {
        Team *echipa = createTeam();

        fscanf(f, "%f", &echipa->punctaj);
        echipa->pozitie = i;
        fseek(f, 1L, SEEK_CUR); // se respecta formatul, in felul acesta numele echipei mu va incepe cu spatiu
        echipa->nume_echipa = readString(f);

        addElem(&lista_echipe, echipa);
    }
    fclose(f);

    return lista_echipe;
}

List* whoWins(List *echipa1, List *echipa2)
{
    if(((Team*)echipa1->val)->punctaj > ((Team*)echipa2->val)->punctaj)
        return echipa1;
    else
        if(((Team*)echipa1->val)->punctaj < ((Team*)echipa2->val)->punctaj)
            return echipa2;
        else
            return ((strcmp(((Team*)echipa1->val)->nume_echipa, ((Team*)echipa2->val)->nume_echipa) > 0 ? echipa1 : echipa2));    
}

void match(Queue *castigatori, Queue *pierzatori, int runda, int *matrice)
{
    for(register int i = 0; i < runda; i++) // la fiecare pas se extrag 2echipe si se pune echipa in lista corespunzatoare
    {
        List *echipa1 = deQueue(castigatori);
        List *echipa2 = deQueue(castigatori);

        List *win = whoWins(echipa1, echipa2);

        if(win == echipa1) // se construieste matricea de adiacenta matrice[i][j] = matrice[32*i+j] = 1, daca echipa de pe pozitia j a castigat
        {
            matrice[((Team*)echipa2->val)->pozitie * 32 + ((Team*)echipa1->val)->pozitie] = 1;

            enQueue(castigatori, echipa1);
            enQueue(pierzatori, echipa2);
        }
        else
        {
            matrice[((Team*)echipa1->val)->pozitie * 32 + ((Team*)echipa2->val)->pozitie] = 1;

            enQueue(castigatori, echipa2);
            enQueue(pierzatori, echipa1);
        }
   }
}

int* tournamentMatrix(List *lista_echipe, Queue **lista_invinsi)
{
    int *matrice_turneu = (int*)malloc(sizeof(int) * 32 * 32);
    if(!matrice_turneu)
    {
        printf("variabilei matrice turneu nu i s-a putut aloca memorie");
        exit(1);
    }

    for(register int i = 0; i < 32; i++) // matrice[i * 32 + j] = matrice[i][j]
        for(register int j = 0; j <= i; j++)
            matrice_turneu[i * 32 + j] = matrice_turneu[j * 32 + i] = 0;

    Queue *castigatori = createQueue();
    *lista_invinsi = createQueue();
    for(register List *p = lista_echipe; p; p = p->next) 
        enQueue(castigatori, p);

    int numar_echipe = 16;
    while(numar_echipe)
    {
        match(castigatori, *lista_invinsi, numar_echipe, matrice_turneu);
        numar_echipe /= 2; // se tine cont de numarul de meciuri dintr-o runda
    }
    enQueue(*lista_invinsi, deQueue(castigatori));
    delQueue(&castigatori);

    return matrice_turneu;
}

void writeMatrix(int *matrice, char *fisier)
{
    FILE *f = fopen(fisier, "wt");
    if(!f)
    {
        printf("nu s-a putut deschide fisierul %s\n", fisier);
        exit(1);
    }

    for(register int i = 0; i < 32; i++) // matrice[i * 32 + j] = matrice[i][j]
    {
        for(register int j = 0; j < 32; j++)
            fprintf(f, "%d ", matrice[i * 32 + j]);
        fprintf(f, "\n");
    }
    fclose(f);
}
