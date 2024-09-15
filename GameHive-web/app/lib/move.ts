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