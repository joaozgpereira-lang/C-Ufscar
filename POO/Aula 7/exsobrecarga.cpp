#include <iostream>
using namespace std;

class Fracao{

    // operadores por funcao global
    friend Fracao operator+(int i, const Fracao &FD);

    friend Fracao operator-(int i, const Fracao &FD);

    friend Fracao operator*(int i, const Fracao& FD);

    friend ostream &operator<<(ostream &output, const Fracao &F);
    friend istream &operator>>(istream &output, Fracao &F);

    private:
        int num;
        int den;
    public:
        // metodos usuais da classe
        Fracao();
        Fracao(int n, int d);
        void set_num(int n);
        void set_den(int d = 1);
        int get_num() const;
        int get_den() const;

        // operadores por membro
        Fracao operator+(const Fracao &FD) const;
        Fracao operator+(int i) const;

        Fracao operator-(const Fracao &FD) const;
        Fracao operator-(int i) const;

        Fracao operator*(const Fracao& FD) const;
        Fracao operator*(int i) const;

        Fracao & operator++();
        Fracao operator++(int);

        Fracao & operator--();
        Fracao operator--(int);

        bool operator<(const Fracao &FD) const;

        bool operator<=(const Fracao &FD) const;

        bool operator>(const Fracao &FD) const;

        bool operator>=(const Fracao &FD) const;

        bool operator==(const Fracao &FD) const;

        bool operator!=(const Fracao &FD) const;

};

//métodos de utilização da classe
Fracao::Fracao(){
    set_num(0);
    set_den(1);
}

Fracao::Fracao(int n, int d){
    set_num(n);
    set_den(d);
}

void Fracao::set_num(int n){
    num = n;
}

void Fracao::set_den(int d){
    if(d != 0){
        den = d;
    }
    else{
        den = 1;
    }
}

int Fracao::get_num() const{
    return num;
}

int Fracao::get_den() const{
    return den;
}


//sobrecarga do operador +
Fracao Fracao::operator+(const Fracao &FD) const{
    Fracao res;
    res.set_den(den * FD.den);
    res.set_num(num * FD.den + FD.num * den);
    return res;
}

Fracao Fracao::operator+(int i) const{
    Fracao res;
    res.set_den(den);
    res.set_num(num + (i * den));
    return res;
}

Fracao operator+(int i, const Fracao &FD){
    Fracao res;
    res.set_den(FD.den);
    res.set_num(FD.num + (i * FD.den));
    return res;
}


//sobrecarga do operador -
Fracao Fracao::operator-(const Fracao &FD) const{
    Fracao res;
    res.set_den(den * FD.den);
    res.set_num(num * FD.den - FD.num * den);
    return res;
}

Fracao Fracao::operator-(int i) const{
    Fracao res;
    res.set_den(den);
    res.set_num(num - (i * den));
    return res;
}

Fracao operator-(int i, const Fracao &FD){
    Fracao res;
    res.set_den(FD.den);
    res.set_num((i * FD.den) - FD.num);
    return res;
}


//sobrecarga do operador *
Fracao Fracao::operator*(const Fracao& FD) const{
    Fracao res;
    res.set_num(this->num * FD.num);
    res.set_den(this->den * FD.den);
    return res;
}

Fracao Fracao::operator*(int i) const{
    Fracao res;
    res.set_num(num * i);
    res.set_den(den);
    return res;
}

Fracao operator*(int i, const Fracao& FD) {
    return FD * i;
}


//sobrecarga do operador ++
Fracao & Fracao::operator++(){ // pre fixado
    num += den;
    return *this;
}

Fracao Fracao::operator++(int){ // pos fixado
    Fracao copia(*this); 
    num += den;
    return copia;
}

//sobrecarga do operador --
Fracao & Fracao::operator--(){ // pre fixado
    num -= den;
    return *this;
}

Fracao Fracao::operator--(int){ // pos fixado
    Fracao copia(*this); 
    num -= den;
    return copia;
}


//sobrecarga do operador <<
ostream &operator<<(ostream &output, const Fracao &F){
    output << F.num << "/" << F.den;
    return output;
}


