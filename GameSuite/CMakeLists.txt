cmake_minimum_required(VERSION 3.16)

project(GameSuite VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ChessCore ${CMAKE_CURRENT_BINARY_DIR}/ChessCore)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ChessEngine ${CMAKE_CURRENT_BINARY_DIR}/ChessEngine)
add_subdirectory(GameSuite)
