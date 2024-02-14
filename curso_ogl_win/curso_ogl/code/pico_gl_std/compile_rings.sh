
g++ -c -g -Wall -O0 -o /tmp/pico_gl.o pico_gl.cpp
g++ -c -g -Wall -O0 -o /tmp/raster.o raster.cpp
g++ -c -g -Wall -O0 -o /tmp/example_rings.o example_rings.cpp

g++ -o test.elf /tmp/pico_gl.o /tmp/raster.o /tmp/example_rings.o -lSDL -lm 
