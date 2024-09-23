import ChessPlayerInfo from "./chess-player-info";
import ChessMoveHistory from "./chess-move-history";
import IMove, { IMoveRecord } from "@/app/lib/move";
import { IChessUtils } from "@/app/lib/chess-utils";
import { TGameResult } from "@/app/lib/game-result";
import { ITimeControl } from "@/app/lib/time-control";

export default function ChessSidebar({
  moveHistory,
  player1Turn,
  player2Turn,
  timersActive,
  result,
  timeControl,
  chessUtils,
  player1IsEngine,
  player2IsEngine,
  onTimeout,
}: {
  moveHistory: IMoveRecord[];
  player1Turn: boolean;
  player2Turn: boolean;
  timersActive: boolean;
  result: TGameResult;
  timeControl: ITimeControl;
  chessUtils: IChessUtils | null;
  player1IsEngine: boolean;
  player2IsEngine: boolean;
  onTimeout: (player1: boolean) => void;
}) {
  return (
    <div className="ml-4 flex flex-col justify-between w-72 bg-gradient-to-b from-neutral-800 via-neutral-700 to-neutral-800 rounded-xl">
      <ChessPlayerInfo
        isEngine={player2IsEngine}
        playerTurn={player2Turn}
        timerActive={timersActive}
        timeControl={timeControl}
        onTimeout={() => onTimeout(false)}
      />
      <ChessMoveHistory moveHistory={moveHistory} result={result} chessUtils={chessUtils} />
      <ChessPlayerInfo
        isEngine={player1IsEngine}
        playerTurn={player1Turn}
        timerActive={timersActive}
        timeControl={timeControl}
        onTimeout={() => onTimeout(true)}
      />
    </div>
  );
}
