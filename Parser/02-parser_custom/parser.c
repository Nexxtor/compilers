#include "parser.h"

Parser* crear_parser(const char *entrada) {
    Parser *parser = (Parser*)malloc(sizeof(Parser));
    if (!parser) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el parser\n");
        return NULL;
    }
    
    parser->lexer = crear_lexer(entrada);
    if (!parser->lexer) {
        free(parser);
        return NULL;
    }
    
    parser->hay_error = 0;
    parser->mensaje_error[0] = '\0';
    
    // Obtener el primer token
    parser->token_actual = obtener_siguiente_token(parser->lexer);
    
    return parser;
}

void liberar_parser(Parser *parser) {
    if (parser) {
        if (parser->lexer) {
            liberar_lexer(parser->lexer);
        }
        liberar_token(&parser->token_actual);
        free(parser);
    }
}

void avanzar_token(Parser *parser) {
    liberar_token(&parser->token_actual);
    parser->token_actual = obtener_siguiente_token(parser->lexer);
}

int coincidir(Parser *parser, TipoToken tipo_esperado) {
    if (parser->token_actual.tipo == tipo_esperado) {
        avanzar_token(parser);
        return 1;
    }
    return 0;
}

void reportar_error(Parser *parser, const char *mensaje) {
    parser->hay_error = 1;
    snprintf(parser->mensaje_error, sizeof(parser->mensaje_error),
             "Error sintáctico en línea %d, columna %d: %s. Token encontrado: %s",
             parser->token_actual.linea, parser->token_actual.columna,
             mensaje, tipo_token_a_string(parser->token_actual.tipo));
}

void imprimir_error(Parser *parser) {
    if (parser->hay_error) {
        printf("%s\n", parser->mensaje_error);
    }
}

NodoArbol* crear_nodo(TipoNodo tipo, const char *valor, NodoArbol *izq, NodoArbol *der, int linea, int columna) {
    NodoArbol *nodo = (NodoArbol*)malloc(sizeof(NodoArbol));
    if (!nodo) {
        fprintf(stderr, "Error: No se pudo asignar memoria para el nodo\n");
        return NULL;
    }
    
    nodo->tipo = tipo;
    nodo->izquierdo = izq;
    nodo->derecho = der;
    nodo->linea = linea;
    nodo->columna = columna;
    
    if (valor) {
        nodo->valor = (char*)malloc(strlen(valor) + 1);
        if (nodo->valor) {
            strcpy(nodo->valor, valor);
        }
    } else {
        nodo->valor = NULL;
    }
    
    return nodo;
}

void liberar_arbol(NodoArbol *nodo) {
    if (nodo) {
        liberar_arbol(nodo->izquierdo);
        liberar_arbol(nodo->derecho);
        if (nodo->valor) {
            free(nodo->valor);
        }
        free(nodo);
    }
}

char* tipo_nodo_a_string(TipoNodo tipo) {
    switch (tipo) {
        case NODO_EXPRESION: return "E";
        case NODO_TERMINO: return "T";
        case NODO_FACTOR: return "F";
        case NODO_IDENTIFICADOR: return "ID";
        case NODO_SUMA: return "+";
        case NODO_MULTIPLICACION: return "*";
        case NODO_PARENTESIS: return "()";
        default: return "?";
    }
}

void imprimir_arbol(NodoArbol *nodo, int nivel) {
    if (!nodo) return;
    
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
    
    printf("%s", tipo_nodo_a_string(nodo->tipo));
    if (nodo->valor) {
        printf(": %s", nodo->valor);
    }
    printf("\n");
    
    if (nodo->izquierdo) {
        imprimir_arbol(nodo->izquierdo, nivel + 1);
    }
    if (nodo->derecho) {
        imprimir_arbol(nodo->derecho, nivel + 1);
    }
}

// E -> T E'
NodoArbol* analizar_E(Parser *parser) {
    if (parser->hay_error) return NULL;
    
    NodoArbol *termino = analizar_T(parser);
    if (!termino || parser->hay_error) return termino;
    
    return analizar_E_prima(parser, termino);
}

