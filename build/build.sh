#!/bin/bash

echo "starting build in $PWD"

# gcc "-ID:\Git Repositories\boiler-engine\vendor\SDL2\include" "-LD:\Git Repositories\boiler-engine\vendor\SDL2\lib" -g "D:\Git Repositories\boiler-engine\src\app.c" -o "D:\Git Repositories\boiler-engine\bin\app.exe" -lmingw32 -lSDL2main -lSDL2
gcc -I "$PWD\vendor\SDL2\include" -I "$PWD\vendor\SDL2_Image\include" -L "$PWD\vendor\SDL2\lib" -L "$PWD\vendor\SDL2_Image\lib" -g "$PWD\src\app.c" -o "$PWD\bin\app.exe" -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

pause
