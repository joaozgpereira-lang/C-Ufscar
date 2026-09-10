#include <iostream>
#include "fila.cpp" 

using namespace std;

// Operação não primitiva 1: Imprimir todos os elementos da fila
void ImprimirFila(Fila &F) {
    Fila F_aux;
    Cria(F_aux);
    int X;
    bool ok;

    cout << "[ ";
    while (!Vazia(F)) {
        Retira(F, X, ok);
        cout << X << " ";
        Insere(F_aux, X, ok);
    }
    cout << "]" << endl;

    // Restaura os elementos de volta para a fila original
    while (!Vazia(F_aux)) {
        Retira(F_aux, X, ok);
        Insere(F, X, ok);
    }
}

// Operação não primitiva 2: Trocar os elementos de 2 filas (Ex 3.2)
void TrocaDosElementos(Fila &F1, Fila &F2) {
    Fila F3;
    Cria(F3);
    int X;
    bool ok;

    while (!Vazia(F1)) {
        Retira(F1, X, ok);
        Insere(F3, X, ok);
    }

    while (!Vazia(F2)) {
        Retira(F2, X, ok);
        Insere(F1, X, ok);
    }

    while (!Vazia(F3)) {
        Retira(F3, X, ok);
        Insere(F2, X, ok);
    }
}

int main() {
    Fila F1, F2;
    bool ok;

    Cria(F1);
    Cria(F2);

    // Populando a F1
    Insere(F1, 10, ok);
    Insere(F1, 20, ok);
    Insere(F1, 30, ok);

    // Populando a F2
    Insere(F2, 99, ok);
    Insere(F2, 88, ok);

    cout << "Antes da troca:" << endl;
    cout << "F1: ";
    ImprimirFila(F1);
    cout << "F2: ";
    ImprimirFila(F2);

    // Executando operação não primitiva
    TrocaDosElementos(F1, F2);

    cout << "\nDepois da troca:" << endl;
    cout << "F1: ";
    ImprimirFila(F1);
    cout << "F2: ";
    ImprimirFila(F2);

 
    return 0;
}