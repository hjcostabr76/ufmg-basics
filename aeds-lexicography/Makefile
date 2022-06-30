CC = g++
CFLAGS = -W -Wall -g -Wextra

main: obj/utils_debug.o obj/utils_string.o src/main.cpp
	$(CC) $(CFLAGS) -o bin/lexicography obj/utils_debug.o obj/utils_string.o src/main.cpp

#################################################################################

obj/utils_string.o: include/utils_debug.h include/utils_string.h src/utils_string.cpp
	$(CC) $(CFLAGS) -c src/utils_string.cpp -o obj/utils_string.o

obj/utils_debug.o: src/utils_debug.cpp include/utils_debug.h
	$(CC) $(CFLAGS) -c src/utils_debug.cpp -o obj/utils_debug.o

#################################################################################

clean:
	rm -rf obj/* bin/*