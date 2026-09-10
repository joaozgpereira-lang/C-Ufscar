#ifndef PILHATAD_H
#define PILHATAD_H

#include <cstddef>

struct Node {
    char Info;
    Node* Next;
};

struct Pilha {
    Node* Topo;
};

void Cria(Pilha* P) {
    P->Topo = NULL;
}

bool Vazia(Pilha* P) {
    return (P->Topo == NULL);
}

bool Cheia(Pilha* P) {
    return false;
}

void Empilha(Pilha* P, char X, bool* DeuCerto) {
    Node* PAux = new Node;
    if (PAux == NULL) {
        *DeuCerto = false;
    } else {
        *DeuCerto = true;
        PAux->Info = X;
        PAux->Next = P->Topo;
        P->Topo = PAux;
    }
}

void Desempilha(Pilha* P, char* X, bool* DeuCerto) {
    if (Vazia(P)) {
        *DeuCerto = false;
    } else {
        *DeuCerto = true;
        *X = P->Topo->Info;
        Node* PAux = P->Topo;
        P->Topo = P->Topo->Next;
        delete PAux;
    }
}

#endif