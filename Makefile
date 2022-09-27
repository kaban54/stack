CFLAGS += -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -D_DEBUG -D_EJUDGE_CLIENT_SIDE
CC = g++

all: stack.exe


stack.exe: main.o stack.o
	$(CC) -o stack.exe main.o stack.o $(CFLAGS) -DCAN -DHASH

main.o: main.cpp 
	$(CC) -o main.o main.cpp -c $(CFLAGS) -DCAN -DHASH

stack.o: stack.cpp 
	$(CC) -o stack.o stack.cpp -c $(CFLAGS) -DCAN -DHASH

clean:
	rm *.o
	clear
	
.PHONY: clean
