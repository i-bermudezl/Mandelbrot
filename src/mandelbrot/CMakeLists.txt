find_package(Eigen3 CONFIG REQUIRED)

add_library(mandelbrot INTERFACE "Mandelbrot.hpp")

target_include_directories(utility INTERFACE .)

target_link_libraries(mandelbrot INTERFACE Eigen3::Eigen)
target_link_libraries(mandelbrot INTERFACE utility)

target_compile_features(utility INTERFACE cxx_std_20)