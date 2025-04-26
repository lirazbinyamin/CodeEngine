<h1> Assembler  </h1>

The purpose of this project is to build an assembler for 16-instruction assembly language, for an imaginary 12-bit CPU with 12-bit & 256 words memory size. 

<h2> Program Description  </h2>
This program gets an '.as' file, scan it for macros and organize them in a macro table.

Then, creates an '.am' file with all macros spreaded, scans the file (twice) to realize commands and data from assembly and checks for any errors. Afterwards, it converts all the content to binary machine code and create 3 output files: 

* Object file: the am. file transferred to machine code. 
* Externals file: details of addresses in the machine code where the is an information word coding a value of a symbol which defined external symbol.
* Entries file: details of each symbol which defined entry symbol.
<h3> Files in project </h3>

 * assembler.c - main file starts the assembly process.
 * pre_assembler.c - handles all pre-assembler process.
 * first_second_pass.c - handles first and second passes on file.
 * symbols.c - handles all symbols work.
 * utils.c - includes helper functions used in all other files.
 * errors.c - includes error functions.
 * code.c - handles machine code.
 * create_file.c - creates all output files after second pass.
 * globals.c - includes all global variables used in program.
 
<h4> Instructions to run program </h4>

 * Open terminal and type "make", then press Enter.

 * Type "./assembler" adding '.as' file/s name you want to us, then press Enter.

Here's an example command for assembling multiple files:

```console
./assembler test1 test2 test3 error1 error2
```
<h5> Printings to the screen </h5>
 
* Print macro table: use printMacroTable defined in pre_assembler.h.
 
* Print symbol table: use printSymbolTable defined in symbols.h.
 
* Print binary machine code representation: use printBinaryLines defined in create_files.h.


* All descriptions for functions used in each file are located in file's header.

ENJOY!

 
