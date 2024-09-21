import { TSquare } from '@/app/lib/square';
import { TPiece } from '@/app/lib/piece';

export default interface IMove {
    from: TSquare;
    to: TSquare;
    promotionPiece: TPiece;
}

export function isValidMove(move: IMove | null) {
    return (move && move.from !== -1 && move.to !== -1);
}

export const NOMOVE: IMove = {
    from: -1,
    to: -1,
    promotionPiece: 0
}