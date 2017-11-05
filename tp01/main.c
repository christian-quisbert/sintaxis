/**
		\file    main.c
		\brief   Contiene el menu principal. Donde se recibe el archivo fuente en lenguaje "micro".
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.11.04
		\version Versión 1.0.1
*/  
#include <stdio.h>
#include "funciones.h"

#define TAMLIN 80

int main (int argc, char ** argv){

	in	= fopen(argv[1],"r");
	out	= fopen(argv[2],"w");

	if(argc == 1){
		printf("\n(ERROR) Debe ingresar 2 nombres de archivo!");
		return -1;
	}
	if (argc != 3){
		puts("\n(ERROR) Número incorrecto de argumentos!");
		puts("\nDebe ingresar 1 lexema.");
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

	Objetivo();

	/*while(fgets(linea, TAMLIN+1, in) == NULL){

	}*/

	fclose(in);
	fclose(out);
	return 0;
}
