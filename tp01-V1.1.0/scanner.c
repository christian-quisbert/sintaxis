/**
		\file    funciones.c
		\brief   Contiene las funciones para main.c
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.08.21
		\version Versión 1.0.0
*/
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "micro.h"
#include "scanner.h"

/**
		\fn     columna
		\brief  Devuelve la COLUMNA correspondiente al caracter ingresado.
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
		\brief  
		\date   2017.08.23
		\return TOKEN
*/
TOKEN scanner(void){
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
	
	/*Leo caracter por caracter hasta llegar al fin de linea.*/
	do{
		c = fgetc(in);
		estado = TT[estado][columna(c)];
		if(columna(c) != 11){
			buffer[i] = c;
			i++;
		}
	}while(!esEstadoFinal(estado));

	/*buffer[i] = '\0';*/

	/*Retorno el token que corresponda al último estado*/
	switch(estado){
		case 1:
			return esReservada();
		case 2:
			ungetc(buffer[i],in);
			buffer[i-1] = '\0';
			return esReservada();
		case 3:
			return CONSTANTE;
		case 4:
			ungetc(buffer[i], in);
			buffer[i-1] = '\0';
			return CONSTANTE;
		case 5:
			return SUMA;
		case 6:
			return RESTA;
		case 7:
			return PARENIZQUIERDO;
		case 8:
			return PARENDERECHO;
		case 9:
			return COMA;
		case 10:
			return PUNTOYCOMA;
		case 12:
			return ASIGNACION;
		case 13:
			return FDT;
		case 11:
		case 14:
			return ERRORLEXICO;
	}
    return -1; /* nunca se va a leer esto */
}
/**
		\fn     indiceTS
		\brief  Devuelve el indice de la palabra reservada lexema.
		\date   2017.11.06
		\param  char * lexema
		\return int
*/
int indiceTS(char * lexema){
	int i;
	for(i=0; i < indiceActualTS; i++)
		if(!strcmp(lexema,TS[i].cadena)) break;
	/*Devuelve el indice de la palabra reservada*/
	return i+1; /* le sumo 1 para que quede igual que el enum */
}

/**
		\fn     esReservada
		\brief  Devuelve el TOKEN correspondiente a una palabra reservada o identificador.
		\date   2017.11.06 
*/
TOKEN esReservada(void){
	switch(indiceTS(buffer)){
		case 1:
			return INICIO;
		case 2:
			return FIN;
		case 3:
			return LEER;
		case 4:
			return ESCRIBIR;
		default:
			return ID;
		}
};
/**
		\fn     initTS
		\brief  Inicializo la TS, con las palabras reservada del lenguaje MICRO (4 palabras).
		\date   2017.11.06 
*/
void initTS(void){
	/*strcpy(TS[0].cadena, "INICIO");		strcpy(TS[0].atributo, "reservada");*/
	/*strcpy(TS[1].cadena, "FIN");		strcpy(TS[1].atributo, "reservada");*/
	/*strcpy(TS[2].cadena, "LEER");		strcpy(TS[2].atributo, "reservada");*/
	/*strcpy(TS[3].cadena, "ESCRIBIR");	strcpy(TS[3].atributo, "reservada");*/
	/* A partir de este indiceActualTS = 3, se empiezan a almacenar los IDENTIFICADORES */
	indiceActualTS = 3;
}
int esEstadoFinal(int estado){
	switch (estado){
		case 0:
		case 1:
		case 3:
		case 11: 
		case 14:
			return 0;
	}
	return 1;
}