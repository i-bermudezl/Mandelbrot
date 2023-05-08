add_executable(sandbox "Application.cpp" "Application.hpp" "sandbox.cpp")
target_link_libraries(sandbox PRIVATE mandelbrot)
target_link_libraries(sandbox PRIVATE utility)
target_link_libraries(sandbox PRIVATE presentation)

target_compile_features(sandbox PRIVATE cxx_std_20)