CC = g++
SDLLIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
RELEASE = -c -O3 
DEBUG = -c -g -D_DEBUG
CSTD = -std=c++14
CFLAGS = -Wall $(DEBUG) $(CSTD)

game: game.o texture_pack.o texture.o ball.o collision.o paddle.o font_renderer.o utilities.o font.o
	$(CC) $(SDLLIBS) game.o texture_pack.o texture.o ball.o collision.o paddle.o font_renderer.o utilities.o font.o -o game

game.o: game.cpp
	$(CC) $(CFLAGS) game.cpp

texture.o: texture.cpp texture.h
	$(CC) $(CFLAGS) texture.cpp

font.o: font.cpp font.h
	$(CC) $(CFLAGS) font.cpp

ball.o: ball.cpp ball.h
	$(CC) $(CFLAGS) ball.cpp

texture_pack.o: texture_pack.cpp texture_pack.h
	$(CC) $(CFLAGS) texture_pack.cpp

collision.o: collision.cpp collision.h
	$(CC) $(CFLAGS) collision.cpp

paddle.o: paddle.cpp paddle.h
	$(CC) $(CFLAGS) paddle.cpp

font_renderer.o: font_renderer.cpp font_renderer.h
	$(CC) $(CFLAGS) font_renderer.cpp

utilities.o: utilities.cpp utilities.h
	$(CC) $(CFLAGS) utilities.cpp

clean:
	rm *.o game