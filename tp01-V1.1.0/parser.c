/**
		\file    parser.c
		\brief   Contiene las funciones que implementa el parser.
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.11.14
		\version Versión 1.1.0
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "micro.h"
#include "parser.h"
#include "rutinas.h"
#include "auxiliares.h"

/**
		\fn     Objetivo
		\brief  Objetivo del compilador para el lenguaje "micro"
		\date   2017.11.04
*/
void Objetivo (void){
	Programa();
    Match(FDT);
    Terminar();
}
/**
		\fn     Programa
		\brief  Analiza la sintáxis del codigo fuente.
		\date   2017.11.04
*/
void Programa (void){
    Comenzar();
    Match(INICIO);
    ListaSentencias();
    Match(FIN);
}
/**
		\fn     ListaSentencias
		\brief  Lee las sentencias del codigo fuente hasta el final.
		\date   2017.11.04
*/
void ListaSentencias(void){
    Sentencia();
    while(1){
        switch(ProximoToken()){
            case ID: 
            case LEER:
            case ESCRIBIR:
                Sentencia();
                break;
            default:
                return;
        }
    }
}
/*
		\fn     Sentencia
		\brief  Analiza sintaxis de una sentencia. (Empieza con ID, LEER o ESCRIBIR).
		\date   2017.11.04
*/
void Sentencia(void){
    TOKEN token = ProximoToken();
    REG_EXPRESION izquierda;
    REG_EXPRESION derecha;

    switch(token){
        case ID:
            Identificador(&izquierda);
            Match(ASIGNACION);
            Expresion(&derecha);
            Asignar(izquierda, derecha);
            Match(PUNTOYCOMA);
            break;
        case LEER:
            Match(LEER);
            Match(PARENIZQUIERDO);
            ListaIdentificadores();
            Match(PARENDERECHO);
            Match(PUNTOYCOMA);
            break;
        case ESCRIBIR:
            Match(ESCRIBIR);
            Match(PARENIZQUIERDO);
            ListaExpresiones(); 
            Match(PARENDERECHO);
            Match(PUNTOYCOMA);
            break;
        default:
            ErrorSintactico(token);
            break;
    }
}
/*
		\fn     Expresion
		\brief  Analiza la expresion de una asignacion.
		\date   2017.11.04
*/
void Expresion(REG_EXPRESION * resultado){
    REG_EXPRESION operandoIzq, operandoDer;
    REG_OPERACION op;
    TOKEN t;
    
	Primaria(&operandoIzq);
	for (t = ProximoToken(); t == SUMA || t == RESTA ; t = ProximoToken())
	{
        OperadorAditivo(&op);
        Primaria(&operandoDer);
        operandoIzq = GenInfijo(operandoIzq, &op, operandoDer);
        /*memcpy(&operandoIzq, GenInfijo(operandoIzq, op, operandoDer), sizeof(REG_EXPRESION)); */
    }
    *resultado = operandoIzq;
}
/*
		\fn     OperadorAditivo
		\brief  Analiza que el ProximoToken sea un operador.
		\date   2017.11.04
*/
void OperadorAditivo(REG_OPERACION * op){
    TOKEN token = ProximoToken();
    if(token == SUMA || token == RESTA){
        Match(token);
        *op = ProcesarOp();
    }else
        ErrorSintactico(token);
    
}
/*
		\fn     Primaria
		\brief  Analiza el contenido de una expresión.
		\date   2017.11.04
*/
void Primaria(REG_EXPRESION * resultado){
    switch(ProximoToken()){
        case ID:
            Identificador(resultado);
            break;
        case CONSTANTE:
            Match(CONSTANTE);
            *resultado = ProcesarCte();
            break;
        case PARENIZQUIERDO:
            Match(PARENIZQUIERDO);
            Expresion(resultado);
            Match(PARENDERECHO);
            break;
        default:
            return;
    }
}
/*
		\fn     ListaIdentificadores
		\brief  Analiza ID's dentro de la funcion LEER.
		\date   2017.11.04
*/
void ListaIdentificadores(void){
    TOKEN t;
    REG_EXPRESION reg;
    Identificador(&reg);
    Leer(reg);

    for(t = ProximoToken(); t == COMA; t = ProximoToken()){
        Match(COMA);
        Identificador(&reg);
        Leer(reg);
    }
}
/*
		\fn     ListaExpresiones
		\brief  Analiza "Expresiones" dentro de la funcion ESCRIBIR.
		\date   2017.11.04
*/
void ListaExpresiones(void){
    TOKEN t;
    REG_EXPRESION reg;
    Expresion(&reg);
    Escribir(reg);

    for(t = ProximoToken(); t == COMA; t = ProximoToken()){
        Match(COMA);
        Expresion(&reg);
        Escribir(reg);
    }

}
/*
		\fn     Primaria
		\brief  Procesa un ID, genera el REG semantico apropiado.
        \date   2017.11.04
        \param  REG_EXPRESION * resultado
*/
void Identificador(REG_EXPRESION * resultado){
    Match(ID);
    *resultado = ProcesarId();
}
