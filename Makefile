CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -O2 $(shell llvm-config --cflags)
LDFLAGS := $(shell llvm-config --libs core native --link-static 2>/dev/null \
            || llvm-config --libs core native) \
           $(shell llvm-config --system-libs) \
           -lm

TARGET  := minipasc
SRCS    := main.c ast.c codegen.c
OBJS    := $(SRCS:.c=.o) lex.yy.o parser.tab.o

.PHONY: all clean distclean test

all: $(TARGET)

# ── Flex ─────────────────────────────────────────────────────
lex.yy.c: lexer.l parser.tab.h
	flex -o $@ $<

# ── Bison ────────────────────────────────────────────────────
parser.tab.c parser.tab.h: parser.y
	bison -d -Wcounterexamples -o parser.tab.c $<

# ── Generic C compile ─────────────────────────────────────────
%.o: %.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

lex.yy.o: lex.yy.c parser.tab.h
	$(CC) $(CFLAGS) -I. -Wno-unused-function -c $< -o $@

parser.tab.o: parser.tab.c
	$(CC) $(CFLAGS) -I. -c $< -o $@

# ── Link ─────────────────────────────────────────────────────
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -I. -o $@ $^ $(LDFLAGS)

# ── Test programs ─────────────────────────────────────────────
test: $(TARGET)
	@bash run_tests.sh

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h /tmp/compile_err

distclean: clean
