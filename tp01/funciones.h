#define ESTADOS     15
#define COLUMNAS    13

#define TAMLEX  32

FILE * in;
FILE * out;

typedef enum{
    INICIO,
    FIN,
    LEER,
    ESCRIBIR,
    ID,
    CONSTANTE,
    PARENIZQUIERDO,
    PARENDERECHO,
    PUNTOYCOMA,
    COMA,
    ASIGNACION,
    SUMA,
    RESTA,
    FDT,
    ERRORLEXICO
} TOKEN;

/* Registros semánticos */
typedef struct{
    TOKEN clase;
    char nombre[TAMLEX];
    int valor;
} REG_EXPRESION;

typedef struct{
    char simbolo[TAMLEX];
} REG_OPERACION;

/* Luego de leer un token se asigna a 0 */
int flagToken;
/* Variable que almacena el LEXEMA */
char buffer[TAMLEX];
/* Token actual */
TOKEN tokenActual;


/* Prototipos de función */
/* Scanner */
int columna(char);
TOKEN scanner();
int tablaSimbolos(char*);

/* Parser*/
void Match(TOKEN);
TOKEN ProximoToken(void);
void objetivo (void);
void Programa (void);
void ListaSentencias(void);
void Sentencia(void);
void Expresion(REG_EXPRESION*);
void OperadorAditivo(REG_OPERACION*);
void Primaria(REG_EXPRESION*);
void ListaIdentificadores(void);
void ListaExpresiones(void);
void Identificador(REG_EXPRESION*);

/* Funciones auxiliares del Parser */
void Generar(char*, char*, char*, char*);
char* Extraer(REG_EXPRESION);
void Buscar(char*);
void Colocar(char*);
void Chequear(char*);

/* Rutinas semánticas y funciones auxiliares */
void Comenzar(void);
void terminar(void);
void Asignar(REG_EXPRESION, REG_EXPRESION);
void Leer(REG_EXPRESION);
void Escribir(REG_EXPRESION);
REG_EXPRESION ProcesarId(void);
REG_EXPRESION ProcesarCte(void);
REG_OPERACION ProcesarOp(void);
REG_EXPRESION GenInfijo(REG_EXPRESION, REG_OPERACION, REG_EXPRESION);