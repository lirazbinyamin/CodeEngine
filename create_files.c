#include <string.h>
#include "create_files.h"
#include "assembler.h"
#include "utils.h"
#include "errors.h"
/*--------------------------------------------------------------------------------------------------------------------*/
/*create_files creates all output files needed to be created after the second pass:
 * object file
 * entry file
 * extern file*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*the machine code that contains both code and data in binary*/
char objBinary[MAX_FILE];
/*the final machine code that contains everything in base64*/
char objBase64[MAX_FILE];
/*--------------------------------------------------------------------------------------------------------------------*/
void createOutputFiles(void)
{
    /*printf("Starting files creation...\n");*/
    char externFileName[MAX_FILE_NAME];
    char entryFileName[MAX_FILE_NAME];
    char objectFileName[MAX_FILE_NAME];

    strcat(objBinary,machineCodeString);
    strcat(objBinary,machineDataString);
    /*printBinaryLines(objBinary, 12);*//*print machine code file in lines*/

    /*Copy provided filename from command line argument into the filename*/
    strcpy(externFileName,fileName);
    strcpy(entryFileName,fileName);
    strcpy(objectFileName,fileName);

    writeFile(objectFileName,OBJECT);
    if (entryString[0] != '\0') /*create entry file only if were .entry definitions in the .am file*/
        writeFile(entryFileName,ENTRIES);
    if (externString[0] != '\0') /*create extern file only if were .extern definitions in the .am file*/
        writeFile(externFileName,EXTERNALS);

    /*printf("done files creation...\n");*/

}
/*--------------------------------------------------------------------------------------------------------------------*/
void writeFile(char* inputFilename,int type)
{

    FILE* filePtr;
    int i;
    int length;

    /*printf("\nfilename before= %s\n",inputFilename);*/

    filePtr = fopen(inputFilename, "r");/*Open the input file for reading*/
    if (filePtr==NULL)
        fileNotFound(inputFilename);

    if (type==OBJECT)
        changeExtension(inputFilename, "ob");
    else if (type==ENTRIES)
        changeExtension(inputFilename,"ent");
    else if (type==EXTERNALS)
        changeExtension(inputFilename,"ext");

    /*printf("filename after= %s\n",inputFilename);*/

    filePtr = fopen(inputFilename, "w");/*Open an output file with the new extension for writing*/
    if(filePtr==NULL)
        fileNotFound(inputFilename);

    if (type==ENTRIES)
    {
        fprintf(filePtr,"%s",entryString);
        if(filePtr)
            fclose(filePtr);
    }
    else if (type==EXTERNALS)
    {
        fprintf(filePtr,"%s",externString);
        if(filePtr)
            fclose(filePtr);
    }
    else if (type==OBJECT)
    {
        base64(objBinary);
        length= strlen(objBase64);

        fprintf(filePtr,"%d %d\n",ic-100,dc); /*minus the 100 we added before*/

        for (i = 0; i < length; i += 2)
        {
            fprintf(filePtr,"%.2s\n", objBase64 + i);
        }

    }
}
/*--------------------------------------------------------------------------------------------------------------------*/

