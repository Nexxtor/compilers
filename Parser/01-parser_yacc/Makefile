# Makefile para Parser LL(1) con Lex/Yacc
# Gramática: E -> T E' | E' -> + T E' | ε | T -> F T' | T' -> * F T' | ε | F -> ( E ) | ident

CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
FLEX = flex
BISON = bison
TARGET = parser
SOURCES = lex.yy.c parser.tab.c
OBJECTS = $(SOURCES:.c=.o)

# Archivos de prueba
TEST_INPUT = test_input.txt
TEST_ERRORS = test_errores.txt
EXAMPLES = ejemplos.txt

.PHONY: all run test clean test-errors test-all info check-tools help

# Regla principal
all: check-tools $(TARGET)
	@echo "✅ Compilación completada exitosamente"
	@echo "📋 Ejecuta 'make run' para probar el parser"
	@echo "📋 Ejecuta 'make test' para ejecutar las pruebas"

# Compilar el parser
$(TARGET): parser.tab.c lex.yy.c
	@echo "🔨 Compilando parser LL(1)..."
	$(CC) $(CFLAGS) -o $(TARGET) parser.tab.c lex.yy.c
	@echo "✅ Parser compilado: $(TARGET)"

# Generar parser con Bison
parser.tab.c parser.tab.h: parser.y
	@echo "🔧 Generando parser con Bison..."
	$(BISON) -d parser.y

# Generar lexer con Flex
lex.yy.c: lexer.l parser.tab.h
	@echo "🔧 Generando lexer con Flex..."
	$(FLEX) lexer.l

# Ejecutar el parser interactivamente
run: $(TARGET)
	@echo "🚀 Ejecutando parser LL(1) (Ctrl+D para terminar):"
	@echo "📝 Ejemplos válidos: a, a+b, a*b, (a+b)*c, a+b*c"
	./$(TARGET)

# Ejecutar pruebas con casos válidos
test: $(TARGET) $(TEST_INPUT)
	@echo "🧪 Ejecutando pruebas con casos válidos..."
	@echo "📁 Archivo de prueba: $(TEST_INPUT)"
	@echo "----------------------------------------"
	@if [ -f $(TEST_INPUT) ]; then \
		while IFS= read -r line; do \
			if [ -n "$$line" ] && [ "$${line#\#}" = "$$line" ]; then \
				echo "🔍 Probando: $$line"; \
				echo "$$line" | ./$(TARGET); \
				echo "----------------------------------------"; \
			fi; \
		done < $(TEST_INPUT); \
	else \
		echo "❌ Archivo $(TEST_INPUT) no encontrado"; \
	fi

# Ejecutar pruebas con casos de error
test-errors: $(TARGET) $(TEST_ERRORS)
	@echo "🧪 Ejecutando pruebas con casos de error..."
	@echo "📁 Archivo de prueba: $(TEST_ERRORS)"
	@echo "----------------------------------------"
	@if [ -f $(TEST_ERRORS) ]; then \
		while IFS= read -r line; do \
			if [ -n "$$line" ] && [ "$${line#\#}" = "$$line" ]; then \
				echo "🔍 Probando (error esperado): $$line"; \
				echo "$$line" | ./$(TARGET); \
				echo "----------------------------------------"; \
			fi; \
		done < $(TEST_ERRORS); \
	else \
		echo "❌ Archivo $(TEST_ERRORS) no encontrado"; \
	fi

# Ejecutar todas las pruebas
test-all: test test-errors
	@echo "✅ Todas las pruebas completadas"

# Mostrar ejemplos
ejemplos: $(EXAMPLES)
	@echo "📚 Ejemplos de uso del parser LL(1):"
	@echo "======================================"
	@if [ -f $(EXAMPLES) ]; then \
		cat $(EXAMPLES); \
	else \
		echo "❌ Archivo $(EXAMPLES) no encontrado"; \
	fi

# Limpiar archivos generados
clean:
	@echo "🧹 Limpiando archivos generados..."
	rm -f $(TARGET) $(OBJECTS) lex.yy.c parser.tab.c parser.tab.h
	rm -rf $(TARGET).dSYM
	@echo "✅ Limpieza completada"

# Verificar herramientas necesarias
check-tools:
	@echo "🔍 Verificando herramientas necesarias..."
	@which $(CC) > /dev/null || (echo "❌ $(CC) no encontrado" && exit 1)
	@which $(FLEX) > /dev/null || (echo "❌ $(FLEX) no encontrado" && exit 1)
	@which $(BISON) > /dev/null || (echo "❌ $(BISON) no encontrado" && exit 1)
	@echo "✅ Todas las herramientas están disponibles"

# Mostrar información del proyecto
info:
	@echo "📋 INFORMACIÓN DEL PROYECTO"
	@echo "=========================="
	@echo "Proyecto: Parser LL(1) con Lex/Yacc"
	@echo "Gramática implementada:"
	@echo "  E  -> T E'"
	@echo "  E' -> + T E' | ε"
	@echo "  T  -> F T'"
	@echo "  T' -> * F T' | ε"
	@echo "  F  -> ( E ) | ident"
	@echo ""
	@echo "Archivos fuente:"
	@echo "  - lexer.l: Analizador léxico (Flex)"
	@echo "  - parser.y: Analizador sintáctico (Bison)"
	@echo ""
	@echo "Herramientas requeridas:"
	@echo "  - gcc: Compilador C"
	@echo "  - flex: Generador de analizadores léxicos"
	@echo "  - bison: Generador de analizadores sintácticos"
	@echo ""
	@echo "Comandos disponibles:"
	@echo "  make all      - Compilar el proyecto"
	@echo "  make run      - Ejecutar interactivamente"
	@echo "  make test     - Ejecutar pruebas válidas"
	@echo "  make test-errors - Ejecutar pruebas de error"
	@echo "  make clean    - Limpiar archivos generados"

# Mostrar ayuda
help:
	@echo "📖 AYUDA - Parser LL(1) con Lex/Yacc"
	@echo "===================================="
	@echo ""
	@echo "COMANDOS PRINCIPALES:"
	@echo "  make all          Compilar el proyecto completo"
	@echo "  make run          Ejecutar el parser interactivamente"
	@echo "  make test         Ejecutar pruebas con casos válidos"
	@echo "  make test-errors  Ejecutar pruebas con casos de error"
	@echo "  make test-all     Ejecutar todas las pruebas"
	@echo "  make clean        Limpiar archivos generados"
	@echo ""
	@echo "COMANDOS DE INFORMACIÓN:"
	@echo "  make info         Mostrar información del proyecto"
	@echo "  make ejemplos     Mostrar ejemplos de uso"
	@echo "  make check-tools  Verificar herramientas necesarias"
	@echo "  make help         Mostrar esta ayuda"
	@echo ""
	@echo "EJEMPLOS DE USO:"
	@echo "  Expresión simple:     a"
	@echo "  Suma:                 a + b"
	@echo "  Multiplicación:       a * b"
	@echo "  Expresión compleja:   (a + b) * c"
	@echo "  Precedencia:          a + b * c"