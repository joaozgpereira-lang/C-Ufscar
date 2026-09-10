#include <iostream>
#include "PilhaTAD.h"

using namespace std;

int main() {
    Pilha P;
    Cria(&P);

    bool Ok;
    char Valor;

    cout << "Empilhando A, B e C..." << endl;
    Empilha(&P, 'A', &Ok);
    Empilha(&P, 'B', &Ok);
    Empilha(&P, 'C', &Ok);

    cout << "Desempilhando elementos:" << endl;
    while (!Vazia(&P)) {
        Desempilha(&P, &Valor, &Ok);
        if (Ok) {
            cout << "Elemento retirado: " << Valor << endl;
        }
    }

    return 0;
}