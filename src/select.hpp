#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <unistd.h>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
std::vector<std::pair<int, int>> select_points(SDL_Renderer *renderer, SDL_Texture *map, TTF_Font *font, int matrix[100][100]);
#endif