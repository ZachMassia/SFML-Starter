#include "gameengine.h"

#include "introstate.h"
#include "menustate.h"
#include "playstate.h"

GameEngine::GameEngine(const std::string& title,
                       unsigned int width, unsigned int height,
                       unsigned int bpp,
                       bool _fullscreen)
    : resume(false),
      running(false),
      fullscreen(_fullscreen)
{
    int flags = 0;

    if (fullscreen) {
        flags = sf::Style::Fullscreen;
    } else {
        flags = sf::Style::Default;
    }

    // Create window
    screen.create(sf::VideoMode(width, height, bpp), title, flags);
    screen.setVerticalSyncEnabled(true);

    // Register quit action
    actionMap["quit"] = thor::Action(sf::Event::Closed);
    actionSystem.connect("quit", [&] (GameEngine::actionContext c) {
        quit();
    });

    // Common keys mapped for convenience
    actionMap["escape_key"]     = thor::Action(sf::Keyboard::Escape, thor::Action::PressOnce);
    actionMap["space_key"]      = thor::Action(sf::Keyboard::Space);
    actionMap["up_key"]         = thor::Action(sf::Keyboard::Up);
    actionMap["down_key"]       = thor::Action(sf::Keyboard::Down);
    actionMap["left_key"]       = thor::Action(sf::Keyboard::Left);
    actionMap["right_key"]      = thor::Action(sf::Keyboard::Right);
    actionMap["up_key_once"]    = thor::Action(sf::Keyboard::Up,    thor::Action::PressOnce);
    actionMap["down_key_once"]  = thor::Action(sf::Keyboard::Down,  thor::Action::PressOnce);
    actionMap["left_key_once"]  = thor::Action(sf::Keyboard::Left,  thor::Action::PressOnce);
    actionMap["right_key_once"] = thor::Action(sf::Keyboard::Right, thor::Action::PressOnce);

    currentTime = clock.getElapsedTime();
}

void GameEngine::run(std::unique_ptr<GameState> state)
{
    running = true;
    states.push(std::move(state));
}

void GameEngine::nextState()
{
    if (resume) {
        // Cleanup the current states
        if (!states.empty()) {
            states.pop();
        }
        // Resume previous state
        if (!states.empty()) {
            states.top()->resume();
        }
        resume = false;
    }

    // There needs to be a state
    if (!states.empty()) {
        std::unique_ptr<GameState> temp = states.top()->next();

        // Only change states if there's a next one existing
        if (temp != nullptr) {
            // Replace the running state
            if (temp->isReplacing()) {
                states.pop();
            } else {
                states.top()->pause();
            }
            states.push(std::move(temp));
        }
    }
}

void GameEngine::lastState()
{
    resume = true;
}

std::string GameEngine::currentStateID()
{
    return states.top()->stateID;
}

void GameEngine::update()
{
    if (!screen.isOpen()) {
        running = false;
    }

    // Update delta time
    previousTime = currentTime;
    currentTime  = clock.getElapsedTime();
    deltaTime    = currentTime - previousTime;

    // Update active actions
    actionMap.update(screen);
    // Call global callbacks
    actionMap.invokeCallbacks(actionSystem, &screen);
    // Call game state callbacks
    actionMap.invokeCallbacks(states.top()->actionSystem, &screen);

    states.top()->update(deltaTime);
}

void GameEngine::draw()
{
    states.top()->draw();
}

bool GameEngine::isRunning()
{
    return running && screen.isOpen();
}

void GameEngine::quit()
{
    screen.close();
    running = false;
}
