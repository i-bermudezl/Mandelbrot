#pragma once

#include <Eigen/Dense>

#include <cmath>
#include <concepts>
#include <numbers>

#include "Buffer.hpp"

class Mandelbrot
{
  public:
    Mandelbrot(int width, int height);

    Buffer<Color<double>> operator()(int iterations, double scale, double rotate, const Eigen::Vector2d &translate);

  private:
    const int width;
    const int height;
    Buffer<Color<double>> buffer;
};

Mandelbrot::Mandelbrot(int width, int height) : width{width}, height{height}, buffer{width, height}
{
}

Buffer<Color<double>> Mandelbrot::operator()(int iterations, double scale, double rotate,
                                             const Eigen::Vector2d &translate)
{
    Eigen::Vector2d resolution{width, height};
    auto radians{rotate * std::numbers::pi / 180.0};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Eigen::Vector2d coordinate{j, i};
            Eigen::Vector2d flippedNDC{(coordinate.array() / resolution.array() * 2.0) - 1.0};
            Eigen::Vector2d NDC{flippedNDC.x(), -flippedNDC.y()};

            NDC /= scale;
            auto SIN{std::sin(radians)};
            auto COS{std::cos(radians)};
            NDC = Eigen::Vector2d{NDC.x() * COS - NDC.y() * SIN, NDC.x() * SIN + NDC.y() * COS};
            NDC +=
                Eigen::Vector2d{translate.x() * COS - translate.y() * SIN, translate.x() * SIN + translate.y() * COS};

            Eigen::Vector2d z{0.0, 0.0};
            Eigen::Vector2d c{NDC};

            int k = 0;
            while (z.norm() <= 4.0 && k < iterations)
            {
                Eigen::Vector2d z2{z.x() * z.x() - z.y() * z.y(), 2.0 * z.x() * z.y()};
                z = z2 + c;
                k++;
            }

            auto ratio{std::sqrt(static_cast<double>(k) / static_cast<double>(iterations))};
            Color color{ratio, ratio, ratio, 1.0};
            buffer.write(color, j, i);
        }
    }
    return buffer.clone();
}