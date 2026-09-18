cmake_minimum_required(VERSION 3.25) # Minimum CMake version required

project(NetShield LANGUAGES CXX) # Define the project and use C++

set(CMAKE_CXX_STANDARD 20) # Use C++20

set(CMAKE_CXX_STANDARD_REQUIRED ON) # Require C++20

set(CMAKE_CXX_EXTENSIONS OFF) # Disable compiler-specific C++ extensions

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Generate compile_commands.json

file(GLOB_RECURSE NETSHIELD_SOURCES
    CONFIGURE_DEPENDS
    apps/vpn-client/src/*.cpp
) # Automatically find all .cpp files

add_executable(netshield
    ${NETSHIELD_SOURCES}
) # Build the executable from all discovered .cpp files

target_include_directories(netshield
    PRIVATE
        include
) # Add header search directory

target_compile_options(netshield
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
) # Enable compiler warnings

enable_testing() # Enable CMake testing