CC = g++
CFLAGS = -W -Wall -g -Wextra

main: obj/poker.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/poker obj/poker.o obj/game.o obj/debug.o

test_hands: obj/testHands.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/testHands obj/testHands.o obj/game.o obj/debug.o

test_input: obj/testInput.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/testInput obj/testInput.o obj/game.o obj/debug.o

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

obj/testInput.o: test/testInput.cpp include/types.h include/game.h include/debug.h
	$(CC) $(CFLAGS) -c test/testInput.cpp -o obj/testInput.o

clean:
	rm -rf obj/* bin/*