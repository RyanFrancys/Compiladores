all:
	clear
	flex compilador_lexico.l
	bison -d compilador_sintatico.y -Wcounterexamples
	g++ *.c -o Compilador