add_executable (Mandelbrot "main.cpp""Buffer.hpp" "Color.hpp")

find_package(SDL2 CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)

target_link_libraries(Mandelbrot
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

target_link_libraries(Mandelbrot PRIVATE Eigen3::Eigen)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Mandelbrot PROPERTY CXX_STANDARD 20)
endif()
