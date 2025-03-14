cmake_minimum_required(VERSION 3.10)
project(AuthenticationSystem)

set(CMAKE_CXX_STANDARD 17)

# Add your source files
add_executable(AuthSystem projetC++.cpp)

# Link OpenSSL for SHA-256 hashing
find_package(OpenSSL REQUIRED)
target_link_libraries(AuthSystem OpenSSL::Crypto)
