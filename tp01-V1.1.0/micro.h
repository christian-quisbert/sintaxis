#define ESTADOS     15
#define COLUMNAS    13
#define TAMLEX      32

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


/* Estructura que representa un símbolo, en la Tabla de Símbolos */
typedef struct{
    char cadena[TAMLEX];    /* Lexema */
    TOKEN atributo;        /*INICIO, FIN, LEER, ESCRIBIR, ID */
} SIMBOLO;

/* Registros semánticos */
typedef struct{
    TOKEN clase;
    char nombre[TAMLEX];
    int valor;
} REG_EXPRESION;

typedef struct{
    char simbolo[TAMLEX];
} REG_OPERACION;


/* -----DECLARACIÓN DE LAS VARIABLES GLOBALES----- */

/* Tabla Símbolos */
SIMBOLO TS[1000];

/* Luego de leer un token se asigna a 0 */
int flagToken;

/* Variable que almacena el LEXEMA */
char buffer[TAMLEX];

/* Token actual */
TOKEN tokenActual;

/* para usar en la funcion colocar() y saber en que posición está el puntero al vector TS. */
int indiceActualTS;