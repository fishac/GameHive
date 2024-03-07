add_executable(EngineDepthDriver EngineDepthDriver.cpp)
add_executable(EngineTimeDriver EngineTimeDriver.cpp)
add_executable(PerftCustomDriver PerftCustomDriver.cpp)
add_executable(WeightOptimizationDriver WeightOptimizationDriver.cpp 
	src/WeightEvaluationEngine.cpp
)

target_include_directories(WeightOptimizationDriver PUBLIC incl)

target_link_libraries(EngineDepthDriver 
	PRIVATE ${PROJECT_NAME} ChessCore
)
target_link_libraries(EngineTimeDriver 
	PRIVATE ${PROJECT_NAME} ChessCore
)
target_link_libraries(PerftCustomDriver 
	PRIVATE ${PROJECT_NAME} ChessCore
)
target_link_libraries(WeightOptimizationDriver 
	PRIVATE ${PROJECT_NAME} ChessCore
)
