#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <stdint.h>
#include <vector>
#include "constants.h"
#include "select.hpp"

using namespace std;
int xsize = 37; //2*x-3
int ysize = 37; //2*y-3
int map[37][37];
SDL_Texture *get_map_texture(SDL_Renderer *renderer)
{
    SDL_Surface *bitmap = NULL;
    SDL_Texture *map_texture;
    SDL_Rect rect;
    rect.w = TILE_SIZE;
    rect.h = TILE_SIZE;
    bitmap = SDL_LoadBMP("resources/tile.bmp");
    SDL_Texture *tex = NULL;
    tex = SDL_CreateTextureFromSurface(renderer, bitmap);
    map_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_WIDTH, SCREEN_HEIGHT);
    SDL_SetRenderTarget(renderer, map_texture);
    int i, j;
    for (i = 0; i < SCREEN_HEIGHT / TILE_SIZE; i++)
    {
        for (j = 0; j < SCREEN_WIDTH / TILE_SIZE; j++)
        {
            if (!map[i][j])
            {
                rect.x = TILE_SIZE * j;
                rect.y = TILE_SIZE * i;
                SDL_RenderCopy(renderer, tex, NULL, &rect);
            }
        }
    }
    SDL_SetRenderTarget(renderer, NULL);
    return map_texture;
}

int main()
{
    // 1. Map reading from matrix.out
    freopen("matrix.out", "r", stdin);
    for (int i = 0; i < xsize; i++)
    {
        for (int j = 0; j < ysize; j++)
        {
            cin >> map[i][j];
        }
    }
    for (int i = 0; i < xsize; i++)
    {
        for (int j = 0; j < ysize; j++)
        {
            printf("%d", map[i][j]);
        }
        printf("\n");
    }

    // 2. SDL initialization
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Texture *tex = NULL;
    SDL_Texture *map = NULL;
    TTF_Init();
    TTF_Font *font;
    font = TTF_OpenFont("resources/m5x7.ttf", 24);
    window = SDL_CreateWindow(
        "game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        0);

    if (window == NULL)
    {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }
    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        printf("Could not create renderer: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // 3. Generate maze texture from matrix
    map = get_map_texture(renderer);
    // 4. select points prompt
    vector<pair<int, int>> selectedpoints = select_points(renderer, map, font);
    for (int i = 0; i < selectedpoints.size(); i++)
    {
        cout << selectedpoints[i].first << " " << selectedpoints[i].second << endl;
    }
    // 5. displaying
    int key = 0;
    cin >> key;
    cout << key << "DONE" << endl;
    int x = 0, y = 0;
    SDL_Event e;

    while (true)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                break;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, map, NULL, NULL);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&x, &y);
                cout << x << " F " << y << endl;
            }
        }
        if (e.type == SDL_KEYDOWN)
        {
            break;
        }
        // Uint32 SDL_GetMouseState(int &x, int &y);

        // cout << x << " " << y << endl;
    }
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
