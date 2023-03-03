#pragma once
#ifndef _WORD_MAP_H_
#define _WORD_MAP_H_
#include<map>
#include<string>
#include<sstream>
//单词其的数量的图
class wordMap
{
private:
	std::map<std::string, int> _wordMap;
public:
	//插入一个单词，返回其现有的个数
	int insert(std::string word);
	//输出到字符串流
	std::ostringstream output(std::ostringstream& out);
};







#endif