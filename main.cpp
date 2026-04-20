#include "raylib.h"
#include <string>
#include "Game.h"

int main() {
    Game game;
    
    InitWindow(828, 684, "Alien Jump");
    InitAudioDevice();
    game.init();

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        game.update();
        game.draw();

        EndDrawing();
    }
    game.unload();
    CloseAudioDevice();
    CloseWindow();
    return 0;
}