#include <iostream>
#include <string>
using namespace std;
/*
    materia da prova:
    - encapsulamento de dados
    - uso de const
    - membros static
    - alocacao dinamica
*/

class Pedido {
    private:
        static int pedido;
        static int PedidosAtivos;
        static int PresentesPendentes;
        string nome;
        int quantidade;
        int NroPedido;
        string* presentes;
    public:
        Pedido(string nome, int quantidade);
        ~Pedido();
        Pedido(const Pedido& outro);
        void SetPresentes();
        void GetPresentes() const;
        string GetNome() const;
        static int TotalItens();
        static int NroPedidosAtivos();
        int GetNumero() const;
        int GetQuantidade() const;
        void PrintPedido() const;
};

int main() {
    Pedido p1("João", 3);
    p1.SetPresentes();
    cout << "Pedidos ativos: " << Pedido::NroPedidosAtivos() << endl;
    p1.PrintPedido();
    Pedido p2("Maria", 3);
    cout << "Pedidos ativos: " << Pedido::NroPedidosAtivos() << endl;
    p2.PrintPedido();
    return 0;
}

int Pedido::pedido = 0;
int Pedido::PedidosAtivos = 0;
int Pedido::PresentesPendentes = 0;

Pedido::Pedido(string nome, int quantidade) {
    this->nome = nome;
    this->quantidade = quantidade;
    presentes = new string[quantidade];
    pedido++;
    NroPedido = pedido;
    PedidosAtivos++;
    PresentesPendentes += quantidade;
}

void Pedido::SetPresentes() {
    for (int i = 0; i < quantidade; i++) {
        cin >> presentes[i];
    }
}

Pedido::~Pedido() {
    delete[] presentes;
    PedidosAtivos--;
    PresentesPendentes -= quantidade;
}

void Pedido::GetPresentes() const {
    for (int i = 0; i < quantidade; i++) {
        cout << presentes[i] << endl;
    }
}

string Pedido::GetNome() const {
    return nome;
}

int Pedido::GetNumero() const {
    return NroPedido;
}

int Pedido::GetQuantidade() const {
    return quantidade;
}

int Pedido::NroPedidosAtivos() {
    return PedidosAtivos;
}

int Pedido::TotalItens() {
    return PresentesPendentes;
}


void Pedido::PrintPedido() const {
    cout << "Pedido #" << GetNumero() << endl;
    cout << "Nome: " << GetNome() << endl;
    cout << "Qtd: " << GetQuantidade() << endl;
    cout << "Itens:" << endl;
    GetPresentes();
}

Pedido::Pedido(const Pedido& outro) {
    nome = outro.nome;
    quantidade = outro.quantidade;
    presentes = new string[quantidade];
    for (int i = 0; i < quantidade; i++) {
        presentes[i] = outro.presentes[i];
    }
    pedido++;
    NroPedido = pedido;
    PedidosAtivos++;
    PresentesPendentes += quantidade;
}