#include <iostream>
#include <string>

using namespace std;

class Pedido {
    private:
        static int numeroPedidoGlobal;
        static int pedidosAtivos;
        static int totalItensPedidos;
        const int numeroSequencial = numeroPedidoGlobal;
        string nome;
        int quantidadeItens;
        string *itens;
    public:
        Pedido(string nome, int quantidadeItens);
        ~Pedido();
        void SetPresente(int indice, string presente);
        string GetPresente(int indice) const;
        static int GetPedidosAtivos();
        static int GetTotalItensPedidos();

        string GetNome() const;
        int GetQuantidade() const;
        int GetNumeroSequencial() const;
};

int main() {    
    Pedido Maria = Pedido("Maria", 2);
    Maria.SetPresente(0, "Notebook");
    Maria.SetPresente(1, "Cagador");
    
    cout << "Pedido #" << Maria.GetNumeroSequencial() << endl;
    cout << "Nome: " << Maria.GetNome() << endl;
    cout << "Quantidade: " << Maria.GetQuantidade() << endl;
    cout << "Itens: " << endl;
    for(int i = 0; i < Maria.GetQuantidade(); i++) {
        cout << Maria.GetPresente(i) << endl;
    }

    cout << "Total Pedidos ativos: " << Pedido::GetPedidosAtivos() << endl;
    cout << "Total Itens: " << Pedido::GetTotalItensPedidos() << endl;


    Pedido Joao = Pedido("Joao", 2);
    Joao.SetPresente(0, "Notebook");
    Joao.SetPresente(1, "Cagador");
    
    cout << "Pedido #" << Joao.GetNumeroSequencial() << endl;
    cout << "Nome: " << Joao.GetNome() << endl;
    cout << "Quantidade: " << Joao.GetQuantidade() << endl;
    cout << "Itens: " << endl;
    for(int i = 0; i < Joao.GetQuantidade(); i++) {
        cout << Joao.GetPresente(i) << endl;
    }

    cout << "Total Pedidos ativos: " << Pedido::GetPedidosAtivos() << endl;
    cout << "Total Itens: " << Pedido::GetTotalItensPedidos() << endl;

    return 0;
}

int Pedido::numeroPedidoGlobal = 1;
int Pedido::pedidosAtivos = 0;
int Pedido::totalItensPedidos = 0;

Pedido::Pedido(string nome, int quantidadeItens) {
    numeroPedidoGlobal++;
    pedidosAtivos++;
    totalItensPedidos += quantidadeItens;
    this->nome = nome;
    this->quantidadeItens = quantidadeItens;
    itens = new string[quantidadeItens];
}

void Pedido::SetPresente(int indice, string presente) {
    itens[indice] = presente;
}

string Pedido::GetPresente(int indice) const { 
    return itens[indice]; 
}

int Pedido::GetPedidosAtivos() {
    return pedidosAtivos;
}

int Pedido::GetTotalItensPedidos() {
    return totalItensPedidos;
}

Pedido::~Pedido() {
    pedidosAtivos--;
    totalItensPedidos -= quantidadeItens;
    delete[] itens;
}

string Pedido::GetNome() const {
    return nome;
}
 
int Pedido::GetQuantidade() const {
    return quantidadeItens;
}

int Pedido::GetNumeroSequencial() const{
    return numeroSequencial;
}