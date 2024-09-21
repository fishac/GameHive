import ChessPlayerInfo from "./chess-player-info";
import ChessMoveHistory from "./chess-move-history";
import IMove from "@/app/lib/move";
import { IChessUtils } from "@/app/lib/chess-utils";

export default function ChessSidebar({
  moveHistory,
  player1Turn,
  player2Turn,
  timersActive,
  chessUtils,
  onTimeout,
}: {
  moveHistory: IMove[];
  player1Turn: boolean;
  player2Turn: boolean;
  timersActive: boolean;
  chessUtils: IChessUtils | null;
  onTimeout: (player1: boolean) => void;
}) {
  return (
    <div className="ml-4 flex flex-col justify-between w-72 bg-gradient-to-b from-neutral-800 via-neutral-700 to-neutral-800 rounded-xl">
      <ChessPlayerInfo
        isEngine={true}
        playerTurn={player2Turn}
        timerActive={timersActive}
        onTimeout={() => onTimeout(false)}
      />
      <ChessMoveHistory moveHistory={moveHistory} chessUtils={chessUtils} />
      <ChessPlayerInfo
        isEngine={false}
        playerTurn={player1Turn}
        timerActive={timersActive}
        onTimeout={() => onTimeout(true)}
      />
    </div>
  );
}
