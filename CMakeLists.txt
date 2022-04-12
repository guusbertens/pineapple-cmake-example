cmake_minimum_required(VERSION 3.16)
project(Pineapple VERSION 0.1 LANGUAGES CXX)

add_executable(pineapple main.cpp Rng.cpp SimpleRng.cpp)
target_compile_features(pineapple PRIVATE cxx_std_17)

option(WITH_OPENSSL "Build with OpenSSL (enables MD5 RNG)" OFF)
if (WITH_OPENSSL)
	find_package(OpenSSL)
	target_link_libraries(pineapple PRIVATE OpenSSL::Crypto)
	target_sources(pineapple PRIVATE Md5Rng.cpp)
	target_compile_definitions(pineapple PRIVATE ENABLE_MD5RNG)
endif()

install(TARGETS pineapple)
