#pragma once


// predeclare the SDL_Window
struct SDL_Window;

class BaseApplication
{
public:

	BaseApplication(int argc, char **argv);
	virtual ~BaseApplication();

	bool Startup(int windowWidth, int windowHeight, const char *title);
	void Shutdown();

	void Run();
	void GameLoop();

	void Quit();

	unsigned int GetWindowWidth() const;
	unsigned int GetWindowHeight() const;

	unsigned int GetFps() const;

protected:
	virtual void Load();
	virtual void Unload();

	virtual void Update(float deltaTime);
	virtual void Draw();

private:

	// helper function to update the FPS
	void UpdateFPS(float deltaTime);

	// helper function to update the delta time variables
	void UpdateDeltaTime();

private:

	SDL_Window *m_sdlWindow = 0;

	int m_windowWidth = 0;
	int m_windowHeight = 0;

	bool m_quitApplication = false;

	// application running time variables
	float m_runningTime;
	float m_lastFrameRunningTime;
	float m_deltaTime;

	// fps calculation
	unsigned int m_fps;
	unsigned int m_fpsCount;
	float m_fpsIntervial;

private:
};