#include <iostream>
#include <raylib.h>

using namespace std;

int pl1 = 0, pl2 = 0;

class Jogador {
    public:
    int comprimento, altura, vel = 15, cima, baixo;
    float x, y;

    Jogador(float x0, float y0, int com, int alt, int up, int down) {
        comprimento = com;
        altura = alt;
        x = x0;
        y = y0;
        cima = up;
        baixo = down;
    }

    void DesenhaJogador() {
        DrawRectangle(x, y, comprimento, altura, WHITE);
    }

    void AtualizaJogador() {
        if(IsKeyDown(cima)) {
            y -= vel;
            ColisaoJogador();
        }
        if(IsKeyDown(baixo)) {
            y += vel;
            ColisaoJogador();
        }
    }

    void ColisaoJogador() {
        if(y < 0) y = 0;
        if(y + altura > GetScreenHeight()) y = GetScreenHeight() - altura;
    }

    

};

class Bola {
    public:
    float x = 400, y = 300, raio = 14;
    int velx = 6, vely = 6;

    void DesenhaBola() {
        DrawCircle(x, y, raio, WHITE);
    }

    void AtualizaBola() {
        x += velx;
        y += vely;
        ColisaoBola();
    }

    void ColisaoBola() {
        if (y+raio >= 600) {
            y = 600 - raio;
            vely = vely * (-1);
        }

        if (y-raio <= 0) {
            y = raio;
            vely = vely * (-1);
        }

        if (x+raio > 800) {
            pl1++;
            x = 400;
            y = 300;
            velx = 6;
            vely = 6;
        }
        if (x-raio < 0) {
            pl2++;
            x = 400;
            y = 300;
            velx = 6;
            vely = 6;
        }
    }
};

int main () {

    const int comprimento_janela = 800, altura_janela = 600;
    InitWindow(comprimento_janela, altura_janela, "Nome");
    SetTargetFPS(60);

    Jogador P1 (10, GetScreenHeight()/2 - P1.altura/2, 15, 120, KEY_W, KEY_S);
    Jogador P2 (775, GetScreenHeight()/2 - P2.altura/2, 15, 120, KEY_UP, KEY_DOWN);
    Bola bola;


    while (!WindowShouldClose()){
    
        P1.AtualizaJogador();
        P2.AtualizaJogador();
        bola.AtualizaBola();

        // Colisão bola x players
        if(CheckCollisionCircleRec(Vector2{bola.x, bola.y}, bola.raio, Rectangle{P1.x, P1.y, P1.comprimento, P1.altura})) {
            bola.velx *= -1.2;
        }

        if(CheckCollisionCircleRec(Vector2{bola.x, bola.y}, bola.raio, Rectangle{P2.x, P2.y, P2.comprimento, P2.altura})) {
            bola.velx *= -1.2;
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawText(TextFormat("%d", pl1), 200, 20, 80, WHITE);
            DrawText(TextFormat("%d", pl2), 600, 20, 80, WHITE);
            DrawLine(GetScreenWidth()/2, 0, GetScreenWidth()/2, GetScreenHeight(), WHITE);
            P1.DesenhaJogador();
            P2.DesenhaJogador();
            bola.DesenhaBola();

        EndDrawing();
    }

    CloseWindow();
}