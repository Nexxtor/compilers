#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Definición de tokens */
typedef enum {
    TOKEN_EOF = 0,
    TOKEN_NUMERO = 1,
    TOKEN_SUMA = 2,
    TOKEN_RESTA = 3,
    TOKEN_MULTIPLICACION = 4,
    TOKEN_DIVISION = 5,
    TOKEN_PARENTESIS_IZQ = 6,
    TOKEN_PARENTESIS_DER = 7,
    TOKEN_ASIGNACION = 8,
    TOKEN_IDENTIFICADOR = 9,
    TOKEN_FIN_LINEA = 10,
    TOKEN_ERROR = -1
} TipoToken;

/* Estructura para representar un token */
typedef struct {
    TipoToken tipo;
    double valor_numerico;
    char lexema[256];
    int linea;
    int columna;
} Token;

/* Variables globales del analizador */
static FILE *entrada = NULL;
static int caracter_actual = 0;
static int linea_actual = 1;
static int columna_actual = 1;
static int fin_archivo = 0;

/* Prototipos de funciones */
void inicializar_analizador(FILE *archivo);
int leer_caracter(void);
void retroceder_caracter(void);
void saltar_espacios(void);
Token leer_numero(void);
Token leer_identificador(void);
Token obtener_siguiente_token(void);
void imprimir_token(Token token);
const char* nombre_token(TipoToken tipo);

/* Inicializar el analizador lexicográfico */
void inicializar_analizador(FILE *archivo) {
    entrada = archivo;
    caracter_actual = 0;
    linea_actual = 1;
    columna_actual = 1;
    fin_archivo = 0;
}

/* Leer el siguiente caracter del archivo */
int leer_caracter(void) {
    if (fin_archivo) {
        return EOF;
    }
    
    caracter_actual = fgetc(entrada);
    
    if (caracter_actual == EOF) {
        fin_archivo = 1;
        return EOF;
    }
    
    if (caracter_actual == '\n') {
        linea_actual++;
        columna_actual = 1;
    } else {
        columna_actual++;
    }
    
    return caracter_actual;
}

/* Retroceder un caracter (simulación simple) */
void retroceder_caracter(void) {
    if (!fin_archivo && caracter_actual != EOF) {
        ungetc(caracter_actual, entrada);
        if (caracter_actual == '\n') {
            linea_actual--;
        } else {
            columna_actual--;
        }
    }
}

/* Saltar espacios en blanco y tabulaciones */
void saltar_espacios(void) {
    while (leer_caracter() != EOF && (caracter_actual == ' ' || caracter_actual == '\t')) {
        /* Continuar leyendo hasta encontrar un caracter no-espacio */
    }
    
    /* Retroceder el último caracter leído si no es espacio */
    if (caracter_actual != EOF && caracter_actual != ' ' && caracter_actual != '\t') {
        retroceder_caracter();
    }
}

/* Leer un número (entero o decimal) */
Token leer_numero(void) {
    Token token;
    char buffer[256];
    int indice = 0;
    int tiene_punto = 0;
    
    token.tipo = TOKEN_NUMERO;
    token.linea = linea_actual;
    token.columna = columna_actual;
    
    /* Leer dígitos y posible punto decimal */
    while (leer_caracter() != EOF) {
        if (isdigit(caracter_actual)) {
            buffer[indice++] = caracter_actual;
        } else if (caracter_actual == '.' && !tiene_punto) {
            tiene_punto = 1;
            buffer[indice++] = caracter_actual;
        } else {
            /* Caracter no pertenece al número, retroceder */
            retroceder_caracter();
            break;
        }
    }
    
    buffer[indice] = '\0';
    strcpy(token.lexema, buffer);
    token.valor_numerico = atof(buffer);
    
    return token;
}

/* Leer un identificador */
Token leer_identificador(void) {
    Token token;
    char buffer[256];
    int indice = 0;
    
    token.tipo = TOKEN_IDENTIFICADOR;
    token.linea = linea_actual;
    token.columna = columna_actual;
    
    /* Leer letras y dígitos (sin guión bajo para consistencia con Flex) */
    while (leer_caracter() != EOF) {
        if (isalpha(caracter_actual) || isdigit(caracter_actual)) {
            buffer[indice++] = caracter_actual;
        } else {
            /* Caracter no pertenece al identificador, retroceder */
            retroceder_caracter();
            break;
        }
    }
    
    buffer[indice] = '\0';
    strcpy(token.lexema, buffer);
    token.valor_numerico = 0.0;
    
    return token;
}