// E' -> + T E' | ε
NodoArbol* analizar_E_prima(Parser *parser, NodoArbol *izquierdo) {
    if (parser->hay_error) return izquierdo;
    
    if (parser->token_actual.tipo == TOKEN_SUMA) {
        int linea = parser->token_actual.linea;
        int columna = parser->token_actual.columna;
        
        avanzar_token(parser); // consumir '+'
        
        NodoArbol *termino = analizar_T(parser);
        if (!termino || parser->hay_error) return NULL;
        
        NodoArbol *nodo_suma = crear_nodo(NODO_SUMA, "+", izquierdo, termino, linea, columna);
        
        return analizar_E_prima(parser, nodo_suma);
    }
    
    // Producción epsilon
    return izquierdo;
}

// T -> F T'
NodoArbol* analizar_T(Parser *parser) {
    if (parser->hay_error) return NULL;
    
    NodoArbol *factor = analizar_F(parser);
    if (!factor || parser->hay_error) return factor;
    
    return analizar_T_prima(parser, factor);
}

// T' -> * F T' | ε
NodoArbol* analizar_T_prima(Parser *parser, NodoArbol *izquierdo) {
    if (parser->hay_error) return izquierdo;
    
    if (parser->token_actual.tipo == TOKEN_MULTIPLICACION) {
        int linea = parser->token_actual.linea;
        int columna = parser->token_actual.columna;
        
        avanzar_token(parser); // consumir '*'
        
        NodoArbol *factor = analizar_F(parser);
        if (!factor || parser->hay_error) return NULL;
        
        NodoArbol *nodo_mult = crear_nodo(NODO_MULTIPLICACION, "*", izquierdo, factor, linea, columna);
        
        return analizar_T_prima(parser, nodo_mult);
    }
    
    // Producción epsilon
    return izquierdo;
}

// F -> ( E ) | ident
NodoArbol* analizar_F(Parser *parser) {
    if (parser->hay_error) return NULL;
    
    if (parser->token_actual.tipo == TOKEN_PAREN_IZQ) {
        int linea = parser->token_actual.linea;
        int columna = parser->token_actual.columna;
        
        avanzar_token(parser); // consumir '('
        
        NodoArbol *expresion = analizar_E(parser);
        if (!expresion || parser->hay_error) return NULL;
        
        if (parser->token_actual.tipo != TOKEN_PAREN_DER) {
            reportar_error(parser, "Se esperaba ')'");
            return NULL;
        }
        
        avanzar_token(parser); // consumir ')'
        
        return crear_nodo(NODO_PARENTESIS, "()", expresion, NULL, linea, columna);
        
    } else if (parser->token_actual.tipo == TOKEN_IDENTIFICADOR) {
        int linea = parser->token_actual.linea;
        int columna = parser->token_actual.columna;
        char *valor = parser->token_actual.valor;
        
        NodoArbol *nodo = crear_nodo(NODO_IDENTIFICADOR, valor, NULL, NULL, linea, columna);
        avanzar_token(parser);
        
        return nodo;
        
    } else {
        reportar_error(parser, "Se esperaba identificador o '('");
        return NULL;
    }
}

NodoArbol* analizar(Parser *parser) {
    if (parser->token_actual.tipo == TOKEN_ERROR) {
        printf("Error léxico: %s en línea %d, columna %d\n",
               parser->token_actual.valor,
               parser->token_actual.linea,
               parser->token_actual.columna);
        return NULL;
    }
    
    NodoArbol *arbol = analizar_E(parser);
    
    if (parser->hay_error) {
        imprimir_error(parser);
        liberar_arbol(arbol);
        return NULL;
    }
    
    if (parser->token_actual.tipo != TOKEN_EOF) {
        reportar_error(parser, "Se esperaba fin de entrada");
        imprimir_error(parser);
        liberar_arbol(arbol);
        return NULL;
    }
    
    return arbol;
}