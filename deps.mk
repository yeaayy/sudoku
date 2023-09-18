# This file is generated automaticaly. Please do not touch.
$(SUDOKU_SRC)/constraint.hpp: \
	$(SUDOKU_SRC)/sudoku.hpp \

	$(TOUCH) $@

$(SUDOKU_OUT)/constraint_increase$o: $(SUDOKU_SRC)/constraint_increase.cpp \
	$(SUDOKU_SRC)/constraint_increase.hpp \
	$(COMMON_HEAD)/list.tcc \

$(SUDOKU_SRC)/constraint_increase.hpp: \
	$(SUDOKU_SRC)/sudoku.hpp \

	$(TOUCH) $@

$(SUDOKU_OUT)/constraint_no_consecutive_adjacent$o: $(SUDOKU_SRC)/constraint_no_consecutive_adjacent.cpp \
	$(SUDOKU_SRC)/constraint_no_consecutive_adjacent.hpp \

$(SUDOKU_SRC)/constraint_no_consecutive_adjacent.hpp: \
	$(SUDOKU_SRC)/sudoku.hpp \

	$(TOUCH) $@

$(SUDOKU_OUT)/constraint_no_duplicate$o: $(SUDOKU_SRC)/constraint_no_duplicate.cpp \
	$(SUDOKU_SRC)/constraint_no_duplicate.hpp \
	$(COMMON_HEAD)/list.tcc \

$(SUDOKU_SRC)/constraint_no_duplicate.hpp: \
	$(COMMON_HEAD)/list.hpp \
	$(SUDOKU_SRC)/sudoku.hpp \
	$(SUDOKU_SRC)/group_generator.hpp \

	$(TOUCH) $@

$(SUDOKU_OUT)/constraint_standard_shifted$o: $(SUDOKU_SRC)/constraint_standard_shifted.cpp \
	$(SUDOKU_SRC)/constraint_standard_shifted.hpp \
	$(SUDOKU_SRC)/sudoku.hpp \

$(SUDOKU_SRC)/constraint_standard_shifted.hpp: \
	$(SUDOKU_SRC)/sudoku.hpp \
	$(SUDOKU_SRC)/group_generator.hpp \

	$(TOUCH) $@

$(SUDOKU_OUT)/group_generator$o: $(SUDOKU_SRC)/group_generator.cpp \
	$(SUDOKU_SRC)/group_generator.hpp \

$(SUDOKU_OUT)/log.android$o: $(SUDOKU_SRC)/log.android.c \

$(SUDOKU_OUT)/log.linux$o: $(SUDOKU_SRC)/log.linux.c \

$(SUDOKU_OUT)/main$o: $(SUDOKU_SRC)/main.cpp \
	$(COMMON_HEAD)/list.tcc \
	$(SUDOKU_SRC)/sudoku.hpp \
	$(SUDOKU_SRC)/constraint_no_duplicate.hpp \
	$(SUDOKU_SRC)/constraint_increase.hpp \
	$(SUDOKU_SRC)/constraint_no_consecutive_adjacent.hpp \
	$(SUDOKU_SRC)/constraint_standard_shifted.hpp \

$(SUDOKU_OUT)/sudoku$o: $(SUDOKU_SRC)/sudoku.cpp \
	$(SUDOKU_SRC)/sudoku.hpp \
	$(COMMON_HEAD)/list.tcc \

$(SUDOKU_SRC)/sudoku.hpp: \
	$(COMMON_HEAD)/list.hpp \

	$(TOUCH) $@

