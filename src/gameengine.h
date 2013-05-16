#pragma once

#include <stack>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>

class GameState;

class GameEngine
{
public:
    GameEngine(const std::string& title, unsigned width = 640,
               unsigned height = 480, unsigned bpp = 32,
               bool _fullscreen = false);

    void run(std::unique_ptr<GameState> state);

    void nextState();
    void lastState();
    std::string currentStateID();

    void update();
    void draw();

    bool isRunning();
    void quit();

    template <typename T>
    std::unique_ptr<T> build(bool replace = true);

    sf::RenderWindow screen;

    thor::ActionMap<std::string> actionMap;
    thor::ActionMap<std::string>::CallbackSystem actionSystem; // global callbacks
    typedef thor::ActionContext<std::string> actionContext;

private:
    std::stack<std::unique_ptr<GameState>> states;
    bool resume;
    bool running;
    bool fullscreen;
};

// -- Template Methods -- //

template <typename T>
std::unique_ptr<T> GameEngine::build(bool replace)
{
    return std::move(std::unique_ptr<T>(new T(*this, replace)));
}
