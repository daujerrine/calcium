# Calcium Makefile
# See COPYING for licensing details.

CC      := gcc
CFLAGS  := -Wall
LDFLAGS := -lm

TEST_DIR := test/

OBJS := eval.o        \
        hashmap.o     \
        interpreter.o \
        main.o        \
        stack.o

INTERPRETER_EXEC = calcium

TEST_OBJS := test_stack.o \
             test_hash.o

.PHONY: all clean build-interpreter

all: $(INTERPRETER_EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

test/%: build test/%.c 
	$(CC) $(CFLAGS) $^ -o $@ $(OBJS)

clean:
	rm *.o
	rm $(INTERPRETER_EXEC)
	rm test/*.o

build-interpreter: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(INTERPRETER_EXEC)

$(INTERPRETER_EXEC): build-interpreter
