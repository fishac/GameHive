import initializeNewChessEngine, { IChessEngine } from "@/app/lib/chess-engine";
import IMove, { isValidMove } from "@/app/lib/move";
import { 
    CHESS_ENGINE_WORKER_MESSAGE_TYPES, 
    IInitializeRequest,
    IProvideMoveRequest,
    ISuggestMoveRequest,
    IInitializeResponse,
    IProvideMoveResponse,
    ISuggestMoveResponse,
    IEngineTurnRequest
  } from "@/app/lib/chess-engine-messages";

let chessEngine: IChessEngine;

async function initialize() {
    chessEngine = await initializeNewChessEngine();
}

async function provideMove(message: IProvideMoveRequest) {
    if (!chessEngine) {
        await initialize();
    }
    const provideSuccess: boolean = chessEngine.provideMove(message.providedMove);
}

async function suggestMove(message: ISuggestMoveRequest) {
    if (!chessEngine) {
        await initialize();
    }
    const move: IMove = chessEngine.suggestMove(180000,0);
    return move;
}

async function engineMove(message: IEngineTurnRequest) {
    if (!chessEngine) {
        await initialize();
    }
    if (isValidMove(message.previousMove)) {
        const provideSuccess: boolean = chessEngine.provideMove(message.previousMove);
    }
    const move: IMove = chessEngine.suggestMove(message.remainingMillis,message.incrementMillis);
    const engineProvideSuccess: boolean = chessEngine.provideMove(move);
    return move;
}

async function handleMessage(e: MessageEvent) {
    const requestType: number = e.data.requestType;
    let response = {};
    switch(requestType) {
        case CHESS_ENGINE_WORKER_MESSAGE_TYPES.INITIALIZE:
            await initialize();
            response = { responseType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.INITIALIZE };
            break;
        case CHESS_ENGINE_WORKER_MESSAGE_TYPES.PROVIDE_MOVE:
            provideMove(e.data);
            response = { responseType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.PROVIDE_MOVE };
            break;
        case CHESS_ENGINE_WORKER_MESSAGE_TYPES.SUGGEST_MOVE:
            const sMove: IMove = await suggestMove(e.data);
            response = { 
                responseType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.SUGGEST_MOVE,
                move: sMove
            };
            break;
        case CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE:
            const eMove: IMove = await engineMove(e.data);
            response = { 
                responseType: CHESS_ENGINE_WORKER_MESSAGE_TYPES.ENGINE_MOVE,
                move: eMove
            };
            break;
        default:
            break;
    }
    self.postMessage(response);
}

self.addEventListener("message", handleMessage, false)
