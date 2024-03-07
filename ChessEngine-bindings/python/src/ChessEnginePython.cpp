#include "ChessCore.h"
#include "ChessEngine.h"

#include <pybind11/pybind11.h>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


namespace py = pybind11;

PYBIND11_MODULE(ChessEnginePython, m) {
	py::class_<ChessEngine>(m,"ChessEngine")
		.def(py::init<>())
		.def("suggest_move", &ChessEngine::suggestMove)
		.def("provide_move", &ChessEngine::provideMove)
		.def("set_fen", &ChessEngine::setFEN)
		.def("get_fen", &ChessEngine::getFEN);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}