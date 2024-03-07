#include "ChessCore.h"
#include "WeightEvaluationEngine.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "math.h"

#define FENDATA "../data/fen_evaluations_3ba201f7.csv"

int main(int argc, char *argv[]) {
	if (argc != 4) {
		//std::cout << "Usage: WeightOptimizationDriver baseWeights earlygameWeights endgameWeights" << std::endl;
		//std::cout << "Separate parameters by commas (,) and rows by semicolons (;)." << std::endl;
		//std::cout << "baseWeights (7 parameters), earlygameWeights (64 parameters, 7 rows), endgameWeights (64 parameters, 7 rows)" << std::endl;
		return 1;
	}
	//std::cout << "Current directory: " << std::filesystem::current_path() << std::endl;
	//std::cout << "Input: " << std::endl;
	//std::cout << "Program name: " << argv[0] << std::endl;
	//std::cout << "Base Weights: " << argv[1] << std::endl;
	//std::cout << "Earlygame Weights: " << argv[2] << std::endl;
	//std::cout << "Endgame Weights: " << argv[3] << std::endl;
	
	std::array<int,7> baseWeights;
	std::array<std::array<int,64>,7> earlygameWeights;
	std::array<std::array<int,64>,7> endgameWeights;
	std::string arg;
	std::string param;
	std::string pieceWeights;
	
	//std::cout << "Getting base weights" << std::endl;
	// https://stackoverflow.com/questions/34218040/how-to-read-a-csv-file-data-into-an-array
	arg = argv[1];
	std::stringstream baseWeightsStream(arg);
	int bwidx = 0;
    while(std::getline(baseWeightsStream,param,',')) {
		baseWeights[bwidx] = stoi(param);
		bwidx++;
	}
	//std::cout << "Done getting base weights" << std::endl;
	
	//std::cout << "Getting earlygame weights" << std::endl;
	arg = argv[2];
	std::stringstream earlygameStream(arg);
	int earlygamePieceIdx = 0;
	int earlygameParamIdx = 0;
    while(std::getline(earlygameStream,pieceWeights,':')) {
		std::stringstream pieceStream(pieceWeights);
		earlygameParamIdx = 0;
		while(std::getline(pieceStream,param,',')) {
			earlygameWeights[earlygamePieceIdx][earlygameParamIdx] = stoi(param);
			earlygameParamIdx++;
		}
		earlygamePieceIdx++;
	}
	//std::cout << "Done getting earlygame weights" << std::endl;
	
	//std::cout << "Getting endgame weights" << std::endl;
	arg = argv[3];
	std::stringstream endgameStream(arg);
	int endgamePieceIdx = 0;
	int endgameParamIdx = 0;
    while(std::getline(endgameStream,pieceWeights,':')) {
		////std::cout << "Endgame pieceWeights: " << pieceWeights << std::endl;
		std::stringstream pieceStream(pieceWeights);
		endgameParamIdx = 0;
		while(std::getline(pieceStream,param,',')) {
			////std::cout << "param: " << param << std::endl;
			endgameWeights[endgamePieceIdx][endgameParamIdx] = stoi(param);
			endgameParamIdx++;
		}
		endgamePieceIdx++;
	}
	//std::cout << "Done getting endgame weights" << std::endl;
	
	//std::cout << "Setting weights" << std::endl;
	WeightEvaluationEngine eng;
	eng.setBaseWeights(baseWeights);
	eng.setEarlygameWeights(earlygameWeights);
	eng.setEndgameWeights(endgameWeights);
	//std::cout << "Done setting weights" << std::endl;
	
	//std::cout << "Evaluating" << std::endl;
	//std::cout << "Opening evaluations file: " << std::string(std::filesystem::current_path()) + "/" + FENDATA << std::endl;
	std::ifstream fenEvaluationsFile(std::filesystem::current_path().generic_string() + "/" + FENDATA);
	//std::cout << "Done opening evaluations file" << std::endl;
	std::string fenEvalEntry;
	std::string fenString;
	std::string evaluationString;
	int stockfishEval;
	int currentEval;
	long long int score = 0;
	//std::cout << "Looping through evaluations" << std::endl;
	while (std::getline(fenEvaluationsFile,fenEvalEntry)) {
		//std::cout << "Reading line" << std::endl;
		std::stringstream fenEvalRowStream(fenEvalEntry);
		std::getline(fenEvalRowStream,fenString,',');
		std::getline(fenEvalRowStream,evaluationString,',');
		//std::cout << "FEN: " << fenString << std::endl;
		//std::cout << "Stockfish eval: " << evaluationString << std::endl;
		//std::cout << "Done reading line" << std::endl;
		stockfishEval = (int) round(stod(evaluationString)*100);
		
		eng.setFEN(fenString);
		currentEval = eng.evaluatePosition();
		
		//std::cout << "Stockfish eval (int): " << stockfishEval << ", currentEval: " << currentEval << std::endl;
		
		score += (stockfishEval-currentEval)*(stockfishEval-currentEval);
	}
	//std::cout << "Done looping through evaluations" << std::endl;
	
	fenEvaluationsFile.close();
	
	//std::cout << "Done evaluating" << std::endl;
	
	printf("%.2f\n",sqrt(score));
}