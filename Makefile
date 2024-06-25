CXX ?= clang++
CXXFLAGS := -Og -fsanitize=address -fsanitize=undefined

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:src/%.cpp=o/%.o)

OUT := theriocide

o/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $(CWD)$@ -c

theriocide:
	mkdir -p o/
	$(MAKE) compile

compile: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT)

clean:
	rm -rf ./o $(OUT)
	rm -ff ./*.ppm

install: theriocide

.PHONY: theriocide compile clean install
