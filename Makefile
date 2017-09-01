game: game.cpp texture.cpp ball.cpp texture_pack.cpp paddle.cpp collision.cpp
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer game.cpp  texture_pack.cpp texture.cpp \
		ball.cpp collision.cpp paddle.cpp font_renderer.cpp utilities.cpp -std=c++14 -o game

texture: texture.cpp texture.h
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf texture.cpp -c -std=c++14

ball: ball.cpp ball.h
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf ball.cpp -c -std=c++14

texture_pack: texture_pack.cpp texture_pack.h
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf texture_pack.cpp -c -std=c++14

collision: collision.cpp collision.h
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf collision.cpp -c -std=c++14

paddle: paddle.cpp paddle.h
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf paddle.cpp -c -std=c++14

font_renderer: font_renderer.cpp font_renderer.h
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf font_renderer.cpp -c -std=c++14

utilities: utilities.cpp utilities.h
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf utilities.cpp -c -std=c++14

clean:
	rm texture.o ball.o texture_pack.o collision.o paddle.o font_renderer.o utilities.o game