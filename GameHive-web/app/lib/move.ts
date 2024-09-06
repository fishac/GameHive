import { TSquare } from '@/app/lib/square';
import { TPiece } from '@/app/lib/piece';

export default interface IMove {
    from: TSquare;
    to: TSquare;
    promotionPiece: TPiece;
}