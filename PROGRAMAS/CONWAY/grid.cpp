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
    geracao = 0;
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
            DrawRectangle(j * quadrado, i * quadrado, quadrado-1, quadrado-1, CorCelula(grid[i][j]));
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
    geracao = 0;
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
                grid[i][j]++; // Reprodução
            }
            else if (proxima[i][j] > 0 and vizinhos == 2) {
                grid[i][j]++; // Sobrevivência
            }
        }
    }
    geracao++;
}

int Grid::Vizinhos(int matriz[][100], int numerolinhas, int linha, int coluna) {
    int contador = 0;
    if (!(linha-1<0 or linha+1>99 or coluna-1<0 or coluna+1>99)){
        if (matriz[linha-1][coluna-1] > 0) contador++;
        if (matriz[linha-1][coluna] > 0) contador++;
        if (matriz[linha-1][coluna+1] > 0) contador++;
        if (matriz[linha][coluna-1] > 0) contador++;
        if (matriz[linha][coluna+1] > 0) contador++;
        if (matriz[linha+1][coluna-1] > 0) contador++;
        if (matriz[linha+1][coluna] > 0) contador++;
        if (matriz[linha+1][coluna+1] > 0) contador++;
    }
    return contador;
}

Color Grid::CorCelula(int celula) {
    switch (celula) {
        case -1: return {10,10,10,255};
        case 0: return BLACK;
        case 1: return RED;
        case 2: return ORANGE;
        case 3: return YELLOW;
        case 4: return GREEN;
        case 5: return DARKGREEN;
        case 6: return BLUE;
        case 7: return DARKBLUE;
        
        default: return {0, 41, 55, 255};
    }

        //case 0: return BLACK;
        //case 1: return {223, 177, 203, 255};
        //case 2: return {189, 148, 195, 255};
        //case 3: return {159, 134, 192, 255};
        //case 4: return {94, 85, 142, 255};
        
        //default: return {36, 25, 67, 255};
}

void Grid::UpFPS() {
    int fps = GetFPS();
    fps+=10;
    SetTargetFPS(fps);
}

void Grid::DownFPS() {
    int fps = GetFPS();
    fps-=10;
    SetTargetFPS(fps);
}
