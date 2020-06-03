SRCS = comm.cpp interface.cpp ntable.cpp util.cpp
CXX = mpicxx
CXXFLAGS = -fPIC
OBJS = $(SRCS:.cpp=.o)
LDFLAGS = -shared
TARGET = libmpi.so

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(TARGET) $(OBJS)
