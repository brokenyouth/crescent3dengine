#pragma once

#include <GL/glew.h>
#include "GLFW/glfw3.h"

struct WindowInfo
{
	int					Width;
	int					Height;
	const char*			Title;
};

class Window
{
private:
	int mWidth;
	int mHeight;
	bool bInitialized = false;

	GLFWwindow* mGLFWwindow = nullptr;

public:
	Window();
	virtual ~Window() { Release(); };

public:
	void Initialize(WindowInfo& WindowInfo);
	void Release();
	void PollEvents();
	void SwapBuffers();
	bool WindowShouldClose() const;
	inline GLFWwindow* GetContext() const { return mGLFWwindow; }
};

