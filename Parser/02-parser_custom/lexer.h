#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tipos de tokens
typedef enum {
    TOKEN_IDENTIFICADOR,
    TOKEN_SUMA,
    TOKEN_MULTIPLICACION,
    TOKEN_PAREN_IZQ,
    TOKEN_PAREN_DER,
    TOKEN_EOF,
    TOKEN_ERROR
} TipoToken;

// Estructura para un token
typedef struct {
    TipoToken tipo;
    char *valor;
    int linea;
    int columna;
} Token;

// Estructura para el lexer
typedef struct {
    char *entrada;
    int posicion;
    int linea;
    int columna;
    int longitud;
} Lexer;

// Funciones del lexer
Lexer* crear_lexer(const char *entrada);
void liberar_lexer(Lexer *lexer);
Token obtener_siguiente_token(Lexer *lexer);
void liberar_token(Token *token);
char* tipo_token_a_string(TipoToken tipo);
void imprimir_token(Token *token);

// Funciones auxiliares
void saltar_espacios(Lexer *lexer);
Token crear_token(TipoToken tipo, const char *valor, int linea, int columna);
Token leer_identificador(Lexer *lexer);

#endif // LEXER_H