//sobrecarga do operador >>
istream &operator>>(istream &input, Fracao &F){
    input >> F.num;
    input.ignore();
    input >> F.den;
    return input;
}


//sobrecarga do operador <
bool Fracao::operator<(const Fracao &FD) const{
     if(((float)num/den) < ((float)FD.num/FD.den)){
        return true;
    }
    else{
        return false;
    }
}


//sobrecarga do operador <=
bool Fracao::operator<=(const Fracao &FD) const{
     if(((float)num/den) <= ((float)FD.num/FD.den)){
        return true;
    }
    else{
        return false;
    }
}


//sobrecarga do operador >
bool Fracao::operator>(const Fracao &FD) const{
     if(((float)num/den) > ((float)FD.num/FD.den)){
        return true;
    }
    else{
        return false;
    }
}


//sobrecarga do operador >=
bool Fracao::operator>=(const Fracao &FD) const{
     if(((float)num/den) >= ((float)FD.num/FD.den)){
        return true;
    }
    else{
        return false;
    }
}

//sobrecarga do operador ==
bool Fracao::operator==(const Fracao &FD) const{
    if(((float)num/den) == ((float)FD.num/FD.den)){
        return true;
    }
    else{
        return false;
    }
}


//sobrecarga do operador !=
bool Fracao::operator!=(const Fracao &FD) const{
    if(((float)num/den) != ((float)FD.num/FD.den)){
        return true;
    }
    else{
        return false;
    }
}



int main() {
    Fracao f12(12, 1);
    Fracao f1(1, 1);
    Fracao f14(14, 1);
    Fracao f13(13, 1);

    // Operadores de adicao
    cout << "Soma de fracoes: " << f12 + f1 << endl; // Chama operator+(Fracao)
    cout << "Fracao + inteiro: " << f12 + 1 << endl; // Chama operator+(int)
    cout << "Inteiro + fracao: " << 1 + f12 << endl; // Chama operator+(int, Fracao)

    // Operadores de subtracao
    cout << "Subtracao de fracoes: " << f14 - f1 << endl; // Chama operator-(Fracao)
    cout << "Fracao - inteiro: " << f14 - 1 << endl; // Chama operator-(int)
    cout << "Inteiro - fracao: " << 14 - f1 << endl; // Chama operator-(int, Fracao)

    // Operadores de multiplicacao
    cout << "Multiplicacao de fracoes: " << f13 * f1 << endl; // Chama operator*(Fracao)
    cout << "Fracao * inteiro: " << f13 * 1 << endl; // Chama operator*(int)
    cout << "Inteiro * fracao: " << 1 * f13 << endl; // Chama operator*(int, Fracao)

    // Operadores de incremento
    Fracao preInc(12, 1);
    cout << "Pre-incremento: " << ++preInc << endl; // Chama operator++()

    Fracao posInc(12, 1);
    posInc++; // Chama operator++(int)
    cout << "Pos-incremento: " << posInc << endl;

    // Operadores de decremento
    Fracao preDec(14, 1);
    cout << "Pre-decremento: " << --preDec << endl; // Chama operator--()

    Fracao posDec(14, 1);
    posDec--; // Chama operator--(int)
    cout << "Pos-decremento: " << posDec << endl;

    // Operador de saida
    cout << "Saida: " << f13 << endl; // Chama operator<<

    // Operador de entrada
    Fracao entrada;
    cout << "Digite uma fracao (ex.: 13/1): ";
    cin >> entrada; // Chama operator>>

    cout << "Fracao digitada: " << entrada << endl; // Chama operator<<

    // Operadores de comparacao
    cout << boolalpha;

    cout << "12 < 13: " << (f12 < f13) << endl; // Chama operator<
    cout << "12 <= 12: " << (f12 <= f12) << endl; // Chama operator<=
    cout << "14 > 13: " << (f14 > f13) << endl; // Chama operator>
    cout << "14 >= 14: " << (f14 >= f14) << endl; // Chama operator>=
    cout << "13 == 13: " << (f13 == Fracao(13, 1)) << endl; // Chama operator==
    cout << "12 != 13: " << (f12 != f13) << endl; // Chama operator!=

    return 0;
}


