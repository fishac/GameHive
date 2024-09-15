"use client";

import IMove from "@/app/lib/move";
import EmptyChessBoard from "./empty-chess-board";
import ChessBoard from "@/app/ui/chess/game/chess-board";
import Timer from "@/app/ui/timer";
import initializeNewBoardState, { IBoardState } from "@/app/lib/board-state";
import { useState, useEffect, Dispatch, SetStateAction } from "react";
import { useSearchParams } from 'next/navigation'
import { IChessEngine } from "@/app/lib/chess-engine";
import { 
  CHESS_ENGINE_WORKER_MESSAGE_TYPES, 
  IInitializeRequest,
  IProvideMoveRequest,
  ISuggestMoveRequest,
  IInitializeResponse,
  IProvideMoveResponse,
  ISuggestMoveResponse
} from "@/app/lib/chess-engine-messages";
import { FaSliders } from "react-icons/fa6";

interface IGameContext {
  ply: number,
  engineReady: boolean,
  waitingForEngine: boolean
};

function handlePlayerMove(move: IMove, chessEngineWorker: Worker | null, boardState: IBoardState, gameContext: IGameContext, setGameContext: Dispatch<SetStateAction<IGameContext>>) {
  console.log("handlePlayerMove");
  if (boardState && chessEngineWorker && gameContext.engineReady && !gameContext.waitingForEngine) {
    chessEngineWorker.postMessage({
      requestType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE,
      previousMove: move
    })
    boardState.makeMove(move);
    setGameContext({
      ply: gameContext.ply+1,
      engineReady: gameContext.engineReady,
      waitingForEngine: true
    });
  }
}

function handleChessEngineWorkerResponse(
  e: MessageEvent, 
  humanPlayerColor: boolean,
  chessEngineWorker: Worker,
  boardState: IBoardState | null,
  gameContext: IGameContext,
  setGameContext: Dispatch<SetStateAction<IGameContext>>
): void {
  const response = e.data;
  console.log("response data: " + JSON.stringify(response));
  if (response.responseType === CHESS_ENGINE_WORKER_MESSAGE_TYPES.INITIALIZE) {
    if (!humanPlayerColor) {
      chessEngineWorker.postMessage({ 
        requestType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE,
        previousMove: {
          from: -1,
          to: -1,
          promotionPiece: 0
        }
      });
    } 
    setGameContext({
      ply: gameContext.ply,
      engineReady: true,
      waitingForEngine: false
    });
  } else if (response.responseType === CHESS_ENGINE_WORKER_MESSAGE_TYPES.PROVIDE_MOVE) {
    console.log("received provide move response");
  } else if (response.responseType === CHESS_ENGINE_WORKER_MESSAGE_TYPES.SUGGEST_MOVE) {
    console.log("received suggest move response: " + JSON.stringify(response));
    if (boardState) {
      boardState.makeMove(response.move);
      setGameContext({
        ply: gameContext.ply+1,
        engineReady: gameContext.engineReady,
        waitingForEngine: gameContext.waitingForEngine
      });
    }
  } else if (response.responseType === CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE) {
    console.log("received engine move response: " + JSON.stringify(response));
    if (boardState) {
      console.log("making move in game state");
      boardState.makeMove(response.move);
      console.log("setting game context");
      setGameContext({
        ply: gameContext.ply+1,
        engineReady: gameContext.engineReady,
        waitingForEngine: false
      });
    }
  }
}

export default function ChessPage() {
  const [boardState, setBoardState] = useState<IBoardState | null>(null);
  const [chessEngineWorker, setChessEngineWorker] = useState<Worker | null>(null);
  const [gameContext, setGameContext] = useState<IGameContext>({ply: 0, engineReady: false, waitingForEngine: true});
  const searchParams = useSearchParams();
  const humanPlayerColor = searchParams.get('white') === '1';

  useEffect(() => {
    initializeNewBoardState().then((bs) => {
      setBoardState(bs);
    });
    return () => {};
  }, []);
  useEffect(() => {
    const cew = new Worker(new URL("@/app/lib/chess-engine-worker.ts",import.meta.url));
    cew.postMessage({ requestType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.INITIALIZE });
    setChessEngineWorker(cew);
    return () => {};
  }, []);
  useEffect(() => {
    if (chessEngineWorker) {
      chessEngineWorker.onmessage = (e: MessageEvent) => handleChessEngineWorkerResponse(
        e, 
        humanPlayerColor,
        chessEngineWorker,
        boardState,
        gameContext,
        setGameContext
      );
    }
  }, [chessEngineWorker,gameContext,boardState]);

  return (
    <div className="flex flex-row justify-center mt-8">
      {(boardState && gameContext.engineReady) ? (
        <ChessBoard 
          boardState={boardState} 
          humanPlayerColor={humanPlayerColor}
          onMove={(move: IMove) => handlePlayerMove(move, chessEngineWorker, boardState, gameContext, setGameContext)}
        />
      ) : (
        <EmptyChessBoard />
      )}
      <div className="flex flex-col justify-between w-72 bg-blue-500">
        <Timer />
        <Timer />
      </div>
    </div>
  );
}
