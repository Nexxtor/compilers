#include "parser.h"

void mostrar_ayuda() {
    printf("=== PARSER LL(1) PERSONALIZADO EN C ===\n");
    printf("Gramática implementada:\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | ε\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' | ε\n");
    printf("F  -> ( E ) | ident\n\n");
    
    printf("Ejemplos válidos:\n");
    printf("  a\n");
    printf("  a + b\n");
    printf("  a * b\n");
    printf("  (a + b)\n");
    printf("  a + b * c\n");
    printf("  (a + b) * c\n\n");
}

void procesar_entrada(const char *entrada) {
    printf("🔍 Analizando: %s\n", entrada);
    printf("----------------------------------------\n");
    
    Parser *parser = crear_parser(entrada);
    if (!parser) {
        printf("❌ Error: No se pudo crear el parser\n");
        return;
    }
    
    NodoArbol *arbol = analizar(parser);
    
    if (arbol) {
        printf("✅ ANÁLISIS SINTÁCTICO EXITOSO\n");
        printf("Árbol de análisis sintáctico:\n");
        imprimir_arbol(arbol, 0);
        liberar_arbol(arbol);
    } else {
        printf("❌ ERROR EN EL ANÁLISIS SINTÁCTICO\n");
    }
    
    liberar_parser(parser);
    printf("----------------------------------------\n\n");
}

void modo_interactivo() {
    char entrada[256];
    
    mostrar_ayuda();
    printf("Modo interactivo - Ingrese expresiones (escriba 'salir' para terminar):\n\n");
    
    while (1) {
        printf(">>> ");
        fflush(stdout);
        
        if (!fgets(entrada, sizeof(entrada), stdin)) {
            break;
        }
        
        // Eliminar el salto de línea
        entrada[strcspn(entrada, "\n")] = '\0';
        
        // Verificar comando de salida
        if (strcmp(entrada, "salir") == 0 || strcmp(entrada, "exit") == 0) {
            break;
        }
        
        // Saltar líneas vacías
        if (strlen(entrada) == 0) {
            continue;
        }
        
        procesar_entrada(entrada);
    }
    
    printf("¡Hasta luego!\n");
}

void procesar_archivo(const char *nombre_archivo) {
    FILE *archivo = fopen(nombre_archivo, "r");
    if (!archivo) {
        printf("❌ Error: No se pudo abrir el archivo '%s'\n", nombre_archivo);
        return;
    }
    
    printf("📁 Procesando archivo: %s\n", nombre_archivo);
    printf("========================================\n\n");
    
    char linea[256];
    int numero_linea = 1;
    
    while (fgets(linea, sizeof(linea), archivo)) {
        // Eliminar el salto de línea
        linea[strcspn(linea, "\n")] = '\0';
        
        // Saltar líneas vacías y comentarios
        if (strlen(linea) == 0 || linea[0] == '#') {
            numero_linea++;
            continue;
        }
        
        printf("Línea %d: ", numero_linea);
        procesar_entrada(linea);
        numero_linea++;
    }
    
    fclose(archivo);
    printf("✅ Procesamiento del archivo completado\n");
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Modo interactivo
        modo_interactivo();
    } else if (argc == 2) {
        // Procesar archivo
        procesar_archivo(argv[1]);
    } else if (argc == 3 && strcmp(argv[1], "-e") == 0) {
        // Procesar expresión directa
        mostrar_ayuda();
        procesar_entrada(argv[2]);
    } else {
        printf("Uso:\n");
        printf("  %s                    # Modo interactivo\n", argv[0]);
        printf("  %s <archivo>          # Procesar archivo\n", argv[0]);
        printf("  %s -e \"expresión\"     # Procesar expresión directa\n", argv[0]);
        printf("\nEjemplos:\n");
        printf("  %s test_input.txt\n", argv[0]);
        printf("  %s -e \"a + b * c\"\n", argv[0]);
        return 1;
    }
    
    return 0;
}