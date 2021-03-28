#include "assembler.h"

// Break line into words
int break_line(char *str, int start, char *words[], const char *delimiter)
{
	str = strtok(str, "\n");

	int size = start; // Store number of words
	char *ptr = strtok(str, delimiter);

	while (ptr != NULL)
	{
		words[size++] = ptr;
		ptr = strtok(NULL, delimiter);
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
	int format;
	string opcode, code;
	while (fscanf(ot, "%s %s %d", row1, row2, &format) != EOF)
	{
		opcode = row1;
		code = row2;
		if (optab.find(opcode) != optab.end())
			return -1;
		optab[opcode] = {code, format};
	}
	fclose(ot);
	return 1;
}

// Search opcode table for specified
// operation and return corresponding opcode
opcode_info *search_optab(char *OPCODE)
{
	string opcode = OPCODE;
	if (optab.find(opcode) == optab.end())
	{
		return NULL;
	}
	else
	{
		return &optab[opcode];
	}
	return NULL;
}

// Search symbol table for specified
// symbol and return corresponding adress
symbol_info *symtab::search_symtab(const char *LABEL)
{
	string label = LABEL;
	table.find("RLOOP");
	if (table.find(label) == table.end())
	{
		return NULL;
	}
	else
	{
		return &table[label];
	}
	return NULL;
}

// Insert symbol and adress in the symbol table
int symtab::insert_symtab(const char *LABEL, int LOCCTR)
{
	FILE *filesymtab = fopen(SYMTAB, "a");
	string label = LABEL;
	char addr[MAXW];
	sprintf(addr, "%0X", LOCCTR);
	table[label] = {addr};
	fprintf(filesymtab, "%s\t%s\n", addr, LABEL);
	fclose(filesymtab);
	return 1;
}

// print symbol table
int symtab::print_symtab()
{
	for (auto i = table.begin(); i != table.end(); i++)
	{
		cout << i->first << ' ' << i->second.addr << endl;
	}
	return 1;
}

// insert label in external definition list
int symtab::insert_extdef(char *LABEL)
{
	extdef.insert((string)LABEL);
	return 1;
}

// insert label in external reference list
int symtab::insert_extref(char *LABEL)
{
	extref.insert((string)LABEL);
	return 1;
}

// print all the literals encountered
int print_literals(int LOCCTR, FILE *outputFile, symtab *base)
{
	while (literal_pool.size())
	{
		string lit = *literal_pool.begin();
		fprintf(outputFile, "%04X\t*\t%s\n", LOCCTR, lit.c_str());
		base->insert_symtab(lit.c_str(), LOCCTR);
		if (lit[1] == 'C')
		{
			LOCCTR += lit.length() - 4;
		}
		else
		{
			LOCCTR += (lit.length() - 4 + 1) / 2;
		}
		literal_pool.erase(literal_pool.begin());
	}
	return LOCCTR;
}

// check if symbol is an external reference
bool symtab::is_extref(const char *SYMBOL)
{
	return (extref.find((string)SYMBOL) != extref.end());
}

// symtab constructor
symtab::symtab()
{
}

// set length of section
void symtab::set_length(int length)
{
	this->length = length;
}

// get length of section
int symtab::get_length()
{
	return length;
}

// calculate value of operand and insert modification records
int handle_operand(char *OPERAND, queue<modrec> &modification_records, symtab *base, int oplen, int addr)
{
	// check if constant numeral
	if (isdigit(OPERAND[0]))
	{
		return (int)strtol(OPERAND, NULL, 10);
	}
	else if (strcmp(OPERAND, "*") == 0)
	{
		return addr;
	}
	else
	{
		int operand_value = 0;
		string operand = OPERAND;
		int prev = 0;
		bool sign = true;

		// split expression
		for (int i = 0; i < operand.length(); i++)
		{
			if (operand[i] == '-' || operand[i] == '+' || i == operand.length() - 1)
			{
				if (i == operand.length() - 1)
					i++;
				string symbol = operand.substr(prev, i - prev);
				prev = i + 1;

				// check if symbol and external reference
				if (base->is_extref(symbol.c_str()))
				{
					modification_records.push({addr, oplen, sign, symbol});
				}
				else
				{
					symbol_info *sym = base->search_symtab(symbol.c_str());
					if (sym != NULL)
						operand_value += (sign ? 1 : -1) * (int)strtol(sym->addr.c_str(), NULL, 16);
				}
				sign = operand[i] == '+';
			}
		}

		return operand_value;
	}
}