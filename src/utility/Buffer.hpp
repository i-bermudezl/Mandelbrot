#pragma once

#include <memory>

template <typename T> class Buffer
{
  public:
    Buffer(const int width, const int height);

    int getWidth() const;
    int getHeight() const;

    T read(const int x, const int y) const;
    void write(T value, const int x, const int y);

    Buffer<T> clone() const;

  private:
    const int width;
    const int height;
    std::unique_ptr<T[]> buffer;
};

template <typename T>
Buffer<T>::Buffer(const int width, const int height) : width{width}, height{height}, buffer{new T[width * height]}
{
}

template <typename T> int Buffer<T>::getWidth() const
{
    return width;
}

template <typename T> int Buffer<T>::getHeight() const
{
    return height;
}

template <typename T> T Buffer<T>::read(const int x, const int y) const
{
    return buffer[x + width * y];
}

template <typename T> void Buffer<T>::write(T value, const int x, const int y)
{
    buffer[x + width * y] = value;
}

template <typename T> Buffer<T> Buffer<T>::clone() const
{
    Buffer tmp{width, height};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            auto value{read(j, i)};
            tmp.write(value, j, i);
        }
    }
    return tmp;
}
