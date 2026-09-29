#pragma once
#include <iostream>
#include <raylib.h>
#include <random>

class Grid {
    public:
        int quadrado = 8;
        float largura = 800, altura = 800;
        int grid[100][100];
        int geracao = 0;
        Grid();
        void Inicializa();
        void Print();
        void Copia(int matrizoriginal[][100], int linhasoriginal, int matrizalvo[][100], int linhasalvo);
        void Desenha();
        bool Aleatorio();
        void Inicial();
        void Atualiza();
        int Vizinhos(int matriz[][100], int numerolinhas, int linha, int coluna);
        Color CorCelula(int celula);
        void UpFPS();
        void DownFPS();
};