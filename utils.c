#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "assembler.h"
#include "utils.h"
#include "errors.h"
#include "code.h"
/*--------------------------------------------------------------------------------------------------------------------*/
/*utils file includes all the helper functions used in the project - finding/changing/converting/checking-validation..*/
/*--------------------------------------------------------------------------------------------------------------------*/
void changeExtension(char* fileName, const char* newExtension)
{
    char* dotPosition = strrchr(fileName, '.');  /*Find the last occurrence of '.' */
    if (dotPosition != NULL)
    {
        *dotPosition = '\0';  /*Replace the dot with null terminator to remove the extension */
    }

    strcat(fileName, ".");  /* Add a dot before the new extension */
    strcat(fileName, newExtension);  /* Append the new extension to the file name */
    /*printf("Extension changed to %s \n", newExtension);*/
}
/*--------------------------------------------------------------------------------------------------------------------*/
void skipWhites(char line[])
{
    /*printf("\nline before:%s\n",line);*/
    int i, j = 0;
    int leadingWhitespace = 1;

    for (i = 0; line[i] != '\0'; i++) {
        if (leadingWhitespace && isspace(line[i])) {
            continue; /*Skip leading whitespace characters*/
        } else {
            leadingWhitespace = 0;
            line[j++] = line[i];
        }
    }
    line[j] = '\0'; /* Null-terminate the modified line*/
    /*printf("\nline after:%s\n",line);*/
}
/*--------------------------------------------------------------------------------------------------------------------*/
int isOperation(char label[])
{
    if (!strcmp(label, "mov") || !strcmp(label, "cmp") || !strcmp(label, "add") || !strcmp(label, "sub") ||
        !strcmp(label, "not") || !strcmp(label, "clr") || !strcmp(label, "lea") || !strcmp(label, "inc")
        || !strcmp(label, "dec") || !strcmp(label, "jmp") || !strcmp(label, "bne") || !strcmp(label, "red") ||
        !strcmp(label, "prn") || !strcmp(label, "jsr") || !strcmp(label, "rts") || !strcmp(label, "stop"))
        return 1;
    else
        return 0;
}
/*--------------------------------------------------------------------------------------------------------------------*/

