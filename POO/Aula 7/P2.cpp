#include <iostream>
#include <string>
using namespace std;

class Funcionario {
private:
    string nome;
    int codigo;
    double salario;
public:
    Funcionario() {
        nome = "";
        codigo = 0;
        salario = 0;
    }

    Funcionario(string nome, int codigo, double salario) {
        this->nome = nome;
        this->codigo = codigo;
        this->salario = salario;
    }
    
    void SetNome(string nome) {
        this->nome = nome;
    }
    
    void SetCodigo(int codigo) {
        this->codigo = codigo;
    }
    
    void SetSalario(double salario) {
        this->salario = salario;
    }

    string GetNome(){
        return nome;
    }

    int GetCodigo() {
        return codigo;
    }

    double GetSalario() {
        return salario;
    }

    virtual double Remuneracao() {
        return salario;
    }

    void ExibirDados() {
        cout << "Nome: " << GetNome() << endl;
        cout << "Código: " << GetCodigo() << endl;
        cout << "Salario: " << GetSalario() << endl;
    }
};

class Gerente:public Funcionario {
private:
    int supervisao;
public:
    Gerente(string nome, int codigo, double salario, int supervisao) : Funcionario(nome, codigo, salario) {
        this->supervisao = supervisao;
    }
    
    void SetSupervisao(int supervisao);

    double Remuneracao() override {
        double novoSalario = GetSalario() + (0.01 * supervisao) * GetSalario();
        SetSalario(novoSalario);
        return GetSalario();
    }
};

int main() {
    return 0;
}