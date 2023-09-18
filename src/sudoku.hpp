#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <stdio.h>

#include "list.hpp"

// #define HAS_HISTORY

#define SudokuNote1 1
#define SudokuNote2 2
#define SudokuNote3 4
#define SudokuNote4 8
#define SudokuNote5 16
#define SudokuNote6 32
#define SudokuNote7 64
#define SudokuNote8 128
#define SudokuNote9 256
#define SudokuNoteAll 511
#define SudokuNoteOk 512
#define SudokuNoteFixed 1024

typedef enum SudokuResult
{
	SudokuResultError = -1,
	SudokuResultUnchanged,
	SudokuResultOk,
} SudokuResult;

#ifdef HAS_HISTORY
typedef struct CollapseHistory {
	int index;
	int value;
} CollapseHistory;
#endif

typedef int SudokuNote;

class Sudoku
{
public:
	class Constraint;

public:
    Sudoku(int dim = 9);
    Sudoku(Sudoku *src);
	Sudoku(const Sudoku&) = delete;
	Sudoku(const Sudoku&&) = delete;
    ~Sudoku();

	int getIndex(int x, int y);
	void setFixed(int index, int value);
	void setFixed(int x, int y, int value);

	void fixNote();
	SudokuResult collapse(int index, int value);

	void addConstraint(int index, Constraint *eventListener);

	static void solve(Sudoku *, List<Sudoku*> &dst, int limit = 0x7fffffff);
	static void printSpecialSolution(List<Sudoku*> &solutions);
	static int countSolution(Sudoku *, int limit = 0x7fffffff);

    void print(const char *fixedNoteFormat = "\e[3m%c\e[23m", int marked = -1);
	void printRemaining();
	int getSize();
	int getDimension();
	void ignore(int index);
	bool isIgnored(int index);
	bool read(FILE *file);
	bool read(const char *path);

    static int note2value(SudokuNote);
    static SudokuNote value2note(int);
	static char note2char(SudokuNote);
	static int noteGetRemaining(SudokuNote);
	static void printAvailable(SudokuNote);

    SudokuNote *note;
#ifdef HAS_HISTORY
	List<CollapseHistory> history;
	void printHistory();
#endif

private:
	List<Constraint*> *constraints;
	bool *ignored;
	bool isDuplicate;
	int dim;
	int size;
};

class Sudoku::Constraint
{
public:
	virtual void onAdded(Sudoku *, int index);
	virtual SudokuResult onCollapsed(Sudoku *, int index, int value, SudokuNote note) = 0;
};

#endif /* SUDOKU_HPP */