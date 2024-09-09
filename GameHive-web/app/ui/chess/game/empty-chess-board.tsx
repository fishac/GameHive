import clsx from "clsx";
import { TSquare, getSquare } from "@/app/lib/square";

const ranks = [0, 1, 2, 3, 4, 5, 6, 7];
const files = [0, 1, 2, 3, 4, 5, 6, 7];

export default function EmptyChessBoard() {
  return (
    <div className="bg-red-500 w-[36%] aspect-square grid">
      {ranks.toReversed().map((rank) => (
        <div key={rank} className="col-span-1 row-span-8 flex flex-row">
          {files.map((file) => {
            const sq: TSquare = getSquare({ rank, file });
            return (
              <div
                key={`${sq}`}
                className={clsx("height-full aspect-square relative", {
                  "bg-orange-200": rank % 2 === file % 2,
                  "bg-orange-900": rank % 2 !== file % 2,
                })}
              />
            );
          })}
        </div>
      ))}
    </div>
  );
}
