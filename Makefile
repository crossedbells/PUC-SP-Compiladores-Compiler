LLVM_CONFIG := llvm-config

CC      := gcc
CFLAGS := -std=c11 -Wall -Wextra -O2 $(shell $(LLVM_CONFIG) --cflags) -Wno-unused-parameter -Wno-unused-function
LDFLAGS := $(shell $(LLVM_CONFIG) --ldflags) \
           $(shell $(LLVM_CONFIG) --libs all) \
           $(shell $(LLVM_CONFIG) --system-libs) \
           -lz -lm -lstdc++

TARGET  := minipasc
SRCS    := main.c ast.c codegen.c
OBJS    := $(SRCS:.c=.o) lex.yy.o parser.tab.o

.PHONY: all clean test

all: $(TARGET)

lex.yy.c: lexer.l parser.tab.h
	flex -o $@ $<

parser.tab.c parser.tab.h: parser.y
	bison -d -Wcounterexamples -o parser.tab.c $<

%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

lex.yy.o: lex.yy.c parser.tab.h
	$(CC) $(CFLAGS) -I. -Wno-unused-function -c $< -o $@

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -I. -o $@ $^ $(LDFLAGS)

test: $(TARGET)
	@bash run_tests.sh

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h
