#include "fileIO.h"

fileI::fileI(const char* filedir) :_fileI(nullptr), _buff(nullptr), _available(false), _istext(false)
{
	_fileI = new std::ifstream(filedir, std::ios::binary);
	//if (_fileI->is_open())
	//{
	//	if (_isText())
	//	{
	//		load();
	//		_istext = true;
	//		_available = true;
	//	}
	//	else
	//	{
	//		_fileI->close();
	//		_istext = false;
	//		_available = false;
	//	}
	//}
	//else
	//{
	//	_istext = false;
	//	_available = false;
	//}
	if (_fileI->is_open())
	{
		//std::cout << _isText();
		if (_isText())
		{
			_istext = true;
			_available = true;
			load();
		}
	}
}

fileI::~fileI()
{
	if (_fileI)
		delete _fileI;
	if (_buff)
		delete _buff;
}

bool fileI::is_available()
{
	return _available;
}

std::stringstream* fileI::toSStream()
{
	if (is_available())
		return _buff;
	return nullptr;
}

bool fileI::isText()
{
	return _istext;
}

bool fileI::_isText()
{
	_istext = true;
	for (int i = 0; i < 8000 && _fileI->good(); ++i)
	{
		if (int(_fileI->get()) == 0)
			_istext = false;
	}
	_fileI->clear();
	_fileI->seekg(0);
	return _istext;
}

void fileI::load()
{
	_buff = new std::stringstream;

	while (_fileI->good())
	{
		(*_buff) << char(_fileI->get());
	}
}

fileO::fileO(const char* dir, std::ostringstream& src)
{
	std::ofstream outputfile(getFileDir(dir));
	outputfile << src.str();
}

std::string fileO::getFileDir(const char* dir)
{
	std::string fdir(dir);
	auto pos = fdir.find_last_of('.');
	if (pos == -1)
		fdir.append(".csv");
	else
	{
		fdir = fdir.substr(0, pos) + std::string(".csv");
	}
	return fdir;
}
