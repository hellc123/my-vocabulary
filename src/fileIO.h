#pragma once
#ifndef _FILE_I_O_H_
#define _FILE_I_O_H_
#include<iostream>
#include<fstream>
#include<sstream>

//文件读
//输入一个文件路径
//返回一个 stringstream
//判断是否是文本文件
class fileI
{
public:
	//打开文件
	fileI(const char* filedir);
	//析构函数
	~fileI();
	//判断是否可用
	bool is_available();
	//返回stringstream
	std::stringstream* toSStream();
	//判断是否为文本文件
	bool isText();
protected:
	//从文件流装载到字符串流
	bool _isText();
	void load();
private:
	std::stringstream* _buff;
	std::ifstream* _fileI;
	bool _available;
	bool _istext;
};

//保存到文件
//输入一个原来文件的路径，在原来路径生成一个csv文件
class fileO
{
public:
	fileO(const char* dir, std::ostringstream& src);
protected:
	//返回文件名
	std::string getFileDir(const char* dir);
};


#endif