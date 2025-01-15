#pragma once
#include <GLSLProgram.h>
#include <Window.h>
#include <Camera.h>
#include <SpriteBatch.h>
#include <InputManager.h>
#include <Timing.h>
#include <vector>

#include "Level.h"
#include "Player.h"
#include "Skybox.h"
#include "netPlayerManager.h"

//#include <message.pb.h>

enum class gameState {PLAY, EXIT};

class MainGame
{
public:
    MainGame();
    ~MainGame();

    void run();

private:
    void initSystems();
    void gameLoop();
    void processInput();
    void drawGame();
    void drawUi();
    void initShaders();

    Window _window;

    int _screenWidth;
    int _screenHeight;

    uint32_t _maxFPS;
    uint32_t _fps{};

    int _currentLevel{};

    float x = 35.264f;
    float y = -45.0f;

    gameState _gameState;

    GLSLProgram _shader;

    Camera _camera;

    Skybox _skybox;

    SpriteBatch _playerBatch;

    SpriteBatch _batch;

    InputManager _inputManager;

    FpsLimiter _fpsLimiter;

    std::vector<Level*> _level;

    std::vector<Entity*> _entity;

    Player* _player;

    NetworkManager _networkManager;

    netPlayerManager _netPlayerManager;

    RPC rpc;
};
