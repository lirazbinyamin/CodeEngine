/*Defines 3 types of file:*/
#define OBJECT 0
#define ENTRIES 1
#define EXTERNALS 2
/*--------------------------------------------------------------------------------------------------------------------*/
extern char machineCodeString[];
extern char machineDataString[];
extern int ic,dc;
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that creates name for the output file and checks if needed to create the .ext and .entry files*
 * calls to a function to write the output files */
void createOutputFiles(void);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function the gets a name of file and output type(object/entry/external) and write the file with by type settings
 * entry and external files - include their symbols and addresses
 * object file - title is: ic and dc as title, and the rest is the assembler binary code in base64*/
void writeFile(char* inputFilename,int type);
/*--------------------------------------------------------------------------------------------------------------------*/
