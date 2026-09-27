#include <iostream>
#include <raylib.h>
#include "grid.hpp"
#include <random>
using namespace std;

int main () {

    const int comprimento_janela = 800, altura_janela = 800;
    InitWindow(comprimento_janela, altura_janela, "Conway's Game");
    SetTargetFPS(30);

    Grid tab = Grid();

    while (!WindowShouldClose()) {
        
        tab.Atualiza();
        if(IsKeyDown(KEY_R)) tab.Inicial();
        BeginDrawing();
            ClearBackground({15, 15, 15, 255});
            tab.Desenha();
        EndDrawing();

    }
    
    CloseWindow();
}