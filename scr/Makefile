all:
	flex compilador_lexico.l
	bison -d compilador_sintatico.y 
	g++ *.c -o Compilador