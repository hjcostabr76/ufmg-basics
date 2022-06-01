CC = g++
CFLAGS = -W -Wall -g -Wextra

main: obj/poker.o obj/game.o obj/debug.o
	$(CC) $(CFLAGS) -o bin/poker obj/poker.o obj/game.o obj/debug.o
 
obj/poker.o: src/main.cpp include/game.h include/debug.h
	$(CC) $(CFLAGS) -c src/main.cpp -o obj/poker.o

obj/debug.o: include/game.h include/debug.h
	$(CC) $(CFLAGS) -c src/debug.cpp -o obj/debug.o

obj/game.o: include/game.h include/debug.h
	$(CC) $(CFLAGS) -c src/game.cpp -o obj/game.o

clean:
	rm -rf obj/* bin/*