UNAME = $(shell uname)

CPP = g++

OPTS=-g
OPTS=-O0

CPPFLAGS += $(OPTS) -W -Wall -Wextra -Weffc++ -std=c++11
CPPFLAGS += -I./ -I./ext/glui/include/

DEPS = $(wildcard ./include/*.h)

SOURCES=$(wildcard ./src/*.cc)
SOURCE_NAMES =  $(notdir $(SOURCES))
OBJECTS = $(addprefix ./build/,$(SOURCE_NAMES:.cc=.o))

GLUI_LIB = ext/glui/lib/libglui.a

MAIN = bin/BrushWork

ifeq ($(UNAME), Darwin)
        LIBS += -framework glut -framework opengl
else
        LIBS += -lglut -lGL -lGLU
endif


all: setup $(GLUI_LIB) $(OBJECTS) bin/BrushWork

setup: build

build:
	mkdir -p bin
	mkdir -p build

$(GLUI_LIB):
	$(MAKE) -C ext/glui

build/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.o:
	$(CXX) $(CPPFLAGS) -c $<


$(MAIN): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS)  $(LIBS) $(GLUI_LIB) -o $(MAIN)

clean:
	\rm -rf bin
	\rm -rf build
	\rm -rf GL
	\rm -rf ext/glui/build
	\rm -rf ext/glui/bin
	\rm -rf ext/glui/lib
