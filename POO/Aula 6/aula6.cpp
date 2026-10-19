#include <iostream>

using namespace std;

class Fracao {
    private:
        int num;
        int den;
    public:
        Fracao();
        Fracao(int num, int den);
        void SetNum(int num);
        void SetDen(int den);
        int GetNum() const;
        int GetDen() const;
        void Print() const;
};

Fracao operator* (Fracao f1, Fracao f2);

int main() {
    Fracao f1(3, 4);

    Fracao f2(2, 1);

    f1.Print();
    f2.Print();

    Fracao f3 = f1 * f2;
    f3.Print();

    return 0;
}

Fracao::Fracao() {
    SetNum(0);
    SetDen(1);
}

Fracao::Fracao(int num, int den) {
    this->num = num;
    this->den = den;
}

void Fracao::SetNum(int num) {
    this->num = num;
}

void Fracao::SetDen(int den) {
    (den==0) ? this->den = 1 : this->den = den;
}

int Fracao::GetNum() const {
    return num;
}

int Fracao::GetDen() const {
    return den;
}

void Fracao::Print() const {
    cout << GetNum() << "/" << GetDen() << endl;
}

Fracao operator* (Fracao fe, Fracao fd) {
    Fracao resultado;
    resultado.SetNum(fe.GetNum() * fd.GetNum());
    resultado.SetDen(fe.GetDen() * fd.GetDen());
    return resultado;
}