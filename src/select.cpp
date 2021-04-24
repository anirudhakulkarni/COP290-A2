#include "select.hpp"
#include <iostream>
using namespace std;

std::vector<std::pair<int, int>> select_points(SDL_Renderer *renderer, SDL_Texture *map, TTF_Font *font)
{
    SDL_Event e;
    int pressed = false;
    int x = 0, y = 0;
    std::vector<std::pair<int, int>> pointsarray;
    while (!pressed)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_MOUSEMOTION)
            {
                SDL_GetMouseState(&x, &y);
                cout << x << " F " << y << endl;
            }
            //

            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_GetMouseState(&x, &y);
                cout << x << " clicked " << y << endl;
                pointsarray.push_back(make_pair(x, y));
            }
        }
        if (e.type == SDL_KEYDOWN)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, map, NULL, NULL);

        // disp_text(renderer, "[s]erver or [c]lient?", font, 240, 200);
        SDL_RenderPresent(renderer);
    }
    return pointsarray;
}
