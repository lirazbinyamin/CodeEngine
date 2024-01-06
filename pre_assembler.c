#include "pre_assembler.h"
#include "utils.h"
#include "assembler.h"
#include "errors.h"
/*--------------------------------------------------------------------------------------------------------------------*/
/*pre_assembler file handles the pre assembler process:
 * scan file content
 * create macro table for all macros(if there are)
 * create .am file*/
/*--------------------------------------------------------------------------------------------------------------------*/
int preAssembler (char* filename,FILE* fileptr)
{
    MacroNode* macroTable;
    /*printf("Pre Assembler started..\n");*/

    macroTable = createMacroTable(fileptr); /*Create macros linked list table*/

    createAmFile(filename,macroTable); /*Create ".am" file*/

    /*printMacroTable(macroTable);*/

    /*freeMacroTable(macroTable);*/
    fclose(fileptr);
    /*printf("\npreAssembler OK!\n");*/
    return 1;

}
/*--------------------------------------------------------------------------------------------------------------------*/
FILE* createAmFile(char* inputFilename, const MacroNode* head)
{
    FILE* inputFile; /*".as" extension FILE from input*/
    FILE* amFile; /*".am" extension FILE as output*/
    char line[MAX_LINE_LENGTH];
    int macroFound; /* A flag to check if a macro name is found in a line*/
    const MacroNode* current;

    inputFile = fopen(inputFilename, "r");/*Open the input file for reading*/
    if (inputFile==NULL)
        fileNotFound(inputFilename);

    changeExtension(inputFilename,"am");/*Change file name extension to ".am" */

    amFile = fopen(inputFilename, "w");/*Open an output file with the ".am" extension for writing*/
    if(amFile==NULL)
        fileNotFound(inputFilename);

    macroFound=0;/*Initialize flag*/

    while (fgets(line, sizeof(line), inputFile) != NULL)/*Read the input file line by line*/
    {
            if(line[0]==';') /*line is a comment and won't be included in am file*/
            {
                continue;
            }
            if (strncmp(line, "mcro", 4) == 0)
            {
                /*fprintf(amFile,"----This line was macro name definition----\n"); CHECK IF WORKS*/
                while (fgets(line, sizeof(line), inputFile) != NULL && strncmp(line, "endmcro", 7) != 0)/*Skip macro definitions*/
                {
                    /*fprintf(amFile,"----macro lines----\n"); CHECK IF WORKS*/
                    continue;
                }
            }
            else
            {
                current = head;
                /*printf("line: %s\n",line);*/
                while (current != NULL)
                {
                    if (strncmp(line, current->name, 2) == 0) /*Check if line starts with macro name*/
                    {
                        /*fprintf(amFile, "%s:", current->name);*/
                        fprintf(amFile, "%s", current->lines); /*Print lines of the macro instead macro's name*/
                        macroFound = 1;/*flag is on*/
                        break;
                    }
                    current = current->next;
                }

                /*Current line is a macro name:*/
                if (macroFound)
                {
                    macroFound=0; /*Initialize flag*/
                    continue; /*Move to next line and check it*/
                }

                /*Regular line:*/
                if (!macroFound)
                {
                    /*printf("lo macro: %s",line);*/
                    fprintf(amFile, "%s", line); /*Print line as is*/
                }
            }
    }

    /*Free memory used:*/
    fclose(amFile);
    fclose(inputFile);
    /*printf("Output file '%s' created successfully.\n", amFilename);*/

    return amFile;
}
/*--------------------------------------------------------------------------------------------------------------------*/
MacroNode* createMacroTable(FILE* file)
{
    MacroNode* head = NULL;
    MacroNode* current = NULL;

    char line[MAX_LINE_LENGTH];
    char macroName[MCRO];

    while (fgets(line, sizeof(line), file))/*Read the file line by line*/
    {
        if (strncmp(line, "mcro", 4) == 0) /*Check if the line starts with "mcro"*/
        {
            MacroNode* newNode = (MacroNode*)malloc(sizeof(MacroNode));/*Allocate memory for the MacroNode*/
            if (sscanf(line, "mcro %2s", macroName) == 1) /*Extract the name of the macro from the line*/
            {
                strcpy(newNode->name, macroName);
            }
            newNode->lines[0] = '\0';
            newNode->next = NULL;

            if (head == NULL) /*Add the new node to the linked list*/
            {
                head = newNode;
                current = newNode;
            }
            else
            {
                current->next = newNode;
                current = current->next;
            }

            /*Read the lines of the macro until "endmcro" is encountered*/
            while (fgets(line, sizeof(line), file))
            {
                if (strncmp(line, "endmcro", 7) == 0)
                {
                    break;
                }
                strcat(current->lines, line);

            }
        }
    }

    return head;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void printMacroTable(const MacroNode* head)
{
    const MacroNode* current = head;

    printf("Macro Table:\n");
    printf("----------------------\n");
    while (current != NULL) {
        printf("Macro Name:\n%-10s\nLines:\n%s\n", current->name, current->lines);
        current = current->next;
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void freeMacroTable(MacroNode* head)
{
    MacroNode* current = head;
    MacroNode* next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}
