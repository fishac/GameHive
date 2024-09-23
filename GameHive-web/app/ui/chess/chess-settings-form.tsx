"use client";

import { useState } from "react";
import Dropdown, { DropdownOption } from "@/app/ui/dropdown";
import { useRouter } from "next/navigation";
import { timeControlOptions } from "@/app/lib/time-control";

export default function ChessSettingsForm() {
  const [selectedTimeControl, setSelectedTimeControl] =
    useState<DropdownOption | null>(null);
  const router = useRouter();
  const playAsWhite = () => {
    if (selectedTimeControl) {
      const params = new URLSearchParams();
      params.set("white", "1");
      params.set("timeControl", selectedTimeControl.value.toString());
      router.push("/play/chess/game?" + params.toString());
    }
  };
  const playAsBlack = () => {
    if (selectedTimeControl) {
      const params = new URLSearchParams();
      params.set("white", "0");
      params.set("timeControl", selectedTimeControl.value.toString());
      router.push("/play/chess/game?" + params.toString());
    }
  };

  return (
    <div className="flex flex-col justify-center">
      <Dropdown
        label="Time Control"
        options={timeControlOptions}
        selectedOption={selectedTimeControl}
        setSelectedOption={setSelectedTimeControl}
        dropdownClassName="mb-2"
        listboxButtonClassName="w-96"
        listboxOptionsClassName="w-96"
        listboxOptionClassName="w-96"
      />
      <div className="flex flex-row justify-center mt-16">
        <button
          onClick={playAsWhite}
          type="button"
          className="px-2 h-12 bg-neutral-200 rounded-lg text-neutral-800 font-bold mx-8 transition duration-100 ease-in-out hover:shadow-lg hover:shadow-neutral-500/50 active:shadow-neutral-500/80"
        >
          Play as White
        </button>
        <button
          onClick={playAsBlack}
          type="button"
          className="px-2 h-12 bg-neutral-800 rounded-lg text-neutral-200 font-bold mx-8 transition duration-100 ease-in-out hover:shadow-lg hover:shadow-neutral-500/50 active:shadow-neutral-500/80"
        >
          Play as Black
        </button>
      </div>
    </div>
  );
}
