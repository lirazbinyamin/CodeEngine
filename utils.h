/*A function to change extension of a file name*/
void changeExtension(char* fileName, const char* newExtension);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to read a line and skip white spaces and tabs*/
void skipWhites(char line[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check if word is an operation word.
 * Returns 1 - if it's an operation word
 * Else - returns 0*/
int isOperation(char word[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check if the word is supposed to be a label.
 * If so- returns 1, else- returns 0.*/
int isLabel(char line[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check if label is valid.
 * If so- returns 1, else- returns 0.*/
int validLabel(char label[]);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check if a register is valid.
 * Returns 1 - if it's one of the valid registers,else - returns 0;*/
int validRegister(char* registerName);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to check if a number is valid.
 * If so- returns 1,else - returns 0;*/
int validNumber(char *num);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A Function to check is char is a letter;
 * Returns 1 - if is a letter.
 * Else - returns 0*/
int isLetter(char ch);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A Function to check is char is a digit;
 * Returns 1 - if is a digit.
 * Else - returns 0*/
int isDigit(char d);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to convert a single character of digit into it's value in int
 * Returns character value in int*/
unsigned int convertToDigit(unsigned char c);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to extract string from its double quote to a string array and check for errors
 * Returns 1 - if extracted successfully.
 * Else - returns 0*/
int extractString(char *line,char *string);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to separate a word to 2 words with 6 characters each, and then convert their binary representation
 * to integers, and then convert them to Base64*/
void base64(char* word);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function that takes two integers 'a' and 'b' as input and converts them to Base64 representation*/
void convertToBase64(int a, int b);
/*--------------------------------------------------------------------------------------------------------------------*/
/*A function to print the binary representation of the input string in lines*/
void printBinaryLines(const char* binaryString, int charsPerLine);
