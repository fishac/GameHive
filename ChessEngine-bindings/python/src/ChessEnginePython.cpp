#include "ChessCore.h"
#include "ChessEngine.h"

#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;

PYBIND11_MODULE(ChessEnginePython, m) {
	py::class_<ExtendedMove>(m, "EngineMove")
		.def(py::init<>())
		.def_readwrite("from_sq", &ExtendedMove::from)
		.def_readwrite("to_sq", &ExtendedMove::to)
		.def_readwrite("promotion_piece", &ExtendedMove::promotionPiece);
	py::class_<ChessEngine>(m,"ChessEngine")
		.def(py::init<>())
		.def("suggest_move", &ChessEngine::suggestMove)
		.def("provide_move", &ChessEngine::provideMove)
		.def("set_fen", &ChessEngine::setFEN)
		.def("get_fen", &ChessEngine::getFEN)
		.def("get_move_search_depth", &ChessEngine::getMoveSearchDepth)
		.def("get_move_search_time", &ChessEngine::getMoveSearchTime)
		.def("get_move_search_time_limit", &ChessEngine::getMoveSearchTimeLimit)
		.def("search_was_hard_time_cutoff", &ChessEngine::searchWasHardTimeCutoff)
		.def("get_num_scanned_nodes", &ChessEngine::getNumScannedNodes);
	m.def("get_square_index", py::overload_cast<const Square_t&>(&(ChessCore::Square::getIndex)));
	m.def("get_move_string", py::overload_cast<ExtendedMove&>(&(ChessCore::MoveUtils::getString)));

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}