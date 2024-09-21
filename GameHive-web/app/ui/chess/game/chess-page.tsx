"use client";

import IMove, { NOMOVE } from "@/app/lib/move";
import EmptyChessBoard from "./empty-chess-board";
import ChessBoard from "@/app/ui/chess/game/chess-board";
import ChessSidebar from "@/app/ui/chess/game/chess-sidebar";
import initializeNewBoardState, { IBoardState } from "@/app/lib/board-state";
import { useState, useEffect, Dispatch, SetStateAction } from "react";
import { useSearchParams } from "next/navigation";
import { IChessEngine } from "@/app/lib/chess-engine";
import {
  CHESS_ENGINE_WORKER_MESSAGE_TYPES,
  IInitializeRequest,
  IProvideMoveRequest,
  ISuggestMoveRequest,
  IInitializeResponse,
  IProvideMoveResponse,
  ISuggestMoveResponse,
} from "@/app/lib/chess-engine-messages";
import { TGameResult, GameResult } from "@/app/lib/game-result";
import { TPiece } from "@/app/lib/piece";
import initializeNewChessUtils, { IChessUtils } from "@/app/lib/chess-utils";

interface IGameContext {
  ply: number;
  engineReady: boolean;
  waitingForEngine: boolean;
  player1Turn: boolean;
  player2Turn: boolean;
  result: TGameResult;
}

interface MoveRecord {
  move: IMove;
  movedPiece: TPiece;
  moveWasCapture: boolean;
}

export default function ChessPage() {
  const [boardState, setBoardState] = useState<IBoardState | null>(null);
  const [chessUtils, setChessUtils] = useState<IChessUtils | null>(null);
  const [chessEngineWorker, setChessEngineWorker] = useState<Worker | null>(
    null
  );
  const [gameContext, setGameContext] = useState<IGameContext>({
    ply: 0,
    engineReady: false,
    waitingForEngine: true,
    player1Turn: false,
    player2Turn: false,
    result: GameResult.UNDECIDED,
  });
  const [lastMove, setLastMove] = useState<IMove>(NOMOVE);
  const [moveHistory, setMoveHistory] = useState<IMove[]>([]);
  const searchParams = useSearchParams();
  const humanPlayerColor = searchParams.get("white") === "1";

  function handleChessEngineWorkerResponse(e: MessageEvent): void {
    const response = e.data;
    if (
      response.responseType === CHESS_ENGINE_WORKER_MESSAGE_TYPES.INITIALIZE
    ) {
      if (!humanPlayerColor) {
        chessEngineWorker?.postMessage({
          requestType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE,
          previousMove: NOMOVE,
        });
      }
      setGameContext((gc) => {
        return {
          ply: gc.ply,
          engineReady: true,
          waitingForEngine: false,
          player1Turn:
            true &&
            !boardState?.getCheckmateStatus() &&
            !boardState?.getStalemateStatus(),
          player2Turn: false,
          result: gc.result,
        };
      });
    } else if (
      response.responseType === CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE
    ) {
      if (boardState) {
        boardState.makeMove(response.move);
        setGameContext((gc) => {
          return {
            ply: gc.ply + 1,
            engineReady: gc.engineReady,
            waitingForEngine: false,
            player1Turn: !gc.player1Turn,
            player2Turn: !gc.player2Turn,
            result: gc.result,
          };
        });
        setMoveHistory((hist) => {
          hist.push(response.move);
          return hist;
        });
      }
    }
  }

  function handlePlayerMove(move: IMove) {
    if (
      boardState &&
      chessEngineWorker &&
      gameContext.engineReady &&
      !gameContext.waitingForEngine
    ) {
      chessEngineWorker.postMessage({
        requestType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE,
        previousMove: move,
      });
      boardState.makeMove(move);
      setGameContext((gc) => {
        return {
          ply: gameContext.ply + 1,
          engineReady: gameContext.engineReady,
          waitingForEngine: true,
          player1Turn: !gc.player1Turn,
          player2Turn: !gc.player2Turn,
          result: gc.result,
        };
      });
      setMoveHistory((hist) => {
        hist.push(move);
        return hist;
      });
    }
  }

  function handleTimeout(player1: boolean) {
    setGameContext((gc) => {
      return {
        ply: gc.ply,
        engineReady: gc.engineReady,
        waitingForEngine: false,
        player1Turn: false,
        player2Turn: false,
        result: player1 ? GameResult.BLACK_WIN : GameResult.WHITE_WIN,
      };
    });
  }

  useEffect(() => {
    initializeNewBoardState().then((bs) => {
      setBoardState(bs);
    });
    return () => {};
  }, []);

  useEffect(() => {
    const cew = new Worker(
      new URL("@/app/lib/chess-engine-worker.ts", import.meta.url)
    );
    cew.postMessage({
      requestType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.INITIALIZE,
    });
    setChessEngineWorker(cew);
    return () => {};
  }, []);

  useEffect(() => {
    initializeNewChessUtils().then((cu) => {
      setChessUtils(cu);
    });
    return () => {};
  }, []);

  useEffect(() => {
    if (chessEngineWorker) {
      chessEngineWorker.onmessage = (e: MessageEvent) =>
        handleChessEngineWorkerResponse(e);
    }
  }, [chessEngineWorker, gameContext, boardState]);

  return (
    <div className="flex flex-row justify-center mt-8">
      <div className="w-72" />
      {boardState && gameContext.engineReady ? (
        <ChessBoard
          boardState={boardState}
          humanPlayerColor={humanPlayerColor}
          lastMove={
            moveHistory.length > 0
              ? moveHistory[moveHistory.length - 1]
              : NOMOVE
          }
          onMove={(move: IMove) => handlePlayerMove(move)}
        />
      ) : (
        <EmptyChessBoard />
      )}
      <ChessSidebar
        moveHistory={moveHistory}
        player1Turn={
          !!boardState && gameContext.engineReady && gameContext.player1Turn
        }
        player2Turn={
          !!boardState && gameContext.engineReady && gameContext.player2Turn
        }
        timersActive={gameContext.result === GameResult.UNDECIDED}
        chessUtils={chessUtils}
        onTimeout={handleTimeout}
      />
    </div>
  );
}
