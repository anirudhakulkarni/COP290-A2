build: main.cpp
	g++ -o game main.cpp mazegenerator.cpp select.cpp travel.cpp steiner_tsp.cpp `sdl2-config --cflags --libs` -lSDL2_ttf -lpthread -I. -Wall
	./game old
no:
	./game new