EXE := adventofcode
CFLAGS := -Wall -Werror -O2

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

all: $(EXE)

debug: CFLAGS += -g -O0

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)
