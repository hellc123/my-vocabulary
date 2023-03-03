#pragma once
#ifndef _WORD_H_
#define _WORD_H_

#include<string>

//表示一个英语单词的类

class word
{
private:
	//单词
	std::string _word;
	//该单词的数量
	int _count;
public:
	word();
	word(std::string word);
	std::string getword();
	int getcount();
};



#endif // !_WORD_H_
