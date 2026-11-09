#include <iostream>
using namespace std;


class Complexo {
private:
    double real;
    double imag;

public:
    Complexo() {
        real = imag = 0;
    }

    Complexo(double R, double I) {
        real = R;
        imag = I;
    }

    double GetReal() const {
        return real;
    }

    double GetImag() const {
        return imag;
    }

    friend ostream& operator<<(ostream& output, const Complexo& CD);

    Complexo operator+(Complexo& CD) const {
        Complexo res(real + CD.real, imag + CD.imag);
        return res;
    }

    friend Complexo operator+(double Real, Complexo& CD);

    Complexo operator++(int) {
        Complexo copia(*this);
        real++;
        return copia;
    }

    bool operator==(const Complexo& CD) const {
        return (real==CD.real && imag==CD.imag);
    }

};

int main() {
    Complexo A(2, 3), B(4, -1), C;

    cout << "A = " << A << endl;
    cout << "B = " << B << endl;

    C = A + B;
    cout << "C = A + B = " << C << endl;

    A = 2.0 + A;
    cout << "A = 2.0 + A = " << A << endl;

    cout << "A++ = " << A++ << endl;

    if (A == Complexo(5, 3))
        cout << "A possui o valor esperado" << endl;

    return 0;
}

ostream& operator<<(ostream& output, const Complexo& CD) {
    output << CD.real << "+" << CD.imag << "i";
    return output;
}

Complexo operator+(double Real, Complexo& CD) {
    Complexo res(Real + CD.GetReal(), CD.GetImag());
    return res;
}