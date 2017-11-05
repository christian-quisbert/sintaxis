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

/* Registro semántico */
typedef struct{
    TOKEN clase;
    char nombre[TAMLEX];
    int valor;
} REG_EXPRESION;


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
void Match(TOKEN t);
TOKEN ProximoToken(void);
void objetivo (void);
void Programa (void);
void ListaSentencias(void);
void Sentencia(void);
void Expresion(REG_EXPRESION *);
void OperadorAditivo (void);
void Primaria(REG_EXPRESION *);
void ListaIdentificadores(void);
void ListaExpresiones(void);

void Identificador(REG_EXPRESION *);
REG_EXPRESION ProcesarId(void);
void Chequear(char * s);
void Colocar(char *);
void Generar(char *, char *, char *, char *);
char * Extraer(REG_EXPRESION);