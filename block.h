#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <ostream>
#include <algorithm>

class Block
{
public:
	Block();
	Block(int value);
	~Block();

	void setOnlyOneValue(const int v);
	bool eraseValue(const int v);

	bool hasOnlyOnePossibleValue() const;
	int countPossibleValues() const;

	int getFirstPossibleValue() const;
	std::vector<int> getPossibleValues() const;

	friend std::ostream& operator<<(std::ostream& os, const Block& b);

	bool operator==(const Block& b1) const;
	bool operator!=(const Block& b1) const;

	static const std::vector<int> DEFAULT_VALUES;

private:	
	static const char SPACEMENT = ' ';

	std::vector<int> values;
};

#endif