"use client";

import ChessSquare from "@/app/ui/chess/game/chess-square";
import { DndContext, pointerWithin } from "@dnd-kit/core";
import { useState } from "react";
import { snapCenterToCursor } from "@dnd-kit/modifiers";
import BoardState, { IBoardState } from "@/app/lib/board-state";
import IMove from "@/app/lib/move";
import { TSquare, getSquare } from "@/app/lib/square";
import {
  isValidPromotionContext,
  IPromotionContext,
} from "@/app/lib/promotions";
import { TPiece } from "@/app/lib/piece";
import { IoSwapVerticalOutline } from "react-icons/io5";

const ranks = [0, 1, 2, 3, 4, 5, 6, 7];
const files = [0, 1, 2, 3, 4, 5, 6, 7];

export default function ChessBoard({
  boardState,
  humanPlayerColor,
  lastMove,
  gameOngoing,
  onMove,
}: {
  boardState: IBoardState;
  humanPlayerColor: boolean;
  lastMove: IMove;
  gameOngoing: boolean;
  onMove: (m: IMove) => void;
}) {
  const [draggingFromSquare, setDraggingFromSquare] = useState(-1 as TSquare);
  const [promotionContext, setPromotionContext] = useState({
    from: -1,
    to: -1,
  } as IPromotionContext);
  const legalDroppingSquares =
    draggingFromSquare === -1
      ? []
      : boardState.getLegalMovesFromSquare(draggingFromSquare);

  function handleDragStart(
    e: any
  ): void {
    setDraggingFromSquare(parseInt(e.active.id) as TSquare);
  }

  function handleDragEnd(
    e: any
  ): void {
    if (e.over) {
      const move: IMove = { from: (parseInt(e.active.id) as TSquare), to: (parseInt(e.over.id) as TSquare), promotionPiece: 0 };
      if (boardState.moveRequiresPromotion(move)) {
        setPromotionContext({ from: move.from, to: move.to });
        setDraggingFromSquare(-1);
      } else {
        onMove(move);
        setDraggingFromSquare(-1);
      }
    }
  }

  function handlePromotionSelection(
    promotionPiece: TPiece
  ): void {
    if (isValidPromotionContext(promotionContext, boardState)) {
      setPromotionContext({ from: -1, to: -1 });
      onMove({
        from: promotionContext.from,
        to: promotionContext.to,
        promotionPiece,
      });
    }
  }

  return (
    <DndContext
      onDragStart={handleDragStart}
      onDragEnd={handleDragEnd}
      modifiers={[snapCenterToCursor]}
      collisionDetection={pointerWithin}
    >
      <div className="bg-red-500 w-[36%] aspect-square grid">
        {ranks.toReversed().map((rank) => (
          <div key={rank} className="col-span-1 row-span-8 flex flex-row">
            {files.map((file) => {
              const sq: TSquare = getSquare({ rank, file });
              return (
                <ChessSquare
                  key={`${sq}`}
                  square={sq}
                  rank={rank}
                  file={file}
                  piece={boardState.getPieceOnSquare(sq)}
                  pieceColor={boardState.getColorOnSquare(sq)}
                  isLegalFromSquare={
                    boardState.isLegalFromSquare(sq) &&
                    boardState.getColorOnSquare(sq) === humanPlayerColor &&
                    boardState.getTurnColor() ===
                      boardState.getColorOnSquare(sq)
                  }
                  isLegalToSquare={legalDroppingSquares.includes(sq)}
                  wasInLastMove={lastMove.from === sq || lastMove.to === sq}
                  boardState={boardState}
                  promotionContext={promotionContext}
                  gameOngoing={gameOngoing}
                  onPromotionSelection={handlePromotionSelection
                  }
                />
              );
            })}
          </div>
        ))}
      </div>
    </DndContext>
  );
}
