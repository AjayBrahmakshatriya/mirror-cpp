BASE_DIR=$(shell pwd)
SRC_DIR=$(BASE_DIR)/src
BUILD_DIR=$(BASE_DIR)/build
INCLUDE_DIR=$(BASE_DIR)/include
SAMPLES_DIR=$(BASE_DIR)/samples

INCLUDES=$(wildcard $(INCLUDE_DIR)/*.h) $(wildcard $(INCLUDE_DIR)/*/*.h)


$(shell mkdir -p $(BUILD_DIR))
$(shell mkdir -p $(BUILD_DIR)/blocks)
$(shell mkdir -p $(BUILD_DIR)/builder)
$(shell mkdir -p $(BUILD_DIR)/samples)

SAMPLES_SRCS=$(wildcard $(SAMPLES_DIR)/*.cpp)
SAMPLES=$(subst $(SAMPLES_DIR),$(BUILD_DIR),$(SAMPLES_SRCS:.cpp=))




CFLAGS=-std=c++14
LINKER_FLAGS=-rdynamic


BUILDER_SRC=$(wildcard $(SRC_DIR)/builder/*.cpp)
BLOCKS_SRC=$(wildcard $(SRC_DIR)/blocks/*.cpp)

BUILDER_OBJS=$(subst $(SRC_DIR),$(BUILD_DIR),$(BUILDER_SRC:.cpp=.o))
BLOCKS_OBJS=$(subst $(SRC_DIR),$(BUILD_DIR),$(BLOCKS_SRC:.cpp=.o))

LIBRARY_OBJS=$(BUILDER_OBJS) $(BLOCKS_OBJS)

all: executables

.PRECIOUS: $(BUILD_DIR)/builder/%.o 
.PRECIOUS: $(BUILD_DIR)/blocks/%.o 
.PRECIOUS: $(BUILD_DIR)/samples/%.o 

$(BUILD_DIR)/builder/%.o: $(SRC_DIR)/builder/%.cpp $(INCLUDES)
	$(CXX) $(CFLAGS) $< -o $@ -I$(INCLUDE_DIR) -c
$(BUILD_DIR)/blocks/%.o: $(SRC_DIR)/blocks/%.cpp $(INCLUDES)
	$(CXX) $(CFLAGS) $< -o $@ -I$(INCLUDE_DIR) -c


$(BUILD_DIR)/samples/%.o: $(SAMPLES_DIR)/%.cpp $(INCLUDES)
	$(CXX) $(CFLAGS) $< -o $@ -I$(INCLUDE_DIR) -c 

$(BUILD_DIR)/sample%: $(BUILD_DIR)/samples/sample%.o $(LIBRARY_OBJS)
	$(CXX) -o $@ $^ $(LINKER_FLAGS)


.PHONY: executables
executables: $(SAMPLES)

clean:
	- rm -rf build
