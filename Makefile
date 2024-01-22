# the compiler: gcc for C program, define as g++ for C++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS  = -g -std=c++17 
CFLAGS_ADD  = $(CLAGS) -Wall -Werror -Woverflow


OBJ=obj/
SRC=src/
INCLUDE=include/
BUILD=build
OBJS=$(patsubst %.cpp, %.o, $(wildcard $(SRC)*.cpp))

$(OBJ)%.o : $(SRC)%.cpp
	g++ -c $(INCLUDE) $< -o $@


no_opt: $(OBJS) build 
	$(CC) $(CFLAGS) main.cpp -o $(BUILD)/main_no_opt

opt: $(OBJS) build 
	$(CC) $(CFLAGS_ADD) main.cpp -o $(BUILD)/main_opt

build:
	mkdir -p $(BUILD)
clean:
	rm -rf build

# These rules do not correspond to a specific file
.PHONY: build clean no_opt opt