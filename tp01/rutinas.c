/**
		\file    rutinas.c
		\brief   Contiene las rutinas semanticas y funciones auxiliares.
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.11.05
		\version Versión 1.0.0
*/
#include <stdio.h>
#include <string.h>
#include "funciones.h"

/****************************************
********** FUNCIONES AUXILIARES *********
*****************************************/

/**
		\fn     Comenzar
		\brief  Inicializaciones semánticas
        \date   2017.11.05
*/
void Comenzar(void){
    flagToken = 0;
}
/**
		\fn     Terminar
		\brief  Genera la instrucción para terminar la ejecución del programa.
        \date   2017.11.05
*/
void terminar(void){
    Generar("Detiene", "", "", "");
}
/**
		\fn     Asignar
		\brief  Genera la instrucción para la asignación.
        \date   2017.11.05
*/
void Asignar(REG_EXPRESION izquierda, REG_EXPRESION derecha){
    Generar("Almacena", Extraer(derecha), izquierda.nombre, "");
}

/****************************************
*********** RUTINAS SEMÁNTICAS **********
*****************************************/
/**
		\fn     Leer
		\brief  Genera la instrucción para Leer.
        \date   2017.11.05
*/
void Leer(REG_EXPRESION in){
    Generar("Read", in.nombre, "Entera", "");
}
/**
		\fn     Escribir
		\brief  Genera la instrucción para Escribir.
        \date   2017.11.05
*/
void Escribir(REG_EXPRESION out){
    Generar("Write", Extraer(out), "Entera", "");
}
/*
		\fn     ProcesarId
		\brief  Declara ID y construye el correspondiente registro semántico (struct).
        \date   2017.11.04
        \return REG_EXPRESION        
*/
REG_EXPRESION ProcesarId(void){
    REG_EXPRESION t;
    Chequear(buffer);
    t.clase = ID;
    strcpy(t.nombre, buffer);
    return t;
}
/*
		\fn     ProcesarCte
		\brief  Convierte cadena que representa un NÚMERO a número entero y construye registro semántico.
        \date   2017.11.04
        \return REG_EXPRESION         
*/
REG_EXPRESION ProcesarCte(void){
    REG_EXPRESION t;
    t.clase = CONSTANTE;
    sscanf(buffer, "%d", &t.valor);
    return t;
}
/*
		\fn     ProcesarOp
		\brief  Construye registro semántico de un Operador.
        \date   2017.11.04
        \return REG_EXPRESION         
*/
REG_OPERACION ProcesarOp(void){
    REG_OPERACION op;
    sscanf(buffer, "%s", &op.simbolo);
    return op;
}
/*
		\fn     GenInfijo
		\brief  Genera la instrucción para una operación INFIJA y construye un registro semántico con el resultado.
		\date   2017.11.04
*/
REG_EXPRESION GenInfijo(REG_EXPRESION e1, REG_OPERACION operador, REG_EXPRESION e2){
    REG_EXPRESION reg;
    static unsigned int numTemp = 1;    /*Se ejecuta solo la 1era vez que ingresa a la función*/
    char cadTemp[TAMLEX] = "Temp&";
    char cadNum[TAMLEX];
    char cadOp[TAMLEX];

    if(operador.simbolo[0] == "-") strcpy(cadOp,"Resta");
    if(operador.simbolo[0] == "+") strcpy(cadOp,"Suma");

    sprintf(cadNum,"%d",numTemp);   /*Convierte a numTemp(INT) en cadena, y lo guarda en cadNum*/
    numTemp ++;
    strcat(cadTemp,cadNum);

    if(e1.clase == ID) Chequear(Extraer(e1));
    if(e2.clase == ID) Chequear(Extraer(e2));
    Chequear(cadTemp);  /* ??? */
    Generar(cadOp, Extraer(e1), Extraer(e2), cadTemp);
    strcpy(reg.nombre, cadTemp);
    return reg;
}