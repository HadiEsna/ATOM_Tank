//
// Created by hadi on 12/14/18.
//

#include "globals_structs_const.h"

bool key_s[503];


void high_cont() {
    h = -h;
}

void U_D(double *angle) {
    *angle = p - *angle;
}

void R_L(double *angle) {
    *angle = -*angle;
}

int move[2];

void key_move(int ind) {
    if (ind == 0) {
        move[0] = key_s[tank1[0].D % 503] - key_s[tank1[0].U % 503];
        move[1] = (-key_s[tank1[0].R % 503] + key_s[tank1[0].L % 503]);
        moveTank(0);
    }
    if (ind == 1) {
        move[0] = key_s[tank1[1].D % 503] - key_s[tank1[1].U % 503];
        move[1] = (-key_s[tank1[1].R % 503] + key_s[tank1[1].L % 503]);
        moveTank(1);
    }
    if (ind == 2) {
        move[0] = key_s[tank1[2].D % 503] - key_s[tank1[2].U % 503];
        move[1] = (-key_s[tank1[2].R % 503] + key_s[tank1[2].L % 503]);
        moveTank(2);
    }


}

void moveTank(int ind) {
    int x_perv = tank1[ind].x, y_perv = tank1[ind].y;
    int box_num_x_l_perv = (tank1[ind].x + (tank_rad + 7) * cos(tank1[ind].ang)) / (box_width);
    int box_num_y_l_perv = (tank1[ind].y + (tank_rad + 7) * sin(tank1[ind].ang)) / (box_width);
    double abc = tank1[ind].ang;
    tank1[ind].ang -= (move[1]) * w;
    tank1[ind].y -= (move[0]) * sin(tank1[ind].ang) * tank_speed;
    tank1[ind].x -= (move[0]) * cos(tank1[ind].ang) * tank_speed;
    int x_now = tank1[ind].x, y_now = tank1[ind].y;
    int x_box = x_now % (box_width), y_box = y_now % (box_width), box_num_x = (x_now) / (box_width), box_num_y = y_now / (box_width);
    int box_num_x_l = (x_now + (tank_rad + 11) * cos(tank1[ind].ang)) / (box_width);
    int box_num_y_l = (y_now + (tank_rad + 11) * sin(tank1[ind].ang)) / (box_width);
    // check kardan looleye tank
    if (tank1[ind].ang != abc && ((x_box + (tank_rad + 10) * cos(tank1[ind].ang)) < 0) && wal_v[box_num_y][box_num_x])tank1[ind].x -= x_box + (tank_rad + 10) * cos(tank1[ind].ang);
    if (tank1[ind].ang != abc && ((x_box + (tank_rad + 10) * cos(tank1[ind].ang)) > box_width) && wal_v[box_num_y][box_num_x + 1])tank1[ind].x -= tank_rad + 10 - (tank_rad + 10) * cos(tank1[ind].ang);
    if (tank1[ind].ang != abc && ((y_box + (tank_rad + 10) * sin(tank1[ind].ang)) < 0) && wal_h[box_num_y][box_num_x])tank1[ind].y -= y_box + (tank_rad + 10) * sin(tank1[ind].ang);
    if (tank1[ind].ang != abc && ((y_box + (tank_rad + 10) * sin(tank1[ind].ang)) > box_width) && wal_h[box_num_y + 1][box_num_x])tank1[ind].y -= tank_rad + 10 - (tank_rad + 10) * sin(tank1[ind].ang);


    if (x_box * x_box + y_box * y_box < (tank_rad + 12) * (tank_rad + 12) - 10) {//بالا چپ
        if (box_num_y_l < box_num_y_l_perv && wal_h[box_num_y][box_num_x - 1] && box_num_x - 1 == box_num_x_l && !wal_v[box_num_y][box_num_x] && !wal_h[box_num_y][box_num_x]) {
            tank1[ind].y += 3;
        }
        if (box_num_x_l < box_num_x_l_perv && wal_v[box_num_y - 1][box_num_x] && box_num_y - 1 == box_num_y_l && !wal_v[box_num_y][box_num_x] && !wal_h[box_num_y][box_num_x]) {
            tank1[ind].x += 3;
        }
    }
    if (x_box * x_box + (box_width - y_box) * (box_width - y_box) < (tank_rad + 12) * (tank_rad + 12) - 10) {//پایین چپ
        if (box_num_y_l > box_num_y_l_perv && wal_h[box_num_y + 1][box_num_x - 1] && box_num_x - 1 == box_num_x_l && !wal_v[box_num_y][box_num_x] && !wal_h[box_num_y + 1][box_num_x]) {
            tank1[ind].y -= 3;
        }
        if (box_num_x_l < box_num_x_l_perv && wal_v[box_num_y + 1][box_num_x] && box_num_y + 1 == box_num_y_l && !wal_v[box_num_y][box_num_x] && !wal_h[box_num_y + 1][box_num_x]) {
            tank1[ind].x += 3;
        }
    }

    if ((box_width - x_box) * (box_width - x_box) + (box_width - y_box) * (box_width - y_box) < (tank_rad + 12) * (tank_rad + 12) - 10) {//پایین راست
        if (box_num_y_l > box_num_y_l_perv && wal_h[box_num_y + 1][box_num_x + 1] && box_num_x + 1 == box_num_x_l && !wal_v[box_num_y][box_num_x + 1] && !wal_h[box_num_y + 1][box_num_x]) {
            tank1[ind].y -= 3;
        }
        if (box_num_x_l > box_num_x_l_perv && wal_v[box_num_y + 1][box_num_x + 1] && box_num_y + 1 == box_num_y_l && !wal_v[box_num_y][box_num_x + 1] && !wal_h[box_num_y + 1][box_num_x]) {
            tank1[ind].x -= 3;
        }
    }

    if ((box_width - x_box) * (box_width - x_box) + y_box * y_box < (tank_rad + 12) * (tank_rad + 12) - 10) {//بالا راست
        if (box_num_y_l < box_num_y_l_perv && wal_h[box_num_y][box_num_x + 1] && box_num_x + 1 == box_num_x_l && !wal_v[box_num_y][box_num_x + 1] && !wal_h[box_num_y][box_num_x]) {
            tank1[ind].y += 3;
        }
        if (box_num_x_l > box_num_x_l_perv && wal_v[box_num_y - 1][box_num_x + 1] && box_num_y - 1 == box_num_y_l && !wal_v[box_num_y][box_num_x + 1] && !wal_h[box_num_y][box_num_x]) {
            tank1[ind].x -= 3;
        }
    }

    // check kardan dayereye tank
    if (x_perv >= x_now && (x_box < tank_rad || (x_box + (tank_rad + 10) * cos(tank1[ind].ang)) < 0) && wal_v[box_num_y][box_num_x])tank1[ind].x += (move[0]) * cos(tank1[ind].ang) * tank_speed;
    if (x_perv <= x_now && (x_box > (box_width) - tank_rad || x_box + (tank_rad + 10) * cos(tank1[ind].ang) > (box_width)) && wal_v[box_num_y][box_num_x + 1])tank1[ind].x += (move[0]) * cos(tank1[ind].ang) * tank_speed;
    if (y_perv >= y_now && (y_box < tank_rad || (y_box + (tank_rad + 10) * sin(tank1[ind].ang)) < 0) && wal_h[box_num_y][box_num_x]) tank1[ind].y += (move[0]) * sin(tank1[ind].ang) * tank_speed;
    if (y_perv <= y_now && (y_box > (box_width) - tank_rad || (y_box + (tank_rad + 10) * sin(tank1[ind].ang)) > (box_width)) && wal_h[box_num_y + 1][box_num_x])tank1[ind].y += (move[0]) * sin(tank1[ind].ang) * tank_speed;

    //check kardan gooshe ha
    if (x_box * x_box + y_box * y_box < tank_rad * tank_rad - 40) {//بالا چپ
        if (x_perv > x_now && wal_h[box_num_y][box_num_x - 1] + wal_v[box_num_y - 1][box_num_x]) {
            tank1[ind].x += (move[0]) * cos(tank1[ind].ang) * tank_speed;
            tank1[ind].y += 1;
        }
        if (y_perv > y_now && wal_h[box_num_y][box_num_x - 1] + wal_v[box_num_y - 1][box_num_x]) {
            tank1[ind].y += (move[0]) * sin(tank1[ind].ang) * tank_speed;
            tank1[ind].x += 1;
        }
    }


    if (x_box * x_box + (box_width - y_box) * (box_width - y_box) < tank_rad * tank_rad - 40) {//پایین چپ
        if (x_perv > x_now && wal_h[box_num_y + 1][box_num_x - 1] + wal_v[box_num_y + 1][box_num_x]) {
            tank1[ind].x += (move[0]) * cos(tank1[ind].ang) * tank_speed;
            tank1[ind].y -= 1;
        }
        if (y_perv < y_now && wal_h[box_num_y + 1][box_num_x - 1] + wal_v[box_num_y + 1][box_num_x]) {
            tank1[ind].y += (move[0]) * sin(tank1[ind].ang) * tank_speed;
            tank1[ind].x += 1;
        }
    }


    if ((box_width - x_box) * (box_width - x_box) + y_box * y_box < tank_rad * tank_rad - 40) {//بالا راست
        if (x_perv < x_now && wal_h[box_num_y][box_num_x + 1] + wal_v[box_num_y - 1][box_num_x + 1]) {
            tank1[ind].x += (move[0]) * cos(tank1[ind].ang) * tank_speed;
            tank1[ind].y += 1;
        }
        if (y_perv > y_now && wal_h[box_num_y][box_num_x + 1] + wal_v[box_num_y - 1][box_num_x + 1]) {
            tank1[ind].y += (move[0]) * sin(tank1[ind].ang) * tank_speed;
            tank1[ind].x -= 1;
        }
    }

    if ((box_width - x_box) * (box_width - x_box) + (box_width - y_box) * (box_width - y_box) < tank_rad * tank_rad - 40) {//پایین راست
        if (x_perv < x_now && wal_h[box_num_y + 1][box_num_x + 1] + wal_v[box_num_y + 1][box_num_x + 1]) {
            tank1[ind].x += (move[0]) * cos(tank1[ind].ang) * tank_speed;
            tank1[ind].y -= 1;
        }
        if (y_perv < y_now && wal_h[box_num_y + 1][box_num_x + 1] + wal_v[box_num_y + 1][box_num_x + 1]) {
            tank1[ind].y += (move[0]) * sin(tank1[ind].ang) * tank_speed;
            tank1[ind].x -= 1;
        }
    }


}

