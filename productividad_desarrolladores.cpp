#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// ─────────────────────────────────────────────
//  NIVEL 3 — Operación atómica
//  Calcula un único elemento C[i][k] mediante
//  el producto punto entre fila i de A y columna k de B
// ─────────────────────────────────────────────
double calcularElemento(const vector<vector<double>>& A,
                        const vector<vector<double>>& B,
                        int i, int k, int n)
{
    double resultado = 0.0;
    for (int j = 0; j < n; j++) {
        resultado += A[i][j] * B[j][k];
    }
    return resultado;
}

// ─────────────────────────────────────────────
//  NIVEL 2 — División por fase
//  Calcula la fila completa i de la matriz C
//  (todos los puntos del desarrollador i por fase)
// ─────────────────────────────────────────────
vector<double> calcularFila(const vector<vector<double>>& A,
                            const vector<vector<double>>& B,
                            int i, int n)
{
    vector<double> fila(n);
    for (int k = 0; k < n; k++) {
        // Subproblema: calcular C[i][k]
        fila[k] = calcularElemento(A, B, i, k, n);
    }
    return fila;
}

// ─────────────────────────────────────────────
//  NIVEL 1 — División por desarrollador
//  Orquesta el cálculo de cada fila y ensambla
//  la matriz C final
// ─────────────────────────────────────────────
vector<vector<double>> multiplicarMatrices(const vector<vector<double>>& A,
                                           const vector<vector<double>>& B,
                                           int n)
{
    vector<vector<double>> C(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        // Subproblema: calcular fila i completa
        C[i] = calcularFila(A, B, i, n);
    }
    return C;
}

// ─────────────────────────────────────────────
//  UTILIDADES — Impresión de matrices
// ─────────────────────────────────────────────
void imprimirMatriz(const vector<vector<double>>& M,
                    const string& nombre,
                    const vector<string>& etiquetasFila,
                    const vector<string>& etiquetasCol)
{
    int n = M.size();
    cout << "Matriz " << nombre << "\n";

    // Encabezado de columnas
    cout << setw(18) << " ";
    for (const auto& col : etiquetasCol)
        cout << setw(12) << col;
    cout << "\n" << string(18 + 12 * n, '-') << "\n";

    // Filas
    for (int i = 0; i < n; i++) {
        cout << setw(17) << etiquetasFila[i] << " |";
        for (int j = 0; j < n; j++)
            cout << setw(12) << fixed << setprecision(1) << M[i][j];
        cout << "\n";
    }
}

void mostrarDesglose(const vector<vector<double>>& A,
                     const vector<vector<double>>& B,
                     const vector<vector<double>>& C, int n)
{
    vector<string> devs    = {"Desarrollador 1", "Desarrollador 2", "Desarrollador 3"};
    vector<string> proyect = {"Proyecto 1",      "Proyecto 2",      "Proyecto 3"};
    vector<string> fases   = {"Fase 1",          "Fase 2",          "Fase 3"};

    cout << "   SISTEMA DE PRODUCTIVIDAD — DIVIDE Y VENCERÁS\n";

    imprimirMatriz(A, "A  (Productividad pts/hora)", devs, proyect);
    imprimirMatriz(B, "B  (Horas requeridas/fase) ", proyect, fases);
    imprimirMatriz(C, "C  (Puntos totales/fase)   ", devs, fases);

    // Desglose del cálculo por desarrollador

    cout << "Desglose del cálculo (Nivel 3)   \n";

    for (int i = 0; i < n; i++) {
        cout << "\n▶ " << devs[i] << ":\n";
        for (int k = 0; k < n; k++) {
            cout << "  C[" << i+1 << "][" << k+1 << "] = ";
            for (int j = 0; j < n; j++) {
                cout << "(" << A[i][j] << " x " << B[j][k] << ")";
                if (j < n - 1) cout << " + ";
            }
            cout << " = " << C[i][k] << " pts  -->  " << fases[k] << "\n";
        }
    }
}

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────
int main()
{
    const int N = 3;

    // Matriz A: productividad (pts/hora) de cada desarrollador por proyecto
    vector<vector<double>> A = {
        {4.0, 2.0, 3.0},   // Desarrollador 1
        {1.0, 5.0, 2.0},   // Desarrollador 2
        {3.0, 3.0, 4.0}    // Desarrollador 3
    };

    // Matriz B: horas requeridas por proyecto en cada fase
    vector<vector<double>> B = {
        {10.0,  5.0,  8.0},  // Proyecto 1
        { 6.0, 12.0,  4.0},  // Proyecto 2
        { 7.0,  3.0, 11.0}   // Proyecto 3
    };

    // ── Divide y Vencerás: Nivel 1 ──
    vector<vector<double>> C = multiplicarMatrices(A, B, N);

    // Mostrar resultados y desglose
    mostrarDesglose(A, B, C, N);

    // Conclusión: desarrollador con mayor productividad por fase
    cout << "Asignación óptima de recursos    \n";

    vector<string> devs  = {"Desarrollador 1", "Desarrollador 2", "Desarrollador 3"};
    vector<string> fases = {"Fase 1", "Fase 2", "Fase 3"};

    for (int k = 0; k < N; k++) {
        int mejorDev = 0;
        for (int i = 1; i < N; i++)
            if (C[i][k] > C[mejorDev][k]) mejorDev = i;
        cout << "  " << fases[k] << " → Asignar a " << devs[mejorDev]
             << "  (" << C[mejorDev][k] << " pts)\n";
    }

    cout << "\n";
    return 0;
}