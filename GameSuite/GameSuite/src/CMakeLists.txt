qt_add_executable(GameSuite
	${CMAKE_SOURCE_DIR}/resources.qrc
    GameSuiteWindow.cpp
	CommonWidgets/ClockWidget.cpp
	Pages/ChooseGamePage.cpp
	Pages/ChessSetupPage.cpp
	Pages/ChessGamePage.cpp
	Dialogs/AboutDialog.cpp
	Dialogs/ChessStyleDialog.cpp
	Chess/ChessBoardWidget.cpp
	Chess/ChessEngineManager.cpp
	Chess/ChessSquareWidget.cpp
	Chess/ChessPromotionSelectionWidget.cpp
	Chess/ChessPromotionSelectionSquareWidget.cpp
    main.cpp
)

target_include_directories(GameSuite PRIVATE CommonWidgets)
target_include_directories(GameSuite PRIVATE Pages)
target_include_directories(GameSuite PRIVATE Dialogs)
target_include_directories(GameSuite PRIVATE Chess)

target_link_libraries(GameSuite PRIVATE Qt6::Widgets PRIVATE ChessCore PRIVATE ChessEngine)

set_target_properties(GameSuite PROPERTIES
    WIN32_EXECUTABLE ON
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)