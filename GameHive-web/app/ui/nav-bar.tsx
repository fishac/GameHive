"use client";
import Link from "next/link";
import { usePathname } from "next/navigation";
import clsx from "clsx";

const links = [
  { name: "Home", href: "/" },
  { name: "Play", href: "/play" },
  // { name: "Leaderboards", href: "/leaderboards" },
];

export default function NavBar() {
  const pathname = usePathname();
  return (
    <div className="flex flex-row w-full py-2">
      {links.map((link) => {
        return (
          <Link
            className={clsx(
              "flex m-1 justify-center px-3 rounded border border-transparent hover:border hover:border-neutral-50 active:border-white text-2xl font-medium items-center",
              {
                "border-bottom border-b-neutral-50":
                  pathname === link.href ||
                  (link.href !== "/" && pathname.startsWith(link.href)),
              }
            )}
            href={link.href}
            key={link.name}
          >
            <p>{link.name}</p>
          </Link>
        );
      })}
    </div>
  );
}
