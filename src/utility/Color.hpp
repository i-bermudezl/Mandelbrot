#pragma once

#include <concepts>
#include <cstdint>

#include "Buffer.hpp"

template <std::floating_point T> struct Color
{
    Color() = default;
    Color(T r, T g, T b, T a);

    std::uint32_t pack() const;

    T r;
    T g;
    T b;
    T a;
};

template <std::floating_point T> Color<T>::Color(T r, T g, T b, T a) : r{r}, g{g}, b{b}, a{a}
{
}

template <std::floating_point T> uint32_t Color<T>::pack() const
{
    auto R = static_cast<std::uint32_t>(r * 255);
    auto G = static_cast<std::uint32_t>(g * 255);
    auto B = static_cast<std::uint32_t>(b * 255);
    auto A = static_cast<std::uint32_t>(a * 255);
    return (R << 24) + (G << 16) + (B << 8) + A;
}
