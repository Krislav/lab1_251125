CC = g++
CFLAGS = -Wall -Wextra -g

SRCS = main.cpp \
       Interface.cpp \
       Stream/WriteStream.cpp \
       Stream/ReadStream.cpp \
       Errors/Errors.cpp \
	   Tests/Tests.cpp \
	   Tests/TestShell.cpp

HEADERS = Stream/WriteStream.hpp \
          Stream/ReadStream.hpp \
          Errors/Errors.hpp \
          Interface.hpp \
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