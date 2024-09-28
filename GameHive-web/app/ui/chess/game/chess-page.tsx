"use client";

import IMove, { NOMOVE, IMoveRecord } from "@/app/lib/move";
import EmptyChessBoard from "./empty-chess-board";
import ChessBoard from "@/app/ui/chess/game/chess-board";
import ChessSidebar from "@/app/ui/chess/game/chess-sidebar";
import initializeNewBoardState, { IBoardState } from "@/app/lib/board-state";
import { useState, useEffect, Dispatch, SetStateAction } from "react";
import { useSearchParams } from "next/navigation";
import { IChessEngine } from "@/app/lib/chess-engine";
import {
  CHESS_ENGINE_WORKER_MESSAGE_TYPES,
  IEngineTurnRequest
} from "@/app/lib/chess-engine-messages";
import { TGameResult, GameResult } from "@/app/lib/game-result";
import { TPiece } from "@/app/lib/piece";
import initializeNewChessUtils, { IChessUtils } from "@/app/lib/chess-utils";
import { ITimeControl, getTimeControl } from "@/app/lib/time-control";

interface IGameContext {
  ply: number;
  engineReady: boolean;
  waitingForEngine: boolean;
  player1Turn: boolean;
  player2Turn: boolean;
  result: TGameResult;
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
  const [moveHistory, setMoveHistory] = useState<IMoveRecord[]>([]);
  const searchParams = useSearchParams();
  const humanPlayerColor = searchParams.get("white") === "1";
  const initialTimeSettings: ITimeControl = getTimeControl(Number.parseInt(searchParams.get("timeControl") || '-1'));
  const [whiteRemainingMillis, setWhiteRemainingMillis] = useState<number>(initialTimeSettings.baseMillis);
  const [blackRemainingMillis, setBlackRemainingMillis] = useState<number>(initialTimeSettings.baseMillis);

  function getGameResult() {
    if (boardState?.getCheckmateStatus() && boardState.getTurnColor()) {
      return GameResult.BLACK_WIN;
    } else if (boardState?.getCheckmateStatus() && !boardState?.getTurnColor()) {
      return GameResult.WHITE_WIN;
    } else if (boardState?.getStalemateStatus()) {
      return GameResult.DRAW;
    } else {
      return gameContext.result;
    }
  }

  function handleChessEngineWorkerResponse(e: MessageEvent): void {
    const response = e.data;
    if (
      response.responseType === CHESS_ENGINE_WORKER_MESSAGE_TYPES.INITIALIZE
    ) {
      if (!humanPlayerColor) {
        chessEngineWorker?.postMessage({
          requestType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE,
          previousMove: NOMOVE,
          remainingMillis: humanPlayerColor ? blackRemainingMillis : whiteRemainingMillis,
          incrementMillis: initialTimeSettings.incrementMillis
        });
      }
      setGameContext((gc: IGameContext) => {
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
      if (boardState && gameContext.result === GameResult.UNDECIDED) {
        setMoveHistory([...moveHistory,{
            move: response.move,
            movedPiece: boardState.getPieceOnSquare(response.move.from),
            moveIsCapture: boardState.moveIsCapture(response.move),
          }]);
        boardState.makeMove(response.move);
        setGameContext((gc: IGameContext) => {
          return {
            ply: gc.ply + 1,
            engineReady: gc.engineReady,
            waitingForEngine: false,
            player1Turn: !gc.player1Turn,
            player2Turn: !gc.player2Turn,
            result: getGameResult(),
          };
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
        remainingMillis: humanPlayerColor ? blackRemainingMillis : whiteRemainingMillis,
        incrementMillis: initialTimeSettings.incrementMillis
      } as IEngineTurnRequest);
      setMoveHistory([...moveHistory,{
        move: move,
        movedPiece: boardState.getPieceOnSquare(move.from),
        moveIsCapture: boardState.moveIsCapture(move)
      }]);
      boardState.makeMove(move);
      setGameContext((gc: IGameContext) => {
        return {
          ply: gameContext.ply + 1,
          engineReady: gameContext.engineReady,
          waitingForEngine: true,
          player1Turn: !gc.player1Turn,
          player2Turn: !gc.player2Turn,
          result: getGameResult(),
        };
      });
    }
  }

  function handleTimeout(player1: boolean) {
    setGameContext((gc: IGameContext) => {
      return {
        ply: gc.ply,
        engineReady: gc.engineReady,
        waitingForEngine: false,
        player1Turn: false,
        player2Turn: false,
        result: player1 ? (boardState?.blackHasSufficientCheckmatingMaterial() ? GameResult.BLACK_WIN : GameResult.DRAW) : (boardState?.whiteHasSufficientCheckmatingMaterial() ? GameResult.WHITE_WIN : GameResult.DRAW)
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
              ? moveHistory[moveHistory.length - 1].move
              : NOMOVE
          }
          onMove={(move: IMove) => handlePlayerMove(move)}
          gameOngoing={gameContext.result===GameResult.UNDECIDED}
        />
      ) : (
        <EmptyChessBoard />
      )}
      <ChessSidebar
        moveHistory={moveHistory}
        player1Turn={
          !!boardState && gameContext.engineReady && gameContext.player1Turn && gameContext.result === GameResult.UNDECIDED
        }
        player2Turn={
          !!boardState && gameContext.engineReady && gameContext.player2Turn && gameContext.result === GameResult.UNDECIDED
        }
        timersActive={gameContext.result === GameResult.UNDECIDED}
        result={gameContext.result}
        timeControl={initialTimeSettings}
        player1IsEngine={!humanPlayerColor}
        player2IsEngine={humanPlayerColor}
        chessUtils={chessUtils}
        player1RemainingMillis={whiteRemainingMillis}
        player2RemainingMillis={blackRemainingMillis}
        setPlayer1RemainingMillis={setWhiteRemainingMillis}
        setPlayer2RemainingMillis={setBlackRemainingMillis}
        onTimeout={handleTimeout}
      />
    </div>
  );
}
