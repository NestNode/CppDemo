/**
 * Only Test
 *
 * Gets the selected content of any window
 *
 * ref: (It doesn't look like it can be done if you don't use a clipboard. But it's slowly when use clipboard)
 * - https://learn.microsoft.com/en-us/answers/questions/840881/how-to-get-selectedtext-from-other-applications
 * - https://stackoverflow.com/questions/21460943/how-to-get-selected-text-of-any-application-into-a-windows-form-application
 * - https://forums.codeguru.com/showthread.php?172312-How-get-SELECTED-text-from-another-application
 * - https://github.com/tauri-apps/tauri/discussions/5624
 *
 */

#include <windows.h>
#include <iostream>
#include <string>
#include <UIAutomation.h>
#include <comdef.h>

#pragma comment(lib, "uiautomationcore.lib")

// 定义全局快捷键
#define GLOBAL_HOTKEY 1

extern LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

// 将 BSTR 转换为 std::string
std::string BstrToStdString(BSTR bstr) {
    if (!bstr) return "";

    // 获取 BSTR 的长度
    int wslen = SysStringLen(bstr);
    // 计算转换为多字节字符串所需的长度
    int len = WideCharToMultiByte(CP_UTF8, 0, bstr, wslen, NULL, 0, NULL, NULL);
    // 创建指定长度的字符串
    std::string str(len, '\0');
    // 将 BSTR 转换为多字节字符串
    WideCharToMultiByte(CP_UTF8, 0, bstr, wslen, &str[0], len, NULL, NULL);

    return str;
}

// 获取选中的文本
std::string GetGlobalSelectedText() {
    IUIAutomation* automation = nullptr;
    IUIAutomationElement* rootElement = nullptr;
    IUIAutomationCondition* condition = nullptr;
    IUIAutomationElement* focusedElement = nullptr;
    IUIAutomationTextPattern* textPattern = nullptr;
    IUIAutomationTextRangeArray* textRanges = nullptr;
    IUIAutomationTextRange* textRange = nullptr;
    BSTR selectedText = nullptr;

    // 初始化 COM 库
    CoInitialize(NULL);
    // 创建 UI Automation 对象
    CoCreateInstance(CLSID_CUIAutomation, NULL, CLSCTX_INPROC_SERVER, IID_IUIAutomation, (void**)&automation);

    // 获取桌面根元素
    automation->GetRootElement(&rootElement);
    // 创建一个条件来查找焦点元素
    automation->CreateTrueCondition(&condition);
    // 查找具有焦点的元素
    rootElement->FindFirst(TreeScope_Subtree, condition, &focusedElement);

    if (focusedElement) {
        // 获取文本模式
        focusedElement->GetCurrentPatternAs(UIA_TextPatternId, IID_PPV_ARGS(&textPattern));
        if (textPattern) {
            // 获取选中的文本范围
            textPattern->GetSelection(&textRanges);
            if (textRanges) {
                // 获取第一个选中的文本范围
                textRanges->GetElement(0, &textRange);
                if (textRange) {
                    // 获取选中的文本
                    textRange->GetText(-1, &selectedText);
                }
            }
        }
    }

    std::string result;
    if (selectedText) {
        // 将 BSTR 转换为 std::string
        result = BstrToStdString(selectedText);
        SysFreeString(selectedText);
    }

    // 释放所有已分配的 COM 对象
    if (textRange) textRange->Release();
    if (textRanges) textRanges->Release();
    if (textPattern) textPattern->Release();
    if (focusedElement) focusedElement->Release();
    if (condition) condition->Release();
    if (rootElement) rootElement->Release();
    if (automation) automation->Release();

    // 取消初始化 COM 库
    CoUninitialize();

    return result;
}

// 窗口过程函数
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_HOTKEY:
            if (wParam == GLOBAL_HOTKEY) {
                // 当按下全局快捷键时获取选中的文本
                std::string selectedText = GetGlobalSelectedText();
                if (!selectedText.empty()) {
                    std::cout << "Selected Text: " << selectedText << std::endl;
                } else {
                    std::cout << "No text selected." << std::endl;
                }
            }
            break;
        case WM_DESTROY:
            // 当窗口销毁时退出消息循环
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

// 运行消息循环
void RunMessageLoop() {
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

// init
int ClipText_Init() {
    const char CLASS_NAME[]  = "GlobalHotkeyWindowClass";

    WNDCLASS wc = { };
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    // 注册窗口类
    RegisterClass(&wc);

    // 创建窗口
    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            "Global Hotkey Demo",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,
            NULL,
            GetModuleHandle(NULL),
            NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    // 隐藏窗口
    ShowWindow(hwnd, SW_HIDE);

    // 注册全局快捷键 (Ctrl + Shift + C)
    if (!RegisterHotKey(hwnd, GLOBAL_HOTKEY, MOD_CONTROL | MOD_SHIFT, 'C')) {
        std::cerr << "Failed to register hotkey." << std::endl;
        return 1;
    }

    // 运行消息循环
    RunMessageLoop();

    // 注销全局快捷键
    UnregisterHotKey(hwnd, GLOBAL_HOTKEY);
}
