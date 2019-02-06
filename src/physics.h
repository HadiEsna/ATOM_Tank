//
// Created by hadi on 12/14/18.
//

#ifndef BASE_PHYSICS_H
#define BASE_PHYSICS_H


#include <stdbool.h>

void moveTank(int);

void key_move(int ind);

int handleEvents();

void U_D(double *angle);

void R_L(double *angle);

void move_ball(int);

#endif //BASE_PHYSICS_H
