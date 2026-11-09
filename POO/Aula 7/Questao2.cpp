#include <iostream>
#include <string>
using namespace std;

class Funcionario {
private:
    string nome;
    int codigo;
    double salario;
public:
    Funcionario(string nome, int codigo, double salario) {
        this->nome = nome;
        this->codigo = codigo;
        this->salario = salario;
    }

    virtual double Remuneracao() const {
        return salario;
    }

    double GetSalario() const {
        return salario;
    }

    string GetNome() const {
        return nome;
    }

    int GetCodigo() const {
        return codigo;
    }

    void ExibirDados() const {
        cout << "Cargo: Funcionário" << endl;
        cout << "Nome: " << GetNome() << endl;
        cout << "Código: " << GetCodigo() << endl;
        cout << "Salário: " << Remuneracao() << endl;
    }

};

class Supervisor:public Funcionario {
private:
    int supervisao;
public:
    Supervisor(string nome, int codigo, double salario, int supervisao) : Funcionario(nome, codigo, salario) {
        this->supervisao = supervisao;
    } 

    double Remuneracao() const override {
        return (GetSalario() + (1.5 * supervisao / 100) * GetSalario());
    }
};

int main() {
    Funcionario Gerson("Gerson", 123, 1000.0);
    Supervisor Recebinha("Recebinha", 246, 2000.0, 1);

    Gerson.ExibirDados();
    Recebinha.ExibirDados();

    return 0;
}