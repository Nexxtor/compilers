%{
#include <stdio.h>
#include <stdlib.h>
#include "parser.tab.h"

int linea = 1;
int columna = 1;

void actualizar_posicion(char *texto);
%}

%option noyywrap

%%

[ \t]+          { actualizar_posicion(yytext); }
\n              { linea++; columna = 1; }
"+"             { actualizar_posicion(yytext); return SUMA; }
"*"             { actualizar_posicion(yytext); return MULTIPLICACION; }
"("             { actualizar_posicion(yytext); return PAREN_IZQ; }
")"             { actualizar_posicion(yytext); return PAREN_DER; }
[a-zA-Z][a-zA-Z0-9_]*  { 
                    actualizar_posicion(yytext); 
                    yylval.cadena = strdup(yytext);
                    return IDENTIFICADOR; 
                }
.               { 
                    printf("Error léxico: caracter no reconocido '%c' en línea %d, columna %d\n", 
                           yytext[0], linea, columna);
                    actualizar_posicion(yytext);
                }

%%

void actualizar_posicion(char *texto) {
    for (int i = 0; texto[i] != '\0'; i++) {
        if (texto[i] == '\n') {
            linea++;
            columna = 1;
        } else {
            columna++;
        }
    }
}

void yyerror(const char *mensaje) {
    printf("Error sintáctico en línea %d, columna %d: %s\n", linea, columna, mensaje);
}