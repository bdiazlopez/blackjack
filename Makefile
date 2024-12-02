CXX = g++
CC = gcc
CXXFLAGS = -Wall -Wextra
CFLAGS = -Wall -Wextra
SRC_CPP = blackjack.cpp
SRC_C = screen_utils.c
OBJ = $(SRC_CPP:.cpp=.o) $(SRC_C:.c=.o)
TARGET = blackjack

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)