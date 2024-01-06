#include <stdio.h>
#include "symbols.h"
/*--------------------------------------------------------------------------------------------------------------------*/
/*symbols file handles all symbol process in the assembler:
 * adds and finds symbols in the symbol table
 * gets location and address of symbols*/
/*--------------------------------------------------------------------------------------------------------------------*/
int isSymbol(char label[])
{
    symbolNode *ptr = symbols.head;
    while(ptr != NULL)
    {
        if(!strcmp(ptr->labelName,label)) /*check if label is equal to current symbol in symbol table*/
            return 1;
        ptr = ptr->next; /*move to next symbolNode*/
    }
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void addSymbol(char label[],int type, int location)
{
    symbolNode* ptr = symbols.head;
    symbolNode* node = NULL;

    if(symbols.head == NULL)
    {
        symbols.head= (symbolNode*)malloc(sizeof(symbolNode)); /*Allocate memory for the symbolNode*/
        symbols.head->next=NULL;
        strcpy(symbols.head->labelName,label); /*insert label to the symbol definition*/

        if (location == external) /*external symbol*/
        {
            symbols.head->externalFlag = 1; /*turn on external flag*/
            symbols.head->address = 0;/*address will be 0 (fake) for external, because the assembler cant find it*/
            symbols.head->type = type;
        }
        else /*not external symbol*/
            symbols.head->externalFlag = 0; /*turn off external flag*/
        if (type == data)
        {
            symbols.head->address = dc;/*address for data is dc*/
            symbols.head->type = data;
        }
        else
        {
            symbols.head->address = ic;/*address for internal is ic*/
            symbols.head->type = command;
        }
    }

    else /*move to the end of the symbol table to add the label*/
    {
        while(ptr->next!= NULL) /*loop to move the pointer to last symbolNode*/
        {
            ptr = ptr->next;
        }

        node = (symbolNode*)malloc(sizeof(symbolNode)); /*Allocate memory for the symbolNode*/
        ptr->next = node; /*set the new node as next*/
        strcpy(node->labelName,label); /*insert label to the symbolNode definition*/
        node->next= NULL;

        if(location == external) /*external symbol*/
        {
            node->externalFlag = 1;/*turn on external flag*/
            node->address = 0; /*address will be 0 (fake) for external, because the assembler cant find it*/
            node->type = type;
            return;
        }
        else /*not external symbol*/
            node->externalFlag = 0;/*turn off external flag*/
        if(type == data)
        {
            node->address = dc; /*address for data is dc*/
            node->type = data;
        }
        else
        {
            node->address = ic; /*address for interanal is ic*/
            node->type = command;
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
int getSymbolLocation(char *label)
{
    symbolNode *ptr = symbols.head;
    while(ptr)
    {
        if(!strcmp(ptr->labelName,label))
            return ptr->externalFlag;
        ptr = ptr->next;
    }
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int getSymbolAddress(char label[])
{
    symbolNode *ptr = symbols.head;
    while(ptr)
    {
        if(!strcmp(ptr->labelName,label))
            return ptr->address;
        ptr = ptr->next;
    }
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void updateSymbolAddress(void)
{
    symbolNode *ptr = symbols.head;
    while(ptr)
    {
        if(ptr->type == data && ptr->externalFlag !=1)/*external symbol address is irrelevant*/
            ptr->address += ic;
        ptr = ptr->next;
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void printSymbolTable(const symbolTable* symbols)
{
    symbolNode* ptr = symbols->head;

    printf("\nSymbol Table:\n");
    printf("%-20s %-10s %-10s %-15s\n", "Label Name", "Type", "Address", "External Flag");
    printf("---------------------------------------------------------\n");

    while (ptr != NULL) {
        printf("%-20s %-10s %-10d %-15d\n", ptr->labelName,
               ptr->type == data ? "Data" : "Command", ptr->address, ptr->externalFlag);
        ptr = ptr->next;
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void freeSymbolTable(symbolTable* symbols)
{
    symbolNode* current = symbols->head;
    symbolNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    symbols->head = NULL; /* Set the head pointer to NULL to indicate an empty list */
}
