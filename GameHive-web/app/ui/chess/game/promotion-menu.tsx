import clsx from "clsx";
import Image from "next/image";

export default function PromotionMenu({
  onTop,
  pieceColor,
  onPromotionSelection,
}: {
  onTop: boolean;
  pieceColor: boolean;
  onPromotionSelection: any;
}) {
  return (
    <div
      className={clsx("absolute flex justify-end flex-col z-30", {
        "flex-col-reverse -translate-y-3/4": !onTop,
      })}
    >
      <Image
        className="w-full aspect-square bg-neutral-400 hover:bg-neutral-200"
        src={pieceColor ? "/pieces/wQ.svg" : "/pieces/bQ.svg"}
        onClick={() => onPromotionSelection(5)}
        alt="Promote to queen"
      />
      <Image
        className="w-full aspect-square bg-neutral-400 hover:bg-neutral-200"
        src={pieceColor ? "/pieces/wR.svg" : "/pieces/bR.svg"}
        onClick={() => onPromotionSelection(4)}
        alt="Promote to rook"
      />
      <Image
        className="w-full aspect-square bg-neutral-400 hover:bg-neutral-200"
        src={pieceColor ? "/pieces/wB.svg" : "/pieces/bB.svg"}
        onClick={() => onPromotionSelection(3)}
        alt="Promote to bishop"
      />
      <Image
        className="w-full aspect-square bg-neutral-400 hover:bg-neutral-200"
        src={pieceColor ? "/pieces/wN.svg" : "/pieces/bN.svg"}
        onClick={() => onPromotionSelection(2)}
        alt="Promote to knight"
      />
    </div>
  );
}
