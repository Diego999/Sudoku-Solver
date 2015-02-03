#include "block.h"

const std::vector<int> Block::DEFAULT_VALUES = {1,2,3,4,5,6,7,8,9};

Block::Block():values(Block::DEFAULT_VALUES)
{

}

Block::Block(int value)
{
	setOnlyOneValue(value);
}

Block::~Block()
{

}

bool Block::hasOnlyOnePossibleValue() const 
{
	return values.size() == 1;
}

void Block::setOnlyOneValue(const int v) 
{
	values.clear(); values.push_back(v);
}

int Block::getFirstPossibleValue() const 
{
	return values.front();
}

int Block::countPossibleValues() const 
{
	if(values.size() == 1)
		return 0;
	else
		return values.size();
}

std::vector<int> Block::getPossibleValues() const {return values;}

//True if a value has been erased
bool Block::eraseValue(const int v)
{
	if(values.size() > 1)
	{
		auto it = std::find(values.begin(), values.end(), v);
		if(it != values.end())
			values.erase(it);
		return it != values.end();
	}
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const Block& b)
{
	for(auto& v : b.values)
		os << v;
	
	for(int i = 0; i < (Block::DEFAULT_VALUES.size() - b.values.size()); ++i)
		os << Block::SPACEMENT;

	return os;
}

bool Block::operator==(const Block& b1) const
{
	return (hasOnlyOnePossibleValue() && b1.hasOnlyOnePossibleValue()) ? values.front() == b1.values.front() : false;
}

bool Block::operator!=(const Block& b1) const
{
	return !operator==(b1);
}