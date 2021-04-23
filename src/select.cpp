#include "select.hpp"

std::vector<std::pair<int, int>> select_points(SDL_Renderer *renderer, SDL_Texture *map, TTF_Font *font)
{
    SDL_Event e;
    int pressed = false;
    std::vector<std::pair<int, int>> pointsarray;
    while (!pressed)
    {
        if (SDL_PollEvent(&e))
        {
            if (e.type == SDL_KEYDOWN)
            {
                break;
            }
            // if (e.type == SDL_KEYDOWN)
            // {
            //     if (e.key.keysym.sym == SDLK_c)
            //     {
            //         *menu = 'c';
            //         pressed = true;
            //     }
            //     else if (e.key.keysym.sym == SDLK_s)
            //     {
            //         *menu = 's';
            //         pressed = true;
            //     }
            // }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, map, NULL, NULL);

        // disp_text(renderer, "[s]erver or [c]lient?", font, 240, 200);
        SDL_RenderPresent(renderer);
    }
    return pointsarray;
}
