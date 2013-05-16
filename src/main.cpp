#include <iostream>
#include <exception>

#include "gameengine.h"
#include "introstate.h"

int main(int argc, char* argv[])
{
    try {
        std::cout << "Initializing engine" << std::endl;

        GameEngine engine("Window Title");
        engine.run(engine.build<IntroState>(true));

        while (engine.isRunning()) {
            engine.nextState();
            engine.update();
            engine.draw();
        }

        std::cout << "Shutting down.." << std::endl;
    } catch (std::exception& e) {
        std::cerr << "An error occured:\n\t" << e.what() << std::endl;
    } catch (...) {
        std::cerr << "An unexpected error occured." << std::endl;
    }
}
