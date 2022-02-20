#include "Window.h"
#include "Logger.h"

void ErrorCallback(int error, const char* msg)
{
	CRESCENT_CORE_ERROR("An error has occured: {}", msg);
}


Window::Window()
{
	bInitialized = false;
	mWidth = 1280;
	mHeight = 720;
}

void Window::Initialize(WindowInfo& WindowInfo)
{
	CRESCENT_CORE_INFO("Initializing OpenGL window... ");
	// If already initialized, release
	if (bInitialized)
		Release();

	// Initialize GLFW
	if (!glfwInit())
	{
		CRESCENT_CORE_ERROR("Failed to initialize GLFW.");
		return;
	}

	glfwSetErrorCallback(ErrorCallback);
	glfwWindowHint(GLFW_SAMPLES, 4); // 4x AA
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Target OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	mGLFWwindow = glfwCreateWindow(WindowInfo.Width, WindowInfo.Height, WindowInfo.Title, nullptr, nullptr);

	if (!mGLFWwindow) {
		CRESCENT_CORE_ERROR("Failed to create GLFW window.");
		glfwTerminate();
		return;
	}

	// Initialize GLEW (OpenGL)
	glfwMakeContextCurrent(mGLFWwindow);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		CRESCENT_CORE_ERROR("Failed to initialize GLEW.");
		glfwTerminate();
		return;
	}
	glfwSetInputMode(mGLFWwindow, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(mGLFWwindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// if we're here then everything went fine.
	bInitialized = true;
	CRESCENT_CORE_INFO("OpenGL window initialized.");
}

void Window::Release()
{
	if (bInitialized)
	{
		glfwDestroyWindow(mGLFWwindow);
		glfwTerminate();
		mGLFWwindow = nullptr;
		bInitialized = false;
		CRESCENT_CORE_INFO("OpenGL window released.");
	}
}

void Window::PollEvents()
{
	glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(mGLFWwindow);
}

bool Window::WindowShouldClose() const
{
	return glfwWindowShouldClose(mGLFWwindow);
}
