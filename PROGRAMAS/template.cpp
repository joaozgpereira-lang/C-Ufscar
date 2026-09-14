#include <iostream>
#include <raylib.h>

using namespace std;

int main () {

    const int comprimento_janela = 1280, altura_janela = 960;
    InitWindow(comprimento_janela, altura_janela, "Nome");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        
        BeginDrawing();
            ClearBackground(BLACK);
        EndDrawing();
    }

    CloseWindow();
}