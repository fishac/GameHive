cmake_minimum_required(VERSION 3.17)

project(ChessEngineJS VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/lib/ChessCore)
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/lib/ChessEngine)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)

add_executable(ChessEngineJS src/ChessEngineJS.cpp)

target_link_libraries(ChessEngineJS PUBLIC ChessEngine ChessCore)

if(BUILD_FOR_WEB) 
	target_link_options(ChessEngineJS 
		PUBLIC "--bind" 
		PUBLIC "-sMODULARIZE=1"
		PUBLIC "-sALLOW_MEMORY_GROWTH=1"
		PUBLIC "-sASSERTIONS=1"
		PUBLIC "-sSINGLE_FILE=1"
		PUBLIC "-sENVIRONMENT='web'"
		PUBLIC "-sEXPORT_NAME=ChessEngineJS"
	)
else()
	target_link_options(ChessEngineJS 
		PUBLIC "--bind" 
		PUBLIC "-sMODULARIZE=1"
		PUBLIC "-sALLOW_MEMORY_GROWTH=1"
		PUBLIC "-sEXPORT_NAME=ChessEngineJS"
	)
endif()


install(TARGETS ChessEngineJS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
