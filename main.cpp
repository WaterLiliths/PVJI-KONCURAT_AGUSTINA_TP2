#include "raylib.h"
#include <string>
#include "Game.h"

int main() {
    Game game;
    
    InitWindow(828, 684, "Maria Agustina Koncurat");
    game.init();

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);

        game.update();
        game.draw();

        EndDrawing();
    }
    
    return 0;
}