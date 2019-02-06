#include "globals_structs_const.h"


int main() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("AtomTank", 10, 10, 300, 300, SDL_WINDOW_OPENGL);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand(time(NULL));
    int con = 1;
    while (con) {
        int l=init();
        if (l == EEEE)
            return 0;
        while (1) {
            if (!load_game)
                start_window();
            load_game = 0;
            con = playing();
            if (con == 0 || con == new_game)
                break;
        }
    }
    destroy();
    return 0;
}
