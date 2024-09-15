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
    console.log("initializing");
    chessEngine = await initializeNewChessEngine();
    console.log("done initializing");
}

async function provideMove(message: IProvideMoveRequest) {
    console.log("providing move");
    if (!chessEngine) {
        console.log("provideMove re-init");
        await initialize();
    }
    const provideSuccess: boolean = chessEngine.provideMove(message.providedMove);
    console.log(`Provided move success?: ${provideSuccess}`);
    console.log("provided move");
}

async function suggestMove(message: ISuggestMoveRequest) {
    console.log("suggesting move");
    if (!chessEngine) {
        console.log("suggestMove re-init");
        await initialize();
    }
    console.log("")
    const move: IMove = chessEngine.suggestMove(180000,0);
    return move;
}

async function engineMove(message: IEngineTurnRequest) {
    if (!chessEngine) {
        console.log("engineMove re-init");
        await initialize();
    }
    if (isValidMove(message.previousMove)) {
        console.log("Informing engine of previous move: " + JSON.stringify(message.previousMove));
        const provideSuccess: boolean = chessEngine.provideMove(message.previousMove);
        console.log(`Provided move success?: ${provideSuccess}`);
    }
    console.log(`pre-think FEN: ${chessEngine.getFEN()}`);
    const move: IMove = chessEngine.suggestMove(5000,0);
    console.log("Engine move suggested move: " + JSON.stringify(move));
    console.log("post-think FEN: " + chessEngine.getFEN() + " move was hard time cutoff: " + chessEngine.searchWasHardTimeCutoff());
    const engineProvideSuccess: boolean = chessEngine.provideMove(move);
    console.log(`Engine provided move success?: ${engineProvideSuccess}`);
    console.log(`post-provide FEN: ${chessEngine.getFEN()}`);
    return move;
}

async function handleMessage(e: MessageEvent) {
    const requestType: number = e.data.requestType;
    console.log("Request: " + JSON.stringify(e.data));
    console.log(`mt: ${requestType}`);
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
            console.log("Engine move response: " + JSON.stringify(response));
            break;
        default:
            break;
    }
    self.postMessage(response);
}

self.addEventListener("message", handleMessage, false)
