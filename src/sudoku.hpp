#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <iostream>
#include <vector>

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

	static void solve(Sudoku *, std::vector<Sudoku*> &dst, std::size_t limit = 0x7fffffff);
	static void printSpecialSolution(std::vector<Sudoku*> &solutions, std::ostream &out = std::cout);
	static int countSolution(Sudoku *, std::size_t limit = 0x7fffffff);

    void print(std::ostream &out, const char *fixedNoteFormat = "\e[3m%c\e[23m", int marked = -1);
	void printRemaining(std::ostream &dst);
	std::string bar();

	int getSize();
	int getDimension();
	void ignore(int index);
	bool isIgnored(int index);

	friend bool operator>>(std::istream &src, Sudoku &dst);

    static int note2value(SudokuNote);
    static SudokuNote value2note(int);
	static char note2char(SudokuNote);
	static int noteGetRemaining(SudokuNote);
	static void printAvailable(SudokuNote, std::ostream &out=std::cout);

    SudokuNote *note;
#ifdef HAS_HISTORY
	std::vector<CollapseHistory> history;
	void printHistory();
#endif

private:
	std::vector<Constraint*> *constraints;
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