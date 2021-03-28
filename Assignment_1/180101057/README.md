# Assignment 1
## CS 348 Introduction to Programming Languages Laboratory
Name: Pooja Gajendra Bhagat  
Roll Number: 180101057  
<em>2 pass assembler</em>

Environment used to run the program :  
`gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04) ` 

Command to compile:  
`g++ 180101057_Assign01.cpp`
   
Command to run the code:  
`./a.out program.txt`

### File description
1. `180101057_Assign01.cpp` : Contains code for file handling, loads optable and calls pass_one and pass_two
1. `assembler.h` : Contains function prototypes, header files and global variable
2. `assembler.cpp` : Contains funtion definition of some functions declared in assembler.h
3. `pass_one.cpp` : Contains code for pass 1 of the assembler. It reads input program and creates intermediate file
4. `pass_two.cpp` : Contains code for pass 1 of the assembler. It reads input program and creates object code and listing file
5. `opcodeTable.txt` : Contains object code for corresponding operations
6. `program.txt` : Contains input assembly code
7. `codeListing.txt` : Contains assembly listing 
8. `symbolTable.txt` : Contains symbols in assembly code and their corresponding addresses
9.  `intermediate.txt` : Intermediate file created after pass 1.
10. `objectCode.txt` : Contains the resultant object code

