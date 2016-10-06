UNAME = $(shell uname)

CPP = g++

OPTS=-g
OPTS=-O0


INC_DIR = ../include

CPPFLAGS += $(OPTS) -W -Wall -Wextra -Weffc++ -std=c++11
CPPFLAGS += -I./ -I$(INC_DIR)

DEPS = $(INC_DIR)/base_gfx_app.h $(INC_DIR)/brushwork_app.h $(INC_DIR)/color_data.h $(INC_DIR)/pixel_buffer.h 

CPPFILES += base_gfx_app.cc
CPPFILES += brushwork_app.cc
CPPFILES += color_data.cc
CPPFILES += main.cc
CPPFILES += pixel_buffer.cc

SOURCES=$(addprefix ./src/,  $(CPPFILES))

OBJECTS = $(addprefix ./build/,  $(CPPFILES:.cc=.o))

GLUI_LIB = ext/glui/lib/libglui.a


all: setup $(GLUI_LIB) $(OBJECTS) bin/BrushWork

setup: build

build: 
	mkdir -p bin
	mkdir -p build

$(GLUI_LIB):
	$(MAKE) -C ext/glui
	mkdir -p GL
	cp ./ext/glui/include/GL/glui.h ./GL/glui.h

build/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.o:
	$(CXX) $(CPPFLAGS) -c $<

bin/BrushWork: $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(OBJECTS) -o bin/BrushWork

clean:
	\rm -rf bin
	\rm -rf build
	\rm -rf GL
	\rm -rf ext/glui/build
	\rm -rf ext/glui/bin
	\rm -rf ext/glui/lib
	
