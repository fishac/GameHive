import Link from 'next/link';
import HRule from '@/app/ui/hrule';

interface Igame {
  name: string,
  image: string,
  alt: string,
  enabled: boolean,
  href: string
}

const games: Igame[] = [
  {
    name: "Chess",
    image: "/knight.svg",
    alt: "Chess Game Icon",
    enabled: true,
    href: "/play/chess"
  },
  {
    name: "Hex Chess",
    image: "/hexagonknight.svg",
    alt: "Hex Chess Game Icon",
    enabled: false,
    href: "/play/hexchess"
  }
]

export default function Page() {
  return (
    <div className="flex flex-col px-96 mt-8 justify-center">
      <p className="text-center text-2xl font-bold">
        Select a game
      </p>
      <HRule />
      <div className="flex flex-wrap justify-center">
        {games.map(game => {
          return (
            game.enabled ?
            <Link key={game.name} href={game.href} className="w-32 h-32 m-2 rounded-2xl bg-gradient-to-b from-gray-200 to-gray-400 hover:from-gray-300 hover:to-gray-500 active:from-gray-400 active:to-gray-600">
              <img src={game.image} alt={game.alt} />
            </Link>
            : <div key={game.name} className="w-32 h-32 m-2 rounded-2xl bg-gradient-to-b from-gray-200 to-gray-400 opacity-50 cursor-default">
              <img src={game.image} alt={game.alt} />
            </div>
          )
        })}
      </div>
    </div>
  );
}