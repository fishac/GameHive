import { useState, useEffect } from "react";

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
}: {
  baseTimeMillis: number;
  incrementMillis: number;
}) {
  const [remainingMillis, setRemainingMillis] =
    useState<number>(baseTimeMillis);
  const [turnMillis, setTurnMillis] = useState<number>(0);
  const [baseDateTime, setBaseDateTime] = useState<number>(Date.now());

  function updateRemainingTime(int: number): void {
    setRemainingMillis(remainingMillis - int);
  }

  useEffect(() => {
    const int = 100;
    const interval = setInterval(() => setTurnMillis(turnMillis + int), int);

    return () => clearInterval(interval);
  });

  const timeBreakdown: ITimeBreakdown = getTimeBreakdown(
    remainingMillis - (Date.now() - baseDateTime)
  );
  return (
    <div className="h-8 text-xl">
      {`${formatDisplayMinSec(timeBreakdown.minutes)}:${formatDisplayMinSec(
        timeBreakdown.seconds
      )}.${formatDisplayMilli(timeBreakdown.milliseconds)}`}
    </div>
  );
}
