
#include "Application.h"

// Only include the windows headers if building for windows
#if defined(BUILD_WIN32) || defined(BUILD_WIN64)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

int main(int argc, char **argv)
{
	// See Project settings linker->input->delay loaded dlls
	// listed dll's will be loaded when they are first required
	// Here, we are adding a path for dlls to be loaded from
	#if defined(BUILD_WIN32)
		SetDllDirectory(L".\\libs\\x86\\");
	#elif defined(BUILD_WIN64)
		SetDllDirectory(L"./libs/x64/");
	#endif

	{
		Application app(argc, argv);
		if (app.Startup(640, 480, "SDL Project"))
		{
			app.Run();
			app.Shutdown();
		}
	}

	return 0;
}