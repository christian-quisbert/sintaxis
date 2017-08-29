#define ESTADOS     15
#define COLUMNAS    13

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

int columna(char);
TOKEN Scanner(char*);
int tablaSimbolos(char*);