find_package(imgui CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)

add_library(presentation "Presenter.hpp" "Presenter.cpp")

target_include_directories(presentation PUBLIC .)

target_compile_features(presentation PRIVATE cxx_std_20)

target_link_libraries(presentation PRIVATE utility)


target_link_libraries(presentation PUBLIC imgui::imgui)

target_link_libraries(presentation
         PUBLIC
         $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
         $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)