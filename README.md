# GameHive

This repository contains a collection of games and engines to play against. 
This project is currently in progress and the only completed game and engine is Chess, though I intend to later add Hex Chess (see [this video](https://www.youtube.com/watch?v=bgR3yESAEVE) by CGPGrey), and other games that interest me.

The Chess Engine is deployed to a playable bot on on Lichess.org under the username [HoneybeeEngine](https://lichess.org/@/HoneybeeEngine). 
Currently it accepts challenges up to 20 minutes base time with 20 seconds increment.

The components of this project are:
* ChessCore: Rules defining Chess board state, moves, move generation, etc.
* ChessCore-exe: The tests and basic driver programs for running ChessCore.
* ChessEngine: The algorithms for finding the best move for a given board state.
* ChessEngine-exe: The tests and basic driver programs for running ChessEngine.
* ChessEngine-bindings: Code to generate bindings for ChessEngine in different languages.
* GameHive: A basic desktop GUI application written in C++ with Qt6 to play games against other players on the same machine or against the engines. This component is currently unstable when playing against an engine and will likely be replaced with a web application interface with JavaScript bindings to the Chess code.

### Performance Stats

Depending on the starting position, ChessEngine and ChessCore can compute up to around 750,000 variations per second. 

### Chess Engine Ideas

I incorporated many ideas in the Chess Engine's searching algorithms including negamax search, alpha-beta pruning, iterative deepening, quiescence search, static exchange evaluation, null move pruning, late move pruning, search extensions, move prioritization, and transposition tables.
I kept the evaluation function relatively simple, incorporating and considering piece weights, piece-square weight tables, piece mobility, king safety, isolated pawns, doubled pawns, passed pawns, early-endgame weight pairs, and king distance-to-edge.

### Tools

I use CMake, MinGW GCC, Qt6, Catch2, pybind11, Python 3, Notepad++, and a Bash terminal in this project.

### Why the name GameHive

I like the theme of bees, hives, and such to fit the goal of developing an engine for Hex Chess. 
Also my girlfriend's name is Melissa which comes from the word Honeybee.
