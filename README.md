# GameHive

This repository contains a collection of games and engines to play against. 
This project is currently in progress and the only completed game and engine is Chess, though I intend to later add Hex Chess (see [this video](https://www.youtube.com/watch?v=bgR3yESAEVE) by CGPGrey), and other games that interest me.

The Chess Engine is currently available to play against on Lichess.org under the username [HoneybeeEngine](https://lichess.org/@/HoneybeeEngine). 
Currently it accepts challenges up to 20 minutes base time with 20 minutes increment.

The components of this project are:
* ChessCore: Rules defining Chess board state, moves, move generation, etc.
* ChessCore-exe: The tests and basic driver programs for running ChessCore.
* ChessEngine: The algorithms for finding the best move for a given board state.
* ChessEngine-exe: The tests and basic driver programs for running ChessEngine.
* ChessEngine-bindings: Code to generate bindings for ChessEngine in different languages.
* GameHive: A basic desktop GUI application written in C++ with Qt6 to play games against other players on the same machine or against the engines. This component is currently unstable when playing against an engine and will likely be replaced with a web application interface with JavaScript bindings to the Chess code.

### Performance stats

Depending on the starting position, ChessEngine and ChessCore can compute up to around 750,000 variations per second. 

### Tools

I use CMake, MinGW GCC, Qt6, Catch2, pybind11, Python 3, Notepad++, and a Bash terminal in this project.
