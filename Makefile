SOURCES=$(shell find src -name '*.cpp')
OBJS=$(SOURCES:src/%.cpp=build/%.o)
LIBS=$(shell pkg-config --static --libs x11 xrandr xi xxf86vm glew glfw3)
TARGET=bump
CPPFLAGS=-std=c++11 -Werror -g -Isrc -DENABLE_LOG
TEST_SOURCES=$(shell find test/src -name '*.cpp')
TEST_OBJS=$(TEST_SOURCES:test/src/%.cpp=test/build/%.o)
TEST_LIBS=-lgtest -lgtest_main
TEST_TARGET=test/build/test
TEST_CPPFLAGS=-std=c++11 -Werror -g -Isrc -Itest/src -DENABLE_LOG

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
	cd res; \
	./run.sh

test/build/%.o: test/src/%.cpp
	g++ $(TEST_CPPFLAGS) -c -o $@ $<

build_test: check_test_dir $(TEST_OBJS)
	g++ $(TEST_CPPFLAGS) -o $(TEST_TARGET) $(TEST_OBJS) $(TEST_LIBS)

check_test_dir:
	if [ ! -d "test/build" ]; then \
		mkdir test/build; \
	fi

clean_test:
	rm -f test/build/*

run_test:
	test/build/test

