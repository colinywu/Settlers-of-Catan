####  Adapted from https://spin.atomicobject.com/2016/08/26/makefile-c-projects/ ####
####  Professor Gustavo said its fine to use it ####
####  Refer to https://piazza.com/class/kduh3xm2q4w3yw?cid=2945 ####

TARGET_EXEC ?= constructor

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

CXX=g++ 
CC=g++

SRCS := $(shell find $(SRC_DIRS) -name *.cc -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -std=c++14 -Wall -O0 -g -MMD -Werror=vla





$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)


# c++ source
$(BUILD_DIR)/%.cc.o: %.cc
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p