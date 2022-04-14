#include <stdio.h>
#include <stdlib.h>
#define TAILLE_MEMORE 1000

typedef struct processusNode {
    int size;
    struct processusNode *next;
}processusNode;

processusNode *head = NULL;

void RemoveProcBySize(int size)
{
    processusNode *temp = head;
    processusNode *supNode = NULL;

    if(temp == NULL)
    {
        printf("ERROR");
        return;
    }

    while(temp != NULL)
    {
        if((temp->next)->size == size)
        {
            break;
        }
        temp = temp->next;
    }

    supNode = temp->next;
    temp->next = supNode->next;
    free(supNode);
}

void PrintList()
{
    processusNode *temp = head;
    int i=1;
    if(head == NULL)
    {
        printf("No data in the list");
        return;
    }
    printf("This is your data liste : \n");

    while(temp != NULL)
    {
        printf("\n%d) %d",i++,temp->size);
        temp = temp->next;
    }
}

void AddProcEndOrRemove(int sizeProc)
{
    processusNode *temp = head;
    processusNode *proc = (processusNode*)malloc(sizeof(processusNode));
    proc->size = sizeProc;
    proc->next = NULL;

    if(head == NULL)
    {
        head = proc;
        return;
    }

    while(temp->next != NULL)
    {
        if(proc->size < 0 && (proc->size == (temp->size*(-1)) || proc->size == (temp->next)->size*(-1)))
        {

            RemoveProcBySize(temp->size);
            //PrintList();
            return;
        }
        temp = temp->next;

    }

    temp->next = proc;
    PrintList();
}

int stockDataFromFile(int processusArray[])
{
    int i,cpt;
    char signe;

    FILE *fichier = fopen("../processus.txt","r");

    if(fichier != NULL)
    {
        i = 0;
        cpt = 0;
        while( !feof(fichier))
        {
            processusArray[i] = 0;
            fscanf(fichier,"%c%dKo,",&signe,&processusArray[i]);
            i++;
            cpt++;
        }
    }else
    {
        printf("Aucun fichier trouvee");
    }

    return cpt;
}
int main()
{
    int i = 0;
    // LIRE LES DONNEE D'UN FICHIER
    int processusArray[100],lengthData;
    lengthData = stockDataFromFile(processusArray);



    for(i = 0;i<lengthData;i++)
    {
        AddProcEndOrRemove(processusArray[i]);
        PrintList();
    }

    PrintList();


    return 0;
}
