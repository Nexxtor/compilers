# Makefile para Analizador Lexicográfico en C Puro
# Ejemplo pedagógico sin Flex

# Configuración del compilador
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = calculadora
SOURCE = calculadora.c

# Archivos de prueba
TEST_INPUT = test_input.txt
TEST_ERRORS = test_errores.txt
EXAMPLES = ejemplos.txt

# Regla principal
all: $(TARGET)

# Compilar el analizador
$(TARGET): $(SOURCE)
	@echo "Compilando analizador lexicográfico en C puro..."
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCE)
	@echo "Compilación exitosa!"

# Ejecutar interactivamente
run: $(TARGET)
	@echo "Ejecutando analizador (Ctrl+D para terminar):"
	./$(TARGET)

# Ejecutar con archivo de prueba
test: $(TARGET) $(TEST_INPUT)
	@echo "Probando con archivo de entrada:"
	./$(TARGET) $(TEST_INPUT)

# Ejecutar pruebas de errores
test-errors: $(TARGET) $(TEST_ERRORS)
	@echo "Probando manejo de errores:"
	./$(TARGET) $(TEST_ERRORS)

# Ejecutar todos los ejemplos
test-all: $(TARGET) $(EXAMPLES)
	@echo "Ejecutando todos los ejemplos:"
	./$(TARGET) $(EXAMPLES)

# Limpiar archivos generados
clean:
	@echo "Limpiando archivos generados..."
	rm -f $(TARGET)
	rm -rf $(TARGET).dSYM
	@echo "Limpieza completada!"

# Mostrar información del sistema
info:
	@echo "Información del sistema:"
	@echo "Compilador: $(CC)"
	@echo "Flags: $(CFLAGS)"
	@echo "Archivo fuente: $(SOURCE)"
	@echo "Ejecutable: $(TARGET)"

# Verificar herramientas necesarias
check-tools:
	@echo "Verificando herramientas..."
	@which $(CC) > /dev/null || (echo "Error: $(CC) no encontrado" && exit 1)
	@$(CC) --version | head -1
	@echo "Herramientas disponibles!"

# Comparar con la versión Flex
compare: $(TARGET)
	@echo "Comparando salidas (C puro vs Flex):"
	@echo "--- Salida C puro ---"
	@./$(TARGET) $(TEST_INPUT) 2>/dev/null || echo "Error en C puro"
	@echo ""
	@echo "--- Salida Flex ---"
	@cd ../01-calculadora_flex && ./calculadora < ../02-calculadora_custom/$(TEST_INPUT) 2>/dev/null || echo "Error en Flex"

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
	@echo "  make compare      - Comparar con versión Flex"
	@echo "  make help         - Mostrar esta ayuda"

# Declarar targets que no son archivos
.PHONY: all run test test-errors test-all clean info check-tools compare help