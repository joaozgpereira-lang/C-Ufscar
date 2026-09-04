/*

Integrantes: João Zavaglia Gâmbaro Pereira - 859425
Luigi Barbazia e Silva - 845686

Imagem do microondas utilizado no projeto: https://imgur.com/a/fEnMxlb

*/

#include <iostream>
using namespace std;


class Microondas {
    private:
        string modelo;
        int PotenciaMax;
        int tempo;
        bool Ligado;
        bool Porta;
    
    public:
        Microondas(string nome, int potmax) {
            modelo = nome;
            PotenciaMax = potmax;
            Ligado = 0;
            Porta = 0;
            tempo = 0;
        }

        void Ligar() {
           if(Porta) {
                cout << "Impossível ligar, porta aberta!\n";
            }
            else {
                Ligado = 1;
                cout << "Ligou!" << endl;
            }
        }

        void Desligar() {
            Ligado = 0;
            cout << "Desligou!" << endl;
        }
        
        void AbrirFecharPorta() {
            Porta = !Porta;
            cout << ((Porta) ? "Porta aberta" : "Porta fechada") << endl;
            if(Porta == 1 and Ligado == 1) {
                Desligar();
            }
        }
        
        void SetTempo(int segundos) {
            if (segundos > 600) {
                cout << "Tempo inválido, selecione outro tempo: ";
            }
            else {
                tempo = segundos;
            }
        }
        
        string GetModelo() {
            return modelo;
        }

        int GetTempo() {
            return tempo;
        }

        int GetPotencia() {
            return PotenciaMax;
        }

        bool GetPorta() {
            return Porta;
        }
};

int main() {
    
    Microondas Electrolux = Microondas("Electrolux 20l Branco MTO30", 1100);
    
    cout << "Exemplo de uso:" << endl;
    cout << "Modelo: " << Electrolux.GetModelo() << "\nPotência: " << Electrolux.GetPotencia() << "W" << endl;
    
    cout << "Abra a porta" << endl;
    Electrolux.AbrirFecharPorta();
    
    Electrolux.SetTempo(180);
    cout << "Tempo selecionado: " << Electrolux.GetTempo() << " segundos" << endl;
    
    cout << "Tenta ligar" << endl;
    Electrolux.Ligar();

    cout << "Fecha a porta e tenta ligar" << endl;
    Electrolux.AbrirFecharPorta();
    Electrolux.Ligar();

    cout << "Desliga" << endl;
    Electrolux.Desligar();

    return 0; 
}