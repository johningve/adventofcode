.PHONY: all debug clean

EXE = adventofcode
CXXFLAGS = -Wall -Werror -O2
LDFLAGS =

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

all: $(EXE)

debug: CFLAGS += -g -O0
debug: $(EXE)

clean:
	$(RM) $(OBJS) $(EXE) $(DEPS)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

-include $(DEPS)

%.o: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) -MMD -MP -c $<