void move_ball(int ind) {
    int x_perv = ball[ind].x;
    int y_perv = ball[ind].y;
    ball[ind].x += ball_speed * (cos(ball[ind].angle));
    ball[ind].y += ball_speed * (sin(ball[ind].angle));
    int f = 0;
    int x_now = ball[ind].x, y_now = ball[ind].y;
    int x_box = x_now % (box_width), y_box = y_now % (box_width), box_num_x = (x_now) / (box_width), box_num_y = y_now / (box_width);
    if (x_box < 5 && wal_v[box_num_y][box_num_x]) {
        U_D(&(ball[ind].angle));
        ball[ind].x += 5;
        f = 1;
    }
    if (x_box > (box_width) - 5 && wal_v[box_num_y][box_num_x + 1] || ball[ind].x < 0) {
        U_D(&(ball[ind].angle));
        ball[ind].x -= 5;
        f = 1;
    }
    if (y_box < 5 && wal_h[box_num_y][box_num_x]) {
        R_L(&(ball[ind].angle));
        ball[ind].y += 5;
        f = 1;
    }
    if (y_box + 5 > box_width && wal_h[box_num_y + 1][box_num_x]) {
        R_L(&(ball[ind].angle));
        ball[ind].y -= 5;
        f = 1;
    }
    if (f == 1)
        return;
    if (x_box <= 3 && y_box <= 3 && x_perv > x_now && y_perv > y_now) {
        if (wal_v[box_num_y - 1][box_num_x])
            U_D(&(ball[ind].angle));
        if (wal_h[box_num_y][box_num_x - 1])
            R_L(&(ball[ind].angle));
    }
    if (x_box <= 3 && y_box + 3 >= (box_width) && x_perv > x_now && y_perv < y_now) {
        if (wal_v[box_num_y + 1][box_num_x - 1])
            U_D(&(ball[ind].angle));
        if (wal_h[box_num_y + 1][box_num_x])
            R_L(&(ball[ind].angle));
    }
    if (x_box + 3 >= (box_width) && y_box <= 3 && x_perv < x_now && y_perv > y_now) {
        if (wal_v[box_num_y - 1][box_num_x + 1])
            U_D(&(ball[ind].angle));
        if (wal_h[box_num_y][box_num_x + 1])
            R_L(&(ball[ind].angle));
    }
    if (x_box + 3 >= (box_width) && y_box + 3 >= (box_width) && x_perv < x_now && y_perv < y_now) {
        if (wal_v[box_num_y - 1][box_num_x])
            U_D(&(ball[ind].angle));
        if (wal_h[box_num_y][box_num_x - 1])
            R_L(&(ball[ind].angle));
    }
}

