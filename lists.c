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

TeamList* createTeamList()
{
    TeamList *nod = (TeamList*)malloc(sizeof(TeamList));
    if(!nod)
    {
        printf("variabilei nod nu i s-a putut aloca memorie");
        exit(1);
    }

    nod->echipa = NULL;
    nod->next = NULL;

    return nod;
}

void addTeam(TeamList **list, Team *elem)
{
    if(!(*list))
    {
        *list = createTeamList();
        (*list)->echipa = elem;

        return;
    }

    TeamList *p;
    for(p = *list; p->next; p = p->next)
        ;
    
    p->next = createTeamList();
    p->next->echipa = elem;
}

void delTeamList(TeamList **list)
{
    TeamList *p = *list;
    while(p)
    {
        TeamList *q = p->next;

        free(p->echipa->nume_echipa);
        free(p->echipa);
        free(p);

        p = q;
    }

    *list = NULL;
}