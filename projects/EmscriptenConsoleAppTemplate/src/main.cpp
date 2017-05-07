
#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

#include "Application.h"

int main(int argc, char **argv)
{
	{
		BaseApplication app(argc, argv);
		app.Run();
	}

	return 0;
}