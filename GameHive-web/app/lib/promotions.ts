
import BoardState, { IBoardState } from '@/app/lib/board-state';
import { TSquare, isValidTSquare } from '@/app/lib/square';

export interface IPromotionContext {
    from: TSquare,
    to: TSquare
}

export function isValidPromotionContext(promotionContext: IPromotionContext, boardState: IBoardState): boolean {
    return (isValidTSquare(promotionContext.from) && isValidTSquare(promotionContext.to)
      && boardState.moveRequiresPromotion({from: promotionContext.from, to: promotionContext.to, promotionPiece: 0}));
}

