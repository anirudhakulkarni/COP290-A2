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
#include "travel.hpp"
#include "steiner_tsp.hpp"
using namespace std;
int xsize = 37;       //2*x-3 dynamic
int ysize = 37;       //2*y-3 dynamic
int matrix[100][100]; // constant
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
            if (!matrix[i][j])
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
    // int distances[1400][1400];
    // 1. Map reading from matrix.out
    freopen("../outputs/matrix.out", "r", stdin);
    for (int i = 0; i < xsize; i++)
    {
        for (int j = 0; j < ysize; j++)
        {
            cin >> matrix[i][j];
        }
    }
    for (int i = 0; i < xsize; i++)
    {
        for (int j = 0; j < ysize; j++)
        {
            printf("%d", matrix[i][j]);
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
        888,
        888,
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
    vector<pair<int, int>> selectedpoints = select_points(renderer, map, font, matrix);
    cout << "points selected are: \n";
    for (int i = 0; i < selectedpoints.size(); i++)
    {
        cout << selectedpoints[i].first << " " << selectedpoints[i].second << endl;
    }

    // REMEMBER
    // CAUTION
    // points are in X,Y format but indexing in matrix is Y,X
    // 5. travel the points
    cout << "Matrix start\n";
    vector<vector<int>> maze_mat_a(xsize, vector<int>(ysize));
    for (int i = 0; i < xsize; i++)
    {
        for (int j = 0; j < ysize; j++)
        {
            maze_mat_a[i][j] = matrix[i][j];
        }
    }
    cout << "Matrix done\n";
    pair<int, int> starting_point_a = selectedpoints[0];
    pair<int, int> ending_point_a = selectedpoints[1];

    vector<pair<int, int>> stone_coordinates_a(selectedpoints.size() - 2);
    for (int i = 0; i < selectedpoints.size() - 2; i++)
    {
        stone_coordinates_a[i] = selectedpoints[i + 2];
    }
    cout << "starting point: " << starting_point_a.first << " " << starting_point_a.second << endl;
    cout << "ending point: " << ending_point_a.first << " " << ending_point_a.second << endl;
    cout << "stone coordinates are: \n";
    for (int i = 0; i < selectedpoints.size() - 2; i++)
    {
        cout << stone_coordinates_a[i].first << " " << stone_coordinates_a[i].second << endl;
    }
    cout << "Path start\n";
    vector<pair<int, int>> path = maincopy(maze_mat_a, starting_point_a, ending_point_a, stone_coordinates_a);
    cout << "path done\n";
    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i].first << " " << path[i].second << endl;
    }

    // path.push_back(make_pair(1, 1));
    // path.push_back(make_pair(1, 2));
    // path.push_back(make_pair(1, 3));
    // path.push_back(make_pair(1, 4));
    // path.push_back(make_pair(1, 5));
    // path.push_back(make_pair(1, 6));
    // path.push_back(make_pair(1, 7));
    // path.push_back(make_pair(2, 7));
    // path.push_back(make_pair(3, 7));
    // path.push_back(make_pair(3, 6));
    display(renderer, map, path);
    // 5. displaying

    int key = 0;
    cin >> key;
    cout << key << "DONE" << endl;
    int x = 0, y = 0;
    SDL_Event e;
    // Useless work
    // while (true)
    // {
    //     if (SDL_PollEvent(&e))
    //     {
    //         if (e.type == SDL_QUIT)
    //         {
    //             break;
    //         }
    //     }
    //     std::this_thread::sleep_for(std::chrono::milliseconds(30));
    //     SDL_RenderClear(renderer);
    //     SDL_RenderCopy(renderer, map, NULL, NULL);
    //     SDL_RenderPresent(renderer);

    //     while (SDL_PollEvent(&e) != 0)
    //     {
    //         if (e.type == SDL_MOUSEMOTION)
    //         {
    //             SDL_GetMouseState(&x, &y);
    //             cout << x << " F " << y << endl;
    //         }
    //     }
    //     if (e.type == SDL_KEYDOWN)
    //     {
    //         break;
    //     }
    //     // Uint32 SDL_GetMouseState(int &x, int &y);

    //     // cout << x << " " << y << endl;
    // }
    SDL_DestroyTexture(tex);
    SDL_DestroyTexture(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
