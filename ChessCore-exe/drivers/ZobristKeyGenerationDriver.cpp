#include <iostream>
#include <random>

static std::random_device rd;
static std::mt19937_64 e2(rd());
static std::uniform_int_distribution<uint64_t> dist;

void printPieceKeys(std::string color, std::string piece) {
	std::cout << color << " " << piece << " Zobrist Keys" << std::endl;
	for (int i=0; i<8; i++) {
		std::cout << std::hex 
			<< "0x" << dist(e2) << ", " << "0x" << dist(e2) << ", " 
			<< "0x" << dist(e2) << ", " << "0x" << dist(e2) << ", " 
			<< "0x" << dist(e2) << ", " << "0x" << dist(e2) << ", " 
			<< "0x" << dist(e2) << ", " << "0x" << dist(e2) << ", " << std::endl;
	}
	std::cout << std::endl;
}

int main() {
	printPieceKeys("White", "Pawn");
	printPieceKeys("White", "Knight");
	printPieceKeys("White", "Bishop");
	printPieceKeys("White", "Rook");
	printPieceKeys("White", "Queen");
	printPieceKeys("White", "King");
	printPieceKeys("Black", "Pawn");
	printPieceKeys("Black", "Knight");
	printPieceKeys("Black", "Bishop");
	printPieceKeys("Black", "Rook");
	printPieceKeys("Black", "Queen");
	printPieceKeys("Black", "King");
	
	std::cout << "K Side Castle Hashes" << std::endl;
	std::cout << std::hex << "0x" << dist(e2) << ", " << "0x" << dist(e2) << std::endl;
	std::cout << std::endl;
	
	std::cout << "Q Side Castle Hashes" << std::endl;
	std::cout << std::hex << "0x" << dist(e2) << ", " << "0x" << dist(e2) << std::endl;
	std::cout << std::endl;
	
	std::cout << "En Passant File Hashes" << std::endl;
	std::cout << std::hex 
		<< "0x" << dist(e2) << ", " << "0x" << dist(e2) << ", " 
		<< "0x" << dist(e2) << ", " << "0x" << dist(e2) << ", " 
		<< "0x" << dist(e2) << ", " << "0x" << dist(e2) << ", " 
		<< "0x" << dist(e2) << ", " << "0x" << dist(e2) << ", " << std::endl;
	std::cout << std::endl;
	
	std::cout << "Black Turn Hash" << std::endl;
	std::cout << std::hex << "0x" << dist(e2) << std::endl;
	std::cout << std::endl;
}
