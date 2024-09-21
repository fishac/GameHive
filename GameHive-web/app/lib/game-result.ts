export type TGameResult = 0|1|2|3;

export const GameResult = {
    UNDECIDED: 0 as TGameResult,
    DRAW: 1 as TGameResult,
    WHITE_WIN: 2 as TGameResult,
    BLACK_WIN: 3 as TGameResult
}
Object.preventExtensions(GameResult);