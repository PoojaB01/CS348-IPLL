%{
    void yyerror (const char *s);
    int yylex();
    #include "pascal.h"

    // to display error line number    
    extern int yylineno;
%}

%start prog
%define parse.error verbose

%union {
    char str[MAXLEN];
    int int_num;
    float real_num;
    num_type type;
}

%token PROGRAM
%token VAR
%token _BEGIN
%token END
%token END_DOT
%token INTEGER
%token REAL
%token FOR
%token READ
%token WRITE
%token TO
%token DO
%token SEMICOLON
%token COLON
%token COMMA
%token EQUAL
%token ADD
%token SUB
%token MUL
%token DIV
%token OPENBRACKET
%token CLOSEBRACKET
%token CHARACTER
%token <str> ID
%token <type> INT
%token <type> REAL_NUM
%type <str> idlist
%type <type> type
%type <type> exp
%type <type> factor
%type <type> term


%% 
prog : PROGRAM progname VAR declist _BEGIN stmtlist END_DOT 
    ;

progname : ID
    ;

declist : dec
    | declist SEMICOLON dec
    | error
    ;

dec : idlist COLON type {
                            // insert all symbols in id table with their type
                            // and check for redeclarations
                            if(declare_type($1, $3) < 0)
                            {
                                fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "symbol redeclared.");
                                ERROR_FLAG = 1;
                            }
                        }
    ;

type : INTEGER          {
                            $$ = integer_num;
                        }

    | REAL              {
                            $$ = real_num;
                        }
    ;

idlist : ID             {
                            strcpy($$, $1);
                        }

    | idlist COMMA ID   {
                            strcpy($$, $1); 
                            strcat($$, ","); 
                            strcat($$, $3);
                        }
    ;

stmtlist : stmt 
    | stmtlist SEMICOLON stmt
    | error
    ;

stmt : assign 
    | read
    | write
    | for
    ;

assign : ID EQUAL exp       {   
                                // if LHS not declared
                                if(getType($1) == not_defined)
                                {
                                    fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "symbol not decalred.");
                                    ERROR_FLAG = 1;
                                }
                                // if mismatch in LHS and RHS type
                                else if(getType($1) != $3 && $3 != not_defined)
                                {
                                    fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "type mismatch in assignment statement.");
                                    ERROR_FLAG = 1;
                                }
                            }
    ;

exp : term              {
                            $$ = $1;
                        }
    | exp ADD term      {
                            // check for type mismatch
                            if($1 != $3)
                            {
                                // check if mismatch not reported already
                                if($3 != not_defined && $1 != not_defined)
                                    fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "type mismatch in expression.");
                                $$ = not_defined;
                                ERROR_FLAG = 1;
                            }
                            else 
                                $$ = $1;;
                        }
    | exp SUB term      {
                            // check for type mismatch
                            if($1 != $3)
                            {
                                // check if mismatch not reported already
                                if($3 != not_defined && $1 != not_defined)
                                    fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "type mismatch in expression.");
                                $$ = not_defined;
                                ERROR_FLAG = 1;
                            }
                            else 
                                $$ = $1;
                        }
    ;

term : factor           {
                            $$ = $1;
                        }
    | term MUL factor   {
                            // check for type mismatch
                            if($1 != $3)
                            {
                                // check if mismatch not reported already
                                if($3 != not_defined && $1 != not_defined)
                                    fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "type mismatch in expression.");
                                $$ = not_defined;
                                ERROR_FLAG = 1;
                            }
                            else 
                                $$ = $1;
                        }
    | term DIV factor   {
                            // check for type mismatch
                            if($1 != $3)
                            {
                                // check if mismatch not reported already
                                if($3 != not_defined && $1 != not_defined)
                                    fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "type mismatch in expression.");
                                $$ = not_defined;
                                ERROR_FLAG = 1;
                            }
                            else 
                                $$ = $1;
                        }
    ;

factor : ID                         {
                                        $$ = getType($1);
                                        // if the symbol is not defined
                                        if($$ == not_defined)
                                        {
                                            fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "symbol not declared.");
                                            ERROR_FLAG = 1;
                                        }
                                    }
    | INT                           {
                                        $$ = integer_num;
                                    }
    | REAL_NUM                      {
                                        $$ = real_num;
                                    }
    | OPENBRACKET exp CLOSEBRACKET  {
                                        $$ = $2;
                                    }
    ;

read : READ OPENBRACKET idlist CLOSEBRACKET     {
                                                    // check if all ids are valid
                                                    if(verify_ids($3) < 0)
                                                    {
                                                        fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "symbol not declared.");
                                                        ERROR_FLAG = 1;
                                                    }
                                                }
    ;

write : WRITE OPENBRACKET idlist CLOSEBRACKET   {
                                                    // check if all ids are valid
                                                    if(verify_ids($3) <  0)
                                                    {
                                                        fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "symbol not declared.");
                                                        ERROR_FLAG = 1;
                                                    }
                                                }
    ;

for : FOR indexexp DO body
    | error
    ;

indexexp : ID EQUAL exp TO exp      {
                                        // check if id not declared
                                        if(getType($1) == not_defined)
                                        {
                                            fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "symbol not declared in for loop index expression.");
                                            ERROR_FLAG = 1;
                                        }
                                        // check for type mismatch
                                        else if(($3 != $5 || getType($1) != $3 || getType($1) != $5) && $3 != not_defined && $5 != not_defined)
                                        {
                                            fprintf (stderr, "Line %d : semantic error, %s\n", yylineno, "type mismatch in for loop index expression.");
                                            ERROR_FLAG = 1;
                                        }
                                    }
    ;

body : stmt 
    | _BEGIN stmtlist END
    ;

%% 

// called when a syntax error is encountered
void yyerror (const char *s) 
{
    fprintf (stderr, "Line %d : %s\n", yylineno, s);
    ERROR_FLAG = 1;
} 

int main (void) 
{
	yyparse ();
    
    // check if no error found
    if(ERROR_FLAG == 0)
    {
        printf("Program compiled successfully.\n");
    }

    // print all the symbols
    print_id_table();
    return 0;
}

