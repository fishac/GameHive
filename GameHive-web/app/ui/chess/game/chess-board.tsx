'use client'

import ChessSquare from '@/app/ui/chess/game/chess-square';
import {DndContext} from '@dnd-kit/core';
import {useState} from 'react';
import {snapCenterToCursor} from '@dnd-kit/modifiers';
import BoardState, { IBoardState } from '@/app/lib/board-state';
import {TSquare} from '@/app/lib/square';

const ranks = [0,1,2,3,4,5,6,7];
const files = [0,1,2,3,4,5,6,7];

function handleDragStart(e: any, boardState: IBoardState, setDraggingFromSquare: any) {
  setDraggingFromSquare(e.active.id);
}

function handleDragEnd(e: any, boardState: IBoardState, setDraggingFromSquare: any) {
  setDraggingFromSquare(-1);
  if (e.over) {
    boardState.makeMove({from: e.active.id, to: e.over.id, promotionPiece: 0});
  }
}

function getSquare({rank, file}: {rank: number, file: number}): TSquare {
  return rank*8+file as TSquare;
}

export default function ChessBoard({boardState}: {boardState: IBoardState}) {
  const [draggingFromSquare, setDraggingFromSquare] = useState(-1 as TSquare);
  const legalDroppingSquares = draggingFromSquare === -1 ? [] : boardState.getLegalMovesFromSquare(draggingFromSquare);
  return (
    <DndContext 
      onDragStart={(e) => handleDragStart(e,boardState,setDraggingFromSquare)}
      onDragEnd={(e) => handleDragEnd(e,boardState,setDraggingFromSquare)} 
      modifiers={[snapCenterToCursor]}
    >
    <div className="bg-red-500 w-[36%] aspect-square grid">
        {ranks.reverse().map(rank => (
          <div key={rank} className="col-span-1 row-span-8 flex flex-row">
            {files.map(file => {
              const sq: TSquare = getSquare({rank,file});
              return (
                  <ChessSquare key={`${getSquare({rank,file})}`}
                  square={sq}
                  rank={rank} 
                  file={file} 
                  piece={boardState.getPieceOnSquare(sq)} 
                  pieceColor={boardState.getColorOnSquare(sq)}
                  isLegalFromSquare={boardState.isLegalFromSquare(sq)}
                  isLegalToSquare={legalDroppingSquares.includes(sq)}
                  boardState={boardState}
                />
              );
            })}
          </div>
        ))}
    </div>
    </DndContext>
  );
}