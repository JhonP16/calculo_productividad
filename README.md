# 📊 Asignación de Recursos — Multiplicación de Matrices

Solución en C++ que calcula la productividad total de un equipo de desarrolladores por fase de proyecto, aplicando el paradigma **Divide y Vencerás**.

---

## 🧩 Problema

Dadas dos matrices:
- **A (3×3):** productividad de cada desarrollador por proyecto (pts/hora).
- **B (3×3):** horas requeridas por proyecto en cada fase.

Se obtiene **C = A × B**, donde `C[i][k]` representa los puntos totales que el desarrollador `i` completará en la fase `k`.

---

## ⚙️ Estrategia de Solución

| Nivel | Función | Responsabilidad |
|-------|---------|----------------|
| 1 | `multiplicarMatrices` | Orquesta el cálculo y ensambla la matriz C |
| 2 | `calcularFila` | Calcula todos los elementos de la fila i |
| 3 | `calcularElemento` | Calcula un único elemento C[i][k] (producto punto) |

---

## 🚀 Compilar y Ejecutar

```bash
g++ -o matrix_productivity matrix_productivity.cpp
./matrix_productivity
```

---

## 📤 Salida

El programa muestra las matrices A, B y C, el desglose detallado de cada cálculo y la **asignación óptima** de desarrolladores por fase.
