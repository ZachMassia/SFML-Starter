#pragma once

#include "gamestate.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <memory>
#include <array>

#include "snake.h"

class GameEngine;

class PlayState : public GameState
{
public:
    PlayState(GameEngine& engine, bool replace = true);

    void pause();
    void resume();

    void update(const sf::Time &dt);
    void draw();

private:
    void initApples();
    void spawnApple();

    float cellSize;

    struct Apple {
        Apple() : alive(false) {}
        bool alive;
        sf::RectangleShape sprite;
    };

    std::array<Apple, 6> apples;

    Snake snake;

    sf::Clock clock;
    sf::Time lastAppleSpawn;
};
