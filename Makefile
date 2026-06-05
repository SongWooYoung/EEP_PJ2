CC = clang++
CFLAGS = -std=c++14 -Wall -Wextra -O2

P1_SRC = 20250000_PJT2_P1.cpp
P2_SRC = 20250000_PJT2_P2.cpp

.PHONY: all clean

all: P1 P2

P1: $(P1_SRC)
	$(CC) $(CFLAGS) -o $@ $<

P2: $(P2_SRC)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f P1 P2
