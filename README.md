# Assembler
/*Project goal: Build an assembler for an assembly language provided in MAMAN 14.
 *
 * This program gets an '.as' file -> scan it for macros and spread them -> create an '.am' file with macros spread ->
 * -> scan file (first&second passes) to realize commands and data from assembly and check for any errors ->
 * -> convert all the content to binary machine code -> create output files for content.
 *
 * Files in project:
 * assembler.c - main file starting the assembly process
 * pre_assembler.c - handles all pre-assembler process
 * first_second_pass.c - handles first and second passes on file
 * symbols.c - handles all symbol work
 * utils.c - contains helper functions used in all other files
 * errors.c - contains error functions
 * code.c - handles machine code
 * create_file.c - create all output files after second pass
 * globals.c - contains all global variables used in program
 *
 * Instructions:
 * 1- Open terminal and type "make", then press Enter.
 * 2- Type "./assembler" adding '.as' file/s name you want to us,then press Enter.
 * for example: "./assembler test1 test2 test3 test4 error1 error2".
 * 3- If you want to print macro table: use printMacroTable defined in pre_assembler.h.
 * 4- If you want to print symbol table: use printSymbolTable defined in symbols.h.
 * 5- If you want to print binary machine code representation: use printBinaryLines defined in create_files.h.
 * 6- All descriptions for functions used in each file - located in file header.
 *
 * ENJOY!
 *
 * Author: Liraz Binyamin*/
