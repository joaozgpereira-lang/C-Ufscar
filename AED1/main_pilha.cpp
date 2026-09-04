#include <iostream>
#include "pilha.cpp"

using namespace std;

void mostrarPilha(Pilha p) {
    if (p.Vazia()) {
        cout << "Pilha Vazia!" << endl;
        return;
    }

    cout << "Elementos da Pilha: [ ";
    while (!p.Vazia()) {
        cout << p.Topo() << " ";
        p.Desempilha();
    }
    cout << "]" << endl;
}

bool obterTopo(Pilha &p, int &valorTopo) {
    if (p.Vazia()) {
        return false;
    }
    valorTopo = p.Topo();
    return true;
}

int main() {

    Pilha p1;

    cout << p1.Vazia() << endl; // Deve imprimir 1

    for(int i=0; i<MAX; i++) { // Empilha de 0 a 9
        p1.Empilha(i);
    }

    cout << p1.Tamanho() << endl; // Deve imprimir 10
    
    p1.Empilha(10); // Deve imprimir "Pilha cheia, impossível empilhar!"

    for(int i=0; i<MAX; i++) { // Desempilha de 9 a 0
        cout << p1.Topo() << endl;
        p1.Desempilha();
    }

    p1.Desempilha(); // Deve imprimir "Pilha vazia, impossível desempilhar!"


    Pilha p;

    p.Empilha(10);
    p.Empilha(20);
    p.Empilha(30);

    mostrarPilha(p);

    int topo;
    if (obterTopo(p, topo)) {
        cout << "Valor do topo: " << topo << endl;
    } else {
        cout << "A pilha esta vazia, nao possui topo." << endl;
    }

    return 0;
}