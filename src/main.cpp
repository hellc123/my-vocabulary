#include<iostream>
#include<map>
#include<string>
int main()
{
	std::cout << "Hello World!" << std::endl;
	std::map<std::string, int> wmap;
	wmap.insert(std::pair<std::string, int>("bone1", 1));
	wmap.insert(std::pair<std::string, int>("aone1", 2));
	std::cout << (wmap.begin()->first) << std::endl;
	std::cout << ((++wmap.begin())->first) << std::endl;


	return 0;
}