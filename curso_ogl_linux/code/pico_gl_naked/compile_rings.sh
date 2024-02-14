
g++ -c -g -Wall -O0 -o /tmp/pico_gl.o pico_gl.cpp
g++ -c -g -Wall -O0 -o /tmp/raster.o raster.cpp
g++ -c -g -Wall -O0 -o /tmp/rings.o rings.cpp

g++ -o rings.elf /tmp/pico_gl.o /tmp/raster.o /tmp/rings.o -lSDL -lm 
