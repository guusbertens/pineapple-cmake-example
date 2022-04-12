add_library(rng SHARED Rng.cpp SimpleRng.cpp)
target_compile_features(rng PRIVATE cxx_std_17)

option(WITH_OPENSSL "Build with OpenSSL (enables MD5 RNG)" OFF)
if (WITH_OPENSSL)
	find_package(OpenSSL)
	target_link_libraries(rng PRIVATE OpenSSL::Crypto)
	target_sources(rng PRIVATE Md5Rng.cpp)
	target_compile_definitions(rng PRIVATE ENABLE_MD5RNG)
endif()

target_include_directories(rng INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set_property(TARGET rng APPEND PROPERTY PUBLIC_HEADER Rng.h)

install(TARGETS rng)
