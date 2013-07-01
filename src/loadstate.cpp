#include "loadstate.h"

#include <memory>
#include <iostream>

#include "gameengine.h"
#include "introstate.h"

LoadState::LoadState(GameEngine &engine, bool replace)
    : GameState("load", engine, replace)
{
    using thor::Resources::fromFile;
    // Register resource keys with respective maps


    // Keys registered after this method call will not be cached
    cacheAllAssets();

    // Load intro state
    _next = engine.build<IntroState>(true);
}

void LoadState::cacheAllAssets()
{
    std::cout << "Loading:" << std::endl;

    std::cout << "  Textures" << std::endl;
    for (auto& keyMap : engine.textureKeys.map) {
        std::cout << "    " << keyMap.first << std::endl;
        engine.assets.acquire(keyMap.second);
    }

    std::cout << "  Sound Buffers"<< std::endl;
    for (auto& keyMap : engine.soundBufferKeys.map) {
        std::cout << "    " << keyMap.first << std::endl;
        engine.assets.acquire(keyMap.second);
    }

    std::cout << "  Fonts" << std::endl;
    for (auto& keyMap : engine.fontKeys.map) {
        std::cout << "    " << keyMap.first << std::endl;
        engine.assets.acquire(keyMap.second);
    }
}

void LoadState::pause()
{

}

void LoadState::resume()
{

}

void LoadState::update(const sf::Time &dt)
{

}

void LoadState::draw()
{
    engine.screen.clear();
    engine.screen.display();
}
