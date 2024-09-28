import { ITimeControl } from "@/app/lib/time-control";
import Timer from "@/app/ui/timer";
import Image from "next/image";

export default function ChessPlayerInfo({
  isEngine,
  playerTurn,
  timerActive,
  timeControl,
  onTimeout,
}: {
  isEngine: boolean;
  playerTurn: boolean;
  timerActive: boolean;
  timeControl: ITimeControl;
  onTimeout: () => void;
}) {
  return (
    <div className="flex flex-col">
      <span className="ml-2 mt-2 text-neutral-100">
        {isEngine ? "Honeybee" : "Player"}
      </span>
      <div className="flex flex-row justify-between my-4 mx-2">
        <Timer
          ticking={playerTurn}
          timerActive={timerActive}
          timeControl={timeControl}
          allowGrace={!isEngine}
          onTimeout={onTimeout}
        />
        {isEngine && playerTurn && (
          <Image
            src="/emoji-spin.gif"
            alt="thinking-indicator"
            width={36}
            height={36}
            className="mr-2"
            unoptimized={true}
          />
        )}
      </div>
    </div>
  );
}
