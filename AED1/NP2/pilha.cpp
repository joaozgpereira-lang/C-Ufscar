#include <iostream>

using namespace std;

const int MAX = 10; // Tamnaho máximo da pilha = 10

typedef struct {
    int itens[MAX] = {0};
    int atual = -1;

    void Empilha(int num) {
        if(!(atual+1 == MAX)) {
            atual++;
            itens[atual] = num;
        }
        else {
            cout << "Pilha cheia, impossível empilhar!" << endl;
        }
    }

    void Desempilha() {
        if(atual==-1) {
            cout << "Pilha vazia, impossível desempilhar!" << endl;
        }
        else {
            itens[atual] = 0;
            atual--;
        }
        
    }

    bool Vazia() {
        if(atual==-1) { 
            return 1;
        }
        else {
            return 0;
        }
    }

    int Topo() {
        return itens[atual];
    }

    int Tamanho() {
        return atual+1;
    }
} Pilha;