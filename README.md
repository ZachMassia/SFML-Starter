SFML-Starter
============

A starting point for SFML projects.

Loosly based on eXpl0it3r's [Small Game Engine][sge-git].

An example game can be viewed in the [snake][snake-branch] branch.

###Dependencies
Built against the latest versions of [SFML][sfml-git] and [Thor][thor-git].

Requires [CMake][cmake-home] to build (or import it into your IDE of choice).


Setup
-----
Clone it
```
git clone git://github.com/ZachMassia/SFML-Starter.git
cd SFML-Starter
```

Make a build directory
```
mkdir build && cd build
cmake ..
```

Compile and run
```
make && ./sfml_starter
```

[cmake-home]: http://www.cmake.org/
[sfml-git]: http://github.com/LaurentGomila/SFML
[thor-git]: http://github.com/Bromeon/Thor
[sge-git]: https://github.com/eXpl0it3r/SmallGameEngine
[snake-branch]: https://github.com/ZachMassia/SFML-Starter/tree/snake
