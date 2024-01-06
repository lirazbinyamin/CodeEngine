#include <string.h>
#include "errors.h"
#include "assembler.h"
#include "first_second_pass.h"
/*errors file create functions of errors that prints an error message,
 *and indicate with an errorFlag not to create the files in second pass*/
/*--------------------------------------------------------------------------------------------------------------------*/
/*defined and undefined errors:*/
/*--------------------------------------------------------------------------------------------------------------------*/
void undefinedLabel(char label[])
{
    printf("\nFile: %s: line: %d:error: Label '%s' is undefined\n",fileName,lineCounter,label);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void undefinedRegister(char registerName[])
{
    strtok(registerName,"\n");
    printf("\nFile: %s: line: %d:error: register name undefined: '%s'\n",fileName,lineCounter,registerName);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void labelDefined(char label[])
{
    printf("\nFile: %s: line: %d:error: label: '%s' already defined\n",fileName,lineCounter,label);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*extra errors:*/
/*--------------------------------------------------------------------------------------------------------------------*/
void extraText(void)
{
    printf("\nFile: %s: line: %d:error: extra text\n",fileName,lineCounter);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void extraComma(void)
{
    printf("\nFile: %s: line: %d:error: extra comma\n",fileName,lineCounter);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*expected errors:*/
/*--------------------------------------------------------------------------------------------------------------------*/
void expectedSpace(char command[])
{
    strtok(command,"\n");
    printf("\nFile: %s: line: %d:error: expected space after label '%s'\n",fileName,lineCounter,command);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void expectedNumber(char command[]){
    printf("\nFile: %s: line: %d:error: expected number: '%s'\n",fileName,lineCounter,command);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void expectedComma(char command[])
{
    strtok(command,"\n");
    printf("\nFile: %s: line: %d:error: expected comma after: '%s'\n",fileName,lineCounter,command);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*invalid errors:*/
/*--------------------------------------------------------------------------------------------------------------------*/
void invalidString(char str[])
{
    printf("\nFile: %s: line: %d:error: invalid string: ' %s 'clea\n",fileName,lineCounter,str);
    errorFlag = 1;
}
void invalidLabel(char label[])
{
    printf("\nFile: %s: line: %d:error: label '%s' is invalid\n",fileName,lineCounter,label);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
/*other errors:*/
/*--------------------------------------------------------------------------------------------------------------------*/
void unknownCommand(char command[])
{
    printf("\nFile: %s: line: %d:error: unknown command: '%s'\n",fileName,lineCounter,command);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void fileNotFound(char fileName[])
{
    printf("\nFile %s Not Found!\n",fileName);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void wrongOperand(void)
{
    printf("\nFile: %s: line: %d:error: wrong operand \n",fileName,lineCounter);
    errorFlag = 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void labelDefinitionMeaningless(char label[])
{
    printf("\nFile: %s: line: %d:WARNING: label definition is meaningless: '%s'\n",fileName,lineCounter,label);

}
