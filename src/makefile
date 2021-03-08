OBJS	= main.o
SOURCE	= main.cpp
CC	 = g++
FLAGS	 = -g -c -Wall

all: $(OBJS)
	$(CC) -std=c++0x -pthread -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) -std=c++0x -pthread $(FLAGS) main.cpp


clean:
	rm -f $(OBJS) $(OUT)