#pragma once

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer.h>

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
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    bool demo;
    ImGui::ShowDemoWindow(&demo);

    ImGui::Render();
    auto &io = ImGui::GetIO();
    SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    SDL_SetRenderDrawColor(renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
                           (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));

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

    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

    SDL_RenderPresent(renderer);
}