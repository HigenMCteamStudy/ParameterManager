CC = gcc
CPP = g++
CXXFLAGS = -Wall -Wextra -g
CFLAGS = -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h
CPPFLAGS = -I$(CPPUTEST_HOME)/include -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h
LD_LIBRARIES = -L$(CPPUTEST_HOME)/cpputest_build/lib -lCppUTest -lCppUTestExt

LINKED_LIST_DIR = LinkedList
LINKED_LIST_SRCS = $(LINKED_LIST_DIR)/linked_list.c
CXXFLAGS += -I$(LINKED_LIST_DIR)

PARAMETER_DIR = Parameter
PARAMETER_SRCS = $(PARAMETER_DIR)/parameter.c
CXXFLAGS += -I$(PARAMETER_DIR)

PROFILE_DIR = ProfileDictionary
PROFILE_SRCS = $(PROFILE_DIR)/profile_dic.c
CXXFLAGS += -I$(PROFILE_DIR)

SRCS =  $(LINKED_LIST_SRCS) \
		$(PROFILE_SRCS) \
		$(PARAMETER_SRCS)

TEST_DIR = test
TEST_SRCS = $(TEST_DIR)/ParameterTest.cpp

TEST_TARGET = tests
MAIN_TARGET = parametermanager

# 환경 변수 체크
ifdef CPPUTEST_HOME
    ENABLE_TEST = 1
else
    ENABLE_TEST = 0
endif

all: $(MAIN_TARGET) $(if $(ENABLE_TEST), $(TEST_TARGET))

%.o: %.c
	$(CC) $(CXXFLAGS) -c $< -o $@

%.o: %.cpp
	$(CPP) $(CXXFLAGS) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

C_OBJS = $(SRCS:.c=.o)
CPP_OBJS = $(TEST_SRCS:.cpp=.o)

# TEST_TARGET 타겟 정의
ifeq ($(ENABLE_TEST), 1)
$(TEST_TARGET) : AllTests.cpp $(C_OBJS) $(CPP_OBJS)
	$(CPP) $(CXXFLAGS) $(CPPFLAGS) -o $@ $^ $(LD_LIBRARIES)
endif

$(MAIN_TARGET) : main.c $(C_OBJS)
	$(CC) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(TEST_TARGET) $(MAIN_TARGET) $(C_OBJS) $(CPP_OBJS)

.PHONY: clean
