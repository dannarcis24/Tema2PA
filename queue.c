#include "structs.h"

Queue* createQueue()
{
    Queue *nod = (Queue*)malloc(sizeof(Queue));
    if(!nod)
    {
        printf("variabilei nod nu i s-a putut aloca memorie");
        exit(1);
    }

    nod->first = nod->last = NULL;

    return nod;
}

void enQueue(Queue *q, List *elem) // coada retine adresele elementelor, nu le copiaza
{
    List *nod = createList();
    nod->val = elem;
    nod->next = NULL;

    if(!q->first)
    {
        q->first = q->last = nod;
        return;
    }

    ((List*)q->last)->next = nod;
    q->last = nod;
} 

List* deQueue(Queue *q)
{
    if(!q->first)
        return NULL;

    List *nod = ((List*)q->first)->val;
    void *p = q->first;

    q->first = ((List*)p)->next;
    if(!q->first)
        q->last = NULL;

    free(p);

    return nod;
}

void writeQueue(Queue *q, char *fisier)  // afisarea este specifica, va afisa punctajul, urmat de numele echipei
{
    FILE *f = fopen(fisier, "wt");
    if(!f)
    {
        printf("nu s-a putut deschide fisierul %s\n", fisier);
        exit(1);
    }

    for(register List *p = q->first; p; p = p->next)
        fprintf(f, "%.4f %s\n", ((Team*)((List*)p->val)->val)->punctaj, ((Team*)((List*)p->val)->val)->nume_echipa);
    fclose(f);
}

void delQueue(Queue **q)
{
    if(!(*q))
        return;
    
    while((*q)->first)
    {
        List *p  = ((List*)((*q)->first));
        (*q)->first = p->next;

        free(p);
    }

    free(*q);
    *q = NULL;
}
