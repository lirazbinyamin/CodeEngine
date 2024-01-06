#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*--------------------------------------------------------------------------------------------------------------------*/
#define MCRO 3
#define NUM_LINES 100
/*--------------------------------------------------------------------------------------------------------------------*/
extern int error;
/*Defines a structure to represent a single macro node in a linked list*/
typedef struct MacroNode {
    char name[MCRO];
    char lines[NUM_LINES];
    struct MacroNode* next;
} MacroNode;
/*--------------------------------------------------------------------------------------------------------------------*/
int preAssembler (char* filename,FILE* fileptr);
/*--------------------------------------------------------------------------------------------------------------------*/
/*a Function to create a copy file with ".am" extension from a file with another extension*/
FILE* createAmFile(char* inputFilename, const MacroNode* head);
/*--------------------------------------------------------------------------------------------------------------------*/
/*a Function to read macros from the file and create the linked list table*/
MacroNode* createMacroTable(FILE* file);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A Function to print all macros in the macro table */
void printMacroTable(const MacroNode* head);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A Function to free the memory used by the entire macro table */
void freeMacroTable(MacroNode* head);





