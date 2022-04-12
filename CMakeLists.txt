cmake_minimum_required(VERSION 3.16)
project(Pineapple VERSION 0.1 LANGUAGES CXX)

add_subdirectory(librng)

add_executable(pineapple main.cpp)
target_compile_features(pineapple PRIVATE cxx_std_17)
target_link_libraries(pineapple PRIVATE rng)
install(TARGETS pineapple)
