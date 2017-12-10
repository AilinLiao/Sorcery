CXX=g++
CXXFLAGS=-std=c++14 -Werror=vla 
OBJS=$(patsubst %.cc,%.o,$(wildcard *.cc))
all: sorcery

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

sorcery: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	-rm -f $(OBJS)
