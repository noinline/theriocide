CXX ?= clang++
CXXFLAGS := -Og -fsanitize=address -fsanitize=undefined -std=c++17

SRCS := $(wildcard src/*.cpp)
HPPS := $(wildcard src/*.hpp)
OBJS := $(SRCS:src/%.cpp=o/%.o)
CFMT ?= clang-format
OUT := theriocide
CONV := convert

o/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $(CWD)$@ -c

theriocide:
	mkdir -p o/
	$(MAKE) compile

compile: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT)

format:
	$(CFMT) -i $(SRCS) $(HPPS)

convert:
	cd ./src/$(CONV)/ && $(MAKE)

clean:
	rm -rf ./o ./$(OUT)
	rm -rf ./$(CONV) ./*.jpg ./*.ppm

install: theriocide

.PHONY: theriocide compile format clean install
