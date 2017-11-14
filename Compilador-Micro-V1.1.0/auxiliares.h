/* Funciones auxiliares del Parser */
void Match(TOKEN);
TOKEN ProximoToken(void);
void Generar(char*, char*, char*, char*);
char* Extraer(REG_EXPRESION*);
int Buscar(char*);
void Colocar(char*);
void Chequear(char*);
void ErrorLexico(void);
void ErrorSintactico(TOKEN);

/*Funciones auxiliares de rutinas semánticas*/
void Comenzar(void);
void Terminar(void);
void Asignar(REG_EXPRESION, REG_EXPRESION);