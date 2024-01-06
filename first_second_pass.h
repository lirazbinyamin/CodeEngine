#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/*--------------------------------------------------------------------------------------------------------------------*/
extern int lineCounter;
extern int firstPassFlag;
extern int ic,dc;
extern char entryString[];
extern char externString[];
extern int exC;
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that call all the process of the first pass and returns 1 if completed successfully*/
int first_second_passes(char* fileName, int firstPassFlag);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to read and analyze each line in file*/
void checkLine(char line[],int firstPassFlag);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check command by the first word, trying to find
 * which opcode/definition(entry/data/extern/string/unknown) the command is*/
void checkCommand(char* copyPtr,int labelFlag,char label[], char copy[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to set each operand in line by its type and find errors*/
void setOperand(char *command, char *ptr, char *operand, int operandType);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to handle two operands instruction group and check for errors*/
void twoOperands(char command[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to handle ome operand instruction group and check for errors*/
void oneOperand(char command[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to handle no operands instruction group and check for errors*/
void noOperands(char command[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to write two operands instruction word in machine code as defined in the project*/
void twoOpsMachineCode(char *op1, char *op2) ;
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check data,write in machine code and check for errors*/
void dataCheck(char command[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check string,write in machine code and check for errors*/
void stringCheck(char command[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check entry,add it to entryString(storage) and check for errors*/
void entryCheck(char command[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check extern,add it to extern symbols and check for errors*/
void externCheck(char command[]);
/*--------------------------------------------------------------------------------------------------------------------*/




