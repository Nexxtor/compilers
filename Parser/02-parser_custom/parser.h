#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Tipos de nodos del árbol sintáctico
typedef enum {
    NODO_EXPRESION,
    NODO_TERMINO,
    NODO_FACTOR,
    NODO_IDENTIFICADOR,
    NODO_SUMA,
    NODO_MULTIPLICACION,
    NODO_PARENTESIS
} TipoNodo;

// Estructura para nodos del árbol sintáctico
typedef struct NodoArbol {
    TipoNodo tipo;
    char *valor;
    struct NodoArbol *izquierdo;
    struct NodoArbol *derecho;
    int linea;
    int columna;
} NodoArbol;

// Estructura para el parser
typedef struct {
    Lexer *lexer;
    Token token_actual;
    int hay_error;
    char mensaje_error[256];
} Parser;

// Funciones del parser
Parser* crear_parser(const char *entrada);
void liberar_parser(Parser *parser);
NodoArbol* analizar(Parser *parser);

// Funciones para el árbol sintáctico
NodoArbol* crear_nodo(TipoNodo tipo, const char *valor, NodoArbol *izq, NodoArbol *der, int linea, int columna);
void liberar_arbol(NodoArbol *nodo);
void imprimir_arbol(NodoArbol *nodo, int nivel);
char* tipo_nodo_a_string(TipoNodo tipo);

// Funciones de análisis sintáctico (gramática LL(1))
NodoArbol* analizar_E(Parser *parser);
NodoArbol* analizar_E_prima(Parser *parser, NodoArbol *izquierdo);
NodoArbol* analizar_T(Parser *parser);
NodoArbol* analizar_T_prima(Parser *parser, NodoArbol *izquierdo);
NodoArbol* analizar_F(Parser *parser);

// Funciones auxiliares del parser
void avanzar_token(Parser *parser);
int coincidir(Parser *parser, TipoToken tipo_esperado);
void reportar_error(Parser *parser, const char *mensaje);
void imprimir_error(Parser *parser);

#endif // PARSER_H