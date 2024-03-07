from ChessEnginePython import ChessEngine

def test_main():
	eng = ChessEngine()
	eng.set_fen("8/5K2/1p1k2P1/p7/P3p3/1P3q2/5P2/8 w - - 1 54")
	assert eng.get_fen() == "8/5K2/1p1k2P1/p7/P3p3/1P3q2/5P2/8 w - - 1 54"

if __name__=="__main__":
	test_main()