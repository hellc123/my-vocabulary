#pragma once
#ifndef _WORD_PROCESS_H_
#define _WORD_PROCESS_H_
#include<sstream>
#include<string>
#include"wordMap.h"

//处理文章
//将stringstream流中的数据存到wordMap中
class wordProcess
{
public:
	wordProcess(std::stringstream& in, wordMap& out);
protected:
	//从流中读取一个单词
	std::string readWord(std::stringstream& in);
};

#endif