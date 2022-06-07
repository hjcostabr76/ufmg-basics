CC = g++
CFLAGS = -W -Wall -g -Wextra

main: obj/poker.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/poker obj/poker.o obj/game.o obj/debug.o

test_hands: obj/testHands.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/testHands obj/testHands.o obj/game.o obj/debug.o

test_plays: obj/testPlays.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/testPlays obj/testPlays.o obj/game.o obj/debug.o

test_rounds: obj/testRounds.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/testRounds obj/testRounds.o obj/game.o obj/debug.o

test_game: obj/testGame.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/testGame obj/testGame.o obj/game.o obj/debug.o

#################################################################################

obj/poker.o: src/main.cpp include/types.h include/game.h include/debug.h
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/poker.o

obj/debug.o: src/debug.cpp include/types.h include/debug.h
	$(CC) $(CFLAGS) -c src/debug.cpp -o obj/debug.o

obj/game.o: src/game.cpp include/types.h include/game.h include/debug.h
	$(CC) $(CFLAGS) -c src/game.cpp -o obj/game.o

#################################################################################

obj/testHands.o: test/testHands.cpp include/types.h include/game.h include/debug.h
	$(CC) $(CFLAGS) -c test/testHands.cpp -o obj/testHands.o

obj/testPlays.o: test/testPlays.cpp include/types.h include/game.h include/debug.h
	$(CC) $(CFLAGS) -c test/testPlays.cpp -o obj/testPlays.o

obj/testRounds.o: test/testRounds.cpp include/types.h include/game.h include/debug.h
	$(CC) $(CFLAGS) -c test/testRounds.cpp -o obj/testRounds.o

obj/testGame.o: test/testGame.cpp include/types.h include/game.h include/debug.h
	$(CC) $(CFLAGS) -c test/testGame.cpp -o obj/testGame.o

clean:
	rm -rf obj/* bin/*