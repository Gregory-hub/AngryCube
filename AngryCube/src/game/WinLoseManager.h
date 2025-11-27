#pragma once

class WinLoseManager
{
private:
   enum class WinStatus
   {
      None,
      WinLevel,
      LoseLevel,
      WinGame
   };

private:
   inline static WinStatus status = WinStatus::None;

public:
   static void OnLevelWin();
   static void OnLevelLoose();
   static void OnGameWin();

   static void Reset();
};
