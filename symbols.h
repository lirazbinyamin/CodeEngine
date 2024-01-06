#include <stdlib.h>
#include <string.h>
#define MAX_LABEL_LENGTH 31
extern int dc, ic;
/*--------------------------------------------------------------------------------------------------------------------*/
enum Type {data,command};
enum Location {internal,external};
/*--------------------------------------------------------------------------------------------------------------------*/
/*Defines a node in a linked list of labels*/
typedef struct symbolNode{
    char labelName[MAX_LABEL_LENGTH];
    int address; /*address of symbol in code*/
    enum Type type;/*type of symbol-data/command*/
    int externalFlag;/*if symbol is external =1, else =0*/
    struct symbolNode* next;
}symbolNode;
/*--------------------------------------------------------------------------------------------------------------------*/
/*Defines linked list to store all symbols in code*/
typedef struct symbolTable{
    symbolNode* head;
}symbolTable;
/*--------------------------------------------------------------------------------------------------------------------*/
/*Create a symbol table linked list*/
symbolTable symbols;
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that checks whether a symbol is in the list and if so returns 1, else returns 0 */
int isSymbol(char label[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that gets a label name, type and location and add the symbol to a linked list of symbols table.*/
void addSymbol(char label[],int type ,int location);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that gets a label and check if the symbol is internal or external*/
int getSymbolLocation(char *label);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that gets a label and returns its address*/
int getSymbolAddress(char label[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that updates data labels address to be after instructions (done after 1st pass)*/
void updateSymbolAddress(void);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A Function to print each symbol and its content in the list */
void printSymbolTable(const symbolTable* symbols);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A Function to free the symbol table */
void freeSymbolTable(symbolTable* symbols) ;

