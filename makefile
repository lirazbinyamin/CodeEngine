assembler:	assembler.o utils.o symbols.o pre_assembler.o first_second_pass.o code.o globals.o errors.o create_files.o
	gcc	-g	-ansi	-Wall	-pedantic	assembler.o	utils.o	symbols.o	pre_assembler.o	first_second_pass.o	code.o	globals.o	errors.o	create_files.o	-o	assembler

assembler.o	:	assembler.c pre_assembler.h first_second_pass.h assembler.h utils.h code.h errors.h
	gcc	-c	-ansi	-Wall	-pedantic	assembler.c	-o	assembler.o
utils.o: utils.c utils.h assembler.h errors.h code.h
	gcc	-c	-ansi	-Wall	-pedantic	utils.c	-o	utils.o
symbols.o: symbols.c symbols.h
	gcc	-c	-ansi	-Wall	-pedantic	symbols.c	-o	symbols.o
pre_assembler.o: pre_assembler.c pre_assembler.h utils.h assembler.h errors.h
	gcc	-c	-ansi	-Wall	-pedantic	pre_assembler.c	-o	pre_assembler.o
first_second_pass.o: first_second_pass.c first_second_pass.h utils.h assembler.h code.h symbols.h errors.h
	gcc	-c	-ansi	-Wall	-pedantic	first_second_pass.c	-o	first_second_pass.o
code.o: code.c code.h assembler.h
	gcc	-c	-ansi	-Wall	-pedantic	code.c	-o	code.o
globals.o: globals.c assembler.h
	gcc	-c	-ansi	-Wall	-pedantic	globals.c	-o	globals.o
errors.o: errors.c errors.h assembler.h first_second_pass.h
	gcc	-c	-ansi	-Wall	-pedantic	errors.c	-o	errors.o
create_files.o: create_files.c create_files.h assembler.h utils.h errors.h
	gcc	-c	-ansi	-Wall	-pedantic	create_files.c	-o	create_files.o
