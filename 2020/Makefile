.PHONY: release debug clean

EXE = adventofcode
CXXFLAGS = -std=c++17 -Wall -Werror -O3
LDFLAGS =

SRCS := $(wildcard *.cpp)
TEST_SRCS := $(filter-out adventofcode.cpp, $(SRCS))
SRCS := $(filter-out test.cpp, $(SRCS))
OBJS := $(SRCS:.cpp=.o)
TEST_OBJS := $(TEST_SRCS:.cpp=.test.o)
DEPS := $(SRCS:.cpp=.d)

debug: CXXFLAGS += -g -Og
debug: $(EXE)

release: $(EXE)

clean:
	$(RM) $(OBJS) $(TEST_OBJS) $(EXE) test $(DEPS)

test: CXXFLAGS += -DTEST -g -Og
test: $(TEST_OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

-include $(DEPS)

%.test.o: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) -MMD -MP -c $<

%.o: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) -MMD -MP -c $<
