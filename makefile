a.out: GetInput.o rsdl.o
	g++ GetInput.o rsdl.o -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer -o a.out

GetInput.o : GetInput.cpp game.hpp Cartridge.hpp
	g++ -c GetInput.cpp game.hpp Cartridge.hpp 

rsdl.o : rsdl.cpp
	g++ -c rsdl.cpp	


