import { IChessUtils } from "@/app/lib/chess-utils";
import IMove from "@/app/lib/move";
import Image from "next/image";

export default function ChessMoveHistory({
  moveHistory,
  chessUtils,
}: {
  moveHistory: IMove[];
  chessUtils: IChessUtils | null;
}) {
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
        {moveHistory.map((m: IMove, i: number) => {
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
                  src="/pieces/wR.svg"
                />
                {` ${
                  chessUtils ? chessUtils.getSquareString(m.from) : m.from
                } ${chessUtils ? chessUtils.getSquareString(m.to) : m.to}`}
              </span>
            </div>
          );
        })}
      </div>
    </div>
  );
}
