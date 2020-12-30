#include "pch.h"
#include "../../obs-studio-master/libobs/obs-module.h"
#include <windows.h>

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam);

BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

LRESULT CALLBACK WindowProcessMessages(HWND hwnd, UINT msg, WPARAM param, LPARAM lparam) {
    switch (msg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hwnd, msg, param, lparam);
    }
}

OBS_DECLARE_MODULE()


#define ID_CMD 1

extern "C" void __declspec(dllimport) __stdcall FormMain();

bool obs_module_load(void)
{
    FormMain();

    const LPCWSTR CLASS_NAME = L"myWin32WindowClass";
    const char* Name = "Win32 Tutorial";
    WNDCLASS wc{};
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = L"myWin32WindowClass";
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpfnWndProc = WindowProcessMessages;
    RegisterClass(&wc);

    return true;
}

