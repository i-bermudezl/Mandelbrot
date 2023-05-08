#pragma once

#include <Eigen/Dense>

#include <cmath>
#include <concepts>
#include <numbers>

#include "Buffer.hpp"
#include "Color.hpp"

template <std::floating_point Precision> class Mandelbrot
{
  public:
    Mandelbrot(const int width, const int height);

    Buffer<Color<Precision>> operator()(const int iterations, const double scale, const double rotate,
                                        const double translateX, const double translateY);

  private:
    Color<Precision> operator()(const int iterations, const double i, const double j);

    const int width;
    const int height;
    Buffer<Color<double>> buffer;
};

template <std::floating_point Precision>
Mandelbrot<Precision>::Mandelbrot(const int width, const int height)
    : width{width}, height{height}, buffer{width, height}
{
}

template <std::floating_point Precision>
Buffer<Color<Precision>> Mandelbrot<Precision>::operator()(const int iterations, const double scale,
                                                           const double rotate, const double traslationX,
                                                           const double traslationY)
{
    const Eigen::Vector2d resolution{width, height};
    const Eigen::Vector2d traslation{traslationX, traslationY};

    const auto SIN{std::sin(rotate)};
    const auto COS{std::cos(rotate)};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            const Eigen::Vector2d coordinate{j, i};
            const Eigen::Vector2d flippedNDC{(coordinate.array() / resolution.array() * 2.0) - 1.0};
            const Eigen::Vector2d NDC{flippedNDC.x(), -flippedNDC.y()};

            Eigen::Vector2d uv{NDC / scale};
            uv = Eigen::Vector2d{uv.x() * COS - uv.y() * SIN, uv.x() * SIN + uv.y() * COS};
            uv += traslation;

            const auto color = this->operator()(iterations, uv.x(), uv.y());

            buffer.write(color, j, i);
        }
    }
    return buffer.clone();
}

template <std::floating_point Precision>
Color<Precision> Mandelbrot<Precision>::operator()(const int iterations, const double i, const double j)
{
    Eigen::Vector2d z{0.0, 0.0};
    Eigen::Vector2d c{i, j};
    int k = 0;
    while (z.norm() <= 4.0 && k < iterations)
    {
        Eigen::Vector2d z2{z.x() * z.x() - z.y() * z.y(), 2.0 * z.x() * z.y()};
        z = z2 + c;
        k++;
    }

    auto ratio{std::sqrt(static_cast<double>(k) / static_cast<double>(iterations))};
    return Color{ratio, ratio, ratio, 1.0};
}