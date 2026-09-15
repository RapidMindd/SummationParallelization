CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2
SRC = main.cpp
OUT = a.out

run: $(OUT)
	./$(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	@rm -f $(OUT)
