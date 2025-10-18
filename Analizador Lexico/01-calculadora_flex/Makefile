# Makefile para Analizador Lexicográfico con Flex
# Ejemplo pedagógico usando Flex

# Configuración del compilador y herramientas
FLEX = flex
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = calculadora
SOURCE = calculadora.l
GENERATED_C = lex.yy.c

# Archivos de prueba
TEST_INPUT = test_input.txt
TEST_ERRORS = test_errores.txt
EXAMPLES = ejemplos.txt

# Regla principal
all: $(TARGET)

# Generar código C desde archivo Flex
$(GENERATED_C): $(SOURCE)
	@echo "Generando código C desde Flex..."
	$(FLEX) $(SOURCE)

# Compilar el ejecutable
$(TARGET): $(GENERATED_C)
	@echo "Compilando analizador lexicográfico..."
	$(CC) $(CFLAGS) -o $(TARGET) $(GENERATED_C)
	@echo "Compilación exitosa!"

# Ejecutar interactivamente
run: $(TARGET)
	@echo "Ejecutando analizador (Ctrl+D para terminar):"
	./$(TARGET)

# Ejecutar con archivo de prueba
test: $(TARGET) $(TEST_INPUT)
	@echo "Probando con archivo de entrada:"
	./$(TARGET) < $(TEST_INPUT)

# Ejecutar pruebas de errores
test-errors: $(TARGET) $(TEST_ERRORS)
	@echo "Probando manejo de errores:"
	./$(TARGET) < $(TEST_ERRORS)

# Ejecutar todos los ejemplos
test-all: $(TARGET) $(EXAMPLES)
	@echo "Ejecutando todos los ejemplos:"
	./$(TARGET) < $(EXAMPLES)

# Limpiar archivos generados
clean:
	@echo "Limpiando archivos generados..."
	rm -f $(GENERATED_C) $(TARGET)
	rm -rf $(TARGET).dSYM
	@echo "Limpieza completada!"

# Mostrar información del sistema
info:
	@echo "Información del sistema:"
	@echo "Flex: $(FLEX)"
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Archivo fuente: $(SOURCE)"
	@echo "Ejecutable: $(TARGET)"

# Verificar herramientas necesarias
check-tools:
	@echo "Verificando herramientas..."
	@which $(FLEX) > /dev/null || (echo "Error: Flex no encontrado. Instalar con: brew install flex" && exit 1)
	@which $(CC) > /dev/null || (echo "Error: $(CC) no encontrado" && exit 1)
	@$(FLEX) --version | head -1
	@$(CC) --version | head -1
	@echo "Herramientas disponibles!"

# Mostrar ayuda
help:
	@echo "Comandos disponibles:"
	@echo "  make              - Compilar el analizador"
	@echo "  make run          - Ejecutar interactivamente"
	@echo "  make test         - Probar con archivo de entrada"
	@echo "  make test-errors  - Probar manejo de errores"
	@echo "  make test-all     - Ejecutar todos los ejemplos"
	@echo "  make clean        - Limpiar archivos generados"
	@echo "  make info         - Mostrar información del sistema"
	@echo "  make check-tools  - Verificar herramientas necesarias"
	@echo "  make help         - Mostrar esta ayuda"

# Declarar targets que no son archivos
.PHONY: all run test test-errors test-all clean info check-tools help