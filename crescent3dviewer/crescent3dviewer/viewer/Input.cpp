#include "Input.h"
#include "Engine.h"

Input* Input::sInstance = nullptr;

Input::Input()
{
    pWindow = Engine::GetInstance()->GetWindow()->GetContext();

    mKeyMap["Forward"] = GLFW_KEY_Z;
    mKeyMap["Backward"] = GLFW_KEY_S;
    mKeyMap["Right"] = GLFW_KEY_D;
    mKeyMap["Left"] = GLFW_KEY_Q;
    mKeyMap["Action"] = GLFW_KEY_SPACE;


    CRESCENT_CORE_INFO("Input listener initialized.");
}

Input::~Input()
{

}

Input* Input::GetInstance()
{
    if (sInstance)
        return sInstance;
    else
    {
        sInstance = new Input();
        return sInstance;
    }
}

void Input::Release()
{
    if (sInstance)
    {
        delete sInstance;
        sInstance = nullptr;
        CRESCENT_CORE_INFO("Input listener released.");
    }
}

bool Input::IsKeyPressedImpl(const char* Action)
{
    auto KeyCode = mKeyMap[Action];
    auto KeyState = glfwGetKey(pWindow, KeyCode);
    return (KeyState == GLFW_PRESS || KeyState == GLFW_REPEAT);
}

bool Input::IsMouseButtonPressedImpl(int Button)
{
    auto MouseState = glfwGetMouseButton(pWindow, Button);
    return (MouseState == GLFW_PRESS);
}

std::pair<float, float> Input::GetMouseXYImpl()
{
    double X, Y;
    glfwGetCursorPos(pWindow, &X, &Y);
    return std::make_pair((float)X, (float)Y);
}
