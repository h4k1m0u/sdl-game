# Prerequisites
```bash
sudo apt install libsdl2-dev
```

# Build with g++
```bash
g++ game.cpp -lSDL2  -o game
```

# Build with CMake
```bash
mkdir build && cd build
cmake ..
make
```

# Resources
- [Tutorials from LazyFoo][1].
- [SDL2 API documentation][2].

[1]: https://lazyfoo.net/tutorials/SDL/
[2]: https://wiki.libsdl.org/CategoryAPI
