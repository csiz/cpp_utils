CXX ?= g++
CXXFLAGS += -std=c++14 -Iinclude
LDFLAGS += 

COMPILE := $(CXX) $(CXXFLAGS) $(LDFLAGS)

TARGETS := \
	samples/for_each \
	samples/unpack_call \
	samples/call \

TESTS := \
	tests/test_call \
	tests/test_for_each \

BUILD_TARGETS := $(addprefix build/, $(TARGETS))
TESTS_TARGETS := $(addprefix build/, $(addsuffix .pass, $(TESTS)))

all: $(BUILD_TARGETS) $(TESTS_TARGETS)

$(BUILD_TARGETS): build/%: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $@"
	@$(COMPILE) $< -o $@

$(TESTS_TARGETS): build/%.pass: %.sh $(BUILD_TARGETS)
	@echo -n "Testing $<: "
	@mkdir -p $(dir $@)
	@./$< && (echo "PASS"; touch $@) || (echo "FAIL"; rm $@ 2> /dev/null)

clean:
	@rm -r build

.PHONY: all clean