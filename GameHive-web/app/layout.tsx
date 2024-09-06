import type { Metadata } from "next";
import { Inter } from "next/font/google";
import "./globals.css";
import NavBar from "@/app/ui/nav-bar"

const inter = Inter({ subsets: ["latin"] });

export const metadata: Metadata = {
  title: "GameHive",
  description: "A hive of boardgames and engines.",
};

export default function RootLayout({
  children,
}: Readonly<{
  children: React.ReactNode;
}>) {
  return (
    <html lang="en">
      <body className={`${inter.className} text-slate-300 antialiased flex min-h-screen flex-col p-3 bg-gradient-to-b from-neutral-900 to-neutral-800`}>
      <NavBar />
      {children}
      </body>
    </html>
  );
}
