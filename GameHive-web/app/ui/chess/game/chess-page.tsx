"use client";

import EmptyChessBoard from "./empty-chess-board";
import ChessBoard from "@/app/ui/chess/game/chess-board";
import Timer from "@/app/ui/timer";
import initializeNewBoardState, { IBoardState } from "@/app/lib/board-state";
import { useState, useEffect } from "react";
import initializeNewChessEngine, { IChessEngine } from "@/app/lib/chess-engine";

interface IChessEngineJS {
  ChessEngine: any;
  BoardState: any;
}

export default function ChessPage() {
  const [boardState, setBoardState] = useState<IBoardState | null>(null);
  const [chessEngine, setChessEngine] = useState<IChessEngine | null>(null);
  useEffect(() => {
    initializeNewBoardState().then((bs) => {
      setBoardState(bs);
    });
    return () => {};
  }, []);
  useEffect(() => {
    initializeNewChessEngine().then((ce) => {
      setChessEngine(ce);
    });
    return () => {};
  }, []);

  return (
    <div className="flex flex-row justify-center mt-8">
      {boardState ? (
        <ChessBoard boardState={boardState} />
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
