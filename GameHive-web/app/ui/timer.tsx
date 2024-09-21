import { useState, useEffect } from "react";
import { Red_Hat_Mono } from "next/font/google";

const rhm = Red_Hat_Mono({ subsets: ["latin"] });

interface ITimeBreakdown {
  minutes: number;
  seconds: number;
  milliseconds: number;
}

function getTimeBreakdown(millisTotal: number): ITimeBreakdown {
  const milliseconds = Math.floor(millisTotal % 1000);
  const seconds = Math.floor((millisTotal - milliseconds) / 1000) % 60;
  const minutes = Math.floor(
    (millisTotal - seconds * 1000 - milliseconds) / 1000 / 60
  );
  return {
    minutes,
    seconds,
    milliseconds,
  };
}

function formatDisplayMinSec(n: number): string {
  if (n < 10) {
    return `0${n}`;
  } else {
    return `${n}`;
  }
}

function formatDisplayMilli(n: number): string {
  if (n > 99) {
    return `${Math.floor(n / 100)}`;
  } else if (n > 9) {
    return `${Math.floor(n / 100)}`;
  } else {
    return `${n}`;
  }
}

export default function Timer({
  baseTimeMillis,
  incrementMillis,
  ticking,
  timerActive,
  player,
  onTimeout,
}: {
  baseTimeMillis: number;
  incrementMillis: number;
  ticking: boolean;
  timerActive: boolean;
  player: String;
  onTimeout: () => void;
}) {
  const [hasStarted, setHasStarted] = useState<boolean>(false);
  const [remainingMillis, setRemainingMillis] =
    useState<number>(baseTimeMillis);
  const [turnMillis, setTurnMillis] = useState<number>(0);
  const [baseDateTime, setBaseDateTime] = useState<number>(Date.now());
  function updateRemainingTime(int: number): void {
    setRemainingMillis(remainingMillis - int);
  }

  useEffect(() => {
    console.log(`${player} timer useEffect. ticking: ${ticking}`);
    const int = 50;
    let interval: NodeJS.Timeout;
    if (ticking) {
      console.log(`${player} timer useEffect. setting interval.`);
      setBaseDateTime(Date.now());
      setHasStarted(true);
      setInterval(() => {
        setTurnMillis((t) => t + int);
      }, int);
    } else {
      const rem = setRemainingMillis(
        Math.max(
          hasStarted
            ? remainingMillis - (Date.now() - baseDateTime)
            : remainingMillis,
          0
        )
      );
      setTurnMillis(0);
    }

    return () => {
      if (interval) {
        clearInterval(interval);
      }
    };
  }, [ticking]);

  const time: number = Math.max(
    ticking ? remainingMillis - (Date.now() - baseDateTime) : remainingMillis,
    0
  );
  if (time <= 0 && timerActive) {
    console.log(`${player} timeout!`);
    onTimeout();
  }
  const timeBreakdown: ITimeBreakdown = getTimeBreakdown(time);
  return (
    <div className={`${rhm.className} text-neutral-100`}>
      <span className="text-4xl">
        {`${formatDisplayMinSec(timeBreakdown.minutes)}:${formatDisplayMinSec(
          timeBreakdown.seconds
        )}`}
      </span>
      <span className="text-md">
        {`.${formatDisplayMilli(timeBreakdown.milliseconds)}`}
      </span>
    </div>
  );
}
