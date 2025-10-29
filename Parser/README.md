# Parser LL(1) - Implementaciones Comparativas

## 📋 Descripción General

Este directorio contiene **dos implementaciones completas** de un analizador léxico y parser LL(1) para la misma gramática, utilizando enfoques diferentes para demostrar las distintas metodologías de construcción de compiladores.

### 🎯 Gramática Implementada

```
E  -> T E'
E' -> + T E' | ε
T  -> F T'
T' -> * F T' | ε
F  -> ( E ) | ident
```

Esta gramática reconoce expresiones aritméticas con:
- **Identificadores**: Variables alfanuméricas
- **Operadores**: Suma (`+`) y multiplicación (`*`)
- **Paréntesis**: Para modificar precedencia
- **Precedencia**: `*` tiene mayor precedencia que `+`
- **Asociatividad**: Ambos operadores son asociativos por la izquierda

## 📁 Estructura del Proyecto

```
Parser/
├── README.md                    # Esta documentación
├── .gitignore                   # Exclusiones de Git
├── 01-parser_yacc/             # Implementación con Lex/Yacc
│   ├── lexer.l                 # Especificación Flex
│   ├── parser.y                # Especificación Bison
│   ├── Makefile                # Construcción automática
│   ├── test_input.txt          # Casos de prueba válidos
│   ├── test_errores.txt        # Casos de prueba con errores
│   ├── ejemplos.txt            # Ejemplos de uso
│   ├── .gitignore              # Exclusiones específicas
│   └── README.md               # Documentación detallada
└── 02-parser_custom/           # Implementación manual en C
    ├── main.c                  # Programa principal
    ├── lexer.h / lexer.c       # Analizador léxico manual
    ├── parser.h / parser.c     # Parser LL(1) manual
    ├── Makefile                # Construcción automática
    ├── test_input.txt          # Casos de prueba válidos
    ├── test_errores.txt        # Casos de prueba con errores
    ├── ejemplos.txt            # Ejemplos de uso
    ├── .gitignore              # Exclusiones específicas
    └── README.md               # Documentación detallada
```

## 🔄 Comparación de Implementaciones

### 1️⃣ Implementación con Lex/Yacc (`01-parser_yacc/`)

#### ✅ **Ventajas:**
- **Generación automática**: Código optimizado generado automáticamente
- **Sintaxis declarativa**: Especificación clara y concisa
- **Herramientas maduras**: Lex/Yacc son estándares de la industria
- **Manejo robusto de errores**: Recuperación automática de errores
- **Optimización**: Algoritmos altamente optimizados

#### ❌ **Desventajas:**
- **Dependencias externas**: Requiere Flex y Bison
- **Menos control**: Menor control sobre el proceso interno
- **Curva de aprendizaje**: Sintaxis específica de las herramientas
- **Debug complejo**: Más difícil de debuggear el código generado

#### 🛠️ **Herramientas Requeridas:**
```bash
# macOS
brew install flex bison gcc

# Ubuntu/Debian
sudo apt-get install flex bison gcc
```

#### 🚀 **Uso Rápido:**
```bash
cd 01-parser_yacc/
make all
make run
```

### 2️⃣ Implementación Manual en C (`02-parser_custom/`)

#### ✅ **Ventajas:**
- **Control total**: Manejo completo del proceso de análisis
- **Sin dependencias**: Solo requiere gcc
- **Comprensión profunda**: Entendimiento completo de los algoritmos
- **Personalización**: Fácil modificación y extensión
- **Portabilidad**: Funciona en cualquier sistema con C

#### ❌ **Desventajas:**
- **Más código**: Implementación más extensa y compleja
- **Mantenimiento**: Requiere más esfuerzo de desarrollo
- **Optimización manual**: Menos optimizado que herramientas especializadas
- **Propenso a errores**: Mayor posibilidad de bugs

#### 🛠️ **Herramientas Requeridas:**
```bash
# Solo gcc (disponible en la mayoría de sistemas)
gcc --version
```

#### 🚀 **Uso Rápido:**
```bash
cd 02-parser_custom/
make all
make run
```

## 📊 Tabla Comparativa Detallada

