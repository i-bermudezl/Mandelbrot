#pragma once

#include <sdl2/SDL.h>

#include <concepts>
#include <string>

#include "Buffer.hpp"
#include "Color.hpp"

class Presenter
{
  public:
    Presenter(int width, int height, std::string title);
    ~Presenter();

    template <std::floating_point Precision> void present(const ColorBuffer<Precision> &framebuffer);

    int getWidth();
    int getHeight();

  private:
    int width;

    int height;

    SDL_Window *window;

    SDL_Renderer *renderer;

    SDL_Texture *renderTexture;
};

template <std::floating_point Precision> void Presenter::present(const ColorBuffer<Precision> &framebuffer)
{
    SDL_RenderClear(renderer);

    uint32_t *pixels = nullptr;
    int pitch;
    SDL_LockTexture(renderTexture, nullptr, (void **)&pixels, &pitch);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auto color{framebuffer.read(j, i)};
            pixels[j + i * width] = color.pack();
        }
    }
    SDL_UnlockTexture(renderTexture);

    SDL_RenderCopy(renderer, renderTexture, nullptr, nullptr);

    SDL_RenderPresent(renderer);
}