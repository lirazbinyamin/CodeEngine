#include <stdlib.h>
#include <stdio.h>
#include "pre_assembler.h"
#include "first_second_pass.h"
#include "assembler.h"
#include "utils.h"
#include "code.h"
#include "symbols.h"
#include "errors.h"
#include "create_files.h"
/*--------------------------------------------------------------------------------------------------------------------*/
/*Project goal: Build an assembler for an assembly language provided in MAMAN 14.
 *
 * This program gets an '.as' file -> scan it for macros and spread them -> create an '.am' file with macros spread ->
 * -> scan file (first&second passes) to realize commands and data from assembly and check for any errors ->
 * -> convert all the content to binary machine code -> create output files for content.
 *
 * Author: Liraz Binyamin*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*strings that will contain binary code of operations and data*/
char machineCodeString[MAX_FILE];
char machineDataString[MAX_FILE];
int firstPassFlag=1;/*set a first pass flag turned on*/
/*--------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    int i;
    FILE* fileptr;

    /*Check if the correct number of command line arguments is provided*/
    if (argc < 2)
    {
        printf("Usage: ./assembler filename\n");
        exit(EXIT_FAILURE);
    }

    for (i= 1; i < argc; i++)
    {
        restart();
        /*Copy provided filename from command line argument into the filename*/
        strcpy(fileName, argv[i]);
        /*Concatenate the ".as" extension to the filename*/
        strcat(fileName, ".as");

        fileptr= fopen(fileName, "r"); /*open the file*/

        /*Check if file opening was successful*/
        if (fileptr == NULL)
        {
            fileNotFound(fileName);
        }
        printf("\nChecking file: %s ...\n",fileName);
        /*start file check*/
        checkFile(fileName,fileptr);
        fclose(fileptr);
    }
    return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void checkFile(char* fileName, FILE* fileptr)
{
    int pass; /*number of passes to do on file*/

    if(!preAssembler(fileName,fileptr))
    {
        printf("ERROR: problem in pre assembler!\n");
        return;
    }

    for(pass=0;pass<2;pass++) /*a loop that runs 2 passes on file*/
    {
        if (!first_second_passes(fileName, firstPassFlag)) /*check for first pass*/
        {
            printf("ERROR: problem in first pass!\n");
            return;
        }

        if (firstPassFlag)
        {
            updateSymbolAddress(); /*after done with the first pass need to update symbols addresses*/
        }

        firstPassFlag = 0;/*turn first pass flag off - move to the second pass*/
        lineCounter=1; /*reset line counter*/

        if (errorFlag) /*if there's an error in first pass no need to do second pass and create output files*/
        {
            printf("ERROR:errors found in input file! No need to create output files..\n");
            return;
        }
    }
    
    /*printSymbolTable(&symbols);*/
    /*printf("\n--------------entry:-------------\n%s\n",entryString);*/
    /*printf("\n--------------extern:-------------\n%s\n",externString);*/

    if(!errorFlag)
    {
        createOutputFiles();
        printf("Done file check. file OK!\n");
    }
    
}
/*--------------------------------------------------------------------------------------------------------------------*/
void restart()
{
    /*printf("inside restart...\n");*/

    /*reset counters and flags*/
    firstPassFlag=1;
    errorFlag=0;
    lineCounter=1;/*starts from row 1*/
    dc=0;/*data counter*/
    ic=100;/*instruction counter,we assume address starts from 100*/
    exC=100;/*counted in the second pass, to find address for externals*/

    /*reset all structure definitions */
    firstWordCode.ARE = 0;
    firstWordCode.dest_op = 0;
    firstWordCode.opcode = 0;
    firstWordCode.src_op = 0;
    registerWordCode.src_reg = 0;
    registerWordCode.dest_reg = 0;
    registerWordCode.ARE = 0;
    infoWordCode.ARE = 0;
    infoWordCode.num_label = 0;

    /*reset all storage strings*/
    strcpy(objBase64,"");
    strcpy(machineDataString,"");
    strcpy(machineCodeString,"");
    strcpy(objBinary,"");
    strcpy(externString,"");
    strcpy(entryString,"");

    freeSymbolTable(&symbols);
}
