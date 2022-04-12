cmake_minimum_required(VERSION 3.16)
project(Pineapple VERSION 0.1 LANGUAGES CXX)

find_package(OpenSSL)

add_executable(pineapple main.cpp Rng.cpp SimpleRng.cpp Md5Rng.cpp)
target_compile_features(pineapple PRIVATE cxx_std_17)
target_link_libraries(pineapple PRIVATE OpenSSL::Crypto)

install(TARGETS pineapple)
