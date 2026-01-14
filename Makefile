CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

SRC = src/main.cpp src/tcp_server.cpp src/tcp_client.cpp
INC = -Iinclude

TARGET = tcp_example

all:
	$(CXX) $(CXXFLAGS) $(SRC) $(INC) -o $(TARGET)

clean:
	rm -f $(TARGET)
