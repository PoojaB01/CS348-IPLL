# Assignment 2
## CS 348 Introduction to Programming Languages Laboratory
Name: Pooja Gajendra Bhagat  
Roll Number: 180101057  

## Extended Assembler

Environment used to run the program :  
`gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04) ` 

Command to compile:  
`cd Assembler`  
`g++ -o assembler main.cpp`
   
Command to run the code:  
`./assembler`

### File description
1. `main.cpp` : Contains code for file handling, loads optable and calls pass_one and pass_two
1. `assembler.h` : Contains function prototypes, header files and global variable
2. `assembler.cpp` : Contains funtion definition of some functions declared in assembler.h
3. `pass_one.cpp` : Contains code for pass 1 of the assembler. It reads input program and creates intermediate file
4. `pass_two.cpp` : Contains code for pass 2 of the assembler. It reads input program and creates object code and listing file
5. `opcodeTable.txt` : Contains object code for corresponding operations
6. `program.txt` : Contains input assembly code
7. `codeListing.txt` : Contains assembly listing 
8. `symbolTable.txt` : Contains symbols in assembly code and their corresponding addresses
9.  `intermediate.txt` : Intermediate file created after pass 1.
10. `objectCode.txt` : Contains the resultant object code

## Linking Loader

Environment used to run the program :  
`gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04) ` 

Command to compile:  
`cd Loader`  
`g++ -o loader main.cpp`
   
Command to run the code:  
`./loader`

### File description
1. `main.cpp` : Contains code for file handling, and calls pass_one and pass_two
2. `loader.h` : Contains function prototypes, header files and global variable
3. `loader.cpp` : Contains funtion definition of some functions declared in assembler.h
4. `pass_one.cpp` : Contains code for pass 1 of the loader. It reads input program and fills the ESTAB
5. `pass_two.cpp` : Contains code for pass 2 of the loader. It reads input program and loads the program in memory after relocation
6. `input.txt` : Contains the input object code
7. `estab.txt` : Contains the generated ESTAB
8. `loaderOutput.txt` : Contains the state of memory after loading is complete