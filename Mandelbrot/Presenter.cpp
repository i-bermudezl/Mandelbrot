#include "Presenter.hpp"

#include <iostream>
#include <stdexcept>

Presenter::Presenter(int width, int height, std::string title)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Error initializing SDL.");
    }

    this->width = width;
    this->height = height;

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                              SDL_WINDOW_SHOWN);

    if (window == nullptr)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        throw std::runtime_error("Error creating window");
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    renderTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, width, height);
}

Presenter::~Presenter()
{
    SDL_DestroyTexture(renderTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

int Presenter::getWidth()
{
    return width;
}

int Presenter::getHeight()
{
    return height;
}
