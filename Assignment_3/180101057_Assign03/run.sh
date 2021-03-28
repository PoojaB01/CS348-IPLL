lex -t 180101057.l > 180101057_lex.yy.c
g++ 180101057_lex.yy.c
./a.out < input.pas
