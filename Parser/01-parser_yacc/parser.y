%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern void yyerror(const char *mensaje);
extern int linea, columna;

// Estructura para el árbol sintáctico
typedef struct nodo {
    char *tipo;
    char *valor;
    struct nodo *izquierdo;
    struct nodo *derecho;
} Nodo;

Nodo* crear_nodo(char *tipo, char *valor, Nodo *izq, Nodo *der);
void imprimir_arbol(Nodo *nodo, int nivel);
void liberar_arbol(Nodo *nodo);

Nodo *raiz_arbol = NULL;
%}

%union {
    char *cadena;
    struct nodo *nodo;
}

%token <cadena> IDENTIFICADOR
%token SUMA MULTIPLICACION PAREN_IZQ PAREN_DER

%type <nodo> E E_prima T T_prima F

%start E

%%

E : T E_prima {
        if ($2 != NULL) {
            $$ = crear_nodo("E", "+", $1, $2);
        } else {
            $$ = $1;
        }
        raiz_arbol = $$;
    }
  ;

E_prima : SUMA T E_prima {
            if ($3 != NULL) {
                $$ = crear_nodo("E'", "+", $2, $3);
            } else {
                $$ = $2;
            }
        }
        | /* epsilon */ { $$ = NULL; }
        ;

T : F T_prima {
        if ($2 != NULL) {
            $$ = crear_nodo("T", "*", $1, $2);
        } else {
            $$ = $1;
        }
    }
  ;

T_prima : MULTIPLICACION F T_prima {
            if ($3 != NULL) {
                $$ = crear_nodo("T'", "*", $2, $3);
            } else {
                $$ = $2;
            }
        }
        | /* epsilon */ { $$ = NULL; }
        ;

F : PAREN_IZQ E PAREN_DER {
        $$ = crear_nodo("F", "()", $2, NULL);
    }
  | IDENTIFICADOR {
        $$ = crear_nodo("F", $1, NULL, NULL);
    }
  ;

%%

Nodo* crear_nodo(char *tipo, char *valor, Nodo *izq, Nodo *der) {
    Nodo *nuevo = (Nodo*)malloc(sizeof(Nodo));
    nuevo->tipo = strdup(tipo);
    nuevo->valor = strdup(valor);
    nuevo->izquierdo = izq;
    nuevo->derecho = der;
    return nuevo;
}

void imprimir_arbol(Nodo *nodo, int nivel) {
    if (nodo == NULL) return;
    
    for (int i = 0; i < nivel; i++) {
        printf("  ");
    }
    
    printf("%s: %s\n", nodo->tipo, nodo->valor);
    
    if (nodo->izquierdo != NULL) {
        imprimir_arbol(nodo->izquierdo, nivel + 1);
    }
    if (nodo->derecho != NULL) {
        imprimir_arbol(nodo->derecho, nivel + 1);
    }
}

void liberar_arbol(Nodo *nodo) {
    if (nodo == NULL) return;
    
    liberar_arbol(nodo->izquierdo);
    liberar_arbol(nodo->derecho);
    free(nodo->tipo);
    free(nodo->valor);
    free(nodo);
}

int main() {
    printf("=== PARSER LL(1) CON LEX/YACC ===\n");
    printf("Gramática:\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | ε\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' | ε\n");
    printf("F  -> ( E ) | ident\n\n");
    
    printf("Ingrese una expresión (Ctrl+D para terminar):\n");
    
    if (yyparse() == 0) {
        printf("\n=== ANÁLISIS SINTÁCTICO EXITOSO ===\n");
        printf("Árbol de análisis sintáctico:\n");
        imprimir_arbol(raiz_arbol, 0);
        liberar_arbol(raiz_arbol);
    } else {
        printf("\n=== ERROR EN EL ANÁLISIS SINTÁCTICO ===\n");
    }
    
    return 0;
}