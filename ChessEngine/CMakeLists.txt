add_library(ChessEngine STATIC
	src/ChessEngine.cpp
	src/EngineBoardState.cpp
	src/Evaluation.cpp
	src/BoardUpdating.cpp
	src/MoveComputing.cpp
	src/PerftEngine.cpp
	src/TranspositionTable.cpp
	src/Weights.cpp
)

target_include_directories(ChessEngine PUBLIC incl)

target_link_libraries(ChessEngine PUBLIC ChessCore)

install(TARGETS ChessEngine
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY incl/ 
	TYPE INCLUDE 
)
