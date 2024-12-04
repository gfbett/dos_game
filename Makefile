game: game.exe

FLAGS = -c -mh -G -2 -O -l -v -nD:\GAME\BUILD 
INCLUDES = -ID:\TURBOC3\INCLUDE -I.
SOURCE = main.cpp video.cpp log.cpp keyb.cpp
OBJS = BUILD\main.obj BUILD\video.obj BUILD\log.obj BUILD\keyb.obj

game.exe:
	tcc $(FLAGS) $(INCLUDES) $(SOURCE ) 
	tlink /3 -LD:\TURBOC3\LIB C0h $(OBJS ) ,OUT\game.exe,,FP87 mathh ch 

clean:
	del OUT\game.exe
	del BUILD*.obj
