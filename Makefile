.PHONY: all clean make_dirs

INCLUDE_DIR ?= include
BUILD_DIR ?= build

CXX ?= g++
CXXFLAGS += -std=c++14 -I$(INCLUDE_DIR)
LDFLAGS += 

TARGETS := \
	samples/for_each \
	samples/unpack_call \
	samples/call \

BUILD_TARGETS := $(addprefix $(BUILD_DIR)/, $(TARGETS))

all: $(BUILD_TARGETS)


$(BUILD_TARGETS): $(BUILD_DIR)/%: %.cpp make_dirs
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) $(LDFLAGS) $< -o $@

clean:
	@rm -r $(BUILD_DIR)

