CC=g++
VCORE_INC:= -I../Vixen/include/ -I../Vixen/include/vcore/ -I/usr/include/ -I/usr/local/include/
VCORE_SRC:= $(wildcard ../Vixen/source/vcore/*.cpp)
VCORE_LIB:= -L/usr/lib64/
VGRAPHICS_INC:= -I../Vixen/include/ -I../Vixen/include/vcore/ -I../Vixen/include/vgraphics/ -I/usr/include/ -I/usr/local/include
VGRAPHICS_SRC:= $(wildcard ../Vixen/source/vgraphics/*.cpp)
VGRAPHICS_LIB:= -L/usr/lib64/
VGAME_INC:= -I../Vixen/include/ -I../Vixen/include/vcore/ -I../Vixen/include/vgraphics/ -I../Vixen/include/vgame/ -I/usr/include/ -I/usr/local/include/
VGAME_SRC:= $(wildcard ../Vixen/source/vgame/*.cpp)
VGAME_LIB:= -L/usr/lib64/
VTEST_INC:= -I../Vixen/include/ -I../Vixen/include/vcore/ -I../Vixen/include/vgraphics/ -I../Vixen/include/vgame/ -I/usr/include/ -I/usr/local/include/
VTEST_SRC:= main.cpp
VTEST_LIB:= -L/usr/lib64/nvidia-bumblebee/tls -L/usr/lib64/nvidia-bumblebee  -L/usr/lib64  -L/usr/local/lib -lvgame -lvgraphics -lvcore -lSDL2 -lGLEW -lGL -lGLU -lfreeimage -larchive -ltinyxml2
FLAGS= -std=c++11 -Wall -w -shared -fPIC
TFLAGS= -std=c++11 -Wall -w -g
OUTDIR:= /usr/local/lib/

all: vcore vgraphics vgame

vcore:
	$(CC) $(FLAGS) $(VCORE_INC) $(VCORE_SRC) $(VCORE_LIB) -o $(OUTDIR)libvcore.so

vgraphics:
	$(CC) $(FLAGS) $(VGRAPHICS_INC) $(VGRAPHICS_SRC) $(VGRAPHICS_LIB) -o $(OUTDIR)libvgraphics.so

vgame:
	$(CC) $(FLAGS) $(VGAME_INC) $(VGAME_SRC) $(VGAME_LIB) -o $(OUTDIR)libvgame.so

vtest:
	$(CC) $(TFLAGS) $(VTEST_INC) $(VTEST_SRC) $(VTEST_LIB) -o vtest

clean:
	rm vtest
