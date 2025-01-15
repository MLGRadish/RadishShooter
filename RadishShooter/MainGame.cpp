#include "MainGame.h"
#include "Entity.h"
#include <ResourceManager.h>

#include "../ImGui/imgui.h"
#include "GLTexture.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/trigonometric.hpp>

#include "SaltedRadish.h"

MainGame::MainGame(): _screenWidth(1024),
                      _screenHeight(768),
                      _maxFPS(144.0f),
                      _gameState(gameState::PLAY),
                      _player(nullptr) {}

MainGame::~MainGame()
{
    for (const auto & i : _level)
    {
        delete i;
    }

    for (const auto & i : _entity)
    {
        delete i;
    }

    //_networkManager.clean();
}

void MainGame::run()
{
    initSystems();

    gameLoop();
}

void MainGame::initSystems()
{
    init();

    // create window
    _window.create("Salted Radish v0.3 [Phoenix]", _screenWidth, _screenHeight, 0);

    // load level
    _level.push_back(new Level("Resources/Levels/level.rds"));
    _currentLevel = 0;

    initShaders();

    _skybox.init();

    _playerBatch.init();

    _batch.init();

    _camera.init(_screenWidth, _screenHeight, _shader);

    /* setup stuff required for the game */
    _player = new Player;
    _player->init(0.5f, _level[_currentLevel]);
    _entity.push_back(_player);

    _networkManager.connect("localhost", 6702);

    _netPlayerManager.init(&_entity);

    _fpsLimiter.init(_maxFPS);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO &io = ImGui::GetIO();

    ImGui_ImplSDL2_InitForOpenGL(_window.getWindow(), _window.getContext());
    ImGui_ImplOpenGL3_Init();

    ImGui::StyleColorsDark();
}

void MainGame::initShaders()
{
    _shader.compileShaders("Resources/Shaders/test_vs.glsl", "Resources/Shaders/test_fs.glsl");
    _shader.linkShader();
}

void MainGame::gameLoop()
{
    while (_gameState != gameState::EXIT)
    {
        _fpsLimiter.begin();

        drawUi();

        processInput();

        drawGame();

        _player->update(_inputManager, _networkManager);

        _networkManager.process(rpc);

        //_netPlayerManager.update(_networkManager);

        _fps = _fpsLimiter.end();
    }

    _networkManager.disconnect();
}

void MainGame::processInput()
{
    SDL_Event evnt;

    while (SDL_PollEvent(&evnt))
    {
        switch (evnt.type)
        {
            case SDL_QUIT:
                _gameState = gameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                _inputManager.onMouseMove(glm::vec2(evnt.motion.x, evnt.motion.y));
                break;
            case SDL_KEYDOWN:
                _inputManager.onKeyPress(evnt.key.keysym.sym);
                break;
            case SDL_KEYUP:
                _inputManager.onKeyRelease(evnt.key.keysym.sym);
                break;
            default:
                break;
        }
    }
}

void MainGame::drawUi()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(_window.getWindow());
    ImGui::NewFrame();

    ImGui::SetNextWindowSize(ImVec2(200, 150));
    ImGui::SetNextWindowPos(ImVec2(5, 5));
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);
    ImGui::Begin("Account", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
        ImGui::Text("Name: {name}");
    const GLuint texture = ResourceManager::getTexture("Resources/Textures/qr.png").id;
        ImGui::Image(reinterpret_cast<void *>(static_cast<intptr_t>(texture)), ImVec2(64, 64));
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(100, 150));
    ImGui::SetNextWindowPos(ImVec2(200+15, 5));
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);
    ImGui::Begin("Player", nullptr, ImGuiWindowFlags_NoResize);
        ImGui::Text("Id: %i", _player->getId());
        ImGui::Text("Health: %i", _player->getHealth());
    ImGui::End();

    ImGui::Begin("Debug");
        ImGui::Text("FPS: %f", _fps);
        ImGui::Text("Mouse: %f %f", _inputManager.mousePosition.x, _inputManager.mousePosition.y);
        ImGui::Text("Player: %f %f", _player->getPosition().x, _player->getPosition().z);
        ImGui::Text("Heading: %i", Player::getHeading(_inputManager));
        ImGui::SliderFloat("X", &x, -180, 180);
        ImGui::SliderFloat("Y", &y, -180, 180);
    ImGui::End();
}

void MainGame::drawGame()
{
    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _skybox.draw(_camera.getViewMatrix(), _camera.getProjectionMatrix());

    glUseProgram(_shader.getProgramId());

    constexpr glm::vec3 off(50, 100, 50);
    _camera.update(_player->getPosition(), off, x, y);

    _level[_currentLevel]->draw();

    _playerBatch.clean();
    for(const Entity* ent : _entity) {
        ent->draw(_playerBatch);
    }

    glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramId(), "model"), 1, GL_FALSE,
        glm::value_ptr(glm::mat4(1.0f)));

    _batch.clean();
    _batch.createBatch();
    _batch.renderBatch();

    _playerBatch.createBatch();

    auto asd = glm::mat4(1.0f);
    asd = glm::translate(asd, _player->getPosition()+glm::vec3(0.0f, 45.0f/2.0f, 0.0f));
    asd = glm::rotate(asd, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    asd = glm::rotate(asd, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    asd = glm::rotate(asd, glm::radians(static_cast<float>(Player::getHeading(_inputManager))),
        glm::vec3(0.0f, 0.0f, 1.0f));
    asd = glm::translate(asd, -_player->getPosition());
    glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramId(), "model"), 1, GL_FALSE,
        glm::value_ptr(asd));
    _playerBatch.renderBatch();

    // draw ui
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    _window.swapBuffer();
}
