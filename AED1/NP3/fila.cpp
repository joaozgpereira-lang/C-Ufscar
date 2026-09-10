#include <iostream>
#define MAX 100

// Definição da Fila com alocação estática e sequencial (circular)
struct Fila {
    int itens[MAX];
    int inicio;
    int fim;
    int tamanho;
};

// Operações Primitivas
void Cria(Fila &F) {
    F.inicio = 0;
    F.fim = -1;
    F.tamanho = 0;
}

bool Vazia(Fila &F) {
    return (F.tamanho == 0);
}

bool Cheia(Fila &F) {
    return (F.tamanho == MAX);
}

void Insere(Fila &F, int X, bool &DeuCerto) {
    if (Cheia(F)) {
        DeuCerto = false;
        return;
    }
    // Incremento circular
    F.fim = (F.fim + 1) % MAX;
    F.itens[F.fim] = X;
    F.tamanho++;
    DeuCerto = true;
}

void Retira(Fila &F, int &X, bool &DeuCerto) {
    if (Vazia(F)) {
        DeuCerto = false;
        return;
    }
    X = F.itens[F.inicio];
    // Incremento circular
    F.inicio = (F.inicio + 1) % MAX;
    F.tamanho--;
    DeuCerto = true;
}