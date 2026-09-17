#include <iostream>
#include "ListaCadastral.cpp"

using namespace std;

// Não primitivas
void Imprime(Lista& L) {
    char elemento;
    bool temElemento;

    cout << "[ ";
    PegaOPrimeiro(L, elemento, temElemento);
    
    while (temElemento) {
        cout << elemento << " ";
        PegaOProximo(L, elemento, temElemento);
    }
    
    cout << "]\n";
}

bool SaoIguais(Lista& L1, Lista& L2) {
    char elem1, elem2;
    bool temElem1, temElem2;

    PegaOPrimeiro(L1, elem1, temElem1);
    PegaOPrimeiro(L2, elem2, temElem2);

    while (temElem1 && temElem2) {
        if (elem1 != elem2) {
            return false;
        }

        PegaOProximo(L1, elem1, temElem1);
        PegaOProximo(L2, elem2, temElem2);
    }

    return (temElem1 == temElem2);
}

int main() {
    Lista L1, L2, L3;
    bool ok;

    Cria(L1);
    Cria(L2);
    Cria(L3);

    Insere(L1, 'A', ok);
    Insere(L1, 'B', ok);

    Insere(L2, 'A', ok);
    Insere(L2, 'B', ok);

    Insere(L3, 'X', ok);

    cout << "L1: "; Imprime(L1);
    cout << "L2: "; Imprime(L2);
    cout << "L3: "; Imprime(L3);

    cout << "\nL1 e L2 sao iguais? " << (SaoIguais(L1, L2) ? "Sim" : "Nao") << endl;
    cout << "L1 e L3 sao iguais? " << (SaoIguais(L1, L3) ? "Sim" : "Nao") << endl;

    return 0;
}