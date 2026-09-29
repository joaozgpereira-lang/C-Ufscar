#include <iostream>
#include <raylib.h>
#include "grid.hpp"
#include <random>
using namespace std;

int main () {

    const int comprimento_janela = 800, altura_janela = 800;
    InitWindow(comprimento_janela, altura_janela, "Conway's Game");
    SetTargetFPS(30);
    
    bool pause = 1;
    bool maxfps = 0;
    Grid tab = Grid();

    while (!WindowShouldClose()) {
        
        if(IsKeyDown(KEY_TAB)) {
            
        }
        
        if(!pause) tab.Atualiza();
        if(IsKeyPressed(KEY_R)) tab.Inicial();
        if(IsKeyPressed(KEY_B)) tab.Inicializa();
        if(IsKeyPressed(KEY_RIGHT)) tab.Atualiza();
        if(IsKeyDown(KEY_UP)) tab.Atualiza();
        pause = IsKeyPressed(KEY_SPACE) ? (!pause) : (pause); 

        // FPS
        if(IsKeyDown(KEY_D)) tab.UpFPS();
        if(IsKeyDown(KEY_S)) tab.DownFPS();
        if(IsKeyPressed(KEY_THREE)) SetTargetFPS(30);
        maxfps = IsKeyPressed(KEY_G) ? (!maxfps) : (maxfps);
        if(maxfps) {
            SetTargetFPS(1000000);
        }
        else {
            SetTargetFPS(30);
        }


        //Mouse
        if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            Vector2 posicaoMouse = GetMousePosition();
            int linha = posicaoMouse.y / tab.quadrado;
            int coluna = posicaoMouse.x / tab.quadrado;
            tab.grid[linha][coluna] = 1;
        }
        if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 posicaoMouse = GetMousePosition();
            int linha = posicaoMouse.y / tab.quadrado;
            int coluna = posicaoMouse.x / tab.quadrado;
            tab.grid[linha][coluna] = 0;
        }

        BeginDrawing();
            ClearBackground({10, 10, 10, 255});
            tab.Desenha();
            DrawText(TextFormat("%d", tab.geracao), 10, 10, 15, WHITE);
            DrawText(TextFormat("FPS: %d", GetFPS()), 10, 25, 15, WHITE);
        EndDrawing();

    }
    
    CloseWindow();
}