#include "travel.hpp"
SDL_Texture *load_texture2(SDL_Renderer *renderer, char *file)
{
    SDL_Surface *bitmap = NULL;
    SDL_Texture *texture = NULL;
    bitmap = SDL_LoadBMP(file);
    texture = SDL_CreateTextureFromSurface(renderer, bitmap);
    SDL_FreeSurface(bitmap);
    return texture;
}

void display(SDL_Renderer *renderer, SDL_Texture *map, vector<pair<int, int>> path)
{
    SDL_RenderCopy(renderer, map, NULL, NULL);
    SDL_Rect DestR;
    SDL_Texture *tex = NULL;
    tex = load_texture2(renderer, "resources/player.bmp");

    for (int i = 0; i < path.size(); i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        cout << i << endl;
        DestR.x = (path[i].first) * 24;
        DestR.y = (path[i].second) * 24;
        DestR.w = 24;
        DestR.h = 24;
        SDL_RenderCopy(renderer, tex, NULL, &DestR);
        SDL_RenderPresent(renderer);
    }
}