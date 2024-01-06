#include "assembler.h"
int lineCounter;/*Line Counter*/
int dc;/*Data Counter*/
int ic;/*Instructions Counter - we assume that first instruction from the assembly file will be from address 100*/
int exC;/*External counter*/
int errorFlag;/*if the error flag turns on there is no need for a second scan, and no need to write a machine code*/
char fileName[MAX_FILE_NAME];
