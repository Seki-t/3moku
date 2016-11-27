CXX = g++
TARGET = test
CXXFLAGS = -Wall -std=c++1y
LIBS +=
SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(OBJS)

clean:
	rm -f $(TARGET) $(OBJS)

run : $(TARGET)
	./$(TARGET)


