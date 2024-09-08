import HRule from '@/app/ui/hrule'
import ChessSettingsForm from '@/app/ui/chess/chess-settings-form';

export default function Page() {
  return (
    <div className="flex flex-col px-96 mt-8 justify-center">
      <p className="text-center text-2xl font-bold text-neutral-100">Chess Settings</p>
      <HRule />
      <ChessSettingsForm />
    </div>
  );
}