# define the executable file 
MAINPROG=tempParser
#
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#
# define the C compiler to use
CC=gcc

# for C++ define  CXX = g++
CXX=g++
CPPFLAGS= -Wall -g -std=c++17
LFLAGS=
# define any compile-time flags
CFLAGS= -Wall -g
TARGET=$(MAINPROG)
CPPS=$(wildcard *.cpp)
LINK=g++ $(CPPFLAGS)
OBJS=$(CPPS:%.cpp=%.o)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $*.cpp


all: $(TARGET)  


$(TARGET): $(OBJS)
	$(LINK) $(FLAGS) -o $(TARGET) $^ $(LFLAGS)

clean:
	-/bin/rm -rf *.d *.o  core_*.txt $(TARGET)
