CXX ?= clang++
CXXFLAGS := -Og -fsanitize=address -fsanitize=undefined -std=c++17

SRCS := $(wildcard *.cpp)
HPPS := $(wildcard *.hpp)
OBJS := $(SRCS:%.cpp=o/%.o)
CFMT ?= clang-format
OUT := convert

o/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $(CWD)$@ -c

convert:
	mkdir -p o/
	$(MAKE) compile
	mv $(OUT) ../../

compile: $(OBJS)
	$(CXX) $(OBJS) $(CXXFLAGS) -o $(OUT)

format:
	$(CFMT) -i $(SRCS) $(HPPS)

clean:
	rm -rf ./o

install: convert

.PHONY: convert compile format clean install
