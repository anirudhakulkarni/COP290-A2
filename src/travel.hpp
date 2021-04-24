#ifndef TRAVEL_H
#define TRAVEL_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;
void display(SDL_Renderer *renderer, SDL_Texture *map, vector<pair<int, int>> path);
#endif