| Aspecto | Lex/Yacc | Manual C |
|---------|-----------|----------|
| **Líneas de código** | ~150 | ~800+ |
| **Tiempo de desarrollo** | Rápido | Lento |
| **Dependencias** | Flex, Bison, GCC | Solo GCC |
| **Rendimiento** | Muy alto | Alto |
| **Mantenibilidad** | Media | Baja |
| **Flexibilidad** | Baja | Muy alta |
| **Curva de aprendizaje** | Media | Alta |
| **Debug** | Difícil | Fácil |
| **Portabilidad** | Media | Muy alta |
| **Uso en industria** | Muy común | Común en sistemas embebidos |

## 🧪 Casos de Prueba Comunes

Ambas implementaciones incluyen los mismos casos de prueba para garantizar consistencia:

### ✅ **Casos Válidos:**
```
a                    # Identificador simple
a + b               # Suma básica
a * b               # Multiplicación básica
(a + b)             # Paréntesis
a + b * c           # Precedencia: a + (b * c)
(a + b) * c         # Precedencia modificada
(a + b) * (c + d)   # Expresión compleja
```

### ❌ **Casos con Errores:**
```
a @                 # Carácter no válido
a +                 # Operador sin operando
(a                  # Paréntesis sin cerrar
a b                 # Dos identificadores consecutivos
+ a                 # Operador al inicio
```

## 🚀 Guía de Inicio Rápido

### 1. **Probar Implementación Lex/Yacc:**
```bash
cd 01-parser_yacc/
make all
echo "a + b * c" | ./parser
```

### 2. **Probar Implementación Manual:**
```bash
cd 02-parser_custom/
make all
./parser -e "a + b * c"
```

### 3. **Ejecutar Todas las Pruebas:**
```bash
# En cada directorio:
make test-all
```

## 📚 Recursos Educativos

### 🎓 **Para Estudiantes:**
1. **Comience con**: `02-parser_custom/` para entender los fundamentos
2. **Continúe con**: `01-parser_yacc/` para ver herramientas profesionales
3. **Compare**: Los árboles sintácticos generados por ambas implementaciones

### 👨‍🏫 **Para Instructores:**
- Use ambas implementaciones para mostrar diferentes enfoques
- Compare el código generado vs. manual
- Demuestre las ventajas y desventajas de cada método
- Use los casos de prueba para validar comprensión

### 🏭 **Para Desarrolladores:**
- `01-parser_yacc/` para proyectos de producción
- `02-parser_custom/` para sistemas embebidos o casos especiales
- Estudie ambos para decisiones arquitectónicas informadas

## 🔧 Comandos Útiles

### **Compilar Ambas Implementaciones:**
```bash
# Desde el directorio Parser/
for dir in 01-parser_yacc 02-parser_custom; do
    echo "Compilando $dir..."
    (cd $dir && make all)
done
```

### **Ejecutar Pruebas Comparativas:**
```bash
# Probar la misma expresión en ambas implementaciones
expr="a + b * c"
echo "Probando: $expr"
echo "--- Lex/Yacc ---"
(cd 01-parser_yacc && echo "$expr" | ./parser)
echo "--- Manual C ---"
(cd 02-parser_custom && ./parser -e "$expr")
```

### **Limpiar Todo:**
```bash
for dir in 01-parser_yacc 02-parser_custom; do
    (cd $dir && make clean)
done
```

## 📖 Documentación Adicional

- **[01-parser_yacc/README.md](01-parser_yacc/README.md)**: Documentación detallada de la implementación Lex/Yacc
- **[02-parser_custom/README.md](02-parser_custom/README.md)**: Documentación detallada de la implementación manual

## 🎯 Objetivos de Aprendizaje

Al completar este proyecto, habrás aprendido:

1. ✅ **Teoría de compiladores**: Gramáticas LL(1), análisis léxico y sintáctico
2. ✅ **Herramientas profesionales**: Uso de Flex y Bison
3. ✅ **Implementación manual**: Algoritmos de parsing recursivo descendente
4. ✅ **Manejo de errores**: Detección y reporte de errores sintácticos
5. ✅ **Construcción de AST**: Árboles de sintaxis abstracta
6. ✅ **Gestión de memoria**: Asignación y liberación en C
7. ✅ **Metodologías de desarrollo**: Comparación de enfoques diferentes

## 🏆 Conclusión

Este proyecto demuestra que **no hay una única forma correcta** de implementar un parser. La elección entre herramientas automáticas y implementación manual depende de:

- **Requisitos del proyecto**
- **Recursos disponibles**
- **Experiencia del equipo**
- **Restricciones del sistema**
- **Objetivos de aprendizaje**

Ambas implementaciones son válidas y tienen su lugar en el desarrollo de software real.