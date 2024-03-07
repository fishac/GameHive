add_executable(ZobristKeyGenerationDriver ZobristKeyGenerationDriver.cpp)
add_executable(ZobristDebugger ZobristDebugger.cpp)

target_link_libraries(ZobristDebugger 
	PRIVATE ${PROJECT_NAME} 
)