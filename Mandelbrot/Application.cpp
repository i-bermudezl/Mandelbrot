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
    Mandelbrot m{p.getWidth(), p.getHeight()};

    int iterations = 250;

    const auto defaultScale{1.0};
    const auto defaultRotation{0.0};
    const Eigen::Vector2d defaultTranslation{0.0, 0.0};

    auto scale{defaultScale};
    auto rotation{defaultRotation};
    auto translation{defaultTranslation};

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

            if (keyboardState[SDL_SCANCODE_D])
            {
                translation += Eigen::Vector2d{0.1, 0.0} / scale;
            }
            if (keyboardState[SDL_SCANCODE_A])
            {
                translation -= Eigen::Vector2d{0.1, 0.0} / scale;
            }
            if (keyboardState[SDL_SCANCODE_W])
            {
                translation += Eigen::Vector2d{0.0, 0.1} / scale;
            }
            if (keyboardState[SDL_SCANCODE_S])
            {
                translation -= Eigen::Vector2d{0.0, 0.1} / scale;
            }

            if (keyboardState[SDL_SCANCODE_E])
            {
                rotation += 1.0;
            }

            if (keyboardState[SDL_SCANCODE_Q])
            {
                rotation -= 1.0;
            }

            if (keyboardState[SDL_SCANCODE_O])
            {
                scale *= 0.9;
            }

            if (keyboardState[SDL_SCANCODE_P])
            {
                scale *= 1.1;
            }
        }

        auto buffer = m(iterations, scale, rotation, translation);
        p.present(buffer);
    }
}
