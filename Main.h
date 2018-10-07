#pragma once


//constant and shared values used within program

#define GAME_TITLE "Gooey Defense"

const unsigned short GAME_WINDOW_WIDTH = 1280;
const unsigned short GAME_WINDOW_HEIGHT = 720;

const double RAD2DEG_CONST = 57.29578;
const double DEG2RAD_CONST = 0.017453;

const int GRAVITY_CONST = 1;

extern SDL_Point mouse_pos; //most recent position of the mouse