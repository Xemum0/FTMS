
#pragma once

#include <cassert>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <thread>
#define LA_IMPLEMENTATION
#include "la.h"
#include"Queries.hpp"
#include <iostream>
#include <vector>
#include <Windows.h>
#include<conio.h>

#include <atomic>

using namespace std;

extern std::atomic<bool> stopThreads;

typedef enum {
    BACK = 0,
    FORE = 1,
    PIXEL_N,
} Pixel;

#define WIDTH 44
#define HEIGHT 22
static_assert(HEIGHT % 2 == 0, "If the amount of display rows is not divisible by 2 we can't properly compress it. See show(void) function");
extern Pixel display[WIDTH * HEIGHT];

void fill(Pixel p);
void circle(V2f c, float r);
void show(void);
void back(void);

#define FPS 30
#define RADIUS (HEIGHT/4.0f)
#define GRAVITY 200.0f
#define DT (1.0f/FPS)
#define DAMPER 0.65f

extern V2f pos;
extern V2f vel;

void reset(void);
void runthBall();

void displayMenu(int selectedOption);
void processSelection(int selectedOption);
int runqueries();
