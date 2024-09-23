import { IChessUtils } from "@/app/lib/chess-utils";
import IMove, {IMoveRecord} from "@/app/lib/move";
import { TSquare } from "@/app/lib/square";
import Image from "next/image";
import { getPieceFilename } from "@/app/lib/piece";
import { GameResult, TGameResult } from "@/app/lib/game-result";

export default function ChessMoveHistory({
  moveHistory,
  chessUtils,
  result
}: {
  moveHistory: IMoveRecord[];
  chessUtils: IChessUtils | null;
  result: TGameResult
}) {

  function getSquareDisplay(s: TSquare): string {
    return chessUtils ? chessUtils.getSquareString(s) : s.toString();
  }

  function getResultDisplay(r: TGameResult) {
    switch (r) {
      case GameResult.UNDECIDED:
        return '';
      case GameResult.DRAW:
        return '1/2-1/2';
      case GameResult.WHITE_WIN:
        return '1-0';
      case GameResult.BLACK_WIN:
        return '0-1';
    }
  }

  return (
    <div className="flex flex-row border-2 border-neutral-600 bg-neutral-800 w-48 h-36 mx-auto overflow-y-auto">
      <div className="w-8 flex flex-col mr-0.5">
        {Array.from(
          { length: Math.ceil((moveHistory.length + 1) / 2) },
          (x, i) => i + 1
        ).map((i) => {
          return (
            <div
              key={`${i}`}
              className="bg-neutral-600 h-5 w-full text-sm mb-0.5"
            >
              <span className="ml-1">{i}</span>
            </div>
          );
        })}
      </div>
      <div className="w-full grid grid-cols-2 gap-0.5 auto-rows-min">
        {moveHistory.map((mr: IMoveRecord, i: number) => {
          return (
            <div
              key={`${i}`}
              className="text-left bg-neutral-700 h-5 w-full text-sm"
            >
              <span className="ml-1 inline-flex">
                <Image
                  width={14}
                  height={14}
                  alt="moved piece"
                  src={"/pieces/" + getPieceFilename(mr.movedPiece,i % 2 === 0) + ".svg"}
                />
                {` ${
                  getSquareDisplay(mr.move.from)
                } ${mr.moveIsCapture ? 'x' : ''} ${getSquareDisplay(mr.move.to)}`}
              </span>
            </div>
          );
        })}
        {(result !== GameResult.UNDECIDED) && (
          <div className="text-center bg-neutral-700 h-5 w-full text-sm">
            <span>{getResultDisplay(result)}</span>
          </div>
        )}
      </div>
    </div>
  );
}