int f[16];
int fx = 0;
int fm = 0j;


int handleEvents() {
    SDL_Event event;
    static bool first = 1;
    if (first) {
        first = 0;
        return 0;
    }
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return EEEE;
        if (event.type == SDL_KEYDOWN) {
            key_s[event.key.keysym.sym % 503] = 1;
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                return menu();
            }
            if (event.key.keysym.sym == tank1[0].shot && tank1[0].ex && tank1[0].alive) {
                if (!f[0])
                    make_ball(0);
                f[0] = 1;
            }
            if (event.key.keysym.sym == tank1[2].shot && tank1[2].ex && tank1[2].alive) {
                if (!f[2])
                    make_ball(2);
                f[2] = 1;
            }
            if (event.key.keysym.sym == tank1[1].shot && tank1[1].ex && tank1[1].alive) {
                if (!f[1])
                    make_ball(1);
                f[1] = 1;
            }
            if (event.key.keysym.sym == SDLK_h) {
                if (!fx)
                    high_cont();
                fx = 1;
            }
        }
        if (event.type == SDL_KEYUP) {
            key_s[event.key.keysym.sym % 503] = 0;
            if (event.key.keysym.sym == tank1[0].shot)
                f[0] = 0;
            if (event.key.keysym.sym == tank1[1].shot)
                f[1] = 0;
            if (event.key.keysym.sym == tank1[2].shot)
                f[2] = 0;
            if (event.key.keysym.sym == SDLK_h)
                fx = 0;
        }
    }
}

