cmake_minimum_required(VERSION 3.17)

project(ChessEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ChessCore ${CMAKE_CURRENT_BINARY_DIR}/ChessCore)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../ChessEngine ${CMAKE_CURRENT_BINARY_DIR}/ChessEngine)
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

# -DBUILD_TESTS=true or -DBUILD_TESTS=1 or -DBUILD_TESTS=On
if(BUILD_TESTS)
	enable_testing()
	add_subdirectory(test)
endif()

# -DBUILD_DRIVERS=true or -DBUILD_DRIVERS=1 or -DBUILD_DRIVERS=On
if(BUILD_DRIVERS)
	add_subdirectory(drivers)
endif()

