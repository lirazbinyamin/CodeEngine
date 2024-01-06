#include "code.h"
#include "assembler.h"
/*code file handles machine code:
 * handles word types in assembly and converts them into binary machine code
 */
char entryString[MAX_FILE];
char externString[MAX_FILE];
/*--------------------------------------------------------------------------------------------------------------------*/
void dataMachineCode(int binary, int length)
{
    int mask = 1; /*initialize a mask with the least significant bit set to 1*/
    int i;
    for (i = length - 1; i >= 0; i--)
    {
        mask = 1 << i; /*move the 1 in the mask to the current bit position*/
        if (mask & binary)
            strcat(machineDataString, "1"); /*add 1 if the current bit is 1*/
        else
            strcat(machineDataString, "0"); /*add 0 if the current bit is 0*/
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void opCodeMachineCode(int binary, int length)
{
    int mask = 1; /*initialize a mask with the least significant bit set to 1*/
    int i;
    for (i = length - 1; i >= 0; i--) /*move the 1 in the mask to the current bit position*/
    {
        mask = 1 << i;
        if (mask & binary)
            strcat(machineCodeString, "1");/*add 1 if the current bit is 1*/
        else
            strcat(machineCodeString, "0");/*add 0 if the current bit is 0*/
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void wordMachineCode(int word)
{
        switch(word)
        {
            case firstWord:
                opCodeMachineCode(firstWordCode.src_op, 3);
                opCodeMachineCode(firstWordCode.opcode, 4);
                opCodeMachineCode(firstWordCode.dest_op, 3);
                opCodeMachineCode(firstWordCode.ARE, 2);
                break;
            case registerWord:
                opCodeMachineCode(registerWordCode.src_reg, 5);
                opCodeMachineCode(registerWordCode.dest_reg, 5);
                opCodeMachineCode(registerWordCode.ARE, 2);
                break;
            case infoWord:
                opCodeMachineCode(infoWordCode.num_label, 10);
                opCodeMachineCode(infoWordCode.ARE, 2);
                break;
        }
}
/*--------------------------------------------------------------------------------------------------------------------*/
