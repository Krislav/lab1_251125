CC = g++
CFLAGS = -Wall -Wextra -g

SRCS = main.cpp \
       Interface.cpp \
       Stream/WriteStream.cpp \
       Stream/ReadStream.cpp \
	   Stream/FindSupport.cpp \
       Errors/Errors.cpp \
	   TimeTest/TimeTest.cpp \
	   Tests/Tests.cpp \
	   Tests/TestShell.cpp 

HEADERS = Interface.hpp \
		  Stream/WriteStream.hpp \
          Stream/ReadStream.hpp \
		  Stream/FindSupport.hpp \
          Errors/Errors.hpp \
		  TimeTest/TimeTest.hpp \
		  Tests/Tests.hpp \
		  Tests/TestShell.hpp

OBJS = $(SRCS:.cpp=.o)

TARGET = lab1

.PHONY: all clean cleanall rebuild run rerun

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

cleanall:
	rm -f $(OBJS) $(TARGET)

rebuild: cleanall all

run:
	./$(TARGET)

rerun: rebuild run