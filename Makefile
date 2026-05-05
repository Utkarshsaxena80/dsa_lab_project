CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O3

SRCS = main.cpp UnrolledLinkedList.cpp SuffixArray.cpp IntervalTree.cpp DNAAnalyzer.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = DNAAnalyzer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe
