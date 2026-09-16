CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2
SRC = main.cpp
OUT = a.out
ARGS ?= 4

.PHONY: run clean

run: $(OUT)
	./$(OUT) $(ARGS)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	@rm -f $(OUT)
