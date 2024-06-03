all:
	flex compilador_lexico.l
	bison -d compilador_sintatico.y 
	gcc *.c -o Compilador