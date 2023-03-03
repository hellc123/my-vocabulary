#include<iostream>
#include<map>
#include<string>
int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
		std::cout << argv[i] << std::endl;
	system("pause");
	return 0;
}