cmake_minimum_required(VERSION 3.20)
project(nscpp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

add_library(${PROJECT_NAME}
        src/Foundation/Object.cpp
        src/Foundation/Autoreleasepool.cpp
        src/Foundation/Foundation.cpp
        src/Foundation/String.cpp
)

target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<INSTALL_INTERFACE:>/include
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>/include
)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        "-framework Foundation"
        "-lobjc"
)

add_subdirectory(examples)