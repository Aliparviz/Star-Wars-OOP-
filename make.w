CC=g++
OPT=-fno-elide-constructors
NAME=GetInput

MAIN_PROCEDURE_EXE : rsdl GetInput 
	$(CC) $(OPT) -o $(NAME)_exe rsdl.o GetInput.o 
	rm *.o
	clear
	./$(NAME)_exe

rsdl : rsdl.cpp rsdl.hpp 
	$(CC) $(OPT) -c rsdl.cpp -o rsdl.o

GetInput : GetInput.cpp Cartridge.hpp game.hpp rsdl.hpp 
	$(CC) $(OPT) -c GetInput.cpp -o GetInput.o

