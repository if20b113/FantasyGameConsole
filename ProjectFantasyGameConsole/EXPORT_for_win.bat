set TARGET=export\

copy build\src\Debug\FantasyGame.exe %TARGET%
copy external_deps\sdl2\SDL2.dll %TARGET%
copy external_deps\sdl2_ttf\SDL2_ttf.dll %TARGET%
copy external_deps\sdl2_image\lib\x64\SDL2_image.dll %TARGET%