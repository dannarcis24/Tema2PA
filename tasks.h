#include "structs.h"

char* readString(FILE*);
List* dataInput(char*);
List* whoWIns(List*, List*);
void match(Queue*, Queue*, int, int*);
int* tournamentMatrix(List*);
void writeMatrix(int*, char*);