/* Obtener el siguiente token */
Token obtener_siguiente_token(void) {
    Token token;
    
    /* Saltar espacios en blanco */
    saltar_espacios();
    
    /* Leer el siguiente caracter */
    if (leer_caracter() == EOF) {
        token.tipo = TOKEN_EOF;
        token.linea = linea_actual;
        token.columna = columna_actual;
        strcpy(token.lexema, "EOF");
        token.valor_numerico = 0.0;
        return token;
    }
    
    /* Analizar el caracter actual */
    token.linea = linea_actual;
    token.columna = columna_actual;
    
    if (isdigit(caracter_actual)) {
        /* Es un número, retroceder y leer completo */
        retroceder_caracter();
        return leer_numero();
    }
    
    if (isalpha(caracter_actual)) {
        /* Es un identificador, retroceder y leer completo */
        retroceder_caracter();
        return leer_identificador();
    }
    
    /* Operadores y símbolos de un solo caracter */
    switch (caracter_actual) {
        case '+':
            token.tipo = TOKEN_SUMA;
            strcpy(token.lexema, "+");
            break;
        case '-':
            token.tipo = TOKEN_RESTA;
            strcpy(token.lexema, "-");
            break;
        case '*':
            token.tipo = TOKEN_MULTIPLICACION;
            strcpy(token.lexema, "*");
            break;
        case '/':
            token.tipo = TOKEN_DIVISION;
            strcpy(token.lexema, "/");
            break;
        case '(':
            token.tipo = TOKEN_PARENTESIS_IZQ;
            strcpy(token.lexema, "(");
            break;
        case ')':
            token.tipo = TOKEN_PARENTESIS_DER;
            strcpy(token.lexema, ")");
            break;
        case '=':
            token.tipo = TOKEN_ASIGNACION;
            strcpy(token.lexema, "=");
            break;
        case '\n':
            token.tipo = TOKEN_FIN_LINEA;
            strcpy(token.lexema, "\\n");
            break;
        default:
            token.tipo = TOKEN_ERROR;
            sprintf(token.lexema, "%c", caracter_actual);
            break;
    }
    
    token.valor_numerico = 0.0;
    return token;
}

/* Obtener el nombre del token para imprimir */
const char* nombre_token(TipoToken tipo) {
    switch (tipo) {
        case TOKEN_NUMERO: return "NUMERO";
        case TOKEN_SUMA: return "SUMA";
        case TOKEN_RESTA: return "RESTA";
        case TOKEN_MULTIPLICACION: return "MULTIPLICACION";
        case TOKEN_DIVISION: return "DIVISION";
        case TOKEN_PARENTESIS_IZQ: return "PARENTESIS_IZQ";
        case TOKEN_PARENTESIS_DER: return "PARENTESIS_DER";
        case TOKEN_ASIGNACION: return "ASIGNACION";
        case TOKEN_IDENTIFICADOR: return "IDENTIFICADOR";
        case TOKEN_FIN_LINEA: return "FIN_LINEA";
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";
        default: return "DESCONOCIDO";
    }
}

/* Imprimir información del token */
void imprimir_token(Token token) {
    printf("TOKEN: %s", nombre_token(token.tipo));
    
    switch (token.tipo) {
        case TOKEN_NUMERO:
            printf(", Valor: %.2f", token.valor_numerico);
            break;
        case TOKEN_IDENTIFICADOR:
            printf(", Nombre: %s", token.lexema);
            break;
        case TOKEN_SUMA:
        case TOKEN_RESTA:
        case TOKEN_MULTIPLICACION:
        case TOKEN_DIVISION:
        case TOKEN_ASIGNACION:
            printf(" (%s)", token.lexema);
            break;
        case TOKEN_ERROR:
            printf(": Caracter no reconocido '%s' en línea %d, columna %d", 
                   token.lexema, token.linea, token.columna);
            break;
        default:
            break;
    }
    
    printf("\n");
}

/* Función principal */
int main(int argc, char *argv[]) {
    FILE *archivo_entrada = stdin;
    
    printf("=== ANALIZADOR LEXICOGRAFICO - CALCULADORA (C PURO) ===\n");
    printf("Implementación sin Flex - Análisis caracter por caracter\n");
    
    /* Si se proporciona un archivo como argumento */
    if (argc > 1) {
        archivo_entrada = fopen(argv[1], "r");
        if (!archivo_entrada) {
            fprintf(stderr, "Error: No se puede abrir el archivo '%s'\n", argv[1]);
            return 1;
        }
        printf("Analizando archivo: %s\n", argv[1]);
    } else {
        printf("Ingrese expresiones matemáticas (Ctrl+D para terminar):\n");
        printf("Ejemplo: x = 3.14 + 2 * (5 - 1)\n");
    }
    
    printf("\n");
    
    /* Inicializar el analizador */
    inicializar_analizador(archivo_entrada);
    
    /* Procesar tokens hasta el final del archivo */
    Token token;
    do {
        token = obtener_siguiente_token();
        if (token.tipo != TOKEN_EOF) {
            imprimir_token(token);
        }
    } while (token.tipo != TOKEN_EOF);
    
    printf("\n=== ANÁLISIS COMPLETADO ===\n");
    printf("Líneas procesadas: %d\n", linea_actual - 1);
    
    /* Cerrar archivo si no es stdin */
    if (archivo_entrada != stdin) {
        fclose(archivo_entrada);
    }
    
    return 0;
}