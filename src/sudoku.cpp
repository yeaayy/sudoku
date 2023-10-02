#include "sudoku.hpp"

namespace {

int remaining[512] {
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8,
    4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 5, 6, 6, 7, 6, 7, 7, 8, 6, 7, 7, 8, 7, 8, 8, 9,
};

} // namespace

Sudoku::Sudoku(int dim)
{
    this->dim = dim;
    this->size = dim * dim;
    isDuplicate = false;
    ignored = new bool[size];
    constraints = new std::vector<Constraint*>[size];
    note = new SudokuNote[size];
    for(int i = 0; i < size; i++) {
        note[i] = SudokuNoteAll;
        ignored[i] = false;
    }
}

Sudoku::Sudoku(Sudoku *src)
{
    this->dim = src->dim;
    this->size = src->size;
    this->ignored = src->ignored;
    isDuplicate = true;
    constraints = src->constraints;
    note = new SudokuNote[size];
    std::copy(src->note, src->note + size, note);

#ifdef HAS_HISTORY
    history.resize(src->history.size());
    for(auto &hist : src->history) {
        history.push_back(hist);
    }
#endif
}

Sudoku::~Sudoku()
{
    delete[] note;
    if(!isDuplicate) {
        delete[] ignored;
        delete[] constraints;
    }
}

int Sudoku::getSize()
{
    return size;
}

int Sudoku::getDimension()
{
    return dim;
}

int Sudoku::getIndex(int x, int y)
{
    if(x < 0 || x >= dim) return -1;
    if(y < 0 || y >= dim) return -1;
    return y * dim + x;
}

void Sudoku::ignore(int index)
{
    ignored[index] = true;
}

bool Sudoku::isIgnored(int index)
{
    return ignored[index];
}

void Sudoku::setFixed(int index, int value)
{
    collapse(index, value);
    note[index] = (SudokuNote) (note[index] | SudokuNoteFixed);
}

void Sudoku::setFixed(int x, int y, int value)
{
    setFixed(getIndex(x, y), value);
}

void Sudoku::fixNote()
{
    for (int i = 0; i < size; i++) {
        if(!(note[i] & SudokuNoteFixed)) {
            note[i] = SudokuNoteAll;
        }
    }
    for (int i = 0; i < size; i++) {
        if(note[i] & SudokuNoteFixed) {
            int value = note2value(note[i]);
            note[i] = SudokuNoteAll;
            collapse(i, value);
            note[i] = (SudokuNote) (note[i] | SudokuNoteFixed);
        }
    }
}

bool operator>>(std::istream &src, Sudoku &dst)
{
    int index = 0;
    char c;
    while(src.good() && index < dst.getSize()) {
        src >> c;
        if(c >= '1' && c <= '9') {
            dst.setFixed(index, c - '1');
            index++;
        } else if(c == '@') {
            dst.ignore(index);
            index++;
        } else if(c == '.') {
            index++;
        }
    }
    return index == dst.getSize();
}

SudokuResult Sudoku::collapse(int index, int value)
{
    if(note[index] & SudokuNoteOk) return SudokuResultUnchanged;
    SudokuNote noteValue = value2note(value);
    note[index] = noteValue | SudokuNoteOk;
#ifdef HAS_HISTORY
    CollapseHistory collapseHistory = {index, value};
    history.push_back(collapseHistory);
#endif

    std::vector<Constraint*> &constraint = constraints[index];
    SudokuResult result = SudokuResultUnchanged;
    for (auto &constr : constraint) {
        switch(constr->onCollapsed(this, index, value, noteValue)) {
            case SudokuResultOk: result = SudokuResultOk; break;
            case SudokuResultUnchanged: break;
            case SudokuResultError: return SudokuResultError;
        }
    }
    return result;
}

void Sudoku::addConstraint(int index, Sudoku::Constraint *eventListener)
{
    std::vector<Constraint*> &constraint = constraints[index];
    for (auto &constr : constraint) {
        if(constr == eventListener) return;
    }
    constraint.push_back(eventListener);
    eventListener->onAdded(this, index);
}

int Sudoku::countSolution(Sudoku *src, std::size_t limit)
{
repeat:
    int minRem = 10;
    int minIndex = -1;
    for(int i = 0; i < src->size; i++) {
        SudokuNote note = src->note[i];
        if((note & SudokuNoteAll) == 0) {
            return 0;
        }
        if(note & SudokuNoteOk) continue;
        int rem = Sudoku::noteGetRemaining(note);
        if(rem == 1) {
            switch(src->collapse(i, Sudoku::note2value(note))) {
            case SudokuResultOk:
                goto repeat;
            case SudokuResultError:
                return 0;
            case SudokuResultUnchanged:
                break;
            }
        } else if(rem < minRem) {
            minRem = rem;
            minIndex = i;
        }
    }
    if(minIndex == -1) {
        return 1;
    }
    std::size_t resultCount = 0;
    int note = src->note[minIndex];
    int value = 0;
    while(note != 0 && resultCount < limit) {
        if(note & 1) {
            Sudoku tmp(src);
            switch(tmp.collapse(minIndex, value)) {
            case SudokuResultOk:
            case SudokuResultUnchanged:
                resultCount += countSolution(&tmp, limit);
            case SudokuResultError:
                break;
            }
        }
        note >>= 1;
        value++;
    }
    return resultCount;
}

