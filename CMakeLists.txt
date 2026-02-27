cmake_minimum_required(VERSION 3.16)
project(SFML3Starter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(timber src/timber.cpp)

target_link_libraries(timber PRIVATE SFML::Graphics SFML::Window SFML::System)

# copy resource folders (graphics, fonts, sounds) into the build directory
# so the executable can load them from the working directory during runtime
foreach(resource IN ITEMS graphics fonts sounds)
    if(EXISTS "${CMAKE_SOURCE_DIR}/${resource}")
        file(COPY "${CMAKE_SOURCE_DIR}/${resource}"
             DESTINATION "${CMAKE_BINARY_DIR}")
    endif()
endforeach()