int isLabel(char line[])
{
    char label[MAX_LINE_LENGTH];
    strcpy(label, line);
    strtok(label, ":"); /*separate the label from the rest of the line*/
    if (!strcmp(label, line)) /*if the whole line is the label there isn't any definition*/
        return 0;
    else
        return 1;

}
/*--------------------------------------------------------------------------------------------------------------------*/
int validLabel(char label[])
{
    char* p = label; /*pointer to the next char in label*/
    /*printf("-----------------label name:-----------------\n-----------------%s-----------------\n",label);*/
    if(validRegister(label)&& strlen(label)==2) /*check if label is a register*/
    {
        invalidLabel(label); /*return error*/
        return 0;
    }

    if(isOperation(label)) /*check if label is an operation name*/
    {
        invalidLabel(label); /*return error*/
        return 0;
    }

    if (!isLetter(p[0])) /*check if first character is a letter(must be for valid label)*/
    {
        invalidLabel(label);/*return error*/
        return 0;
    }

    while (*p != '\0')
    {
        if (!isdigit(p[0]) && !isLetter(p[0])) /*check if there's a char in label that isn't a letter nor number*/
        {
            invalidLabel(label); /*return error*/
            return 0;
        }
        p++;
    }

    if (strlen(label) > MAX_LABEL_LENGTH) /*check if label is too long*/
    {
        invalidLabel(label); /*return error*/
        return 0;
    }

    return 1;

}
/*--------------------------------------------------------------------------------------------------------------------*/
int validRegister(char* registerName)
{
    if(registerName[1]!='r') /*check if first character is 'r' as expected*/
        return 0;
    else
    {
        switch (registerName[2]) /*check if it's one of the registers 0-7*/
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                return 1;
            default:
                return 0;
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
int validNumber(char *num)
{
    char *ptr; /* Pointer to iterate through the characters of the string */

    if (num[0] == '\0') /*check if empty*/
        return 0;

    ptr = num;

    if (*ptr == '-' || *ptr == '+')/* If the first character is a positive/negative sign, move the pointer to the next character */
        ptr = num + 1;


    while (*ptr != '\0') /*check the rest of the number*/
    {
        if (*ptr < '0' || *ptr > '9') /* check if the character is not a digit (outside the range '0' to '9')*/
            return 0;
        ptr++;
    }

    return 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int isLetter(char ch)
{
    if (ch < 65 || ch > 122)
        return 0;
    else
        return 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int isDigit(char d)
{
    if (d < 48 || d > 57)
        return 0;
    else
        return 1;
}
/*--------------------------------------------------------------------------------------------------------------------*/
unsigned int convertToDigit(unsigned char c)
{
    return (unsigned int) c - '0';
}
/*--------------------------------------------------------------------------------------------------------------------*/
int extractString(char *line,char *string)
{
    /*printf("inside extractString...\n");*/
    char *ptr = line; /* Initialize a pointer to the current position in the input line*/

    if (*ptr != '"') /* Check if the first character is not a double quote */
    {
        invalidString(line); /*returns error*/
        return 0;
    }
    ptr++;
    while (*ptr && *ptr != '"') /*Find the end of the string (the closing double quote)*/
    {
        ptr++;
    }
    if (*ptr != '"') /* Check if the string does not end with a double quote (invalid format)*/
    {
        invalidString(line); /*returns error*/
        return 0;
    }

    ptr++; /* Move to the character after the closing double quote */

    if(*ptr != '\0' && *ptr != '\n' ) /*there is extra text after end of string*/
    {
        extraText();/*return error*/
        return 0;
    }

    *ptr = '\0'; /* Null-terminate the string at the closing double quote */
    strcpy(string, line); /* Copy the content between the double quotes to the output string */
    /*printf("string extracted successfully!going out...\n");*/
    return 1; /* Return 1 to indicate successful copying*/
}
/*--------------------------------------------------------------------------------------------------------------------*/
void base64(char* word)
{
    char word1[7] = "";
    char word2[7] = "";
    char *ptr = word;
    int a = 0, b = 0;
    int i, power, digit;
    while (ptr[0] != '\0')
    {
        for (i = 0; i < 6; i++)/*extract the first group of 6 characters from 'word' into 'word1'.*/
        {
            word1[i] = ptr[0];
            ptr++;
        }
        for (i = 0; i < 6; i++)/*extract the second group of 6 characters from 'word' into 'word2'.*/
        {
            word2[i] = ptr[0];
            ptr++;
        }
        for (power = 5, i = 0; power >= 0; power--, i++)/*convert the binary representation in 'word1' to an integer 'a'.*/
        {
            digit = convertToDigit(word1[i]);
            a = a + digit * (1 << power); /* Using bitwise left shift (1 << power) for power of 2*/
        }
        for (power = 5, i = 0; power >= 0; power--, i++)/*convert the binary representation in 'word2' to an integer 'b'.*/
        {
            b += convertToDigit(word2[i]) * (1 << power); /* Using bitwise left shift (1 << power) for power of 2*/
        }

        convertToBase64(a, b);/*convert 'a' and 'b' to Base65*/
        a = 0;
        b = 0;
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
void convertToBase64(int a, int b)
{
    char array[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char words[3];
    words[0] = array[a];/*Convert 'a' to its corresponding Base64 character and store it in words[0].*/
    words[1] = array[b];/*Convert 'b' to its corresponding Base64 character and store it in words[1].*/
    words[2] = '\0';/*Add a null terminator at the end of the 'words'.*/
    strcat(objBase64, words);
}
/*--------------------------------------------------------------------------------------------------------------------*/
void printBinaryLines(const char* binaryString, int charsPerLine)
{
    int i;
    int j;
    printf("\nBinary representation of lines: \n");
    printf("-----------------------------------\n");

    for (i = 0,j=100; i < strlen(binaryString); i += charsPerLine,j++)
    {

        printf("%d: %.12s\n",j, binaryString + i);
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
