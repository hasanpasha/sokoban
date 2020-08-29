# Build mario sokoban game 

exec=sokoban
cc=gcc
libs=`pkg-config --libs sdl SDL_image`
cflags=`pkg-config --cflags sdl SDL_image`

${exec} : main.o game.o editor.o files.o
	${cc} -o ${exec} main.o game.o editor.o files.o ${libs} ${cflags}

main.o : main.c constants.h game.h editor.h files.h
	${cc} -c main.c 
game.o : game.c constants.h game.h files.h
	${cc} -c game.c 
editor.o : editor.c constants.h editor.h files.h
	${cc} -c editor.c 
files.o : files.c constants.h files.h
	${cc} -c files.c 

clean : 
	rm sokoban main.o game.o editor.o files.o