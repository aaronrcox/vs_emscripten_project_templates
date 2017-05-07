#include "Application.h"

#include <iostream>

BaseApplication::BaseApplication(int argc, char **argv)
{
	for(int i=0; i<argc; i++)
		std::cout << argv[i] << std::endl;
}

BaseApplication::~BaseApplication()
{

}

void BaseApplication::Run()
{
	std::cout << "Hello World" << std::endl;
}