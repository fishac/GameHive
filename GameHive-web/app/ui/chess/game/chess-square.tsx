import clsx from "clsx";
import { useDraggable, useDroppable } from "@dnd-kit/core";
import { CSS } from "@dnd-kit/utilities";
import { getPieceFilename, TPiece } from "@/app/lib/piece";
import { TSquare } from "@/app/lib/square";
import { IBoardState } from "@/app/lib/board-state";
import PromotionMenu from "./promotion-menu";
import {
  IPromotionContext,
  isValidPromotionContext,
} from "@/app/lib/promotions";



export default function ChessSquare({
  square,
  rank,
  file,
  piece,
  pieceColor,
  isLegalFromSquare,
  isLegalToSquare,
  wasInLastMove,
  boardState,
  promotionContext,
  gameOngoing,
  onPromotionSelection,
}: {
  square: TSquare;
  rank: number;
  file: number;
  piece: TPiece;
  pieceColor: boolean;
  isLegalFromSquare: boolean;
  isLegalToSquare: boolean;
  wasInLastMove: boolean;
  boardState: IBoardState;
  promotionContext: IPromotionContext;
  gameOngoing: boolean;
  onPromotionSelection: any;
}) {


  const promotionMenuOpen: boolean = isValidPromotionContext(
    promotionContext,
    boardState
  );
  const draggable: {
    attributes: any;
    listeners: any;
    setNodeRef: any;
    transform: any;
    isDragging: any;
  } = useDraggable({
    id: square,
    disabled: !isLegalFromSquare || promotionMenuOpen || !gameOngoing,
  });
  const draggableStyle = {
    // Outputs `translate3d(x, y, 0)`
    transform: CSS.Translate.toString(draggable.transform),
    zIndex: draggable.isDragging ? "20" : "10",
  };
  const droppable: { isOver: any; setNodeRef: any } = useDroppable({
    id: square,
    disabled: !isLegalToSquare,
  });

  function getSquareStatus() {
    if (draggable.isDragging) {
      return 0;
    } else if (droppable.isOver && isLegalToSquare) {
      return 1;
    } else if (isLegalToSquare) {
      return 2;
    } else if (
      boardState.getPieceOnSquare(square) === 6 &&
      boardState.getCheckmateStatus() &&
      boardState.getTurnColor() === pieceColor
    ) {
      return 3;
    } else if (
      boardState.getPieceOnSquare(square) === 6 &&
      boardState.getCheckStatus() &&
      boardState.getTurnColor() === pieceColor
    ) {
      return 4;
    } else if (wasInLastMove) {
      return 5;
    } else {
      return 0;
    }
  }

  const squareStatus: number = getSquareStatus();

  return (
    <div
      className={clsx("height-full aspect-square relative", {
        "bg-orange-200": rank % 2 === file % 2,
        "bg-orange-900": rank % 2 !== file % 2,
      })}
      ref={droppable.setNodeRef}
    >
      <div
        className={clsx("h-full w-full absolute", {
          "bg-green-700 bg-opacity-80": squareStatus == 1,
          "bg-green-700 bg-opacity-40": squareStatus == 2,
          "bg-purple-400 bg-opacity-80": squareStatus == 3,
          "bg-red-400 bg-opacity-80": squareStatus == 4,
          "bg-yellow-500 bg-opacity-30": squareStatus == 5,
        })}
      >
        {piece > 0 && promotionContext.from !== square && (
          <img
            src={"/pieces/" + getPieceFilename(piece, pieceColor) + ".svg"}
            className="absolute w-full h-full"
            ref={draggable.setNodeRef}
            style={draggableStyle}
            {...draggable.listeners}
            {...draggable.attributes}
          />
        )}
        {piece > 0 &&
          (draggable.isDragging || promotionContext.from === square) && (
            <img
              src={"/pieces/" + getPieceFilename(piece, pieceColor) + ".svg"}
              className="absolute w-full h-full opacity-50"
            />
          )}
        {promotionMenuOpen && (
          <div className="absolute h-full w-full bg-neutral-900 opacity-50" />
        )}
        {promotionMenuOpen && square === promotionContext.to && (
          <PromotionMenu
            onTop={rank === 7}
            pieceColor={rank === 7}
            onPromotionSelection={onPromotionSelection}
          />
        )}
      </div>
    </div>
  );
}
