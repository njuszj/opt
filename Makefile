VERSION = 1.0.0
CXX = g++
CFLAGS = -Wall -g
SRC_PATH = ./src
DIRS = $(shell find $(SRC_PATH) -maxdepth 3 -type d)
SRCS_CPP += $(foreach dir, $(DIRS), $(wildcard $(dir)/*.cpp))

default:
	$(CXX) src/main.cpp -o a.out
	./a.out

test_time:
	$(CXX) test/currTimeTester.cpp -o a.out
	./a.out
test_print:
	$(CXX) src/utils/printer.cpp test/printTester.cpp -o a.out
	./a.out

probe: $(SRCS_CPP)
	$(CXX) $(CFLAGS) $^ -o a.out

	