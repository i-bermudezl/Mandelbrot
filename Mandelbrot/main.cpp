#include <cstdlib>
#include <iostream>

#include <Eigen/Dense>
#include <SDL2/SDL.h>

#include "Color.hpp"

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    auto width = 1280, height = 720;
    auto simulationWidth = width, simulationHeight = height;

    auto window = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                   SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        std::exit(EXIT_FAILURE);
    }

    auto renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    auto texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);

    int *pixels = nullptr;
    int pitch;
    SDL_LockTexture(texture, nullptr, (void **)&pixels, &pitch);

    Eigen::Vector2d resolution = Eigen::Vector2d(simulationWidth, simulationHeight);
    for (int i = 0; i < simulationHeight; i++)
    {
        for (int j = 0; j < simulationWidth; j++)
        {
            Eigen::Vector2d coordinate = Eigen::Vector2d(j, i);

            Eigen::Vector2d c = (coordinate.array() / resolution.array() * 0.01) - 0.55;

            Eigen::Vector2d zn = c;
            int k;
            for (k = 0; k < 255; k++)
            {
                Eigen::Vector2d z2 = Eigen::Vector2d(zn.x() * zn.x() - zn.y() * zn.y(), 2.0 * zn.x() * zn.y());
                zn = z2 + c;
                if (zn.norm() > 2.0)
                {
                    break;
                }
            }

            pixels[j + i * simulationWidth] = static_cast<double>(k) / 255 * 0xffffffff;
        }
    }
    
    SDL_UnlockTexture(texture);

    std::cout << "Done!\n";

    auto quit = false;
    SDL_Event e{};
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }

            SDL_RenderClear(renderer);

            SDL_RenderCopy(renderer, texture, nullptr, nullptr);

            SDL_RenderPresent(renderer);
        }
    }

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}