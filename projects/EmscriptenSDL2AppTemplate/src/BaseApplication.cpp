#include "BaseApplication.h"

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif



BaseApplication::BaseApplication(int argc, char **argv)
{

}
BaseApplication::~BaseApplication()
{

}

bool BaseApplication::Startup(int windowWidth, int windowHeight, const char *title)
{
	m_windowWidth = windowWidth;
	m_windowHeight = windowHeight;

	// initialise SDL
	SDL_Init(SDL_INIT_VIDEO);

	// Build the game window
	m_sdlWindow = SDL_CreateWindow(
		title, 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		m_windowWidth, m_windowHeight, 
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GLContext context = SDL_GL_CreateContext(m_sdlWindow);

	SDL_Renderer *renderer = SDL_CreateRenderer(
		m_sdlWindow, -1, SDL_RENDERER_ACCELERATED);

	// Initialise glew
	glewExperimental = GL_TRUE;
	GLenum glewInitResult = glewInit();

	// call derrived classes load method after the window has been created
	Load();

	return true;
}
void BaseApplication::Shutdown()
{
	// call the derrived classes unload method before quitting
	Unload();

	SDL_Quit();
}

struct GameLoopFunc
{
	static void Loop() {
		pApp->GameLoop();
	}
	static BaseApplication *pApp;
};
BaseApplication * GameLoopFunc::pApp = NULL;

void BaseApplication::Run()
{
	#ifdef __EMSCRIPTEN__

		// The browser requires the main loop to be executed in a callback
		// this way infinite loops do not crash the browser
		GameLoopFunc::pApp = this;
		emscripten_set_main_loop(GameLoopFunc::Loop, 0, 1);

	#else

		// On windows, we control our own main loop
		// run until the m_quitApplication has been set to true
		while (!m_quitApplication)
			GameLoop();

	#endif
}

void BaseApplication::GameLoop()
{
	UpdateDeltaTime();
	UpdateFPS(m_deltaTime);

	// Process Events for the frame
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		switch (e.type)
		{
			case SDL_QUIT: Quit(); break;
		}
	}

	// Preform Application Update logic
	Update(m_deltaTime);

	// Preform Application rendering logic
	Draw();

	// end of frame, swap the opengl back bufer
	SDL_GL_SwapWindow(m_sdlWindow);
}

void BaseApplication::Update(float deltaTime)
{

}

void BaseApplication::Draw()
{

}

void BaseApplication::Load()
{

}

void BaseApplication::Unload()
{

}

void BaseApplication::UpdateFPS(float deltaTime)
{
	m_fpsIntervial += m_deltaTime;
	m_fpsCount++;

	if (m_fpsIntervial > 0.5f) // update the fps every half second
	{
		m_fps = m_fpsCount * 2; // multiply by 2 because we are updateing every half second
		m_fpsCount = 0;
		m_fpsIntervial = 0;
	}
}

void BaseApplication::UpdateDeltaTime()
{
	m_lastFrameRunningTime = m_runningTime;
	m_runningTime = SDL_GetTicks() / 1000.0f;
	m_deltaTime = m_runningTime - m_lastFrameRunningTime;
}

void BaseApplication::Quit()
{
	m_quitApplication = true;
}

unsigned int BaseApplication::GetWindowWidth() const
{
	return m_windowWidth;
}

unsigned int BaseApplication::GetWindowHeight() const
{
	return m_windowHeight;
}

unsigned int BaseApplication::GetFps() const
{
	return m_fps;
}