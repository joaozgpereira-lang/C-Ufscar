#include <iostream>
#include <cstring>
using namespace std;

typedef struct {
    int hora;
    int min;
    int seg;

    void set() {
        cout << "Insira as horas (24h): ";
        cin >> hora;
        check(&hora, 24);

        cout << "Insira os minutos: ";
        cin >> min;
        check(&min, 60);

        cout << "Insira os segundos: ";
        cin >> seg;
        check(&seg, 60);
    }

    void print24() {
        string period;
        if (hora>=0 and hora<12) {
            period = "AM";
        }
        else {
            period = "PM";
        }
        printf("%02d:%02d:%02d ", hora, min, seg);
        cout << period << endl;
    }

    void print12() {
        int hora12 = hora;
        if (hora12 > 12) {
            hora12 = hora-12;
        }

        printf("%02d:%02d:%02d\n", hora12, min, seg);
    }

    void check(int *val, int max) {
        while ((*val > max) or (*val<0)) {
            cout << "Horário inválido. Insira outro valor: ";
            cin >> *val;
        }
        if (*val == max) {
            *val = 0;
        }
    }

} horario;

int function (int valor) {
    valor++;
}

int main () {
    horario relogio;

    relogio.set();
    relogio.print24();
    relogio.print12();

    return 0;
}