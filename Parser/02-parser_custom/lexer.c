#include "lexer.h"

Lexer* crear_lexer(const char *entrada) {
    Lexer *lexer = (Lexer*)malloc(sizeof(Lexer));
    if (!lexer) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el lexer\n");
        return NULL;
    }
    
    lexer->longitud = strlen(entrada);
    lexer->entrada = (char*)malloc(lexer->longitud + 1);
    if (!lexer->entrada) {
        fprintf(stderr, "Error: No se pudo asignar memoria para la entrada\n");
        free(lexer);
        return NULL;
    }
    
    strcpy(lexer->entrada, entrada);
    lexer->posicion = 0;
    lexer->linea = 1;
    lexer->columna = 1;
    
    return lexer;
}

void liberar_lexer(Lexer *lexer) {
    if (lexer) {
        if (lexer->entrada) {
            free(lexer->entrada);
        }
        free(lexer);
    }
}

void saltar_espacios(Lexer *lexer) {
    while (lexer->posicion < lexer->longitud) {
        char c = lexer->entrada[lexer->posicion];
        
        if (c == ' ' || c == '\t') {
            lexer->posicion++;
            lexer->columna++;
        } else if (c == '\n') {
            lexer->posicion++;
            lexer->linea++;
            lexer->columna = 1;
        } else {
            break;
        }
    }
}

Token crear_token(TipoToken tipo, const char *valor, int linea, int columna) {
    Token token;
    token.tipo = tipo;
    token.linea = linea;
    token.columna = columna;
    
    if (valor) {
        token.valor = (char*)malloc(strlen(valor) + 1);
        if (token.valor) {
            strcpy(token.valor, valor);
        }
    } else {
        token.valor = NULL;
    }
    
    return token;
}

Token leer_identificador(Lexer *lexer) {
    int inicio = lexer->posicion;
    int linea = lexer->linea;
    int columna = lexer->columna;
    
    // Leer el primer carácter (debe ser letra)
    if (!isalpha(lexer->entrada[lexer->posicion])) {
        return crear_token(TOKEN_ERROR, "Identificador debe comenzar con letra", linea, columna);
    }
    
    // Leer el resto del identificador
    while (lexer->posicion < lexer->longitud) {
        char c = lexer->entrada[lexer->posicion];
        if (isalnum(c) || c == '_') {
            lexer->posicion++;
            lexer->columna++;
        } else {
            break;
        }
    }
    
    // Extraer el identificador
    int longitud = lexer->posicion - inicio;
    char *identificador = (char*)malloc(longitud + 1);
    if (!identificador) {
        return crear_token(TOKEN_ERROR, "Error de memoria", linea, columna);
    }
    
    strncpy(identificador, &lexer->entrada[inicio], longitud);
    identificador[longitud] = '\0';
    
    Token token = crear_token(TOKEN_IDENTIFICADOR, identificador, linea, columna);
    free(identificador);
    
    return token;
}

Token obtener_siguiente_token(Lexer *lexer) {
    saltar_espacios(lexer);
    
    if (lexer->posicion >= lexer->longitud) {
        return crear_token(TOKEN_EOF, NULL, lexer->linea, lexer->columna);
    }
    
    char c = lexer->entrada[lexer->posicion];
    int linea = lexer->linea;
    int columna = lexer->columna;
    
    switch (c) {
        case '+':
            lexer->posicion++;
            lexer->columna++;
            return crear_token(TOKEN_SUMA, "+", linea, columna);
            
        case '*':
            lexer->posicion++;
            lexer->columna++;
            return crear_token(TOKEN_MULTIPLICACION, "*", linea, columna);
            
        case '(':
            lexer->posicion++;
            lexer->columna++;
            return crear_token(TOKEN_PAREN_IZQ, "(", linea, columna);
            
        case ')':
            lexer->posicion++;
            lexer->columna++;
            return crear_token(TOKEN_PAREN_DER, ")", linea, columna);
            
        default:
            if (isalpha(c)) {
                return leer_identificador(lexer);
            } else {
                // Carácter no reconocido
                char error_msg[100];
                snprintf(error_msg, sizeof(error_msg), "Carácter no reconocido: '%c'", c);
                lexer->posicion++;
                lexer->columna++;
                return crear_token(TOKEN_ERROR, error_msg, linea, columna);
            }
    }
}

void liberar_token(Token *token) {
    if (token && token->valor) {
        free(token->valor);
        token->valor = NULL;
    }
}

char* tipo_token_a_string(TipoToken tipo) {
    switch (tipo) {
        case TOKEN_IDENTIFICADOR: return "IDENTIFICADOR";
        case TOKEN_SUMA: return "SUMA";
        case TOKEN_MULTIPLICACION: return "MULTIPLICACION";
        case TOKEN_PAREN_IZQ: return "PAREN_IZQ";
        case TOKEN_PAREN_DER: return "PAREN_DER";
        case TOKEN_EOF: return "EOF";
        case TOKEN_ERROR: return "ERROR";
        default: return "DESCONOCIDO";
    }
}

void imprimir_token(Token *token) {
    printf("Token: %s", tipo_token_a_string(token->tipo));
    if (token->valor) {
        printf(" [%s]", token->valor);
    }
    printf(" en línea %d, columna %d\n", token->linea, token->columna);
}