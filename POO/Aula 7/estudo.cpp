#include <iostream>
using namespace std;

class Complexo {
    private:
        double real;
        double imag;
    public:
        Complexo() {
            real =imag = 0;
        }

        Complexo(double R, double I) {
            real = R;
            imag = I;
        }
        
        friend Complexo operator+(double Real, Complexo& CD);
        friend ostream& operator<<(ostream& output, const Complexo& comp);

        Complexo operator+(Complexo& CD);
        Complexo operator++(int);
        bool operator==(const Complexo& CD);
        
};

int main () {  
    Complexo A(3,4), B(5,0), C; 
    cout << "A = " << A << endl << "B = " << B << endl; 
    
    C = A + B; 
    cout << "C = A + B = " << C << endl; 
    
    A = 4.0 + A;
    cout << "A = 4.0 + A = " << A << endl; 
    
    cout << "A++ (incrementa 1 na parte real): " << A++ << endl; 
    
    if(C==A) 
    cout << "C e A são iguais"<< endl; 

    return 0; 
}

Complexo Complexo::operator+(Complexo& CD) {
    Complexo res;
    res.real = real + CD.real;
    res.imag = imag + CD.imag;
    return res;
}

Complexo operator+(double Real, Complexo& CD) {
    Complexo res;
    res.real = CD.real + Real;
    res.imag = CD.imag;
    return res;
}

Complexo Complexo::operator++(int) {
    Complexo copia(*this);
    real++;
    return copia;
}

ostream& operator<<(ostream& output, const Complexo& comp) {
    output << comp.real << "+" << comp.imag << "i";
    return output;
}

bool Complexo::operator==(const Complexo& CD) {
    return ((real==CD.real) && (imag==CD.imag));
}