Coolest Spell-Checker ever. (maybe)
Matric number: 40280334
Author name: Darwon Rashid

(Okay, it is not the coolest spell-checker, it is okay at best.)

Summary:
This is a spell-checking program, it takes in txt files and finds incorrect words (what line they are on as well) and then outputs them either to a new txt file or onto the console, it also works with the console being an input.
To include an input file, you type in the name of the program and then a ‘’-i’’ followed along with the name of the input file.
To include an output file, you do the same as mentioned above except with a ‘’-o’’ followed by the output file, this also works with both being typed in.
We also have a case sensitive flag with ‘’-c’’, this can be used to make case sensitive irrelevant.

Example:
Spell -i input.txt -o output.txt
Spell -i input.txt (this will output to console.)
Spell -c (this will use console for both input and output but is not case sensitive.)

Compiler and Version:

Microsoft (R) C/C++ Optimizing Compiler Version 19.10.24930 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

To build the program from the command line:

                 cl /c functions.c
	               lib /OUT:spell.lib functions.obj
	               cl /c spell.c
	               link spell.obj spell.lib

To build the program from the makefile, you type in nmake in the command line along with any of the test cases provided.
Example:

nmake sentences
nmake sentencesCase
nmake singleWordsCase
