#pragma once
#include <SDL2/SDL.h>
#include <string>

enum WindowFlags {INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x4};

class Window {
public:
    Window();
    ~Window();

    int create(const std::string& windowName, int screenWidth, int screenHeight, unsigned int currentFlags);

    [[nodiscard]] int getScreenWidth() const { return _screenWidth; };
    [[nodiscard]] int getScreenHeight() const { return _screenHeight; };

    void swapBuffer() const;

    [[nodiscard]] SDL_Window* getWindow() const { return _sdlWindow; };
    SDL_GLContext* getContext() { return &_glContext; };

private:
    SDL_Window* _sdlWindow;
    SDL_GLContext _glContext{};
    int _screenWidth, _screenHeight;
};
