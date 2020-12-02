.PHONY: release debug clean

EXE = adventofcode
CXXFLAGS = -Wall -Werror -O3
LDFLAGS =

SRCS := $(wildcard *.cpp)
OBJS := $(SRCS:.cpp=.o)
DEPS := $(SRCS:.cpp=.d)

debug: CXXFLAGS += -g -Og
debug: $(EXE)

release: $(EXE)

clean:
	$(RM) $(OBJS) $(EXE) $(DEPS)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

-include $(DEPS)

%.o: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) -MMD -MP -c $<
