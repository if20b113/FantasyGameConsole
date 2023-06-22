set TARGET=export\

copy build\game\Debug\FantasyGame.exe %TARGET%
copy build\engine\Debug\FantasyGameEngine.dll %TARGET%
copy external_deps\sdl2\SDL2.dll %TARGET%
copy external_deps\sdl2_ttf\SDL2_ttf.dll %TARGET%
copy external_deps\sdl2_image\lib\x64\SDL2_image.dll %TARGET%