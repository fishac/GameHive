#from ChessEnginePython import ChessEngine
import os
# In Python 3.8+, you need so specify where python can find dependency DLLs before loading
# a custom dll-dependent module (i.e. one made from C++ using pybind11)
# Python 3.8+ does not support just using the system PATH for DLL sources.
# This needs to be changed to point to the local installation of DLL files,
# otherwise you will get:
# ImportError: DLL load failed while importing ChessEnginePython: The specified module could not be found.
os.add_dll_directory("C:/mingw64/bin")
import ChessEnginePython

def test_main():
	eng = ChessEnginePython.ChessEngine()
	eng.set_fen("8/5K2/1p1k2P1/p7/P3p3/1P3q2/5P2/8 w - - 1 54")
	assert eng.get_fen() == "8/5K2/1p1k2P1/p7/P3p3/1P3q2/5P2/8 w - - 1 54"
	print(eng.get_fen())

if __name__=="__main__":
	test_main()
