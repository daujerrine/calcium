# Calcium Makefile
# See COPYING for licensing details.

CC = gcc
CFLAGS = -Wall
LDFLAGS = -lm
EXEC = calcium

TEST_DIR = test/

OBJS = eval.o        \
       hashmap.o     \
       interpreter.o \
       main.o        \
       stack.o

TEST_OBJS = test_stack.o \
			test_hash.o

.PHONY: all install main clean test test-build

all: build test

install:
	$(error Not yet implemented)

test: build
	$(MAKE) -C $(TEST_DIR) test-build

build: $(OBJS)
	$(CC) $(LDFLAGS) $^ -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

test/%: build test/%.c 
	$(CC) $(CFLAGS) $^ -o $@ $(OBJS)

clean:
	rm *.o
	rm $(EXEC)
	rm test/*.o
