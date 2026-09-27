#include "grid.hpp"
#include <iostream>
#include <raylib.h>
#include <random>

using namespace std;

Grid::Grid() {
    Inicializa();
    Inicial();
}

void Grid::Inicializa() {
    for(int i = 0; i < altura/quadrado; i++) {
        for(int j = 0; j < largura/quadrado; j++) {
            grid[i][j] = 0;
        }
    }
}

void Grid::Print() {
    for(int i = 0; i < altura/quadrado; i++) {
        for(int j = 0; j < largura/quadrado; j++) {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

void Grid::Desenha() {
    for(int i = 0; i < altura/quadrado; i++) {
        for(int j = 0; j < largura/quadrado; j++) {
            DrawRectangle(j * quadrado, i * quadrado, quadrado-1, quadrado-1, (grid[i][j] ? WHITE : BLACK));
        }
    }
}

bool Grid::Aleatorio() {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0,1);
    return dist(rd);
}

void Grid::Inicial() {
    for(int i = 0; i < altura/quadrado; i++) {
        for(int j = 0; j < largura/quadrado; j++) {
            grid[i][j] = Aleatorio();
        }
    }
}

void Grid::Copia(int matrizoriginal[][100], int linhasoriginal, int matrizalvo[][100], int linhasalvo) {
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            matrizalvo[i][j] = matrizoriginal[i][j];
        }
    }
}

void Grid::Atualiza() {
    int proxima[100][100];
    Copia(grid, 100, proxima, 100);
    for(int i = 0; i < altura/quadrado; i++) {
        for(int j = 0; j < largura/quadrado; j++) {
            int vizinhos = Vizinhos(proxima, 100, i, j);
            if (vizinhos < 2) {
                grid[i][j] = 0; // Solidão
            }
            else if (vizinhos > 3) {
                grid[i][j] = 0; // Superpopulação
            }
             else if (vizinhos == 3) {
                grid[i][j] = 1; // Reprodução
            }
        }
    }

}

int Grid::Vizinhos(int matriz[][100], int numerolinhas, int linha, int coluna) {
    int contador = 0;
    if (!(linha-1<0 or linha+1>99 or coluna-1<0 or coluna+1>99)){
        if (matriz[linha-1][coluna-1]) contador++;
        if (matriz[linha-1][coluna]) contador++;
        if (matriz[linha-1][coluna+1]) contador++;
        if (matriz[linha][coluna-1]) contador++;
        if (matriz[linha][coluna+1]) contador++;
        if (matriz[linha+1][coluna-1]) contador++;
        if (matriz[linha+1][coluna]) contador++;
        if (matriz[linha+1][coluna+1]) contador++;
    }
    return contador;
}

