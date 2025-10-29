# Makefile para Parser LL(1) Personalizado en C
# Gramática: E -> T E' | E' -> + T E' | ε | T -> F T' | T' -> * F T' | ε | F -> ( E ) | ident

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -O2
TARGET = parser
SOURCES = main.c lexer.c parser.c
HEADERS = lexer.h parser.h
OBJECTS = $(SOURCES:.c=.o)

# Archivos de prueba
TEST_INPUT = test_input.txt
TEST_ERRORS = test_errores.txt
EXAMPLES = ejemplos.txt

.PHONY: all run test clean test-errors test-all info check-tools help debug

# Regla principal
all: check-tools $(TARGET)
	@echo "✅ Compilación completada exitosamente"
	@echo "📋 Ejecuta 'make run' para probar el parser"
	@echo "📋 Ejecuta 'make test' para ejecutar las pruebas"

# Compilar el parser
$(TARGET): $(OBJECTS)
	@echo "🔨 Enlazando parser LL(1)..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "✅ Parser compilado: $(TARGET)"

# Compilar archivos objeto
%.o: %.c $(HEADERS)
	@echo "🔧 Compilando $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Ejecutar el parser interactivamente
run: $(TARGET)
	@echo "🚀 Ejecutando parser LL(1) en modo interactivo:"
	@echo "📝 Ejemplos válidos: a, a+b, a*b, (a+b)*c, a+b*c"
	@echo "📝 Escriba 'salir' para terminar"
	./$(TARGET)

# Ejecutar pruebas con casos válidos
test: $(TARGET) $(TEST_INPUT)
	@echo "🧪 Ejecutando pruebas con casos válidos..."
	@echo "📁 Archivo de prueba: $(TEST_INPUT)"
	@echo "========================================"
	@if [ -f $(TEST_INPUT) ]; then \
		./$(TARGET) $(TEST_INPUT); \
	else \
		echo "❌ Archivo $(TEST_INPUT) no encontrado"; \
	fi

# Ejecutar pruebas con casos de error
test-errors: $(TARGET) $(TEST_ERRORS)
	@echo "🧪 Ejecutando pruebas con casos de error..."
	@echo "📁 Archivo de prueba: $(TEST_ERRORS)"
	@echo "========================================"
	@if [ -f $(TEST_ERRORS) ]; then \
		./$(TARGET) $(TEST_ERRORS); \
	else \
		echo "❌ Archivo $(TEST_ERRORS) no encontrado"; \
	fi

# Ejecutar todas las pruebas
test-all: test test-errors
	@echo "✅ Todas las pruebas completadas"

# Probar expresión específica
test-expr: $(TARGET)
	@echo "🧪 Probando expresión específica..."
	@read -p "Ingrese la expresión: " expr; \
	./$(TARGET) -e "$$expr"

# Mostrar ejemplos
ejemplos: $(EXAMPLES)
	@echo "📚 Ejemplos de uso del parser LL(1):"
	@echo "======================================"
	@if [ -f $(EXAMPLES) ]; then \
		cat $(EXAMPLES); \
	else \
		echo "❌ Archivo $(EXAMPLES) no encontrado"; \
	fi

# Compilar en modo debug
debug: CFLAGS += -DDEBUG -g3
debug: clean $(TARGET)
	@echo "🐛 Parser compilado en modo debug"

# Limpiar archivos generados
clean:
	@echo "🧹 Limpiando archivos generados..."
	rm -f $(TARGET) $(OBJECTS)
	rm -rf $(TARGET).dSYM
	@echo "✅ Limpieza completada"

# Verificar herramientas necesarias
check-tools:
	@echo "🔍 Verificando herramientas necesarias..."
	@which $(CC) > /dev/null || (echo "❌ $(CC) no encontrado" && exit 1)
	@echo "✅ Todas las herramientas están disponibles"

# Mostrar información del proyecto
info:
	@echo "📋 INFORMACIÓN DEL PROYECTO"
	@echo "=========================="
	@echo "Proyecto: Parser LL(1) Personalizado en C"
	@echo "Gramática implementada:"
	@echo "  E  -> T E'"
	@echo "  E' -> + T E' | ε"
	@echo "  T  -> F T'"
	@echo "  T' -> * F T' | ε"
	@echo "  F  -> ( E ) | ident"
	@echo ""
	@echo "Archivos fuente:"
	@echo "  - main.c: Programa principal"
	@echo "  - lexer.c/lexer.h: Analizador léxico"
	@echo "  - parser.c/parser.h: Analizador sintáctico"
	@echo ""
	@echo "Características:"
	@echo "  - Implementación completamente manual"
	@echo "  - Manejo detallado de errores"
	@echo "  - Construcción de árbol sintáctico"
	@echo "  - Múltiples modos de ejecución"
	@echo ""
	@echo "Herramientas requeridas:"
	@echo "  - gcc: Compilador C"

# Mostrar ayuda
help:
	@echo "📖 AYUDA - Parser LL(1) Personalizado en C"
	@echo "=========================================="
	@echo ""
	@echo "COMANDOS PRINCIPALES:"
	@echo "  make all          Compilar el proyecto completo"
	@echo "  make run          Ejecutar el parser interactivamente"
	@echo "  make test         Ejecutar pruebas con casos válidos"
	@echo "  make test-errors  Ejecutar pruebas con casos de error"
	@echo "  make test-all     Ejecutar todas las pruebas"
	@echo "  make test-expr    Probar una expresión específica"
	@echo "  make clean        Limpiar archivos generados"
	@echo ""
	@echo "COMANDOS DE DESARROLLO:"
	@echo "  make debug        Compilar en modo debug"
	@echo "  make check-tools  Verificar herramientas necesarias"
	@echo ""
	@echo "COMANDOS DE INFORMACIÓN:"
	@echo "  make info         Mostrar información del proyecto"
	@echo "  make ejemplos     Mostrar ejemplos de uso"
	@echo "  make help         Mostrar esta ayuda"
	@echo ""
	@echo "MODOS DE EJECUCIÓN:"
	@echo "  ./parser                    # Modo interactivo"
	@echo "  ./parser archivo.txt        # Procesar archivo"
	@echo "  ./parser -e \"a + b * c\"     # Expresión directa"
	@echo ""
	@echo "EJEMPLOS DE USO:"
	@echo "  Expresión simple:     a"
	@echo "  Suma:                 a + b"
	@echo "  Multiplicación:       a * b"
	@echo "  Expresión compleja:   (a + b) * c"
	@echo "  Precedencia:          a + b * c"

# Reglas de dependencias
main.o: main.c parser.h lexer.h
lexer.o: lexer.c lexer.h
parser.o: parser.c parser.h lexer.h