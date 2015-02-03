#ifndef SUDOKU_H
#define SUDOKU_H

#include "block.h"

#include <array>
#include <vector>
#include <ostream>

class Sudoku
{
public:
	Sudoku();
	Sudoku(const std::vector<std::pair<int, int>>& values);

	friend std::ostream& operator<<(std::ostream& os, const Sudoku& s);

	void setValue(const int idx, const int v);
	void setValues(const std::vector<std::pair<int, int>>& values);

	bool isValid() const;
	bool isValidAndFull() const;

	static bool solve(Sudoku& s);

private:
	void updateGrid(const int r, const int c, const int v);
	void updateGridAction(const int r, const int c, const int v);

	void findUnitToStartSolving(int& uxMin, int& uyMin) const;

	static const char ROW_SEPARATOR = '-';
	static const char COL_SEPARATOR = '|';
	static const char BLOCK_SEPARATOR = ' ';

	std::array<std::array<Block, 9>, 9> grid;
};

#endif