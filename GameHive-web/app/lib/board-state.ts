import ChessEngineJS from '@/app/lib/ChessEngineJS';
import {TSquare} from '@/app/lib/square';
import {TPiece} from '@/app/lib/piece';
import IMove from '@/app/lib/move';

export interface IBoardState {
    init(ceLib: any): void;
    setFEN(FEN: string): void;
    toFEN(): string;
    isLegalFromSquare(sq: TSquare): boolean;
    getLegalMoves(): IMove[];
    getLegalMovesFromSquare(sq: TSquare): TSquare[];
    makeMove(m: IMove): boolean;
    isMoveLegal(m: IMove): boolean;
    moveRequiresPromotion(m: IMove): boolean;
    getCheckStatus(): boolean;
    getCheckmateStatus(): boolean;
    getStalemateStatus(): boolean;
    isDrawByRepitition(): boolean;
    isDrawByInsufficientMaterial(): boolean;
    getTurnColor(): boolean;
    getWhiteKingSquare(): TSquare;
    getBlackKingSquare(): TSquare;
    getPieceOnSquare(sq: TSquare): TPiece;
    getColorOnSquare(sq: TSquare): boolean;
    isSquareOccupied(sq: TSquare): boolean;
    moveIsCapture(move: IMove): boolean;
}

export class BoardState implements IBoardState {
    #internalState: any;
    #ceLib: any;
    constructor () {
    }
    init(ceLib: any): void {
        this.#ceLib = ceLib;
        this.#internalState = new this.#ceLib.BoardState(true);
    }

    setFEN(FEN: string): void {
        this.#internalState.setFEN(FEN);
    }

    toFEN(): string {
        return this.#internalState.toFEN();
    }

    isLegalFromSquare(sq: TSquare): boolean {
        return this.#internalState.isLegalFromSquare(sq);
    }

    getLegalMoves(): IMove[] {
        const legalMovesVector = this.#internalState.getLegalMoves();
        return new Array(
            legalMovesVector.size()
        ).fill(0)
        .map((_, id) => legalMovesVector.get(id));
    }

    getLegalMovesFromSquare(sq: TSquare): TSquare[] {
        const legalMovesVector = this.#internalState.getLegalMovesFromSquare(sq);
        return new Array(
            legalMovesVector.size()
        ).fill(0)
        .map((_, id) => legalMovesVector.get(id));
    }

    makeMove(m: IMove): boolean {
        return this.#internalState.makeMove(m);
    }

    isMoveLegal(m: IMove): boolean {
        return this.#internalState.isMoveLegal(m);
    }

    moveRequiresPromotion(m: IMove): boolean {
        return this.#internalState.moveRequiresPromotion(m);
    }

    getCheckStatus(): boolean {
        return this.#internalState.getCheckStatus();
    }

    getCheckmateStatus(): boolean {
        return this.#internalState.getCheckmateStatus();
    }

    getStalemateStatus(): boolean {
        return this.#internalState.getStalemateStatus();
    }

    isDrawByRepitition(): boolean {
        return this.#internalState.isDrawByRepitition();
    }

    isDrawByInsufficientMaterial(): boolean {
        return this.#internalState.isDrawByInsufficientMaterial();
    }

    getTurnColor(): boolean {
        return this.#internalState.getTurnColor();
    }

    getWhiteKingSquare(): TSquare {
        return this.#internalState.getWhiteKingSquare();
    }

    getBlackKingSquare(): TSquare  {
        return this.#internalState.getBlackKingSquare();
    }

    getPieceOnSquare(sq: TSquare): TPiece {
        return this.#internalState.getPieceOnSquare(sq);
    }

    getColorOnSquare(sq: TSquare): boolean {
        return this.#internalState.getColorOnSquare(sq);
    }

    isSquareOccupied(sq: TSquare): boolean {
        return this.#internalState.isSquareOccupied(sq);
    }

    moveIsCapture(move: IMove): boolean {
        return this.#internalState.moveIsCapture(move);
    }
}

export default async function initializeNewBoardState(): Promise<IBoardState> {
    const ceLib = await ChessEngineJS();
    const bs: IBoardState = new BoardState();
    bs.init(ceLib);
    return bs;
}