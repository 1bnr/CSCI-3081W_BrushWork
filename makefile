UNAME = $(shell uname)

CPP = g++

OPTS=-g
OPTS=-O0


INC_DIR = ../include

CPPFLAGS += $(OPTS) -W -Wall -Wextra -Weffc++ -std=c++11
CPPFLAGS += -I./ -I$(INC_DIR)

DEPS = base_gfx_app.h brushwork_app.h color_data.h pixel_buffer.h tool.h eraser.h pen.h calligraphy_pen.h
DEPS = $(addprefix $(INC_DIR), $(DEPS))

CPPFILES += base_gfx_app.cc
CPPFILES += brushwork_app.cc
CPPFILES += color_data.cc
CPPFILES += main.cc
CPPFILES += pixel_buffer.cc
CPPFILES += tool.cc
CPPFILES += eraser.cc
CPPFILES += pen.cc
CPPFILES += calligraphy_pen.cc


SOURCES=$(addprefix ./src/,  $(CPPFILES))

OBJECTS = $(addprefix ./build/,  $(CPPFILES:.cc=.o))

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
	mkdir -p GL
	cp ./ext/glui/include/GL/glui.h ./GL/glui.h

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
