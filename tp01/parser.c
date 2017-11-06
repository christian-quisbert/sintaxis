/**
		\file    parser.c
		\brief   Contiene las funciones que implementa el parser
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.11.04
		\version Versión 1.0.0
*/
#include <stdio.h>
#include <string.h>
#include "funciones.h"

/**
		\fn     Match
		\brief  Analiza el token t
        \date   2017.11.04
        \param  TOKEN t
*/
void Match(TOKEN t){
    if(!(t == ProximoToken())) ErrorSintactico();
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
            Buscar(buffer, indiceTS(buffer), &tokenActual);
        }
    }
    return tokenActual;
}
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
        case ESCRIBIR:
            Match(ESCRIBIR);
            Match(PARENIZQUIERDO);
            ListaExpresiones(); 
            Match(PARENDERECHO);
            Match(PUNTOYCOMA);
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
        operandoIzq = GenInfijo(operandoIzq, op, operandoDer);
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
    switch(token){
        case SUMA:
            Match(token);
            *op = ProcesarOp();
            break;
        case RESTA:
            Match(token);
            *op = ProcesarOp();
            break;
        default:
            ErrorSintactico(token);
    }
}
/*
		\fn     Primaria
		\brief  Analiza el contenido de una expresión.
		\date   2017.11.04
*/
void Primaria(REG_EXPRESION * presul){
    TOKEN token = ProximoToken();

    switch(token){
        case ID:
            Identificador(presul);
            break;
        case CONSTANTE:
            Match(CONSTANTE);
            *presul = ProcesarCte();
            break;
        case PARENIZQUIERDO:
            Match(PARENIZQUIERDO);
            Expresion(presul);
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
        \param  REG_EXPRESION * presul
*/
void Identificador(REG_EXPRESION * presul){
    Match(ID);
    *presul = ProcesarId();
}

/****************************************
********** FUNCIONES AUXILIARES *********
*****************************************/

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
char * Extraer(REG_EXPRESION reg){
    return reg.nombre;
}
/*
		\fn     Buscar
        \brief  Bsuca un ID en la tabla de símbolos, y determina si se encuentra o nó.
        \date   2017.11.05
        \param  char * s
*/
void Buscar(char * s){
    
}
/*
		\fn     Colocar
        \brief  Inserta un ID en la tabla de símbolos.
        \date   2017.11.05
        \param  char * s
*/
void Colocar(char * s){

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
