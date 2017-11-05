/**
		\file    parser.c
		\brief   Contiene las funciones que implementa el parser
		\author  Chistian Leonel Quisbert (christianquisbert@gmail.com)
		\date    2017.11.04
		\version Versión 1.0.0
*/
#include <stdio.h>
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
            Buscar(buffer, tablaSimbolos, &tokenActual);
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
}
/**
		\fn     Programa
		\brief  Analiza la sintáxis del codigo fuente.
		\date   2017.11.04
*/
void Programa (void){
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
    switch(token){
        case ID:
            Match(ID);
            Match(ASIGNACION);
            Expresion();
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
    }
    *resultado = operandoIzq;
}
/*
		\fn     OperadorAditivo
		\brief  Analiza que el ProximoToken sea un operador.
		\date   2017.11.04
*/
void OperadorAditivo (void){
	TOKEN token = ProximoToken();
	if(token == SUMA || token == RESTA)
		Match(token);
	else
		ErrorSintactico(token);
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
            Identificador(ID);
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
        Match(COMA);
    }

}

/*---------------------------------------------------------*/

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
		\fn     Chequear
		\brief  Verifica que la cadena esté en la tabla de símbolos.
        \date   2017.11.04
        \param  char * s
*/
void Chequear(char * s){
    if(!Buscar(s)){
        Colocar(s);
        Generar("Declara", s, "Entera", "");
    }
}
/*
		\fn     Colocar
        \brief  Inserta un ID en la tabla de símbolos.
        \date   2017.11.04
        \param  char * s
*/
void Colocar(char * s){

}
/*
		\fn     Generar
		\brief  Genero la instrucción que va en la MV.
        \date   2017.11.04
        \param  char * a,b,c,d
*/
void Generar(char * accion, char * id, char * tipo, char * d){
    fprintf(out,"\nInstrucción: %s %s, %s %s\n", accion, id, tipo, d);
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

