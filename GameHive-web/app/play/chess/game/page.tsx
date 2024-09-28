import HRule from "@/app/ui/hrule";
import ChessPage from "@/app/ui/chess/game/chess-page";
import Link from "next/link";

function areParamsValid(searchParams: any): boolean {
  return (
    searchParams &&
    ["1", "0"].includes(searchParams.white) &&
    ["0", "1", "2", "3", "4", "5", "6"].includes(searchParams.timeControl)
  );
}

export default function Page({
  searchParams,
}: {
  searchParams: { [key: string]: string | string[] | undefined };
}) {
  const validParams = areParamsValid(searchParams);
  if (validParams) {
    return <ChessPage />;
  } else {
    return (
      <div className="flex flex-col px-96 mt-8 justify-center">
        <p className="text-center text-2xl font-bold text-neutral-100">
          Invalid Chess Settings
        </p>
        <HRule />
        <p>
          The settings in the URL are invalid. Click{" "}
          <Link href="/play/chess" className="font-bold hover:underline">
            here
          </Link>{" "}
          to go back to the settings page.
        </p>
      </div>
    );
  }
}
