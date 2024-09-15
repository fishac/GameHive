import IMove from "@/app/lib/move";

export const CHESS_ENGINE_WORKER_MESSAGE_TYPES = {
    INITIALIZE: 0,
    PROVIDE_MOVE: 1,
    SUGGEST_MOVE: 2,
    ENGINE_MOVE: 3
}
Object.preventExtensions(CHESS_ENGINE_WORKER_MESSAGE_TYPES);

export interface IInitializeRequest {
    requestType: 0;
}

export interface IProvideMoveRequest {
    requestType: 1;
    providedMove: IMove;
}

export interface ISuggestMoveRequest {
    requestType: 2;
}

export interface IEngineTurnRequest {
    requestType: 3;
    previousMove: IMove;
}

export interface IInitializeResponse {
    responseType: 0;
}

export interface IProvideMoveResponse {
    responseType: 1;
}

export interface ISuggestMoveResponse {
    responseType: 2;
    move: IMove;
}

export interface IEngineTurnResponse {
    responseType: 3;
    move: IMove;
}