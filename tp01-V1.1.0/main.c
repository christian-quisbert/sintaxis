/**
		\file    main.c
		\brief   Contiene el menu principal. Donde se recibe el archivo fuente en lenguaje "micro".
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.11.04
		\version Versión 1.0.1
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "micro.h"
#include "parser.h"

/* -----PROGRAMA COMANDO----- */

int main (int argc, char *argv[]){
	in	= fopen(argv[1],"r");
	out	= fopen(argv[2],"w");

	if(argc == 1){
		printf("\n(ERROR) Debe ingresar 2 nombres de archivo!\n");
		return -1;
	}
	if (argc != 3){
		printf("\n(ERROR) Número incorrecto de argumentos!\n");
		return -2;
	}
	if(in == NULL){
		printf("\n(File error) No se pudo abrir el archivo de Entrada.\n");
		return -3;
	}
	if(out == NULL){
		printf("\n(File error) No se pudo abrir el archivo de Salida.\n");
		return -4;
	}
	 printf("asdasd");
	Objetivo();

	fclose(in);
	fclose(out);
	return 0;
}
