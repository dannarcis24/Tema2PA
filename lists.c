#include "structs.h"

Team* createTeam()
{
    Team *nod = (Team*)malloc(sizeof(Team));
    if(!nod)
    {
        printf("variabilei nod nu i s-a putut aloca memorie");
        exit(1);
    }

    nod->nume_echipa = NULL;
    nod->punctaj = -1.;
    nod->pozitie = 0;
    
    return nod;
}

List* createList()
{
    List *nod = (List*)malloc(sizeof(List));
    if(!nod)
    {
        printf("variabilei nod nu i s-a putut aloca memorie");
        exit(1);
    }

    nod->val = NULL;

    return nod;
}

void addElem(List **list, Team *elem)
{
    if(!(*list))
    {
        *list = createList();
        (*list)->val = elem;

        return;
    }

    List *p;
    for(p = *list; p->next; p = p->next)
        ;
    
    p->next = createList();
    p->next->val = elem;
}

void delList(List **list)
{
    while(*list)
    {
        List *q = (*list)->next;
        free(((Team*)(*list)->val)->nume_echipa);
        free(*list);

        *list = q;
    }

    *list = NULL;
}
