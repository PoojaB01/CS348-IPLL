#include "assembler.h"

// Pass 1
// Takes program file as input
// and generates intermediate file
// and symbol table
int pass_one(FILE *inputFile, FILE *outputFile)
{

    fseek(inputFile, 0, SEEK_SET);

    //clear symbol table
    FILE *st = fopen(SYMTAB, "w");
    fclose(st);

    char *line = NULL, temp[MAXS];
    size_t len = 0;
    char *args[MAXW];
    int words;
    char *OPCODE, *LABEL, *OPERAND;

    // store addresses
    int LOCCTR;

    // read first line
    getline(&line, &len, inputFile);
    strcpy(temp, line);
    if (line[0] == ' ')
    {
        words = break_line(temp, 1, args);
        LABEL = NULL;
        OPCODE = args[1];
    }
    else
    {
        words = break_line(temp, 0, args);
        LABEL = args[0];
        OPCODE = args[1];
    }

    if (strcmp(args[1], "START") == 0)
    {
        OPERAND = args[2];
        STARTADDR = strtol(OPERAND, NULL, 16);
        strcpy(PROGNAME, LABEL);
        LOCCTR = STARTADDR;

        // write line to intermediate file
        fprintf(outputFile, "%0X\t%s", LOCCTR, line);

        // read next input line
        getline(&line, &len, inputFile);
        strcpy(temp, line);
        if (line[0] == ' ')
        {
            words = break_line(temp, 1, args);
            LABEL = NULL;
            OPCODE = args[1];
        }
        else
        {
            words = break_line(temp, 0, args);
            LABEL = args[0];
            OPCODE = args[1];
        }
    }
    else
    {
        LOCCTR = 0;
    }

    while (strcmp(OPCODE, "END") != 0)
    {
        if (line[0] != '.') // check if not a comment
        {
            if (LABEL) // check if symbol in label
            {
                if (search_symtab(LABEL))
                {
                    printf("Error: Duplicate Symbol. \n");
                    ERROR_FLAG = 1;
                    return -1;
                }
                else
                {
                    insert_symtab(LABEL, LOCCTR);
                }
            }

            // write line to intermediate file
            fprintf(outputFile, "%0X\t%s", LOCCTR, line);

            if (search_optab(OPCODE))
            {
                LOCCTR = LOCCTR + 3 * ILEN;
            }
            else if (strcmp(OPCODE, "WORD") == 0)
            {
                LOCCTR = LOCCTR + 3;
            }
            else if (strcmp(OPCODE, "RESW") == 0)
            {
                OPERAND = args[2];
                LOCCTR = LOCCTR + 3 * strtol(OPERAND, NULL, 10); 
            }
            else if (strcmp(OPCODE, "RESB") == 0)
            {
                OPERAND = args[2];
                LOCCTR = LOCCTR + strtol(OPERAND, NULL, 10); 
            }
            else if (strcmp(OPCODE, "BYTE") == 0)
            {
                OPERAND = args[2];
                if (OPERAND[0] == 'C')
                    LOCCTR = LOCCTR + strlen(OPERAND) - 3;
                else if (OPERAND[0] == 'X')
                    LOCCTR = LOCCTR + (strlen(OPERAND) - 3 + 1) / 2; 
            }
            else
            {
                printf("Error: Invalid operation code. \n");
                ERROR_FLAG = 1;
                return -1;
            }
        }
        else
        {
            fprintf(outputFile, "    \t%s", line);
        }

        // read next input line
        getline(&line, &len, inputFile);
        strcpy(temp, line);
        if (line[0] == ' ')
        {
            words = break_line(temp, 1, args);
            LABEL = NULL;
            OPCODE = args[1];
        }
        else
        {
            words = break_line(temp, 0, args);
            LABEL = args[0];
            OPCODE = args[1];
        }
    }

    fprintf(outputFile, "    \t%s\n", line);
    
    // store program length
    PROGLEN = LOCCTR - STARTADDR;

    printf("PASS ONE COMPLETED.\n");

    return 1;
}
