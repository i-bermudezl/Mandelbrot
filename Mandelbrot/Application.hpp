#pragma once

#include <string>

#include "Presenter.hpp"

class Application
{
  public:
    Application(int width, int height, std::string title);

    void run();

  private:
    Presenter p;
};