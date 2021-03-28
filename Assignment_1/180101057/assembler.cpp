#include "assembler.h"

// Break line into words
int break_line(char *str, int start, char *words[])
{
	str = strtok(str, "\n");

	int size = start; // Store number of words
	char *ptr = strtok(str, " ");

	while (ptr != NULL)
	{
		words[size++] = ptr;
		ptr = strtok(NULL, " ");
	}

	return size;
}

// Loads the optable from OpcodeTable.txt
// Return 1 is successful or -1 if unsuccessful
int load_optab()
{
	FILE *ot = fopen(OPTAB, "r");
	if (!ot)
	{
		cout << "Error here" << endl;
		return -1;
	}
	char row1[MAXS], row2[MAXS];
	string opcode, code;
	while (fscanf(ot, "%s %s", row1, row2) != EOF)
	{
		opcode = row1;
		code = row2;
		if (optab.find(opcode) != optab.end())
			return -1;
		optab[opcode] = code;
	}
	fclose(ot);
	return 1;
}

// Search opcode table for specified 
// operation and return corresponding opcode
const char *search_optab(char *OPCODE)
{
	string opcode = OPCODE;
	if (optab.find(opcode) == optab.end())
	{
		return NULL;
	}
	else
	{
		const char *code = (optab[opcode]).c_str();
		return code;
	}
	return NULL;
}

// Search symbol table for specified 
// symbol and return corresponding adress
const char *search_symtab(char *LABEL)
{
	string label = LABEL;
	if (symtab.find(label) == symtab.end())
		return NULL;
	else
	{
		const char *code = (symtab[label]).c_str();
		return code;
	}
	return NULL;
}

// Insert symbol and adress in the symbol table
int insert_symtab(char *LABEL, int LOCCTR)
{
	FILE *filesymtab = fopen(SYMTAB, "a");
	string label = LABEL;
	char addr[MAXW];
	sprintf(addr, "%0X", LOCCTR);
	symtab[label] = addr;
	fprintf(filesymtab, "%s\t%s\n", addr, LABEL);
	fclose(filesymtab);
	return 1;
}
