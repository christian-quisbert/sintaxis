#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "micro.h"
#include "auxiliares.h"
#include "scanner.h"

/****************************************
********** FUNCIONES AUXILIARES *********
*****************************************/
/**
		\fn     Match
		\brief  Analiza el token t
        \date   2017.11.04
        \param  TOKEN t
*/
void Match(TOKEN t){
    if(!(t == ProximoToken())) ErrorSintactico(t);
    flagToken = 0;
}
/**
		\fn     ProximoToken
		\brief  Llamo al scanner para analizar el token
		\date   2017.11.04
*/
TOKEN ProximoToken(void){
    if(!flagToken){
        tokenActual = scanner();
        if(tokenActual == ERRORLEXICO){
            ErrorLexico();
        }
        flagToken = 1;
        if(tokenActual == ID){
            Buscar(buffer);
        }
    }
    return tokenActual;
}
/*
		\fn     Generar
		\brief  Genero la instrucción que va en la MV.
        \date   2017.11.04
        \param  char * a,b,c,d
*/
void Generar(char * accion, char * v1, char * v2, char * d){
    fprintf(out,"\nInstrucción: %s %s, %s %s\n", accion, v1, v2, d);
}
/*
		\fn     Extraer
		\brief  Retorna la cadena de un registro semántico.
        \date   2017.11.04
        \param  REG_EXPRESION reg
*/
char * Extraer(REG_EXPRESION * reg){
    return reg->nombre;
}
/*
		\fn     Buscar
        \brief  Bsuca un ID en la tabla de símbolos, y (1 = Si) (0 = No).
        \date   2017.11.05
        \param  char * s
*/
int Buscar(char * s){
    int i = 0;
    while(i <= indiceActualTS){
        if(TS[i].cadena == s) return 1;
        i++;
    }    
    return 0;
}
/*
		\fn     Colocar
        \brief  Inserta un ID en la tabla de símbolos.
        \date   2017.11.05
        \param  char * s
*/
void Colocar(char * s){
    /* Actualizo el índice Actual de la TS */
    indiceActualTS++;

    strcpy(TS[indiceActualTS].cadena, s);
    strcpy(TS[indiceActualTS].atributo, "identificador");
}
/*
		\fn     Chequear
		\brief  Verifica que la cadena esté en la tabla de símbolos.
        \date   2017.11.05
        \param  char * s
*/
void Chequear(char * s){
    if(!Buscar(s)){
        Colocar(s);
        Generar("Declara", s, "Entera", "");
    }
}
/*
		\fn     ErrorLexico
		\brief  Indica por consola que hubo error léxico.
        \date   2017.11.09
*/
void ErrorLexico(void){
    printf("***Error Léxico\n");
}
/*
		\fn     ErrorLexico
		\brief  Indica por consola que hubo error sintáctico.
        \date   2017.11.09
*/
void ErrorSintactico(TOKEN token){
    printf("***Error Sintáctico\n");
}

/**************************************************************
********** FUNCIONES AUXILIARES de RUTINAS SEMANTICAS *********
***************************************************************/

/**
		\fn     Comenzar
		\brief  Inicializaciones semánticas
        \date   2017.11.05
*/
void Comenzar(void){
    flagToken = 0;
    indiceActualTS = 0;
    initTS();
}
/**
		\fn     Terminar
		\brief  Genera la instrucción para terminar la ejecución del programa.
        \date   2017.11.05
*/
void Terminar(void){
    Generar("Detiene", "", "", "");
}
/**
		\fn     Asignar
		\brief  Genera la instrucción para la asignación.
        \date   2017.11.05
*/
void Asignar(REG_EXPRESION izquierda, REG_EXPRESION derecha){
    Generar("Almacena", Extraer(&derecha), izquierda.nombre, "");
}
