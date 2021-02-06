# Prerequisites
```bash
sudo apt install libsdl2-dev
```

## Extensions
- **SDL-image**: is used to read png images.

```bash
sudo apt install libsdl2-image-dev
```
- **SDL-ttf**: is used to create textures from text.

```bash
sudo apt install libsdl2-ttf-dev
```
- **SDL-mixer**: is used to play sounds & music.

```bash
sudo apt install libsdl2-mixer-dev
```

- **SDL-gfx**: is used to draw a circle. Following links takes you to its [documentation][sdl-gfx-doc] and its [sourceforge page][sdl-gfx].

```bash
./autogen.sh
./configure
make
sudo make install
```

[sdl-gfx-doc]: https://www.ferzkopp.net/Software/SDL2_gfx/Docs/html/index.html
[sdl-gfx]: https://sourceforge.net/projects/sdl2gfx/files/

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
- [SDL2-image documentation][3].
- [SDL2-ttf documentation][4].
- [SDL2-mixer documentation][5].

[1]: https://lazyfoo.net/tutorials/SDL/
[2]: https://wiki.libsdl.org/CategoryAPI
[3]: https://www.libsdl.org/projects/SDL_image/docs/index.html
[4]: http://www.libsdl.org/projects/docs/SDL_ttf/SDL_ttf_toc.html
[5]: http://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_toc.html

# Assets
**Music**: [Menu Music][music] by [mrpoly][author-music], license: Public Domain.

[music]: https://opengameart.org/content/menu-music
[author-music]: https://opengameart.org/users/mrpoly
