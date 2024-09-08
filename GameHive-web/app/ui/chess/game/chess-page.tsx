'use client'

import ChessBoard from '@/app/ui/chess/game/chess-board';
import Timer from '@/app/ui/timer';
import initializeNewBoardState, {IBoardState} from '@/app/lib/board-state';
import { useState, useEffect } from 'react';

interface IChessEngineJS {
  ChessEngine: any;
  BoardState: any;
};

export default function ChessPage() {
  const [boardState, setBoardState] = useState<IBoardState | null>(null);
  useEffect(() => {
    initializeNewBoardState().then(bs => {
      setBoardState(bs);
    });
    return () => {};
  }, []);

  return (
    <div className="flex flex-row justify-center mt-8">
      {boardState && <ChessBoard boardState={boardState}/>}
      <div className="flex flex-col justify-between w-72 bg-blue-500">
        <Timer />
        <Timer />
      </div>
    </div>
  )
}