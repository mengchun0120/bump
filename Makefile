SOURCES=$(shell find src -name '*.cpp')
OBJS=$(SOURCES:src/%.cpp=build/%.o)
LIBS=$(shell pkg-config --static --libs x11 xrandr xi xxf86vm glew glfw3)
TARGET=bump
CPPFLAGS=-std=c++11 -Werror -g -Isrc -DENABLE_LOG

.PHONY: build

default: build

build/%.o: src/%.cpp
	g++ $(CPPFLAGS) -c -o $@ $<

build: check_dir $(OBJS)
	g++ $(CPPFLAGS) -o build/$(TARGET) $(OBJS) $(LIBS)

check_dir:
	if [ ! -d "build" ]; then \
		mkdir build; \
	fi

clean:
	rm -f build/*

run:
	cd scripts; \
	./run.sh
