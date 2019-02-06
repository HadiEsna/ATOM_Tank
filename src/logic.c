#include "globals_structs_const.h"

int win(int d) {
    int choose = 0;
    double times;
    bool f;
    SDL_SetWindowSize(window, 300, 350);
    while (1) {
        int start_ticks = SDL_GetTicks();
        times = (sin(start_ticks)) * (sin(start_ticks));
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Event event;
        SDL_RenderSetScale(renderer, 2, 2);
        thickLineRGBA(renderer, 2, 50, 148, 50, 100, 100, 100, 100, 150);
        char temp[50];
        sprintf(temp, "%s is winner!", tank1[d].name);
        stringRGBA(renderer, 5, 10, temp, tank1[d].r, tank1[d].g, tank1[d].b, 255);
        int i = 0;
        for (; i < 3 - empty; ++i) {
            if (tank1[i].ex) {
                sprintf(temp, "%s's score: %d", tank1[i].name, tank1[i].score);
                stringRGBA(renderer, 5, 30 + 20 * i, temp, tank1[i].r, tank1[i].g, tank1[i].b, 255);
            }
        }
        stringRGBA(renderer, 5, 50 + 30 * i, "main menu", (choose != 0) * 255 + (choose == 0) * (122), 255, (choose != 0) * 255 + (choose == 0) * (times * 132 + 122), (choose != 0) * 255 + (choose == 0) * times * 255);
        i++;
        stringRGBA(renderer, 5, 50 + 30 * i, "exit", (choose != 1) * 255 + (choose == 1) * (122), 255, (choose != 1) * 255 + (choose == 1) * (times * 132 + 122), (choose != 1) * 255 + (choose == 1) * times * 255);
        SDL_RenderSetScale(renderer, 1, 1);
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                return 0;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    return 0;
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    if (!f)
                        choose--;
                    f = 1;
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    if (!f)
                        choose++;
                    f = 1;
                }
                if (choose < 0)
                    choose += 2;
                choose %= 2;
                if (event.key.keysym.sym == SDLK_RETURN) {
                    if (choose % 4 == 0) {
                        return new_game;
                    } else if (choose % 4 == 1)
                        return 0;
                }
            } else if (event.type == SDL_KEYUP) {
                if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_DOWN)
                    f = 0;
            }
        }
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / 20);
    }
}

int make_laser() {
    if (rand() % 3 <= 1) {
        laser.time = 1500;
        laser.mood = 1;
        laser.x = (rand() % S_x) * box_width + box_width / 2;
        laser.y = (rand() % S_y) * box_width + box_width / 2;
    }
}

int playing() {
    while (1) {
        int i = 0;
        int start_ticks = SDL_GetTicks();
        int i1 = handleEvents();
        if (i1 == EEEE) return 0;
        if (i1 == new_game) return new_game;
        alive_tank = 0;
        if (laser.time > 0) {
            laser.time--;
            if (laser.time <= 0) {
                laser.mood = 0;
                for (int j = 0; j < tank_num; ++j) {
                    tank1[i].shoot=0;
                }
            }
        }
        for (; i < ball_num * tank_num; i++) {
            if (ball[i].time > 0) {
                move_ball(i);
                ball[i].time--;
                if (ball[i].time <= 0) {
                    tank1[ball[i].t].bal_limit++;
                }
            }
        }
        draw();
        if ((SDL_GetTicks() / 1000) % 15 == 0 && laser.mood == 0) {
            make_laser();
        }
        for (i = 0; i < tank_num; i++)
            if (tank1[i].alive) {
                alive_tank++;
                key_move(i);
            }
        for (int k = 0; k < tank_num; ++k) {
            if (tank1[k].alive && tank1[k].shoot == 1) {
                x_laser = tank1[k].x + (tank_rad + 5) * cos(tank1[k].ang);
                y_laser = tank1[k].y + (tank_rad + 5) * sin(tank1[k].ang);
                while (1) {
                    x_laser += cos(tank1[k].ang);
                    y_laser += sin(tank1[k].ang);
                    if (x_laser < 0 || x_laser > S_x * box_width || y_laser < 0 || y_laser > S_y * box_width || (tank1[0].alive && (x_laser - tank1[0].x) * (x_laser - tank1[0].x) + (y_laser - tank1[0].y) * (y_laser - tank1[0].y) < 20 * 20) || (tank1[1].alive && (x_laser - tank1[1].x) * (x_laser - tank1[1].x) + (y_laser - tank1[1].y) * (y_laser - tank1[1].y) < 20 * 20) ||
                        (tank1[2].alive && (x_laser - tank1[2].x) * (x_laser - tank1[2].x) + (y_laser - tank1[2].y) * (y_laser - tank1[2].y) < 20 * 20)) {
                        x_laser -= cos(tank1[k].ang);
                        y_laser -= sin(tank1[k].ang);
                        break;
                    }
                }
            }
        }
        if (alive_tank <= 1 && !time_mordan_baghie) {
            time_mordan_baghie = SDL_GetTicks();
        }
        if (time_mordan_baghie && (SDL_GetTicks() - time_mordan_baghie > 1000)) {
            time_mordan_baghie = 0;
            for (int j = 0; j < tank_num; ++j) {
                if (tank1[j].ex && tank1[j].alive) {
                    tank1[j].score++;
                    if (tank1[j].score == end_score) {
                        return win(j);
                    }
                }
            }
            return 147;
        }
        check_collision();
        SDL_RenderPresent(renderer);
        while (SDL_GetTicks() - start_ticks < 1000 / FPS);
    }
}

void check_collision() {
    int i = 0, j;
    for (int k = 0; k < tank_num; ++k) {
        if (laser.mood == 1 && (laser.x - tank1[k].x) * (laser.x - tank1[k].x) + (laser.y - tank1[k].y) * (laser.y - tank1[k].y) < (12 + 20) * (32)) {
            tank1[k].shoot = 1;
            laser.time = 0;
            laser.mood = 2;
            x_laser = tank1[k].x + (tank_rad + 5) * cos(tank1[k].ang);
            y_laser = tank1[k].y + (tank_rad + 5) * sin(tank1[k].ang);
        }
    }
    for (; i < ball_num * tank_num; i++) {
        if (ball[i].time > 0) {
            for (j = 0; j < tank_num; j++) {
                if (tank1[j].alive && tank1[j].ex && (tank1[j].x - ball[i].x) * (tank1[j].x - ball[i].x) + (tank1[j].y - ball[i].y) * (tank1[j].y - ball[i].y) < +tank_rad * tank_rad) {
                    tank1[j].alive = 0;
                    ball[i].time = 0;
                    tank1[ball[i].t].bal_limit++;
                }
            }
        }
    }
}