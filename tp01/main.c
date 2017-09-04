/**
		\file    main.c
		\brief   Contiene el menu principal. Donde se implementa el SCANNER.
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.08.21
		\version Versión 1.0.0
*/  
#include <stdio.h>
#include "funciones.h"

int main (int argc, char ** argv){
	if (argc != 2){
		printf("uso: scanner lexema");
		return -1;
	}
	
	printf("Lexema: %s \n",argv[1]);

	switch(scanner(argv[1])){
	case INICIO:
		printf("Palabra reservada: INICIO\n");
		return 0;
	case FIN:
		printf("Palabra reservada: FIN\n");
		return 0;
	case LEER:
		printf("Palabra reservada: LEER\n");
		return 0;
	case ESCRIBIR:
		printf("Palabra reservada: ESCRIBIR\n");
		return 0;
	case ID:
		printf("ID\n");
		return 0;
	case ERRORLEXICO:
		printf("ERROR LEXICO\n");
		return 0;
	case CONSTANTE:
		printf("CONSTANTE\n");
		return 0;
	case SUMA:
		printf("SUMA\n");
		return 0;
	case RESTA:
		printf("RESTA\n");
		return 0;
	case PARENIZQUIERDO:
		printf("PARENIZQUIERDO\n");
		return 0;
	case PARENDERECHO:
		printf("PARENDERECHO\n");
		return 0;
	case COMA:
		printf("COMA\n");
		return 0;
	case PUNTOYCOMA:
		printf("PUNTOYCOMA\n");
		return 0;
	case ASIGNACION:
		printf("ASIGNACION\n");
		return 0;
	case FDT:
		printf("FDT");
		return 0;
	}
	return -2; //nunca se va a leer esto
}
