#include "word.h"

word::word() :_word('\0'), _count(0)
{
	
}

word::word(std::string word) : _word(word),_count(0)
{
}

std::string word::getword()
{
	return _word;
}

int word::getcount()
{
	return _count;
}
