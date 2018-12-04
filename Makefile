CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: walk

walk: walk.cpp sergioB.cpp albertoA.cpp guadalupeN.cpp
	g++ $(CFLAGS) walk.cpp sergioB.cpp albertoA.cpp guadalupeN.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -obattle

clean:
	rm -f battle
	rm -f *.o

