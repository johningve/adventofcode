.PHONY: all debug

EXE = adventofcode
CFLAGS = -Wall -Werror -O2 
LDFLAGS = 

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

CFLAGS += $(shell pkg-config --cflags glib-2.0)
LDFLAGS += $(shell pkg-config --libs glib-2.0)

all: $(EXE)

debug: CFLAGS += -g -O0

$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ $(CFLAGS) -c $< 

clean:
	rm -f $(OBJS) $(EXE)
