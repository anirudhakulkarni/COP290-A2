#include "select.hpp"
#include <iostream>
using namespace std;
SDL_Texture *load_texture(SDL_Renderer *renderer, char *file)
{
    SDL_Surface *bitmap = NULL;
    SDL_Texture *texture = NULL;
    bitmap = SDL_LoadBMP(file);
    texture = SDL_CreateTextureFromSurface(renderer, bitmap);
    SDL_FreeSurface(bitmap);
    return texture;
}

std::vector<std::pair<int, int>> select_points(SDL_Renderer *renderer, SDL_Texture *map, TTF_Font *font, int matrix[100][100])
{
    SDL_Event e;
    SDL_Renderer *temprenderer = renderer;
    int pressed = false;
    int x = 0, y = 0;
    SDL_Texture *tex = NULL;
    tex = load_texture(renderer, "resources/player.bmp");
    std::vector<std::pair<int, int>> pointsarray;
    SDL_Rect DestR;
    int i = -1;
    SDL_RenderCopy(renderer, map, NULL, NULL);

    while (!pressed)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&x, &y);
                cout << x << " F " << y << endl;
                // ENHANCEMENT: when mouse location is on invalid render something
            }
            //

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&x, &y);
                cout << x << " clicked " << y << endl;
                pointsarray.push_back(make_pair(x, y));
                i++;
            }
        }
        if (e.type == SDL_KEYDOWN)
        {
            break;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        // SDL_RenderClear(renderer);
        // SDL_RenderCopy(renderer, map, NULL, NULL);
        if (pointsarray.size() > i)
        {
            DestR.x = (pointsarray[i].first / 24) * 24;
            DestR.y = (pointsarray[i].second / 24) * 24;
            DestR.w = 24;
            DestR.h = 24;
            if (matrix[DestR.y / 24][DestR.x / 24])
                SDL_RenderCopy(renderer, tex, NULL, &DestR);
        }
        temprenderer = renderer;
        SDL_RenderPresent(renderer);
    }
    return pointsarray;
}
