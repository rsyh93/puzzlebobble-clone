debug:
	g++ -ggdb -o puzzlebobble-clone_d *.cpp `sdl-config --libs` -lSDL_image -lSDL_gfx -lm

puzzlebobble-clone: ball.o gamestate.o gamestatemenu.o gamestategame.o
	g++ -ggdb -o puzzlebobble-clone main.cpp $^ `sdl-config --libs` -lSDL_image -lSDL_gfx -lm

.c.o:
	g++ -c -o $@ $<

clean:
	rm -f puzzlebobble-clone *.o
