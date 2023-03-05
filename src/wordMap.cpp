#include"wordMap.h"

int wordMap::insert(std::string word)
{
	//先测试_wordMap中是否已经存在 word
	auto temp = _wordMap.find(word);
	if (temp == _wordMap.end())
		_wordMap.insert(std::pair<std::string, int>(word, 1));
	else
	{
		//_wordMap.insert(std::pair<std::string, int>(word, temp->second + 1));
		_wordMap[word]++;
	}
	return 0;
}

std::ostringstream& wordMap::output()
{
	out << "Total words number," << _wordMap.size() << std::endl;
	for (auto word : _wordMap)
	{
		out << word.first << "," << word.second << std::endl;
	}
	return out;
}
