#include "pch.h"

using namespace std;

#define DIE(exitcode, msg)    do { cerr << "Fatal Error: " << msg << endl; exit(exitcode); } while(false)



SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;


void initSDL(uint32_t width, uint32_t height)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        DIE(1, "SDL_Init failed: " << SDL_GetError());

    uint32_t windowFlags = 0;
    g_window = SDL_CreateWindow("slamd", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, windowFlags);
    if (!g_window)
        DIE(2, "Failed to create SDL window: " << SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

    uint32_t rendererFlags = SDL_RENDERER_ACCELERATED;
    g_renderer = SDL_CreateRenderer(g_window, -1, rendererFlags);
    if (!g_renderer)
        DIE(3, "Failed to create SDL renderer: " << SDL_GetError());
}

bool eventPump()
{
    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
        case SDL_QUIT:
            return false;

        case SDL_KEYDOWN:
            if (evt.key.keysym.sym == SDLK_ESCAPE)
                return false;

        default:
            break;
        }
    }

    return true;
}



void update([[maybe_unused]] float deltaTime)
{

}

void render()
{
    SDL_SetRenderDrawColor(g_renderer, 180, 180, 180, 255);
    SDL_RenderClear(g_renderer);

    //...

    SDL_RenderPresent(g_renderer);
}


int main(int, char**)
{
    cout << "what up\n";

    initSDL(1280, 768);

    auto lastFrameTime = chrono::high_resolution_clock::now();
    SDL_Delay(1);
    while (eventPump())
    {
        auto thisFrameTime = chrono::high_resolution_clock::now();
        auto deltaTime = float(double(chrono::duration_cast<chrono::microseconds>(thisFrameTime - lastFrameTime).count()) * (1.0 / 1'000'000.0));
        lastFrameTime = thisFrameTime;

        update(deltaTime);
        render();
    }

    return 0;
}
