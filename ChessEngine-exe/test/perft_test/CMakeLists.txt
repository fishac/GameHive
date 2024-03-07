add_executable(PerftInitialPosition PerftInitialPosition.cpp)
add_executable(PerftPosition2 PerftPosition2.cpp)
add_executable(PerftPosition3 PerftPosition3.cpp)
add_executable(PerftPosition4 PerftPosition4.cpp)
add_executable(PerftPosition5 PerftPosition5.cpp)
add_executable(PerftPosition6 PerftPosition6.cpp)
add_executable(PerftPromotions PerftPromotions.cpp)

find_package(Catch2 3 REQUIRED)

target_link_libraries(PerftInitialPosition 
	PRIVATE ${PROJECT_NAME} ChessCore Catch2::Catch2WithMain
)
target_link_libraries(PerftPosition2 
	PRIVATE ${PROJECT_NAME} ChessCore Catch2::Catch2WithMain
)
target_link_libraries(PerftPosition3 
	PRIVATE ${PROJECT_NAME} ChessCore Catch2::Catch2WithMain
)
target_link_libraries(PerftPosition4 
	PRIVATE ${PROJECT_NAME} ChessCore Catch2::Catch2WithMain
)
target_link_libraries(PerftPosition5 
	PRIVATE ${PROJECT_NAME} ChessCore Catch2::Catch2WithMain
)
target_link_libraries(PerftPosition6 
	PRIVATE ${PROJECT_NAME} ChessCore Catch2::Catch2WithMain
)
target_link_libraries(PerftPromotions 
	PRIVATE ${PROJECT_NAME} ChessCore Catch2::Catch2WithMain
)

add_test(NAME PerftInitialPosition COMMAND PerftInitialPosition)
add_test(NAME PerftPosition2 COMMAND PerftPosition2)
add_test(NAME PerftPosition3 COMMAND PerftPosition3)
add_test(NAME PerftPosition4 COMMAND PerftPosition4)
add_test(NAME PerftPosition5 COMMAND PerftPosition5)
add_test(NAME PerftPosition6 COMMAND PerftPosition6)
add_test(NAME PerftPromotions COMMAND PerftPromotions)