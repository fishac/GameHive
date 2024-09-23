import { TPiece } from "./piece";

export type TPiece = 0|1|2|3|4|5|6;
export function getPieceFilename(piece: TPiece, pieceColor: boolean): string {
  if (piece > 0) {
    const colorString = pieceColor ? "w" : "b";
    let pieceString;
    if (piece == 1) {
      pieceString = "P";
    } else if (piece == 2) {
      pieceString = "N";
    } else if (piece == 3) {
      pieceString = "B";
    } else if (piece == 4) {
      pieceString = "R";
    } else if (piece == 5) {
      pieceString = "Q";
    } else {
      pieceString = "K";
    }
    return colorString + pieceString;
  } else {
    return "";
  }
}
