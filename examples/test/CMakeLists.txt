add_executable(test_mandelbrot "test.cpp")
target_link_libraries(test_mandelbrot PRIVATE mandelbrot)

target_compile_features(test_mandelbrot PRIVATE cxx_std_20)