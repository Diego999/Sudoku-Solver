#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <ostream>
#include <algorithm>

class Block
{
public:
	Block():values(Block::DEFAULT_VALUES){}
	Block(int value){setOnlyOneValue(value);}
	~Block(){}

	bool hasOnlyOnePossibleValue() const {return values.size() == 1;}
	void setOnlyOneValue(const int v) {values.clear(); values.push_back(v);}
	void eraseValue(const int v)
	{
		if(values.size() > 1)
		{
			auto it = std::find(values.begin(), values.end(), v);
			if(it != values.end())
				values.erase(it);
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const Block& b)
	{
		for(auto& v : b.values)
			os << v;
		
		for(int i = 0; i < (DEFAULT_VALUES.size() - b.values.size()); ++i)
			os << SPACEMENT;
	
		return os;
	}

	bool operator==(const Block& b1) const
	{
		return (hasOnlyOnePossibleValue() && b1.hasOnlyOnePossibleValue()) ? values.front() == b1.values.front() : false;
	}

	bool operator!=(const Block& b1) const
	{
		return !operator==(b1);
	}

	static const std::vector<int> DEFAULT_VALUES;

private:	
	static const char SPACEMENT = ' ';

	std::vector<int> values;
};

const std::vector<int> Block::DEFAULT_VALUES = {1,2,3,4,5,6,7,8,9};

#endif