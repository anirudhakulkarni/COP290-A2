CC := gcc
# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CFLAGS := -lSDL2_ttf -lpthread -I. -Wall
LIBS:=`sdl2-config --cflags --libs`
# add source files here
SRCS := main.c server.c client.c
OBJS := $(SRCS:.c=.o)
# name of executable
EXEC := simulator
# directories
BUILD_DIR = ./build
OUT_DIR = ./outputs
SRC_DIR= ./src
# generate names of object files

# default recipe
.DEFAULT:
	@echo make all to build and run
	@echo make build to build
	@echo make run to run the build
	@echo make clean to remove build files
help:
	@echo make all to build and run
	@echo make build to build
	@echo make run to run the build
	@echo make clean to remove build files
all: clean build run
clean:
	@echo Removing old build files :
	$(RM) -r $(BUILD_DIR)
build:
	@echo Building project :
	mkdir $(BUILD_DIR)
	#cd $(SRC_DIR); $(CC) -o .$(BUILD_DIR)/$(EXEC) $(SRCS) $(LIBS) $(CFLAGS)
	cd $(SRC_DIR); $(CC) -o ./$(BUILD_DIR)/$(EXEC) $(SRCS) $(LIBS) $(CFLAGS)
	@echo Generated the executable without errors ...
run:
	@echo Running the executable ...
	cd $(SRC_DIR); ./$(EXEC)

.PHONY: all clean build run maze
maze:
	g++ -o ./build/maze_generator ./src/maze-generator.cpp
	cd ./build; ./maze_generator
