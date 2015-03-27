LIBS = `sdl-config --cflags` `sdl-config --libs` -lSDL_image -lSDL_mixer
TARGETS = CircleObject.o WorldObject.o Sprite.o Animation.o Sound.o
HEADERS = WorldObject.H Sprite.H Animation.H PlatformerException.H CircleObject.H Sound.H
OPTS = -Wall -ansi -pedantic

game: platformer.C ${TARGETS} PlatformerException.H
	g++ -o game platformer.C ${TARGETS} ${OPTS} ${LIBS}

CircleObject.o: CircleObject.C ${HEADERS}
	g++ -c CircleObject.C ${OPTS}

WorldObject.o: WorldObject.C ${HEADERS}
	g++ -c WorldObject.C ${OPTS}

Sprite.o: Sprite.C ${HEADERS} Animation.o
	g++ -c Sprite.C ${OPTS}

Animation.o: Animation.C ${HEADERS}
	g++ -c Animation.C  ${OPTS}

Sound.o: Sound.C ${HEADERS}
	g++ -c Sound.C ${OPTS}

run: game
	./game

clean:
	rm -f *.o *~ game test

