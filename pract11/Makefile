CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2
OBJS = point_types.o sub_tree.o point_set.o main.o
TARGET = emst

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-rm -f $(OBJS) $(TARGET)
