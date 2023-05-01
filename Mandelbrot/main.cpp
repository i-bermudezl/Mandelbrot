#include <iostream>

#include "Application.hpp"

int main(int argc, char **argv)
{
    Application app{640, 360, "Mandelbrot"};

    try
    {
        app.run();
    }
    catch (std::exception e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}