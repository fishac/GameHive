"use client";

import ChessSquare from "@/app/ui/chess/game/chess-square";
import { DndContext } from "@dnd-kit/core";
import { useState } from "react";
import { snapCenterToCursor } from "@dnd-kit/modifiers";
import BoardState, { IBoardState } from "@/app/lib/board-state";
import IMove from "@/app/lib/move";
import { TSquare, isValidTSquare, getSquare } from "@/app/lib/square";
import {
  isValidPromotionContext,
  IPromotionContext,
} from "@/app/lib/promotions";
import { TPiece } from "@/app/lib/piece";
import { IoSwapVerticalOutline } from "react-icons/io5";

const ranks = [0, 1, 2, 3, 4, 5, 6, 7];
const files = [0, 1, 2, 3, 4, 5, 6, 7];

function handleDragStart(
  e: any,
  boardState: IBoardState,
  setDraggingFromSquare: any
): void {
  setDraggingFromSquare(e.active.id);
}

function handleDragEnd(
  e: any,
  boardState: IBoardState,
  setDraggingFromSquare: any,
  setPromotionContext: any
): void {
  if (e.over) {
    const move: IMove = { from: e.active.id, to: e.over.id, promotionPiece: 0 };
    console.log("handleDragEnd move: " + JSON.stringify(move));
    if (boardState.moveRequiresPromotion(move)) {
      setPromotionContext({ from: move.from, to: move.to });
      setDraggingFromSquare(-1);
    } else {
      boardState.makeMove(move);
      setDraggingFromSquare(-1);
    }
  }
}

function handlePromotionSelection(
  promotionPiece: TPiece,
  promotionContext: IPromotionContext,
  boardState: IBoardState,
  setPromotionContext: any
): void {
  if (isValidPromotionContext(promotionContext, boardState)) {
    boardState.makeMove({
      from: promotionContext.from,
      to: promotionContext.to,
      promotionPiece,
    });
    setPromotionContext({ from: -1, to: -1 });
  }
}

export default function ChessBoard({
  boardState,
}: {
  boardState: IBoardState;
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
  return (
    <DndContext
      onDragStart={(e) => handleDragStart(e, boardState, setDraggingFromSquare)}
      onDragEnd={(e) =>
        handleDragEnd(e, boardState, setDraggingFromSquare, setPromotionContext)
      }
      modifiers={[snapCenterToCursor]}
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
                  isLegalFromSquare={boardState.isLegalFromSquare(sq)}
                  isLegalToSquare={legalDroppingSquares.includes(sq)}
                  boardState={boardState}
                  promotionContext={promotionContext}
                  onPromotionSelection={(promotionPiece: TPiece) =>
                    handlePromotionSelection(
                      promotionPiece,
                      promotionContext,
                      boardState,
                      setPromotionContext
                    )
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
