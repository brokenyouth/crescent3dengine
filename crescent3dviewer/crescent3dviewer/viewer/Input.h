#pragma once

#include <tuple>
#include <string>
#include <unordered_map>

struct GLFWwindow;

class Input
{
private:
	static Input* sInstance;
    GLFWwindow* pWindow;
    std::unordered_map<const char*, int> mKeyMap;
    std::unordered_map<const char*, int> mMouseButtonMap;
private:
    Input();
    ~Input();
public:
    static Input* GetInstance();
    void Release();
public:
    inline static bool IsKeyPressed(const char* Action) { return sInstance->IsKeyPressedImpl(Action); }
    inline static bool IsMouseButtonPressed(int Button) { return sInstance->IsMouseButtonPressedImpl(Button); }
    inline static std::pair<float, float> GetMouseXY() { return sInstance->GetMouseXYImpl(); }
private:
    bool IsKeyPressedImpl(const char* Action);
    bool IsMouseButtonPressedImpl(int Button);
    std::pair<float, float> GetMouseXYImpl();
};

