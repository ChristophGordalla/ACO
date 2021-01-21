CXX := g++
CXXFLAGS := -O2 -Wall -Wextra
RM := rm -f

TARGETS := aco
OBJS := main.o aco.o ant.o
DEPS := aco.h ant.h


.PHONY: all clean


all: $(TARGETS)


clean:
	$(RM) $(OBJS) aco


$(TARGETS): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^


$(OBJS): %.o : %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $<



