#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <vector>
#include <deque>
#include <iostream>

class Snake : public sf::Drawable
{
public:
    Snake(const sf::Vector2u& _screenSize, float cellSize);

    void update(const sf::Time& dt);

    virtual void draw(sf::RenderTarget& target,
                      sf::RenderStates states = sf::RenderStates::Default) const;

    void grow();
    bool isDead();

    enum directions { UP, DOWN, LEFT, RIGHT } direction;

    bool snakeDiesOnEdgeCollision;

private:
    /* -- Methods -- */
    void advanceSnake();
    void loopShapeAroundEdges(sf::RectangleShape& shape);

    sf::RectangleShape getNewBodyPiece(const sf::Vector2f& pos = sf::Vector2f());


    /* -- Variables -- */

    std::deque<sf::RectangleShape> body;

    bool newCellNeeded;

    sf::Clock clock;
    sf::Time lastMove;

    sf::Vector2f cellSize;
    sf::Vector2u screenSize;
};
