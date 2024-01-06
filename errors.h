#include <stdio.h>
/*--------------------------------------------------------------------------------------------------------------------*/
extern int errorFlag;
/*--------------------------------------------------------------------------------------------------------------------*/
/*defined and undefined errors:*/
void undefinedLabel(char label[]);
void undefinedRegister(char registerName[]);
void labelDefined(char label[]);
/*extra errors:*/
void extraText(void);
void extraComma(void);
/*expected errors:*/
void expectedSpace(char command[]);
void expectedNumber(char command[]);
void expectedComma(char command[]);
/*invalid errors:*/
void invalidString(char str[]);
void invalidLabel(char label[]);
/*other errors:*/
void unknownCommand(char command[]);
void fileNotFound(char fileName[]);
void wrongOperand(void);
/*warning:*/
void labelDefinitionMeaningless(char label[]);
