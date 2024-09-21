import Timer from "@/app/ui/timer";
import Image from "next/image";

export default function ChessPlayerInfo({
  isEngine,
  playerTurn,
  timerActive,
  onTimeout,
}: {
  isEngine: boolean;
  playerTurn: boolean;
  timerActive: boolean;
  onTimeout: () => void;
}) {
  return (
    <div className="flex flex-col">
      <span className="ml-2 mt-2 text-neutral-100">
        {isEngine ? "Honeybee" : "Player"}
      </span>
      <div className="flex flex-row justify-between my-4 mx-2">
        <Timer
          baseTimeMillis={10000}
          incrementMillis={0}
          ticking={playerTurn}
          timerActive={timerActive}
          player={isEngine ? "Honeybee" : "Player"}
          onTimeout={onTimeout}
        />
        {isEngine && playerTurn && (
          <Image
            src="/emoji-spin.gif"
            alt="thinking-indicator"
            width={36}
            height={36}
            className="mr-2"
          />
        )}
      </div>
    </div>
  );
}
