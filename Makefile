
SUDOKU_PATH  = .
SUDOKU_SRC   = $(SUDOKU_PATH)/src
SUDOKU_OUT   = $(OUT)
COMMON_OUT  = $(OUT)/common
COMMON_PATH = common

include $(COMMON_PATH)/variables.mk

BUILD = $(OUT)/sudoku$x

build: DIRS $(OUT)/sudoku$x

include $(COMMON_PATH)/submodule.mk

include $(SUDOKU_PATH)/deps.mk

SUDOKU_CPP_OUTPUT := \
	$(OUT)/constraint_increase$o \
	$(OUT)/constraint_no_duplicate$o \
	$(OUT)/constraint_no_consecutive_adjacent$o \
	$(OUT)/constraint_standard_shifted$o \
	$(OUT)/group_generator$o \
	$(OUT)/sudoku$o \

CPP_OUTPUT += \
	$(SUDOKU_CPP_OUTPUT) \
	$(OUT)/main$o \

SUDOKU_OUTPUT := $(SUDOKU_CPP_OUTPUT)

$(OUT)/sudoku$x: \
	$(COMMON_OUTPUT) \
	$(SUDOKU_OUTPUT) \
	$(OUT)/main$o \

run: $(OUT)/sudoku$x
	@$(OUT)/sudoku$x

include $(COMMON_PATH)/rule.mk

clean:
	-rm $(BUILD)
	-rm $(SUDOKU_OUTPUT) $(OUT)/main$o
	-rmdir $(SUDOKU_OUT)

.PHONY: clean
.PHONY: build
.PHONY: run