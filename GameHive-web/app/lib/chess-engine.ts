import ChessEngineJS from './ChessEngineJS.js';
import {TSquare} from '@/app/lib/square';
import {TPiece} from '@/app/lib/piece';
import IMove from '@/app/lib/move';

export interface IChessEngine {
    init(ceLib: any): void;
    suggestMove(millisRemaining: number, millisIncrement: number): IMove;
    provideMove(m: IMove): boolean;
    setFEN(FEN: string): void;
    getFEN(): string;
    getMoveSearchDepth(): number;
    getMoveSearchTime(): number;
    getMoveSearchTimeLimit(): number;
    searchWasHardTimeCutoff(): boolean;
    getNumScannedNodes(): number;
}

class ChessEngine {
    #internalEngine: any;
    #ceLib: any;
    constructor () {
    }
    init(ceLib: any): void {
        this.#ceLib = ceLib;
        this.#internalEngine = new this.#ceLib.ChessEngine();
    }

	suggestMove(millisRemaining: number, millisIncrement: number): IMove {
        return this.#internalEngine.suggestMove(Math.ceil(millisRemaining),Math.ceil(millisIncrement),true);
    }

	provideMove(m: IMove): boolean {
        return this.#internalEngine.provideMove(m);
    }

	setFEN(FEN: string): void {
        this.#internalEngine.setFEN(FEN);
    }

	getFEN(): string {
        return this.#internalEngine.getFEN();
    }

	getMoveSearchDepth(): number {
        return this.#internalEngine.getMoveSearchDepth();
    }

	getMoveSearchTime(): number {
        return this.#internalEngine.getMoveSearchTime();
    }

	getMoveSearchTimeLimit(): number {
        return this.#internalEngine.getMoveSearchTimeLimit();
    }

	searchWasHardTimeCutoff(): boolean {
        return this.#internalEngine.searchWasHardTimeCutoff();
    }

	getNumScannedNodes(): number {
        return this.#internalEngine.getNumScannedNodes();
    }

}

export default async function initializeNewChessEngine(): Promise<IChessEngine> {
    const ceLib = await ChessEngineJS();
    const ce: IChessEngine = new ChessEngine();
    ce.init(ceLib);
    return ce;
}