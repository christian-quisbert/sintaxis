/**
		\file    funciones.c
		\brief   Contiene las funciones para main.c
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.08.21
		\version Versión 1.0.0
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

/**
		\fn     columna
		\brief  Devuelve la COLUMNA correspondiente al caracter ingresado.
		\author Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date   2017.08.21
		\param  char c
		\return int col
*/
int columna(char c){
    if(isalpha(c))  return 0;
    if(isdigit(c))  return 1;
    if(c =='+')     return 2;
    if(c =='-')     return 3;
    if(c =='(')     return 4;
    if(c ==')')     return 5;
    if(c ==',')     return 6;
    if(c ==';')     return 7;
    if(c ==':')     return 8;
    if(c =='=')     return 9;
    if(c =='\n')    return 10;
    if(isspace(c))  return 11;
    return 12;
}

/**
		\fn     Scanner
		\brief  Indica el token de un lexema ingresado por parámetro.
		\author Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date   2017.08.23
		\param  char * lexema
		\return TOKEN
*/
TOKEN Scanner(char * lexema){
	/*Tabla de transición de lenguaje MICRO*/
    static int TT[ESTADOS][COLUMNAS] = {
		{1	,3	,5	,6	,7	,8	,9	,10	,11	,14	,13	,0	,14	},
		{1	,1	,2	,2	,2	,2	,2	,2	,2	,2	,2	,2	,2	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{4	,3	,4	,4	,4	,4	,4	,4	,4	,4	,4	,4	,4	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,12	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	},
		{14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	,14	}
		
	};
	int estado = 0;
	int i = 0;
	char c;
	
	/*Leo por caracter y me fijo su estado*/
	do{
		c = lexema[i];
		estado = TT[estado][columna(c)];
		i++;

	}while(lexema[i] != '\0' && estado != 14);
	
	/*Retorno el token que corresponda al último estado*/
	switch(estado){
		case 1:
			/* Me fijo el tipo de ID */
			switch(tablaSimbolos(lexema)){
			case 1:
				printf("Palabra reservada: INICIO\n");
				return INICIO;
			case 2:
				printf("Palabra reservada: FIN\n");
				return FIN;
			case 3:
				printf("Palabra reservada: LEER\n");
				return LEER;
			case 4:
				printf("Palabra reservada: ESCRIBIR\n");
				return ESCRIBIR;
			}
			printf("ID\n");
			return ID;
		case 2:
			printf("ERROR LEXICO\n");
			return ERRORLEXICO;
		case 3:
			printf("CONSTANTE\n");
			return CONSTANTE;
		case 4:
			printf("ERROR LEXICO\n");
			return ERRORLEXICO;
		case 5:
			printf("SUMA\n");
			return SUMA;
		case 6:
			printf("RESTA\n");
			return RESTA;
		case 7:
			printf("PARENIZQUIERDO\n");
			return PARENIZQUIERDO;
		case 8:
			printf("PARENDERECHO\n");
			return PARENDERECHO;
		case 9:
			printf("COMA\n");
			return COMA;
		case 10:
			printf("PUNTOYCOMA\n");
			return PUNTOYCOMA;
		case 11:
			printf("ERROR LEXICO\n");
			return ERRORLEXICO;
		case 12:
			printf("ASIGNACION\n");
			return ASIGNACION;
		case 13:
			printf("FDT");
			return FDT;
		case 14:
			printf("ERROR LEXICO\n");
			return ERRORLEXICO;
		default:
			break;
	}
    return  0;
}
/**
		\fn     tablaSimbolos
		\brief  Indica si un lexema ingresado es palabra reservada.
		\author Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date   2017.08.29
		\param  char * lexema
		\return int 
*/
int tablaSimbolos(char* lexema){
	static char* simbolos[4]={"INICIO","FIN","LEER","ESCRIBIR"};
	int i;
	for(i=0;i<4;i++)
		if(!strcmp(lexema,simbolos[i])) break;
	return i+1;//le sumo 1 para que quede igual que el enum
}