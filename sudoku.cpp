#include "sudoku.h"

Sudoku::Sudoku()
{

}

//Index start at 0, row-major. First value of pair is the index, the second one is the value
Sudoku::Sudoku(const std::vector<std::pair<int, int>>& values)
{
	setValues(values);
}

//Index start at 0, row-major. First value of pair is the index, the second one is the value
void Sudoku::setValues(const std::vector<std::pair<int, int>>& values)
{
	for(auto& p : values)
		setValue(p.first, p.second);
}

//Index start at 0
void Sudoku::setValue(const int idx, const int v)
{
	int r = idx/9;
	int c = idx%9;
	grid[r][c].setOnlyOneValue(v);
	updateGrid(r, c, v);
}

//Update the possible values
void Sudoku::updateGrid(const int r, const int c, const int v)
{
	//Update current row
	for(int cc = 0; cc < 9; ++cc)
		if(cc != c)
			updateGridAction(r, cc, v);

	//Update current col
	for(int rr = 0; rr < 9; ++rr)
		if(rr != r)
			updateGridAction(rr, c, v);

	//Update current unit
	int ur = r/3;
	int uc = c/3;
	for(int rr = 0; rr < 3; ++rr)
		for(int cc = 0; cc < 3; ++cc)
			if(rr != r && cc != c)
				updateGridAction(3*ur+rr, 3*uc+cc, v);
}

void Sudoku::updateGridAction(const int r, const int c, const int v)
{
	if(grid[r][c].eraseValue(v) && grid[r][c].hasOnlyOnePossibleValue())
		updateGrid(r, c, grid[r][c].getFirstPossibleValue());
}

std::ostream& operator<<(std::ostream& os, const Sudoku& s)
{
	for(int r = 0; r < 9; ++r)
	{
		//Print row separators
		if(r%3 == 0)
		{
			//(Block::DEFAULT_VALUES.size()+1) = 9 possibles values + space, *9 because 9 blocks and +4 because 4 col separators
			for(int c = 0; c < (Block::DEFAULT_VALUES.size()+1)*9+4; ++c)
				os << Sudoku::ROW_SEPARATOR;
			os << std::endl;
		}

		for(int c = 0; c < 9; ++c)
		{
			//Print col sperators
			if(c%3 == 0)
				os << Sudoku::COL_SEPARATOR;
			os << s.grid[r][c] << Sudoku::BLOCK_SEPARATOR;
		}
		os << Sudoku::COL_SEPARATOR;
		os << std::endl;
	}

	//(Block::DEFAULT_VALUES.size()+1) = 9 possibles values + space, *9 because 9 blocks and +4 because 4 col separators
	for(int c = 0; c < (Block::DEFAULT_VALUES.size()+1)*9+4; ++c)
		os << Sudoku::ROW_SEPARATOR;

	return os;
}

bool Sudoku::isValid() const
{
	bool valid = true;
	//Check each row
	for(int r = 0; valid && r < 9; ++r)
		for(int c = 0; valid && c < 9; ++c)
			for(int cc = c+1; valid && cc < 9; ++cc)
				valid = grid[r][c] != grid[r][cc];

	//Check each col
	for(int c = 0; valid && c < 9; ++c)
		for(int r = 0; valid && r < 9; ++r)
			for(int rr = r+1; valid && rr < 9; ++rr)
				valid = grid[r][c] != grid[rr][c];

	//Check each unit, i.e. group of 9 blocks
	for(int ux = 0; valid && ux < 3; ++ux)
		for(int uy = 0; valid && uy < 3; ++uy)
		{
			int r = ux*3;
			int c = uy*3;
			std::vector<Block> unit;
			for(int rr = 0; rr < 3; ++rr)
				for(int cc = 0; cc < 3; ++cc)
					unit.push_back(grid[r+rr][c+cc]);

			//Check uniqueness of vector
			for(int i = 0;valid && i < unit.size(); ++i)
				for(int j = i+1;valid && j < unit.size(); ++j)
					valid = unit[i] != unit[j];
		}

	return valid;
}

bool Sudoku::isValidAndFull() const
{
	bool valid = true;
	for(int r = 0; valid && r < 9; ++r)
		for(int c = 0; valid && c < 9; ++c)
			valid = grid[r][c].hasOnlyOnePossibleValue();

	return valid ? isValid() : false;
}

//Solve using depth-first-search and using heuristic starting with the unit which has the minimum number of possibles solutions, then using first block.
bool Sudoku::solve(Sudoku& s)
{
	if(s.isValid())
		if(!s.isValidAndFull())
		{
			int ux, uy;
			s.findUnitToStartSolving(ux, uy);
			int bx = -1;
			int by = -1;

			for(int r = 0; bx == -1 && r < 3; ++r)
				for(int c = 0; bx == -1 && c < 3; ++c)
					if(!s.grid[3*uy+r][3*ux+c].hasOnlyOnePossibleValue())
					{
						bx = 3*uy+r;
						by = 3*ux+c;
					}

			std::vector<int> possibleValues = s.grid[bx][by].getPossibleValues();
			bool solved = false;
			for(int i = 0; !solved && i < possibleValues.size(); ++i)
			{
				Sudoku ss(s);
				ss.grid[bx][by].setOnlyOneValue(possibleValues[i]);
				ss.updateGrid(bx, by, possibleValues[i]);
				
				solved = solve(ss);
				if(solved)
					s = ss;
			}
			return solved;
		}
		else
			return true;
	else
		return false;
}	

void Sudoku::findUnitToStartSolving(int& uxMin, int& uyMin) const
{
	uxMin = uyMin = 0;
	int min = 9*9;

	for(int ux = 0; ux < 3; ++ux)
		for(int uy = 0; uy < 3; ++uy)
		{
			int currMin = 0;
			for(int r = 0; r < 3; ++r)
				for(int c = 0; c < 3; ++c)
					currMin += grid[uy*3+r][ux*3+c].countPossibleValues();
			if(currMin > 0 && currMin < min)
			{
				uxMin = ux;
				uyMin = uy;
				min = currMin;
			}
		}
}
