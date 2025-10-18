%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Definición de tokens */
#define NUMERO 1
#define SUMA 2
#define RESTA 3
#define MULTIPLICACION 4
#define DIVISION 5
#define PARENTESIS_IZQ 6
#define PARENTESIS_DER 7
#define ASIGNACION 8
#define IDENTIFICADOR 9
#define FIN_LINEA 10

/* Variable global para almacenar el valor numérico */
double yylval;
char *identificador;

/* Contador de líneas */
int linea = 1;
%}

%%

[0-9]+(\.[0-9]+)?   {
                        yylval = atof(yytext);
                        printf("TOKEN: NUMERO, Valor: %.2f\n", yylval);
                        return NUMERO;
                    }

[a-zA-Z][a-zA-Z0-9]*    {
                            identificador = strdup(yytext);
                            printf("TOKEN: IDENTIFICADOR, Nombre: %s\n", identificador);
                            return IDENTIFICADOR;
                        }

"+"                 {
                        printf("TOKEN: SUMA (+)\n");
                        return SUMA;
                    }

"-"                 {
                        printf("TOKEN: RESTA (-)\n");
                        return RESTA;
                    }

"*"                 {
                        printf("TOKEN: MULTIPLICACION (*)\n");
                        return MULTIPLICACION;
                    }

"/"                 {
                        printf("TOKEN: DIVISION (/)\n");
                        return DIVISION;
                    }

"("                 {
                        printf("TOKEN: PARENTESIS_IZQ\n");
                        return PARENTESIS_IZQ;
                    }

")"                 {
                        printf("TOKEN: PARENTESIS_DER\n");
                        return PARENTESIS_DER;
                    }

"="                 {
                        printf("TOKEN: ASIGNACION (=)\n");
                        return ASIGNACION;
                    }

[ \t]+              {
                        /* Ignorar espacios en blanco */
                    }

\n                  {
                        printf("TOKEN: FIN_LINEA\n");
                        linea++;
                        return FIN_LINEA;
                    }

.                   {
                        printf("ERROR: Caracter no reconocido '%s' en línea %d\n", yytext, linea);
                    }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    printf("=== ANALIZADOR LEXICOGRAFICO - CALCULADORA ===\n");
    printf("Ingrese expresiones matemáticas (Ctrl+D para terminar):\n");
    printf("Ejemplo: x = 3.14 + 2 * (5 - 1)\n\n");
    
    int token;
    while ((token = yylex()) != 0) {
        /* El análisis se realiza en las reglas de arriba */
    }
    
    printf("\n=== ANÁLISIS COMPLETADO ===\n");
    return 0;
}