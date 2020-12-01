.PHONY: all debug

EXE = adventofcode
CFLAGS = -Wall -Werror -O2 
LDFLAGS =

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)

all: $(EXE)

debug: CFLAGS += -g -O0
debug: $(EXE)

$(EXE): $(OBJS)
	$(CXX) -o $(EXE) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -o $@ $(CFLAGS) -c $< 

clean:
	rm -f $(OBJS) $(EXE)
