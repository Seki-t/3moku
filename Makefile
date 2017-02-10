# CXX = g++
# TARGET = test
# CXXFLAGS = -Wall -std=c++1y
# LIBS +=
# SRCS := main.cpp
# OBJS := $(SRCS:.cpp=.o)
# $(TARGET): $(OBJS)
# 	$(CXX) $(CXXFLAGS) $(LIBS) -o $@ $(OBJS)
#
# clean:
# 	rm -f $(TARGET) $(OBJS)
#
# run : $(TARGET)
# 	./$(TARGET)
#

TARGET ?= a.out
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(addsuffix .o,$(basename $(SRCS)))
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) -MMD -MP

#CPPFLAGS ?= $(INC_FLAGS) -std=c++1y -fsanitize=address
CPPFLAGS ?= $(INC_FLAGS) -std=c++1y

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) $(OBJS) -o $@ $(LOADLIBES) $(LDLIBS)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

run : $(TARGET)
	./$(TARGET) $(ARG_FILE)
	
-include $(DEPS)
