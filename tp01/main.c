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
		return 0;
	}
	
	printf("Lexema: %s \n",argv[1]);
	return Scanner(argv[1]);
}