import clsx from 'clsx';
import {useDraggable, useDroppable} from '@dnd-kit/core';
import {CSS} from '@dnd-kit/utilities';
import {TPiece} from '@/app/lib/piece';
import {TSquare} from '@/app/lib/square';
import { IBoardState } from '@/app/lib/board-state';
import PromotionMenu from './promotion-menu';
import { IPromotionContext, isValidPromotionContext } from '@/app/lib/promotions';

function getPieceFilename(piece: TPiece, pieceColor: boolean): string {
    if (piece > 0) {
        const colorString = pieceColor ? 'w' : 'b';
        let pieceString;
        if (piece == 1) {
            pieceString = 'P';
        } else if (piece == 2) {
            pieceString = 'N';
        } else if (piece == 3) {
            pieceString = 'B';
        } else if (piece == 4) {
            pieceString = 'R';
        } else if (piece == 5) {
            pieceString = 'Q';
        } else {
            pieceString = 'K';
        }
        return colorString + pieceString;
    } else {
        return '';
    }
}

function getSquareStatus({sq, isOver, isDragging, isLegalToSquare, boardState}: {sq: TSquare, isOver: boolean, isDragging: boolean, isLegalToSquare: boolean, boardState: any}) {
    if (isDragging) {
        return 0;
    } else if (isOver && isLegalToSquare) {
        return 1;
    } else if (isLegalToSquare) {
        return 2;
    } else if (boardState.getWhiteKingSquare() === sq) {
        return 3;
    } else if (boardState.getBlackKingSquare() === sq) {
        return 4;
    } else {
        return 0;
    }
}

export default function ChessSquare({square, rank, file, piece, pieceColor, isLegalFromSquare, isLegalToSquare, boardState, promotionContext, onPromotionSelection}: {square: TSquare, rank: number, file: number, piece: TPiece, pieceColor: boolean, isLegalFromSquare: boolean, isLegalToSquare: boolean, boardState: IBoardState, promotionContext: IPromotionContext, onPromotionSelection: any}) {
    const promotionMenuOpen: boolean = isValidPromotionContext(promotionContext, boardState);
    const draggable: {attributes: any, listeners: any, setNodeRef: any, transform: any, isDragging: any} = useDraggable({
        id: square,
        disabled: (!isLegalFromSquare || promotionMenuOpen)
    });
    const draggableStyle = {
    // Outputs `translate3d(x, y, 0)`
        transform: CSS.Translate.toString(draggable.transform),
        zIndex: draggable.isDragging ? '20' : '10'
    };
    const droppable: {isOver: any, setNodeRef: any} = useDroppable({
        id: square,
        disabled: !isLegalToSquare
    });
    
    const squareStatus: number = getSquareStatus({sq: square, isOver: droppable.isOver, isDragging: draggable.isDragging, isLegalToSquare, boardState});

    return (
        <div className={clsx(
            "height-full aspect-square relative",
            {
                "bg-orange-200": (rank % 2 === file % 2),
                "bg-orange-900": (rank % 2 !== file % 2)
            })}
            ref={droppable.setNodeRef}
        >
            <div className={clsx(
                "h-full w-full absolute",
                { 
                    "bg-green-700 bg-opacity-80": (squareStatus == 1),
                    "bg-green-700 bg-opacity-40": (squareStatus == 2),
                    "bg-red-400 bg-opacity-80": (squareStatus == 3),
                    "bg-purple-400 bg-opacity-80": (squareStatus == 4)
                })}
            >
            {(piece>0 && promotionContext.from !== square) && 
                <img 
                    src={'/pieces/' + getPieceFilename(piece,pieceColor) + '.svg'}  
                    className="absolute w-full h-full"
                    ref={draggable.setNodeRef}
                    style={draggableStyle}
                    {...(draggable.listeners)}
                    {...(draggable.attributes)}
                />
            }
            {(piece>0) && (draggable.isDragging || promotionContext.from === square) && 
                <img 
                    src={'/pieces/' + getPieceFilename(piece,pieceColor) + '.svg'}  
                    className="absolute w-full h-full opacity-50"
                />
            }
            {promotionMenuOpen && 
                <div className="absolute h-full w-full bg-neutral-900 opacity-50" />
            }
            {(promotionMenuOpen && square === promotionContext.to) && 
                <PromotionMenu 
                    onTop={rank===7}
                    pieceColor={rank===7}
                    onPromotionSelection={onPromotionSelection}
                />
            }
            </div>
        </div>
    )
}