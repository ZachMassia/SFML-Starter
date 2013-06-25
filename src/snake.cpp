#include "snake.h"

Snake::Snake(const sf::Vector2u& _screenSize, float size) :
    snakeDiesOnEdgeCollision(true),
    newCellNeeded(false),
    screenSize(_screenSize),
    cellSize(size, size)
{
    body.push_front(getNewBodyPiece(sf::Vector2f(screenSize.x / 2,
                                                 screenSize.y / 2)));
    direction = Snake::DOWN;
    lastMove = clock.getElapsedTime();
}

void Snake::update(const sf::Time& dt)
{
    // Slow down the movement
    sf::Time now = clock.getElapsedTime();
    if (now - lastMove < sf::seconds(0.1)) {
        return;
    } else {
        lastMove = now;
    }

    advanceSnake();

    if (newCellNeeded) {
        // By not calling `pop_back()`, the snake grows by one.
        newCellNeeded = false;
    } else if (body.size()) {
        // Calling `pop_[front,back]()` on an empty container causes a
        // SEGFAULT, so make sure `body.size() > 0`.
        body.pop_back();
    }

    loopShapeAroundEdges(body.front());
}

void Snake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto& cell : body) {
        target.draw(cell, states);
    }
}

void Snake::grow()
{
    newCellNeeded = true;
}


bool Snake::isDead()
{
    // Did the head hit it's body
    bool headIsSafe = true;
    sf::FloatRect headRect = body.front().getGlobalBounds();

    std::deque<sf::RectangleShape>::size_type i = 1;
    for ( ; i < body.size(); ++i) {
        if (headRect.intersects(body.at(i).getGlobalBounds())) {
            headIsSafe = false;
        }
    }

    // TODO: Proper edge detection for right and bottom edge.
    if (snakeDiesOnEdgeCollision) {
        sf::Vector2f head = body.front().getPosition();
        return !(headIsSafe && head.x > 0 && head.y > 0);
    } else {
        return !headIsSafe;
    }
}

void Snake::advanceSnake()
{
    sf::Vector2f newHeadPos,
                 oldHeadPos = body.front().getPosition();

    float gap = 5.0f; // gap between each cell in pixels.

    switch (direction)
    {
    case UP:
        newHeadPos.x = oldHeadPos.x;
        newHeadPos.y = oldHeadPos.y - cellSize.y - gap;
        break;
    case DOWN:
        newHeadPos.x = oldHeadPos.x;
        newHeadPos.y = oldHeadPos.y + cellSize.y + gap;
        break;
    case LEFT:
        newHeadPos.x = oldHeadPos.x - cellSize.x - gap;
        newHeadPos.y = oldHeadPos.y;
        break;
    case RIGHT:
        newHeadPos.x = oldHeadPos.x + cellSize.x + gap;
        newHeadPos.y = oldHeadPos.y;
        break;
    }

    // Only the head of the snake should be red
    body.front().setFillColor(sf::Color::Blue);

    body.push_front(getNewBodyPiece(newHeadPos));
}

void Snake::loopShapeAroundEdges(sf::RectangleShape& shape)
{
    sf::Vector2f pos = shape.getPosition();
    sf::Vector2f size = shape.getSize();

    // Left edge to right edge
    if (pos.x < -size.x) {
        shape.setPosition(screenSize.x, pos.y);
    }
    // Right edge to left edge
    else if (pos.x > screenSize.x) {
        shape.setPosition(-size.x, pos.y);
    }

    // Top edge to bottom edge
    if (pos.y < -size.y) {
        shape.setPosition(pos.x, screenSize.y);
    }
    // Bottom edge to top edge
    else if (pos.y > screenSize.y) {
        shape.setPosition(pos.x, -size.y);
    }
}

sf::RectangleShape Snake::getNewBodyPiece(const sf::Vector2f& pos)
{
    sf::RectangleShape rect(cellSize);

    rect.setFillColor(sf::Color::Red);

    rect.setOutlineThickness(-1);
    rect.setOutlineColor(sf::Color::White);

    rect.setPosition(pos);

    return rect;
}
