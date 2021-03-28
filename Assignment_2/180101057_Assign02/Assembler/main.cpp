/*
IPLL Assignment 2
Author: Pooja Bhagat

Environment used to run the program :  
`gcc version 9.3.0 (Ubuntu 9.3.0-17ubuntu1~20.04)` 

Command to compile:  
`g++ -o assembler main.cpp`
   
Command to run the code:  
`./assembler`
*/

#include "assembler.h"
#include "assembler.cpp"
#include "pass_one.cpp"
#include "pass_two.cpp"

int main(int argc, char *argv[])
{
    const char *progFile = "program.txt";
    const char *outFile = "objectCode.txt";
    const char *listingFile = "codeListing.txt";

    FILE *prog, *intm, *out, *list;

    // load opcode table
    if (load_optab() < 0)
    {
        printf("Error loading opcode table. \n");
    }

    // open program, intermediate and output file
    prog = fopen(progFile, "r");
    intm = fopen(INTM, "w");
    out = fopen(outFile, "w");
    list = fopen(listingFile, "w");

    // if error opening files
    if (!prog || !intm || !out || !list)
    {
        printf("Error opening files. \n");
        return 0;
    }

    // execute pass 1 and generate intermediate file
    if (pass_one(prog, intm) < 0)
    {
        printf("Error in Pass one. \n");
        return 0;
    }

    // open intermediate file in read mode
    fclose(intm);
    intm = fopen(INTM, "r");

    // execute pass 2 to generate output
    if (pass_two(intm, out, list) < 0)
    {
        printf("Error in Pass two. \n");
        return 0;
    }

    // close files
    fclose(prog);
    fclose(intm);
    fclose(out);

    printf("Assembly Successful. \n");
    printf("Check objectCode.txt \n");
    printf("ERROR_FLAG = %d\n", ERROR_FLAG);
    return 0;
}