#include "globals_structs_const.h"

void start_window() {
    int i;
    //    readmap();
    mp_gen();
    bool place[S_y][S_x];
    for (i = 0; i < 3; i++)
        if (tank1[i].ex) {
            tank1[i].alive = 1;
            int x0 = rand() % S_x, y0 = rand() % S_y, ang0 = rand() % 20;
            while (place[y0][x0] == 1)
                x0 = rand() % S_x, y0 = rand() % S_y, ang0 = rand() % 20;
            place[y0][x0] = 1;
            tank1[i].bal_limit = ball_num;
            tank1[i].x = x0 * box_width + box_width / 2;
            tank1[i].y = y0 * box_width + box_width / 2;
            tank1[i].ang = ang0;
            tank1[i].rgbs = 255255255;
            tank1[i].shoot = 0;
        }
    h = 1;
    laser.mood = 0;
    laser.time = 0;
    wall_color = 130130130;
    for (int l = 0; l < ball_num * tank_num; l++)
        ball[l].time = 0;
    SDL_SetWindowSize(window, S_Width + 2 * box_width, S_Height + 2 * box_width);
}

void make_ball(int index) {
    if (tank1[index].shoot == 0) {
        for (int i = 0; i < ball_num * tank_num; i++) {
            if (ball[i].time <= 0 && tank1[index].bal_limit > 0) {
                ball[i].time = ball_life_time;
                ball[i].x = tank1[index].x + (tank_rad + 5) * cos(tank1[index].ang);
                ball[i].y = tank1[index].y + (tank_rad + 5) * sin(tank1[index].ang);
                ball[i].angle = tank1[index].ang;
                ball[i].t = index;
                tank1[index].bal_limit--;
                ball[i].collor = 245245245;
                return;
            }
        }
    } else if (tank1[index].shoot == 1) {
        laser.mood=3;
        laser.time=20;
        for (int i = 0; i < tank_num; ++i) {
            if ((x_laser - tank1[i].x) * (x_laser - tank1[i].x) + (y_laser - tank1[i].y) * (y_laser - tank1[i].y) < 22 * 22) {
                tank1[i].alive = 0;
            }
        }
    }
}

void draw() {
    draw_map();
    for (int i = 0; i < tank_num; i++)
        if (tank1[i].alive) {
            draw_tank(i);
        }
    if (laser.mood == 1) {
        filledCircleRGBA(renderer, box_width + laser.x, box_width + laser.y, 12, ((laser.time / 200) % 3 == 0) * 255, ((laser.time / 200) % 3 == 1) * 255, ((laser.time / 200) % 3 == 2) * 255, 255);
    }
}

int rang;

void draw_map() {
    if (h == 1)
        rang = 0;
    if (h == -1)
        rang = 255;
    SDL_SetRenderDrawColor(renderer, rang, rang, rang, 255);
    SDL_RenderClear(renderer);

    int i = 0;
    int j = 0;
    for (; i < ball_num * tank_num; i++) {
        if (ball[i].time > 0) {
            filledCircleRGBA(renderer, ball[i].x + box_width, ball[i].y + box_width, 5, rang + h * ball[i].collor % 1000, rang + h * (ball[i].collor / 1000) % 1000, rang + h * (ball[i].collor / 1000000) % 1000000, 255);
        }
    }
    SDL_RenderSetScale(renderer, 1.5, 1.5);
    for (int k = 0; k < tank_num; ++k) {
        if (tank1[k].ex) {
            char i1[50];
            sprintf(i1, "score: %d", tank1[k].score);
            stringRGBA(renderer, 50 + k * 100, 10, i1, tank1[k].r, tank1[k].g, tank1[k].b, 255);
        }
    }
    char i1[50];
    sprintf(i1, "final score: %d", end_score);
    stringRGBA(renderer, 350, 10, i1, 255, 255, 255, 255);
    SDL_RenderSetScale(renderer, 1, 1);
    for (i = 0; i <= S_x; i++) {
        for (j = 0; j <= S_y; j++) {
            if (wal_h[j][i])
                thickLineRGBA(renderer, (box_width * (i + 1)), (box_width * (j + 1)), box_width * (i + 2), box_width * (j + 1), 5, rang + h * wall_color % 1000, rang + h * (wall_color / 1000) % 1000, rang + h * (wall_color / 1000000) % 1000000, 255);
            if (wal_v[j][i])
                thickLineRGBA(renderer, (box_width * (i + 1)), (box_width * (j + 1)), (box_width * (i + 1)), box_width * (j + 2), 5, rang + h * wall_color % 1000, rang + h * (wall_color / 1000) % 1000, rang + h * (wall_color / 1000000) % 1000000, 255);
        }
    }
}

void draw_tank(int i) {
    if (tank1[i].shoot == 1) {
        if(laser.mood==0)
            tank1[i].shoot=0;
        thickLineRGBA(renderer, tank1[i].x + (tank_rad + 10) * (cos(tank1[i].ang)) + box_width, tank1[i].y + (tank_rad + 10) * sin(tank1[i].ang) + box_width, x_laser + box_width, y_laser + box_width, 3, (laser.mood==3)*255, (laser.mood==2)*255, 0, 255);
    }
    thickLineRGBA(renderer, tank1[i].x + box_width, tank1[i].y + box_width, tank1[i].x + (tank_rad + 10) * (cos(tank1[i].ang)) + box_width, tank1[i].y + (tank_rad + 10) * sin(tank1[i].ang) + box_width, 7, rang + h * tank1[i].rgbs % 1000, rang + h * (tank1[i].rgbs / 1000) % 1000, rang + h * (tank1[i].rgbs / 1000000) % 1000000, 255);
    filledCircleRGBA(renderer, tank1[i].x + box_width, tank1[i].y + box_width, tank_rad, tank1[i].r, tank1[i].g, tank1[i].b, 255);
}

void destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
