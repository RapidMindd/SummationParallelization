CXX = g++
CXXFLAGS = -std=c++20 -Wall -O2
SRC = main.cpp
OUT = a.out
ARGS ?= 4

THREADS ?= 1 2 4 8 16 32 64 128 256 512 1024
RUNS ?= 5

.PHONY: run bench clean

run: $(OUT)
	./$(OUT) $(ARGS)

bench: $(OUT)
	@echo "threads sum_ms total_ms"
	@for t in $(THREADS); do \
		for r in $$(seq $(RUNS)); do ./$(OUT) $$t; done | sort -n | \
		awk -v t=$$t '{s[n]=$$1; o[n]=$$2; n++} END {m=int((n-1)/2); printf "%7s %6s %8s\n", t, s[m], o[m]}'; \
	done

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

clean:
	@rm -f $(OUT)
