import IMove from "@/app/lib/move";
import { TSquare } from "./square";
import ChessEngineJS from './ChessEngineJS.js';
import { IChessEngine } from "./chess-engine";

export interface IChessUtils {
    init(ceLib: any): void;
    getMoveString(move: IMove): string;
    getSquareString(s: TSquare): string;
}

class ChessUtils {
    #ceLib: any;
    constructor () {
    }
    init(ceLib: any): void {
        this.#ceLib = ceLib; 
    }

	getMoveString(move: IMove): string {
        return this.#ceLib.getMoveString(move);
    }

    getSquareString(s: TSquare): string {
        return this.#ceLib.getSquareString(s);
    }
}

export default async function initializeNewChessUtils(): Promise<IChessUtils> {
    const ceLib = await ChessEngineJS();
    const cu: IChessUtils = new ChessUtils();
    cu.init(ceLib);
    return cu;
}