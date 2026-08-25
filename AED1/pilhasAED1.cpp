#include <iostream>

using namespace std;

const int MAX = 10; // Tamnaho máximo da pilha = 10

typedef struct {
    int itens[MAX] = {0};
    int top = 0;

    void Empilha(int num) {
        if(!(top == MAX)) {
            itens[top] = num;
            top++;
        }
        else {
            cout << "Pilha cheia, impossível empilhar!" << endl;
        }
    }

    void Desempilha() {
        if(top==0) {
            cout << "Pilha vazia, impossível desempilhar!" << endl;
        }
        else {
            itens[top] = 0;
            top--;     
        }
        
    }

    bool Vazia() {
        if(!top) { 
            return 1;
        }
        else {
            return 0;
        }
    }

    int Topo() {
        return itens[top-1];
    }

    int Tamanho() {
        return top;
    }
} Pilha;


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

    return 0;
}