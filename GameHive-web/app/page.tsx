import HRule from '@/app/ui/hrule';

export default function Page() {
  return (
    <div className="flex flex-col px-32 h-full w-full justify-left mt-2 text-md">
      <p className="text-2xl font-bold">
        Welcome
      </p>
      <HRule />
      <p>
        &emsp;Welcome to my site! Here you&apos;ll find a range of board games with engines (computer opponents) to play against that I created from scratch.
        The engines run directly in your browser, no setup required! 
      </p>
      <p>
        &emsp;Right now the only game available is Chess with more games in development. 
        I plan to add Hex Chess, discussed in <a href="https://youtu.be/bgR3yESAEVE?si=L_MA5DQ5n7kwHz0z" className="text-sky-500">
         this video 
        </a> by CGPGrey, and other games that interest me such as Connect Four, tic-tac-toe, or other games and variants of them.
      </p>
      <p>
        &emsp;See the GitHub page for this project <a href="https://github.com/fishac/GameHive" className="text-sky-500">here.</a>
      </p>
      <p className="text-2xl font-bold mt-8">
        Games and Engines
      </p>
      <HRule />
      <p>
        &emsp;I wrote the games and engines in C++. 
        Engine performance correlates with the speed at which it can scan through possible positions, so C++ was an obvious choice.
        The games and engines are then compiled into Web Assembly with Emscripten for use in the browser.
        Since the engines run in the browser, the more powerful your computer, the better the engines play!
      </p>
      <p className="text-lg font-bold mt-4">
        Chess
      </p>
      <HRule />
      <p>
        &emsp;I incorporated many ideas in the Chess engine&apos;s best-move-computing algorithms including negamax search, alpha-beta pruning, iterative deepening, quiescence search, bitboards, static exchange evaluation, null move pruning, late move pruning, search extensions, move prioritization, and transposition tables. 
      </p>
      <p>
        &emsp;I kept the evaluation function relatively simple, incorporating and considering piece weights, piece-square weight tables, piece mobility, king safety, isolated pawns, doubled pawns, passed pawns, early-endgame weight pairs, and king distance-to-edge.
      </p>
      <p>
        &emsp;When looking ahead in its attempt to compute the best move, the engine scans through up to 900 thousand positions per second, depending on the search&apos;s initial board state.
        This is a far cry from the top engines&apos; 75-150 million positions per second but a number I am proud of achieving through many rounds of optimization!
      </p>
      <p className="text-2xl font-bold mt-8">
        This Website
      </p>
      <HRule />
      <p>
        &emsp;I created this website using React with Next.js, Typescript, and Tailwind. I created all of the components myself, with the exception of using a dropdown component from Headless UI. 
        The games and engines use custom JavaScript and Web Assembly modules to benefit from the speed of code originally written in C++.
      </p>
      <p>
        &emsp;I plan on increasing the functionality of this site over time. Some ideas I have are:
      </p>
      <ul>
        <li>&emsp;&emsp;&#x2022; More games, as mentioned above.</li>
        <li>&emsp;&emsp;&#x2022; An arcade-style leaderboard with most, or most recent, games where a player beat the engine.</li>
        <li>&emsp;&emsp;&#x2022; Improved board interaction, including square-to-square arrow drawing, rewinding the view-state of the board, and flipping the board display vertically.</li>
        <li>&emsp;&emsp;&#x2022; Expanding the site to include player-versus-player games.</li>
      </ul>
      <p>
        &emsp;This website is hosted on Fly.io.
      </p>
    </div>
  );
}
