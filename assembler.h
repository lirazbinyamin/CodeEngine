/*length of a file name and a line in source file is 80 maximum*/
#define MAX_FILE_NAME 80
#define MAX_LINE_LENGTH 82
#define MAX_LABEL_LENGTH 31
#define MAX_FILE 20000
#include <stdio.h>
/*--------------------------------------------------------------------------------------------------------------------*/
extern int lineCounter;
extern int firstPassFlag;
extern int ic,dc;
extern char fileName[MAX_FILE_NAME];
/*strings for ext and ent files*/
extern char entryString[];
extern char externString[];
extern int exC;
/*--------------------------------------------------------------------------------------------------------------------*/
enum variableType{source,destination};
/*--------------------------------------------------------------------------------------------------------------------*/
/*A Function to check file from input*/
void checkFile(char* filename,FILE* fileptr);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to reset all program*/
void restart(void);
