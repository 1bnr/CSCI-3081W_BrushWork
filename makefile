UNAME = $(shell uname)

CPP = g++

OPTS=-g
OPTS=-O0


INC_DIR = ../include

CPPFLAGS += $(OPTS) -Wall
CPPFLAGS += -I./ -I$(INC_DIR)

DEPS = base_gfx_app.h brushwork_app.h color_data.h pixel_buffer.h



CPPFILES += base_gfx_app.cc
CPPFILES += brushwork_app.cc
CPPFILES += color_data.cc
CPPFILES += main.cc
CPPFILES += pixel_buffer.cc

SOURCES=$(addprefix ./src/,  $(CPPFILES))

OBJECTS = $(addprefix ./build/,  $(CPPFILES:.cc=.o))

GLUI_LIB = ext/glui/lib/libglui.a


all: setup $(GLUI_LIB) 

setup: build lib

build: 
	mkdir -p bin
	mkdir -p build

$(GLUI_LIB):
	$(MAKE) -C ext/glui

build/%.o: src/%.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $<

.o:
	$(CXX) $(CPPFLAGS) -c $<

clean:
	\rm -rf bin
	\rm -rf ext/glui/build
	\rm -rf ext/glui/bin
	\rm -rf ext/glui/lib
	
