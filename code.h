#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*--------------------------------------------------------------------------------------------------------------------*/
/*Defines operation names and their codes*/
#define MOV 0
#define CMP 1
#define ADD 2
#define SUB 3
#define NOT 4
#define CLR 5
#define LEA 6
#define INC 7
#define DEC 8
#define JMP 9
#define BNE 10
#define RED 11
#define PRN 12
#define JSR 13
#define RTS 14
#define STOP 15
/*--------------------------------------------------------------------------------------------------------------------*/
/*Defines addressing modes for operands: immediate(number) / direct(label) / register*/
#define NUM 1
#define LABEL 3
#define REGISTER 5
/*--------------------------------------------------------------------------------------------------------------------*/
/*Defines 3 types of code - A,R,E:*/
#define ABSOLUTE 0
#define RELOCATABLE 2
#define EXTERNAL 1
/*--------------------------------------------------------------------------------------------------------------------*/
extern int dc, ic;
extern char machineCodeString[];
extern char machineDataString[];
extern char objBinary[];
extern char objBase64[];
extern int exC;
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that converts the binary representation of the data into a string and add it to the machineDataString.*/
void dataMachineCode(int binary, int length);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that converts the binary representation of the opcode into a string and add it to the machineCodeString.*/
void opCodeMachineCode(int binary, int length);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that handles different cases of words and add their binary representation to the machineCodeString.*/
void wordMachineCode(int word);
/*--------------------------------------------------------------------------------------------------------------------*/
enum codeType{firstWord,registerWord,infoWord};
/*--------------------------------------------------------------------------------------------------------------------*/
/*Defines the first word in the machine instruction by num of bits represents each info:
 * source operand (2 bits) + opcode (4 bits) + destination operand (2 bits) + ARE (2 bits)*/
struct first_word{
    unsigned int src_op: 3;
    unsigned int opcode: 4;
    unsigned int dest_op: 3;
    unsigned int ARE: 2;
}firstWordCode;
/*--------------------------------------------------------------------------------------------------------------------*/
/*Defines a register word - source register (5 bits) + destination register (5 bits) + ARE (2 bits)*/
struct reg_word{
    unsigned int src_reg: 5;
    unsigned int dest_reg: 5;
    unsigned int ARE: 2;
}registerWordCode;
/*--------------------------------------------------------------------------------------------------------------------*/
/*Defines an info word - which can represent 2 addressing modes:
 * 1- Immediate mode - operand is a number (10 bits) + ARE (2 bits),
 * 2- Direct mode - address of an operand(label) (10 bits) + ARE (2 bits) */
struct info_word{
    unsigned int num_label: 10;
    unsigned int ARE: 2;
}infoWordCode;
/*--------------------------------------------------------------------------------------------------------------------*/

