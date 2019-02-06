//
// Created by hadi on 12/15/18.
//

#ifndef PROJECT_NAME_CONSTm_H
#define PROJECT_NAME_CONST_H
#include <stdio.h>
#include <stdlib.h>
#include "init.h"
#include <math.h>
#include <SDL2/SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <time.h>
#include "view.h"
#include "map_g.h"
#include "physics.h"
#include "logic.h"
#define FPS 100
#define box_width 100
#define S_Width box_width * S_x
#define S_Height box_width * S_y
#define ball_num 5
#define ball_speed 2
#define tank_speed 1.5
#define p 3.14159265359
#define w p / 90
#define tank_rad box_width / 5
#define ball_life_time 1100
#define tank_num 3
#define EEEE  1234
#define new_game  1111
bool load_game;
bool new_game_from_load;
typedef struct tank {
    double x;
    double y;
    double ang;
    int bal_limit;
    int ex;
    int alive;
    int r;
    int b;
    int g;
    int rgbs;
    int score;
    SDL_Keycode shot;
    SDL_Keycode R;
    SDL_Keycode L;
    SDL_Keycode U;
    char name[20];
    SDL_Keycode D;
    int shoot;
} tank;
double x_laser,y_laser;
struct laser{
    double x,y;
    int mood;
    int time;
} laser;
tank tank1[3];
int S_x,S_y;
typedef struct bullet {
    double time;
    double x;
    double y;
    double angle;
    int t;
    int collor;
} bullet;
int alive_tank;
double time_mordan_baghie;
int end_score;
int saved_n;
int empty;
struct bullet ball[tank_num*ball_num];
int t_n;
int map_color, wall_color;
int wal_v[11][11];
int wal_h[11][11];
int h;
SDL_Renderer *renderer;
SDL_Window *window;
#endif //PROJECT_NAME_CONST_H
