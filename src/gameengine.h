#pragma once

#include <stack>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <Thor/Input.hpp>
#include <Thor/Resources.hpp>

#include "assetmanager.h"

class GameState;

class GameEngine
{
public:
    GameEngine(const std::string& title, unsigned width = 640, unsigned height = 480,
               unsigned bpp = 32, bool _fullscreen = false);

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

    // Global action map. This map is used for all states.
    thor::ActionMap<std::string> actionMap;

    // Global callback system. Non state-dependant actions should be connected to this object.
    // Each game state also defines it's own callback system which is called after the global
    // one.
    thor::ActionMap<std::string>::CallbackSystem actionSystem;

    // All callbacks must take the following as an argument.
    typedef thor::ActionContext<std::string> actionContext;

    // The main asset cache. It is capable of returning std::shared_ptr's to all SFML resource
    // types.
    thor::MultiResourceCache assets;

    // Maps for most used resource types.
    AssetManager<std::string, thor::ResourceKey<sf::Texture>>     textureKeys;
    AssetManager<std::string, thor::ResourceKey<sf::Font>>        fontKeys;
    AssetManager<std::string, thor::ResourceKey<sf::SoundBuffer>> soundBufferKeys;

    // Time related objects
    sf::Clock clock;
    sf::Time previousTime, currentTime, deltaTime;

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
