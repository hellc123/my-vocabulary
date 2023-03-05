#include"wordProcess.h"

wordProcess::wordProcess(std::stringstream& in, wordMap& out)
{
	while (in)
	{
		std::string word = readWord(in);
		if (word.empty())
		{
			continue;
		}
		else if (word[0] == '-')
		{
			word = word.substr(word.find_last_of('-') + 1);
		}

		out.insert(word);
	}
}

std::string wordProcess::readWord(std::stringstream& in)
{
	//能够识别一个单词，包括带连字符的单词
	std::string word;
	while (in)
	{
		char alpha = '\0';
		alpha = char(in.get());

		if (isalpha(alpha))
		{
			word.push_back(tolower(alpha));
		}
		else if (alpha == '-' && isalpha(in.peek()))
		{
			word.push_back(tolower(alpha));
		}
		else
		{
			break;
		}
	}
	return word;
}
