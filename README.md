# Proyecto de Estructuras de Datos – 2025-30

Este proyecto tiene como objetivo **construir un sistema interactivo para la manipulación de secuencias genéticas en formato FASTA**, aplicando los conceptos de **estructuras lineales, jerárquicas (árboles) y no lineales (grafos)** vistos en el curso de **Estructuras de Datos**.

---

## 📋 Descripción del problema

El sistema permite trabajar con información genética representada en archivos **FASTA (.fa)**, los cuales contienen secuencias de ADN o ARN.  
A lo largo del proyecto se desarrollan diferentes componentes que permiten cargar, procesar, comprimir, descomprimir y analizar las secuencias.

---

## 🧩 Componentes del sistema

### 1. Resumen de información de un genoma
- Cargar archivos FASTA en memoria.  
- Listar secuencias y número de bases.  
- Generar histogramas de frecuencias.  
- Verificar si una subsecuencia existe.  
- Enmascarar subsecuencias con `X`.  
- Guardar las secuencias modificadas.  

### 2. Compresión y descompresión
- Implementación de **codificación de Huffman** para:
  - Codificar archivos FASTA → `.fabin`.  
  - Decodificar archivos `.fabin` → restaurar secuencias en memoria.  

### 3. Relaciones entre bases (grafos)
- Representar secuencias como matrices y grafos.  
- Calcular **ruta más corta** entre dos posiciones de bases.  
- Determinar la **base remota** más lejana de una posición dada.  

---

## 🖥️ Interacción con el sistema

El programa funciona en **modo consola interactiva**.  
El indicador de línea es el caracter `$`.  

### 🔑 Comandos principales
- `cargar nombre_archivo.fa`  
- `listar_secuencias`  
- `histograma descripcion_secuencia`  
- `es_subsecuencia subsecuencia`  
- `enmascarar subsecuencia`  
- `guardar nombre_archivo.fa`  
- `codificar nombre_archivo.fabin`  
- `decodificar nombre_archivo.fabin`  
- `ruta_mas_corta descripcion_secuencia i j x y`  
- `base_remota descripcion_secuencia i j`  
- `ayuda [comando]`  
- `salir`  

---

## ⚙️ Requisitos

- Compilador **GNU g++ (≥ 4.0.0)**  
- Sistema operativo Linux/Windows/Mac con terminal habilitada  

---

## 🚀 Ejecución

```bash
g++ -std=c++17 -o proyecto *.cpp
./proyecto
