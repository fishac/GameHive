import { useState, useEffect, useRef } from "react";
import { Red_Hat_Mono } from "next/font/google";
import { ITimeControl } from "../lib/time-control";

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
  ticking,
  timerActive,
  timeControl,
  allowGrace,
  remainingMillis,
  setRemainingMillis,
  onTimeout,
}: {
  ticking: boolean;
  timerActive: boolean;
  timeControl: ITimeControl;
  allowGrace: boolean;
  remainingMillis: number;
  setRemainingMillis: (rem: number) => void;
  onTimeout: () => void;
}) {
  const [hasStarted, setHasStarted] = useState<boolean>(false);
  const [turnMillis, setTurnMillis] = useState<number>(0);
  const [baseDateTime, setBaseDateTime] = useState<number>(Date.now());
  const [inGracePeriod,setInGracePeriod] = useState<boolean>(allowGrace);
  useEffect(() => {
    const int = 50;
    let interval: NodeJS.Timeout;
    if (ticking) {
      const bdt = Date.now();
      setBaseDateTime(bdt);
      setHasStarted(hs => true);
      if (!inGracePeriod) {
        interval = setInterval(() => {
          setTurnMillis((t) => t + int);
          if (remainingMillis - (Date.now() - bdt) <= 0) {
            onTimeout();
            setRemainingMillis(0);
          }
        }, int);
      }
    } else {
      const rem = Math.max(
        (hasStarted && !inGracePeriod)
          ? remainingMillis - (Date.now() - baseDateTime)
          : remainingMillis,
        0
      );
      if (hasStarted) {
        setInGracePeriod(false);
      }
      const incr = (hasStarted && timerActive && rem > 0) ? timeControl.incrementMillis : 0;
      setRemainingMillis(rem+incr);
      setTurnMillis(0);
    }

    return () => {
      if (interval) {
        clearInterval(interval);
      }
    };
  }, [ticking]);

  const time: number = Math.max(
    (ticking && !inGracePeriod && hasStarted) ? remainingMillis - (Date.now() - baseDateTime) : remainingMillis,
    0
  );
  const timeBreakdown: ITimeBreakdown = getTimeBreakdown(time);
  return (
    <div className={`${rhm.className} text-neutral-100`}>
      <span className="text-4xl">
        {`${formatDisplayMinSec(timeBreakdown.minutes)}:${formatDisplayMinSec(
          timeBreakdown.seconds
        )}`}
      </span>
      <span className="text-md">
        {time < 60000 && `.${formatDisplayMilli(timeBreakdown.milliseconds)}`}
      </span>
    </div>
  );
}
