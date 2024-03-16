add_executable(EvaluationTest EvaluationTest.cpp)

find_package(Catch2 3 REQUIRED)
target_link_libraries(EvaluationTest ChessCore ChessEngine Catch2::Catch2WithMain)

add_test(NAME EvaluationTest COMMAND EvaluationTest)