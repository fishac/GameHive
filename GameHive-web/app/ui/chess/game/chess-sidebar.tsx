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
  player1RemainingMillis,
  player2RemainingMillis,
  setPlayer1RemainingMillis,
  setPlayer2RemainingMillis,
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
  player1RemainingMillis: number;
  player2RemainingMillis: number;
  setPlayer1RemainingMillis: (rem: number) => void;
  setPlayer2RemainingMillis: (rem: number) => void;
  onTimeout: (player1: boolean) => void;
}) {
  return (
    <div className="ml-4 flex flex-col justify-between w-72 bg-gradient-to-b from-neutral-800 via-neutral-700 to-neutral-800 rounded-xl">
      <ChessPlayerInfo
        isEngine={player2IsEngine}
        playerTurn={player2Turn}
        timerActive={timersActive}
        timeControl={timeControl}
        remainingMillis={player2RemainingMillis}
        setRemainingMillis={setPlayer2RemainingMillis}
        onTimeout={() => onTimeout(false)}
      />
      <ChessMoveHistory moveHistory={moveHistory} result={result} chessUtils={chessUtils} />
      <ChessPlayerInfo
        isEngine={player1IsEngine}
        playerTurn={player1Turn}
        timerActive={timersActive}
        timeControl={timeControl}
        remainingMillis={player1RemainingMillis}
        setRemainingMillis={setPlayer1RemainingMillis}
        onTimeout={() => onTimeout(true)}
      />
    </div>
  );
}
