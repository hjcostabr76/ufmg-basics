CC = g++
CFLAGS = -W -Wall -g -Wextra
FLAGS_DBG = ${FLAGS} -g -o0 -ggdb

# main: obj/utils_debug.o obj/utils_string.o obj/quick_sort.o obj/sorter.o src/main.cpp
# 	$(CC) $(CFLAGS) -o bin/lexicography obj/utils_debug.o obj/utils_string.o obj/quick_sort.o obj/sorter.o src/main.cpp

# main: obj/utils_debug.o obj/utils_string.o obj/sorter.o src/main.cpp
# 	$(CC) $(CFLAGS) -o bin/lexicography obj/utils_debug.o obj/utils_string.o obj/sorter.o src/main.cpp

main: src/main.cpp
	$(CC) $(CFLAGS) -o bin/lexicography src/main.cpp

# memcheck: obj/utils_debug.o obj/utils_string.o obj/quick_sort.o obj/sorter.o src/main.cpp
# 	$(CC) $(FLAGS_DBG) -o bin/memcheck_lexicography obj/utils_debug.o obj/utils_string.o obj/quick_sort.o obj/sorter.o src/main.cpp

memcheck: obj/utils_debug.o obj/utils_string.o obj/sorter.o src/main.cpp
	$(CC) $(FLAGS_DBG) -o bin/memcheck_lexicography src/main.cpp


#################################################################################

obj/quick_sort.o: include/quick_sort.h src/quick_sort.cpp
	$(CC) $(CFLAGS) -c src/quick_sort.cpp -o obj/quick_sort.o

obj/sorter.o: include/quick_sort.h src/sorter.cpp
	$(CC) $(CFLAGS) -c src/sorter.cpp -o obj/sorter.o

obj/utils_string.o: include/utils_debug.h include/utils_string.h src/utils_string.cpp
	$(CC) $(CFLAGS) -c src/utils_string.cpp -o obj/utils_string.o

obj/utils_debug.o: src/utils_debug.cpp include/utils_debug.h
	$(CC) $(CFLAGS) -c src/utils_debug.cpp -o obj/utils_debug.o

#################################################################################

clean:
	rm -rf obj/* bin/*
