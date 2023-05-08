#include "Application.hpp"

#include "Mandelbrot.hpp"

#include <imgui.h>
#include <imgui_impl_sdl2.h>

#include <SDL2/SDL.h>

Application::Application(int width, int height, std::string title) : p{width, height, title}
{
}

void Application::run()
{
    Mandelbrot<double> m{p.getWidth(), p.getHeight()};

    int iterations = 10;

    const auto defaultScale{1.0};
    const auto defaultRotation{0.0};
    const auto defaultTranslationX{0.0};
    const auto defaultTranslationY{0.0};

    auto scale{defaultScale};
    auto rotation{defaultRotation};
    auto radians{defaultRotation * std::numbers::pi / 180.0};
    auto translationX{defaultTranslationX};
    auto translationY{defaultTranslationY};

    auto quit = false;
    SDL_Event e{};
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            ImGui_ImplSDL2_ProcessEvent(&e);
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            const auto keyboardState = SDL_GetKeyboardState(nullptr);

            if (keyboardState[SDL_SCANCODE_ESCAPE])
            {
                quit = true;
            }

            if (keyboardState[SDL_SCANCODE_O])
            {
                scale *= 0.9;
            }

            if (keyboardState[SDL_SCANCODE_P])
            {
                scale *= 1.1;
            }

            if (keyboardState[SDL_SCANCODE_E])
            {
                rotation += 1.0;
            }

            if (keyboardState[SDL_SCANCODE_Q])
            {
                rotation -= 1.0;
            }

            radians = rotation * std::numbers::pi / 180.0;
            const auto SIN{std::sin(radians)};
            const auto COS{std::cos(radians)};

            auto directionX = COS;
            auto directionY = SIN;

            if (keyboardState[SDL_SCANCODE_D])
            {
                translationX += directionX * 0.1 / scale;
                translationY += directionY * 0.1 / scale;
            }
            if (keyboardState[SDL_SCANCODE_A])
            {
                translationX -= directionX * 0.1 / scale;
                translationY -= directionY * 0.1 / scale;
            }

            directionX = -SIN;
            directionY = COS;

            if (keyboardState[SDL_SCANCODE_W])
            {
                translationX += directionX * 0.1 / scale;
                translationY += directionY * 0.1 / scale;
            }
            if (keyboardState[SDL_SCANCODE_S])
            {
                translationX -= directionX * 0.1 / scale;
                translationY -= directionY * 0.1 / scale;
            }
        }

        auto buffer = m(iterations, scale, radians, translationX, translationY);
        p.present(buffer);
    }
}
