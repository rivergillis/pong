game: game.cpp texture.cpp ball.cpp texture_pack.cpp paddle.cpp collision.cpp
	g++ -Wall -lSDL2 -lSDL2_image -lSDL2_ttf game.cpp  texture_pack.cpp texture.cpp \
		ball.cpp collision.cpp paddle.cpp -std=c++14 -o game

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

clean:
	rm texture.o ball.o texture_pack.o collision.o game