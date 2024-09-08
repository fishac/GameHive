import ChessEngineJS from './ChessEngineJS.js';
import {TSquare} from '@/app/lib/square';
import {TPiece} from '@/app/lib/piece';
import IMove from '@/app/lib/move';

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
        return this.#internalEngine.provideMove();
    }

	setFEN(FEN: string): void {
        this.#internalEngine.setFEN();
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

export default async function initializeNewChessEngine() {
    const ceLib = await ChessEngineJS();
    const ce = new ChessEngine();
    ce.init(ceLib);
    return ce;
}