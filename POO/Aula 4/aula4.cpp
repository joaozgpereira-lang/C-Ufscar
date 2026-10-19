#include <iostream>
using namespace std;

class Aluno {
    private:
    int RA;
    string Nome;
    static int contador;

    public:

    Aluno(string Nome);
    ~Aluno();

    void SetNome(string Nome);
    
    string GetNome() const;
    
    int GetRA() const;

    static int GetContador();
};

Aluno::Aluno(string vNome) {
    RA = GetContador();
    SetNome(vNome);
    contador++;
}

Aluno::~Aluno() {
    cout << "Objeto do aluno " << Nome << " destruido." << endl;
}

void Aluno::SetNome(string Nome) {
    this->Nome = Nome;
}

string Aluno::GetNome() const {
    return Nome;
}
    
int Aluno::GetRA() const {
    return RA;
}

int Aluno::GetContador() {
    return contador;
};

int Aluno::contador = 2000;

int main() {
    Aluno A1("Renato");
    Aluno A2("Sílvio");
    Aluno A3("Enrique");

    cout << A1.GetRA() << ": " << A1.GetNome() << endl;
    cout << A2.GetRA() << ": " << A2.GetNome() << endl;
    cout << A3.GetRA() << ": " << A3.GetNome() << endl;

    return 0;
}