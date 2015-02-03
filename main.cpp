#include <iostream>
#include "sudoku.h"

int main(int argc, char* argv[])
{
	//Hardest sudoku : http://www.mirror.co.uk/news/weird-news/worlds-hardest-sudoku-can-you-242294 
	std::string chain = "005300000800000020070010500400005300010070006003200080060500009004000030000009700";

	Sudoku s;
	for(int i = 0; i < chain.size(); ++i)
		if(chain[i] != '0')
			s.setValue(i, chain[i]-'0');

	std::cout << s << std::endl;
	Sudoku::solve(s);
	std::cout << s << std::endl;
	return 0;
}
