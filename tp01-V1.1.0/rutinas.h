/* Rutinas semánticas y funciones auxiliares */

void Leer(REG_EXPRESION);
void Escribir(REG_EXPRESION);
REG_EXPRESION ProcesarId(void);
REG_EXPRESION ProcesarCte(void);
REG_OPERACION * ProcesarOp(void);
REG_EXPRESION GenInfijo (REG_EXPRESION, REG_OPERACION *, REG_EXPRESION);
