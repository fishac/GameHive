import clsx from 'clsx';

export default function PromotionMenu({onTop, pieceColor, onPromotionSelection}: {onTop: boolean, pieceColor: boolean, onPromotionSelection: any}) {
    return (
        <div className={clsx(
            "absolute flex justify-end flex-col z-30",
            {
                "flex-col-reverse -translate-y-3/4": !onTop
            })}
        >
            <img 
                className="w-full aspect-square bg-neutral-400 hover:bg-neutral-200" 
                src={pieceColor ? "/pieces/wQ.svg" : "/pieces/bQ.svg"}
                onClick={() => onPromotionSelection(5)}
            />
            <img 
                className="w-full aspect-square bg-neutral-400 hover:bg-neutral-200" 
                src={pieceColor ? "/pieces/wR.svg" : "/pieces/bR.svg"}
                onClick={() => onPromotionSelection(4)}
            />
            <img 
                className="w-full aspect-square bg-neutral-400 hover:bg-neutral-200" 
                src={pieceColor ? "/pieces/wB.svg" : "/pieces/bB.svg"}
                onClick={() => onPromotionSelection(3)}
            />
            <img 
                className="w-full aspect-square bg-neutral-400 hover:bg-neutral-200" 
                src={pieceColor ? "/pieces/wN.svg" : "/pieces/bN.svg"}
                onClick={() => onPromotionSelection(2)}
            />
        </div>
    )
}