void Sudoku::solve(Sudoku *src, std::vector<Sudoku*> &dst, std::size_t limit)
{
repeat:
    int minRem = 10;
    int minIndex = -1;
    for(int i = 0; i < src->size; i++) {
        if(src->ignored[i]) continue;
        SudokuNote note = src->note[i];
        if((note & SudokuNoteAll) == 0) {
            return;
        }
        if(note & SudokuNoteOk) continue;
        int rem = Sudoku::noteGetRemaining(note);
        if(rem == 1) {
            switch(src->collapse(i, Sudoku::note2value(note))) {
            case SudokuResultOk:
                goto repeat;
            case SudokuResultError:
                return;
            case SudokuResultUnchanged:
                break;
            }
        } else if(rem < minRem) {
            minRem = rem;
            minIndex = i;
        }
    }
    if(minIndex == -1) {
        dst.push_back(new Sudoku(src));
        return;
    }
    int note = src->note[minIndex];
    int value = 0;
    while(note != 0 && dst.size() < limit) {
        if(note & 1) {
            Sudoku tmp(src);
            switch(tmp.collapse(minIndex, value)) {
            case SudokuResultOk:
            case SudokuResultUnchanged:
                solve(&tmp, dst, limit);
            case SudokuResultError:
                break;
            }
        }
        note >>= 1;
        value++;
    }
}

/**
 * Special solution is solution that become solveable after fixing one more box.
 * The box that need to be fixed are highlighted in grey.
*/
void Sudoku::printSpecialSolution(std::vector<Sudoku*> &solutions, std::ostream &out)
{
    int size = solutions[0]->size;
    int count[size][9];
    Sudoku *unique[size][9];
    for(int i = 0; i < size; i++) {
        std::fill(count[i], count[i] + 9, 0);
        std::fill(unique[i], unique[i] + 9, nullptr);
    }
    for(auto sudoku : solutions) {
        for(int j = 0; j < size; j++) {
            int value = Sudoku::note2value(sudoku->note[j]);
            count[j][value]++;
            unique[j][value] = sudoku;
        }
    }
    int resultCount = 0;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < 9; j++) {
            if(count[i][j] == 1) {
                auto sudoku = unique[i][j];
                sudoku->print(out, nullptr, i);
                out << sudoku->bar();
                resultCount++;
            }
        }
    }
    out << resultCount << " special solution found\n";
}

void Sudoku::print(std::ostream &out, const char *fixedNoteFormat, int marked)
{
    for(int y = 0, i = 0; y < dim; y++) {
        for(int x = 0; x < dim; x++, i++) {
            SudokuNote v = note[i];
            char valueChar = note2char(note[i]);
            if(v & SudokuNoteFixed){
				// highlight fixed note
                if(fixedNoteFormat != nullptr) {
                    char *str;
                    asprintf(&str, fixedNoteFormat, valueChar);
                    out << str;
                    free(str);
                } else {
                    out << valueChar;
                }
			}else{
				if(i == marked){
                    out << "\e[48;5;241m" << valueChar << "\e[m";
				}else{
                    out << valueChar;
				}
            }
            if(x < dim - 1) out << ' ';
            if(x % 3 == 2 && x < dim - 1) out << ' ';
        }
        out << '\n';
        if(y % 3 == 2 && y < dim - 1) out << '\n';
    }
}

void Sudoku::printRemaining(std::ostream &out)
{
    for(int y = 0, i = 0; y < dim; y++) {
        for(int x = 0; x < dim; x++, i++) {
            out << '0' + noteGetRemaining(note[i]);
            if(x < 8) out << ' ';
            if(x % 3 == 2 && x < 8) out << ' ';
        }
        out << '\n';
        if(y % 3 == 2 && y < 8) out << '\n';
    }
}

std::string Sudoku::bar()
{
    std::string result;
    result.append(dim * 2 + dim / 3 - 2, '-');
    result.append(1, '\n');
    return result;
}

int Sudoku::note2value(SudokuNote note)
{
	switch(note & SudokuNoteAll){
		case SudokuNote1: return 0;
		case SudokuNote2: return 1;
		case SudokuNote3: return 2;
		case SudokuNote4: return 3;
		case SudokuNote5: return 4;
		case SudokuNote6: return 5;
		case SudokuNote7: return 6;
		case SudokuNote8: return 7;
		case SudokuNote9: return 8;
		default: return -1;
	}
}

char Sudoku::note2char(SudokuNote note)
{
    switch(note & SudokuNoteAll){
		case 0:  return '?';
		case SudokuNote1: return '1';
		case SudokuNote2: return '2';
		case SudokuNote3: return '3';
		case SudokuNote4: return '4';
		case SudokuNote5: return '5';
		case SudokuNote6: return '6';
		case SudokuNote7: return '7';
		case SudokuNote8: return '8';
		case SudokuNote9: return '9';
		default: return '.';
	}
}

SudokuNote Sudoku::value2note(int value)
{
    return (SudokuNote) (1 << value);
}

int Sudoku::noteGetRemaining(SudokuNote note)
{
    return remaining[note];
}

void Sudoku::printAvailable(SudokuNote note, std::ostream &out)
{
    int bits = note & SudokuNoteAll;
    int value = 1;
    while(bits > 0) {
        if(bits & 1) {
            out << value;
        }
        value++;
        bits >>= 1;
    }
    putchar('\n');
}

void Sudoku::Constraint::onAdded(Sudoku *sudoku, int index)
{}

#ifdef HAS_HISTORY
void Sudoku::printHistory()
{
    for(auto &hist : history) {
        printf("%d => %d\n", hist.index, hist.value);
    }
}
#endif
