add_library(${PROJECT_NAME} STATIC
	src/ChessEngine.cpp
	src/EngineBoardState.cpp
	src/Evaluation.cpp
	src/BoardUpdating.cpp
	src/MoveComputing.cpp
	src/PerftEngine.cpp
	src/TranspositionTable.cpp
	src/Weights.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC incl)

target_link_libraries(${PROJECT_NAME} PUBLIC ChessCore)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY incl/ 
	TYPE INCLUDE 
)
