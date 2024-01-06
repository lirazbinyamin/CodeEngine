#include "first_second_pass.h"
#include "utils.h"
#include "assembler.h"
#include "code.h"
#include "symbols.h"
#include "errors.h"
/*first_second_pass file works on the first and second pass of the assembler, using a flag for first pass.
 * in most cases the functions in the file will use a copy to do all checks needed to do
 * (some comments I added were in order to print information while working on the project)*/
/*--------------------------------------------------------------------------------------------------------------------*/
int first_second_passes(char* fileName,int firstPassFlag)
{
    FILE* fileptr = fopen(fileName, "r");
    /*printf("\nPasses started..\n");*/
    char line[MAX_LINE_LENGTH];

    while (fgets(line, sizeof(line), fileptr))
    {
        /*if (firstPassFlag)
            printf("Line %d: %s",lineCounter, line);*/
        checkLine(line,firstPassFlag);
        lineCounter++;
    }
    /*printf("\nfinished passes!!!\n");*/
    return 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void checkLine(char line[],int firstPassFlag)
{
    /*printf("inside checkLine..\n");*/
    char copyLine[MAX_LINE_LENGTH];/*make a copy of the line*/
    int labelLength = 0; /*initialize label length to 0*/
    int labelFlag = 0;/*flag to add label to the symbol table*/
    char label[MAX_LABEL_LENGTH]; /*define label by maximum length of a label - 31 chars*/
    char *copyLinePtr; /*pointer for the copy line*/

    skipWhites(line);/*skip all the white spaces,tabs,lines...*/
    if (line[0] == '\n' || line[0] == ';' || line[0] == '\0')
        return;/*if it is an empty line or a comment, ignore it and go to the next line in the file*/
    strcpy(copyLine, line);

    if (isLabel(copyLine)) /*check for a label definition*/
    {
        strcpy(label, copyLine);
        strtok(label, ":");/*separate label from the rest of the line using ":" */
        labelFlag = 1; /*turn on label flag*/
        /*printf("label is: %s\n", label);*/ /*print the label for check*/

        if (firstPassFlag && isSymbol(label))/*check if there's already a symbol defined*/
        {
            labelDefined(label);
            return;
        }
        /*printf("label wasn't defined- good\n");*/

        if (!validLabel(label)) /*check if the label is not valid*/
        {
            invalidLabel(label);
            return;
        }
        /*printf("label was valid- good\n");*/

        labelLength = strlen(label) + 1;/*Check passed, set the length of the label*/

        /*printf("label length: %d\n",labelLength-1);*/
    }

    if (firstPassFlag == 0) /*if this is the second pass no need to add label*/
    {
        labelFlag = 0;
    }

    strcpy(copyLine, line + labelLength);/*insert to copy line the rest of the line after label*/

    line += labelLength; /*move to the rest of line after label*/
    /*printf("line first char after label is '%c' \n",line[0]);*/

    /*check if there's a space between label definition to rest of the line*/
    if (labelFlag && line[0] != ' ' && line[0] != '\t')
    {
        expectedSpace(line);
        return;
    }
    /*printf("there is a space after label- good\n");*/

    /*set the pointer for copy line*/
    copyLinePtr = copyLine;
    /*printf("before- copylineptr points to '%c'\n ",*copyLine);*/

    while (isspace(*copyLinePtr)) /*move pointers forward to the next word in the line and the copy line*/
    {
        copyLinePtr++;
    }
    strtok(copyLinePtr, " \t\n");

    /*printf("after white-copylineptr is %s\n ",copyLine);*/

    checkCommand(copyLinePtr,labelFlag,label,copyLine); /*check for commands in line*/

    /*printf("done with line\n");*/
}
/*--------------------------------------------------------------------------------------------------------------------*/
void checkCommand(char* copyPtr,int labelFlag,char label[], char copy[])
{
    /*printf("inside checkCommand...\n");*/
    /*A label defined in instruction row gets the value of instruction counter,
     * so if there's a labelFlag the type will be command*/
    /*commands with 2 operands:*/
    if (!strcmp(copyPtr, "mov"))
    {
        /*printf("command is mov\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = MOV;
        if (firstPassFlag)/*if it's the first scan count to the instruction counter*/
            ic++;
        else /*if it's the second scan count instructions+data the external label file*/
            exC++;
        /*printf("finished checkCommand..starting analyze operands\n");*/
        twoOperands(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "cmp"))
    {
        /*printf("command is cmp\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = CMP;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operands\n");*/
        twoOperands(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "add"))
    {
        /*printf("command is add\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = ADD;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operands\n");*/
        twoOperands(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "sub"))
    {
        /*printf("command is sub\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = SUB;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operands\n");*/
        twoOperands(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "lea"))
    {
        /*printf("command is lea\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = LEA;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operands\n");*/
        twoOperands(copyPtr + 4);

        /*commands with 1 operand*/
    }
    else if (!strcmp(copyPtr, "not"))
    {
        /*printf("command is not\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = NOT;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "clr"))
    {
        /*printf("command is clr\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = CLR;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "inc"))
    {
        /*printf("command is inc\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = INC;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "dec"))
    {
        /*printf("command is dec\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = DEC;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "jmp"))
    {
        /*printf("command is jmp\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = JMP;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "bne"))
    {
        /*printf("command is bne\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = BNE;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "red"))
    {
        /*printf("command is red\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = RED;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "prn"))
    {
        /*printf("command is prn\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = PRN;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);
    }
    else if (!strcmp(copyPtr, "jsr"))
    {
        /*printf("command is jsr\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = JSR;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        oneOperand(copyPtr + 4);

        /*commands with no operands*/
    }
    else if (!strcmp(copyPtr, "rts"))
    {
        /*printf("command is rts\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = RTS;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze\n");*/
        noOperands(copyPtr + 5);
    }
    else if (!strcmp(copyPtr, "stop"))
    {
        /*printf("command is stop\n");*/
        if (labelFlag)
            addSymbol(label, command, internal);
        firstWordCode.opcode = STOP;
        if (firstPassFlag)
            ic++;
        else
            exC++;
        /*printf("finished check..starting analyze operand\n");*/
        noOperands(copyPtr + 5);
    }


    else /*check for other definition*/
    {
        /*A label defined as .data/.string gets the value of data counter,
        *so if there's a labelFlag the type will be command*/
        /*case data*/
        if (!strcmp(copyPtr, ".data"))
        {
            /*printf(".data definition\n");*/
            if (labelFlag)
                addSymbol(label, data, internal); /*data label gets current data counter*/
            /*printf("finished check..starting analyze\n");*/
            dataCheck(copyPtr + 6);
        }
        /*case string*/
        else if (!strcmp(copyPtr, ".string"))
        {
            /*printf(".string definition\n");*/
            if (labelFlag)
                addSymbol(label, data, internal); /*string gets current data counter*/
            /*printf("finished check..starting analyze\n");*/
            stringCheck(copyPtr + 8);
        }

        /*A label defined as .entry/.extern is meaningless,
         *so if there's a labelFlag the assembler will print a warning.*/

        /*case entry*/
        else if (!strcmp(copyPtr, ".entry"))
        {
            /*printf(".entry definition\n");*/
            if (labelFlag)
                labelDefinitionMeaningless(label);
            /*printf("finished check..starting analyze\n");*/
            entryCheck(copyPtr + 7);
        }
        /*case extern*/
        else if (!strcmp(copyPtr, ".extern"))
        {
            /*printf(".extern definition\n");*/
            if (labelFlag)
                labelDefinitionMeaningless(label);
            /*printf("finished check..starting analyze\n");*/
            externCheck(copyPtr + 8);
        }

        /*all checks are done and didn't find anything*/
        else
        {
            unknownCommand(copy);
        }
    }

}
/*--------------------------------------------------------------------------------------------------------------------*/
void setOperand(char *command, char *ptr, char *operand, int operandType)
{
    /*printf("inside setOperand...\n");*/
    char copy[MAX_LINE_LENGTH]; /*make a copy of the line to use it*/
    strcpy(copy, command);
    ptr = copy;
    skipWhites(ptr);/*skip all of white spaces/tabs until first char*/
    strtok(copy, " \t\n");
    if (ptr[0] == ',')/*No need to be a comma before operand*/
    {
        extraComma();
        return;
    }

    strcpy(operand, ptr);
    strtok(operand,"\t ,");
    /*printf("operand= '%s'\n",operand);*/

    if (operand[0] == '@') /*check for a register operand, first char should be '@'*/
    {
        if (!validRegister(operand)) /*check for invalid register*/
        {
            undefinedRegister(operand); /*returns error*/
            return;
        }
        /*check for operand type: source/register*/
        if (operandType == source)
        {
            /*printf("src reg.\n");*/
            firstWordCode.src_op = REGISTER;
        }
        else if (operandType == destination)
        {
            /*printf("dest reg.\n");*/
            firstWordCode.dest_op = REGISTER;
        }
    }
    else
    {
        /*printf("not register...\n");*/
        if (isLetter(operand[0])) /*check for a label operand*/
        {
            if (!validLabel(operand)) /*check for invalid label*/
            {
                return;
            }
            /*check for operand type: source/register*/
            if (operandType == source)
                firstWordCode.src_op = LABEL;
            else if (operandType == destination)
                firstWordCode.dest_op = LABEL;
            /*printf("we got a label!\n");*/
        }
        else
        {
            if (!validNumber(operand)) /*check for invalid number*/
            {
                return;
            }
            /*check for operand type: source/register*/
            else if (operandType == source)
                firstWordCode.src_op = NUM;
            else if (operandType == destination)
                firstWordCode.dest_op = NUM;
            /*printf("we got a number! \n");*/
        }
    }
    /*printf("done.. outside setOperand..\n");*/
}
/*--------------------------------------------------------------------------------------------------------------------*/
void twoOperands(char command[])
{
    /*printf("inside twoOperands...\n");*/
    char copy[MAX_LINE_LENGTH]; /* Create a copy of the command for manipulation*/
    char *p1, *p2; /*Pointers to iterate through the copy of the command string*/
    char op1[MAX_LABEL_LENGTH]; /*Buffer to store the 1st operand*/
    char op2[MAX_LABEL_LENGTH]; /*Buffer to store the 2nd operand*/

    skipWhites(command); /*skip all of white spaces/tabs*/
    strcpy(copy, command);
    p1 = copy;
    /*printf("p1 before setOperand= %s\n",p1);*/

    setOperand(copy, p1, op1, source);/*set 1st operand*/

    p1 = copy+ strlen(op1);
    skipWhites(p1);
    /*printf("p1 after setOperand= %s\n",p1);*/

    if (p1[0] != ',')/*between 2 operands should be a comma*/
    {
        expectedComma(command);
        return;
    }
    /*printf("great there is a comma!\n");*/
    p1++;
    skipWhites(p1);/*skip all of white spaces/tabs*/
    p2 = p1;
    p1= p2;
    /*printf("p2= '%s' \n",p2);*/

    setOperand(p2, p2, op2, destination);/*set 2nd operand*/

    p1 += strlen(op2);/*move pointer to the end of the 2nd operand to check if there's extra text after it*/
    skipWhites(p1);
    if (*p1 == '\n')
        p1++;
    if (*p1)
    {
        extraText(); /*return error*/
        return;
    }
    firstWordCode.ARE = ABSOLUTE;
    /*printf("done with 2 operands, go to machinecode...\n");*/

    twoOpsMachineCode(op1, op2);/*write in machine code the word*/
}
/*--------------------------------------------------------------------------------------------------------------------*/
void oneOperand(char command[])
{
    /*printf("inside oneOperand...\n");*/
    char copy[MAX_LINE_LENGTH];
    char *ptr;
    char operand[MAX_LABEL_LENGTH];
    char addExternalLabels[MAX_LINE_LENGTH];

    skipWhites(command); /*skip all of white spaces/tabs*/
    strcpy(copy, command);
    ptr = copy;
    if (*ptr == '\n' || *ptr == '\0')
    {
        wrongOperand();
        return;
    }
    firstWordCode.src_op = 0;/*no source operand*/

    setOperand(copy, ptr, operand, destination); /*set operand to type destination (only one operand)*/

    ptr = copy + strlen(operand); /*move pointer to the end of the operand to check if there's extra text after it*/
    skipWhites(ptr); /*skip all of white spaces/tabs*/
    if (*ptr != '\n' && *ptr != '\0')
    {
        extraText();
        return;
    }

    if (isLetter(operand[0])) /*if operand is a label*/
    {
        if (!firstPassFlag)
        {
            if (!isSymbol(operand)) /*if it's the second scan symbol didn't find, it was not defined*/
            {
                undefinedLabel(operand);
                return;
            }
        }

        infoWordCode.num_label = getSymbolAddress(operand); /*insert the address of the operand to the word code*/
        if(getSymbolLocation(operand) == external) /*check for external*/
        {
            infoWordCode.ARE = EXTERNAL;
            if(!firstPassFlag)
            {
                sprintf(addExternalLabels, "%s\t%d\n", operand, exC); /*Prepare the labels to add*/
                strcat(externString, addExternalLabels); /*add labels to externString*/

            }
        }
        else
            infoWordCode.ARE = RELOCATABLE;
    }

    else if (validNumber(operand) && firstWordCode.opcode!=PRN) /*only prn can have a number dest operand*/
    {
        wrongOperand();
        return;
    }

    else if (validNumber(operand))/*if operand is a number*/
    {
        infoWordCode.num_label = atoi(operand); /*change the operand from str to int representation*/
        infoWordCode.ARE = ABSOLUTE;
    }
    else  /*if operand is a register*/
    {
        infoWordCode.num_label = convertToDigit(operand[2]); /*the third char in the register is a number*/
        infoWordCode.ARE = ABSOLUTE;
    }

    if(!firstPassFlag)
        exC++;
    if (firstPassFlag) /*case first pass*/
        ic++;
    else /*case second pass -write words in machine code*/
    {
        wordMachineCode(firstWord);
        wordMachineCode(infoWord);
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void noOperands(char command[])
{
    /*printf("inside noOperands...\n");*/
    char *ptr = command;
    skipWhites(ptr);
    if (*ptr != '\n' && *ptr != '\0') /*check that there is no extra text after the command*/
    {
        extraText();
        return;
    }

    if(!firstPassFlag)
    {
        firstWordCode.ARE = ABSOLUTE;
        firstWordCode.src_op = 0;/*no operands*/
        firstWordCode.dest_op = 0;/*no operands*/
        wordMachineCode(firstWord);
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void twoOpsMachineCode(char *op1, char *op2)
{
    /*printf("inside twoOpsMachineCode...\n");*/
    char addExternalLabels[MAX_LINE_LENGTH];
    if(!firstPassFlag)
        wordMachineCode(firstWord); /*write the first word in machine code*/

    if (firstWordCode.dest_op != LABEL && firstWordCode.opcode == LEA) /*source of lea cannot be a label*/
    {
        wrongOperand();/*returns error */
        return;
    }
    if (firstWordCode.src_op == REGISTER) /*source operand is a register*/
    {
        if(firstPassFlag)
            ic++;
        else
            exC++;

        registerWordCode.src_reg = convertToDigit(op1[2]);/*convert the num of the register located in the 3rd char*/
        registerWordCode.dest_reg = 0;
        registerWordCode.ARE = ABSOLUTE;

        if (firstWordCode.dest_op != REGISTER)
            if (!firstPassFlag)
                wordMachineCode(registerWord);/*write a machine code of a word with source register only*/
    }
    else if (firstWordCode.src_op == NUM) /*source operand is a num*/
    {
        if (firstPassFlag)
            ic++;
        else
            exC++;

        infoWordCode.num_label = (unsigned) atoi(op1); /*convert number from str to int*/
        infoWordCode.ARE = ABSOLUTE;
        if (!firstPassFlag)
            wordMachineCode(infoWord);
    }
    else if (firstWordCode.src_op == LABEL) /* source operand is a label*/
    {
        if (firstPassFlag)
            ic++;
        if (!firstPassFlag)
        {
            if (!isSymbol(op1)) /*check is symbol is found in symbol table*/
            {
                undefinedLabel(op1); /*in second pass label should be defined already*/
                return;
            }
        }
        infoWordCode.num_label = getSymbolAddress(op1); /*find symbol address*/
        if(getSymbolLocation(op1) == external)
        {
            infoWordCode.ARE = EXTERNAL;
            if(!firstPassFlag)
            {
                sprintf(addExternalLabels, "%s\t%d\n", op1, exC); /*Prepare the labels to add*/
                strcat(externString, addExternalLabels); /*Concatenate the string with externString to accumulate external symbol*/
            }
        }
        else
            infoWordCode.ARE = RELOCATABLE;
        if (!firstPassFlag)
        {
            wordMachineCode(infoWord);
        }

        if(!firstPassFlag)
            exC++;
    }

    if (firstWordCode.dest_op == REGISTER)
    {
        if (firstWordCode.src_op != REGISTER) /*source operand isn't a register*/
        {
            if (firstPassFlag)
                ic++;
            else
                exC++;
            registerWordCode.src_reg = 0;
        }
        /*source operand is a register*/
        registerWordCode.dest_reg = convertToDigit(op2[2]); /*convert to the digit the third char (reg number)*/
        registerWordCode.ARE = ABSOLUTE;
        if (!firstPassFlag)
            wordMachineCode(registerWord);
    }
    if (firstWordCode.dest_op == NUM) /*destination operand is a number*/
    {
        if(firstWordCode.opcode !=CMP)/*destination cannot be a number only if it's cmp*/
        {
            wrongOperand();/*returns error*/
            return;
        }

        infoWordCode.num_label = (unsigned ) atoi(op2); /*convert the number from str to int*/
        infoWordCode.ARE = ABSOLUTE;
        if(!firstPassFlag)
            wordMachineCode(infoWord);
    }
    else if (firstWordCode.dest_op == LABEL) /*destination operand is a label*/
    {
        if (firstPassFlag)
            ic++;

        if (!firstPassFlag)
        {
            if (!isSymbol(op2)) /*check is symbol is found in symbol table*/
            {
                undefinedLabel(op2); /*symbol should be defined already*/
                return;
            }
        }
        infoWordCode.num_label = getSymbolAddress(op2);
        if(getSymbolLocation(op1) == external)
        {
            infoWordCode.ARE = EXTERNAL;
            if(!firstPassFlag)
            {
                sprintf(addExternalLabels, "%s\t%d\n", op1, exC);
                strcat(externString, addExternalLabels);
            }
        }
        else
            infoWordCode.ARE = RELOCATABLE;
        if (!firstPassFlag)
            wordMachineCode(infoWord);

        if(!firstPassFlag)
            exC++;
    }

}
/*--------------------------------------------------------------------------------------------------------------------*/
void dataCheck(char command[])
{
    char copy[MAX_LINE_LENGTH]; /* Create a copy of the command for manipulation*/
    int num; /* Variable to store the number*/
    int commaFlag = 0; /* Flag to indicate if a comma is expected after a number */
    int numFlag = 1; /* Flag to indicate if a number is expected next */
    char *ptr; /* Pointer to iterate through the copy of the command string */
    char *ptrCommand = command; /* Pointer to iterate through the original command string */
    strcpy(copy, command); /* Make a copy of the command string */
    ptr = copy;

    while (*ptr)
    {
        skipWhites(ptr);
        skipWhites(ptrCommand);

        strtok(ptr, " \t,"); /* Tokenize the copy*/

        if (ptr[0] == '\n')
            return; /* reached the end of the line, exit the loop */

        if (commaFlag && ptr[0] != ',')
        {
            expectedComma(command); /*return error*/
            return;
        }

        if (numFlag && (!isDigit(ptr[0]) && ptr[0] != '+' && ptr[0] != '-'))
        {
            expectedNumber(command); /*return error*/
            return;
        }

        if (commaFlag)
        {
            commaFlag = 0; /* Reset the commaFlag as found the expected comma */
            numFlag = 1; /* Set the numFlag to indicate that the next token should be a number */
            ptr++;
            ptrCommand++; /* Move the pointers to the next character */
        }
        else if (numFlag)
        {

            numFlag = 0; /* Reset the numFlag as we found the expected number */
            commaFlag = 1; /* Set the commaFlag to indicate that the next token should be a comma */
            num = atoi(ptr); /* Convert the token (number) to an integer using the atoi function */

            if (!firstPassFlag)
            {
                dataMachineCode(num, 12);/*add data to the output */
            }

            ptrCommand += strlen(ptr); /* Move the pointer in the original command string past the processed data */
            strcpy(copy, ptrCommand); /* Copy the remaining part of the command string to the copy for further processing */
            ptr = copy; /* Reset the pointer to the beginning of the copy for the next iteration */

            if (firstPassFlag)
                dc++; /*increase the data counter */
        }
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/
void stringCheck(char command[])
{
    /*printf("inside stringCheck...\n");*/
    char copy[MAX_LINE_LENGTH]; /* Create a copy of the command for manipulation*/
    char string[MAX_LABEL_LENGTH]; /* Variable to store the string*/
    char *ptr; /* Pointer to iterate through the copy of the command string */
    char *ptrCommand; /* Pointer to iterate through the original command string */
    strcpy(copy, command); /* Make a copy of the command string */
    ptr = copy;

    /*skip white characters in all*/
    skipWhites(ptr);
    skipWhites(copy);
    skipWhites(command);

    if(!extractString(ptr,string)) /*didn't succeed to extract string to the storage variable*/
        return;


    ptrCommand= command+ strlen(string); /*move pointer to the end of the string*/
    skipWhites(ptrCommand);/*skip whites*/


    if(*ptrCommand != '\0' && *ptrCommand != '\n' ) /*there is extra text after end of string*/
    {
        extraText();/*return error*/
        return;
    }

    ptr = string+1; /*move pointer to after the double quote - means beginning of string*/
    if(firstPassFlag)
    {
        while (*(ptr + 1)) /*move pointer until the end double quote*/
        {
            dataMachineCode((unsigned int) *ptr,12);/*Add the ascii code of the character to the machine code*/
            ptr++;
        }

        dataMachineCode(0, 12);
        dc += strlen(string)-1;/*increase data counter by string length (add null char - double quote [+1-2=-1])*/
    }

}
/*--------------------------------------------------------------------------------------------------------------------*/
void entryCheck(char command[])
{
    char copy[MAX_LINE_LENGTH]; /* Create a copy of the command for manipulation*/
    char *ptr; /* Pointer to iterate through the copy of the command string */
    char label[MAX_LABEL_LENGTH]; /* Variable to store the label*/
    char addEntryLabels[MAX_LINE_LENGTH]; /* Variable to store entry*/

    strcpy(copy, command); /* Make a copy of the content */
    ptr = copy; /*set pointer to copy*/

    /*skip white characters in all*/
    skipWhites(ptr);
    skipWhites(copy);
    skipWhites(command);

    strtok(ptr, " \t\n"); /* Tokenize the copy */
    strcpy(label,ptr); /*copy content to label*/

    if(!firstPassFlag)
    {
        if(!isSymbol(label)) /*the label wasn't defined in first pass*/
        {
            undefinedLabel(label);/*return error*/
            return;
        }
        if(getSymbolLocation(label) == external) /*the label is external and not entry*/
        {
            labelDefined(label);/*return error*/
            return;
        }
    }

    ptr= command+ strlen(ptr); /*move pointer to after label*/
    skipWhites(ptr);

    if(*ptr != '\0' && *ptr != '\n' ) /*there is extra text after end of string*/
    {
        extraText();/*return error*/
        return;
    }

    if(!firstPassFlag)
    {
        sprintf(addEntryLabels,"%s\t%d\n",label,getSymbolAddress(label)); /*Prepare the labels to add*/
        strcat(entryString,addEntryLabels);/*Concatenate the string with entryString to accumulate entry symbol*/
    }

}
/*--------------------------------------------------------------------------------------------------------------------*/
void externCheck(char command[])
{
    char copy[MAX_LINE_LENGTH]; /* Create a copy of the command for manipulation*/
    char *ptr; /* Pointer to iterate through the copy of the command string */
    char label[MAX_LABEL_LENGTH]; /* Variable to store the label*/
    strcpy(copy, command);
    ptr = copy;

    /*skip white characters in all*/
    skipWhites(ptr);
    skipWhites(copy);
    skipWhites(command);

    strtok(ptr, " \t\n"); /* Tokenize the copy */
    strcpy(label,ptr); /*copy content to label*/
    ptr= command+ strlen(ptr); /*move pointer to after label*/
    skipWhites(ptr);

    if(*ptr != '\0' && *ptr != '\n' ) /*there is extra text after end of string*/
    {
        extraText();/*return error*/
        return;
    }

    if (firstPassFlag && validLabel(label)) /*label definition valid*/
    {
        if(!isSymbol(label))/*label wasn't define before*/
            addSymbol(label,data,external);
        else
            labelDefined(label); /*return error*/
    }
}

