add_executable(BoardStateFunctionalTest BoardStateFunctionalTest.cpp)

find_package(Catch2 3 REQUIRED)

target_link_libraries(BoardStateFunctionalTest PRIVATE ${PROJECT_NAME} Catch2::Catch2WithMain)

add_test(NAME BoardStateFunctionalTest COMMAND BoardStateFunctionalTest)