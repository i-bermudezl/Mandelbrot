add_library(utility INTERFACE "Buffer.hpp" "Color.hpp")

target_include_directories(utility INTERFACE .)

target_compile_features(utility INTERFACE cxx_std_20)