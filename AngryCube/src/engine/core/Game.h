#pragma once
#include "LevelManager.h"
#include "PlayerController.h"
#include "engine/render/Renderer.h"
#include "engine/utility/Clock.h"
#include "engine/utility/Timer.h"
#include "game/UI/GameplayHUD.h"


class Game
{
public:
    inline static std::unique_ptr<Clock> GameClock = nullptr;
    inline static std::unique_ptr<Timer> GameTimer = nullptr;
    inline static std::unique_ptr<Renderer> GameRenderer = nullptr;
    inline static std::unique_ptr<LevelManager> GameLevelManager = nullptr;
    inline static std::unique_ptr<PlayerController> GameController = nullptr;
    inline static std::unique_ptr<GameplayHUD> GameHUD = nullptr;

    static void OnLevelWin();
};
