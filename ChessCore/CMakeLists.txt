add_library(ChessCore STATIC
	src/BoardState.cpp 
	src/BoardStateRecord.cpp 
	src/DataManagement.cpp
	src/FEN.cpp 
	src/Move.cpp
	src/MoveGeneration.cpp 
	src/MoveMaking.cpp 
	src/MoveSeeking.cpp
	src/MoveValidation.cpp
	src/Piece.cpp 
	src/Stalemate.cpp
	src/Square.cpp
	src/Vector.cpp
)

target_include_directories(ChessCore PUBLIC incl)

install(TARGETS ChessCore
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY incl/ 
	TYPE INCLUDE 
)
