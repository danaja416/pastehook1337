﻿//2024-09-19 21:20
#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <Mmsystem.h>
#include <thread>
#include <cstring>
#include <TlHelp32.h>
#include <time.h>
#include <ctime>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <compare>
#include <string>
#include <string_view>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <tchar.h>
#include <vfw.h>
#include <vector>
#include <io.h>
#include <gdiplus.h>
#include <gdiplusgraphics.h>
#include <dwmapi.h>
#include <urlmon.h>
#include <sapi.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "Dwmapi.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "sapi.lib")
#pragma comment(lib, "ole32.lib")
using namespace std;
namespace Variable//变量
{
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    constexpr float PI() noexcept//圆周率 π
    {//Variable::PI();
        return 3.14159265358;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int ValueAddress(int value) noexcept//转换16进制（可用于偏移修改）*X64游戏地址不需要转16进制
    {//Variable::ValueAddress(100);返回64
        stringstream ioss; //定义字符串流
        int s_temp; //存放转化后字符
        ioss << "0x" << setiosflags(ios::uppercase) << hex << value; //以十六制(大写)形式输出
        ioss >> s_temp;
        return s_temp;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int string_int_(string Str) noexcept//string转int
    {//Variable::string_int_("123");
        return atoi(Str.c_str());
    }
    //-------------------------------------------------------
    uintptr_t string_uint_(string Str) noexcept//string转uintptr_t
    {//Variable::string_uint_("0x16");
        uintptr_t Buffer; sscanf(Str.c_str(), "%X", &Buffer);
        return Buffer;
    }
    //-------------------------------------------------------
    float string_float_(string Str) noexcept//string转float
    {//Variable::string_float_("0.0623");
        return atof(Str.c_str());
    }
    //-------------------------------------------------------
    LPCWSTR string_LPCWSTR_(string Str) noexcept//string转换LPCWSTR
    {//Variable::string_LPCWSTR_("ABC");
        return wstring(Str.begin(), Str.end()).c_str();
    }
    //-------------------------------------------------------
    LPCWSTR string_wstring_(string Str) noexcept//转码 UTF-8 (为了显示中文)
    {//Variable::string_wstring_("你好");
        const auto len = MultiByteToWideChar(CP_UTF8, 0, Str.c_str(), -1, NULL, 0);
        wchar_t* wide_text = new wchar_t[len];
        MultiByteToWideChar(CP_UTF8, 0, Str.c_str(), -1, wide_text, len);
        const auto ReturnValue = wide_text; delete[] wide_text;//释放
        return ReturnValue;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    struct Vector2//用来储存坐标数据 XY
    {
        constexpr Vector2(const int x = 0, const int y = 0) noexcept :x(x), y(y) { }
        constexpr const Vector2 operator+(const Vector2 other) const noexcept { return Vector2{ x + other.x, y + other.y }; }
        constexpr const Vector2 operator-(const Vector2 other) const noexcept { return Vector2{ x - other.x, y - other.y }; }
        constexpr const Vector2 operator*(const int factor) const noexcept { return Vector2{ x * factor, y * factor }; }
        constexpr const Vector2 operator/(const int factor) const noexcept { return Vector2{ x / factor, y / factor }; }
        constexpr const Vector2 operator*(const float factor) const noexcept { return Vector2{ (int)(x * factor), (int)(y * factor) }; }
        constexpr const Vector2 operator/(const float factor) const noexcept { return Vector2{ (int)(x / factor), (int)(y / factor) }; }
        constexpr const Vector2 operator*(const double factor) const noexcept { return Vector2{ (int)(x * factor), (int)(y * factor) }; }
        constexpr const Vector2 operator/(const double factor) const noexcept { return Vector2{ (int)(x / factor), (int)(y / factor) }; }
        constexpr const BOOL IsZero() const noexcept { return x == 0 && y == 0; }//判断是否为0
        int x, y;//初始化变量
    };
    struct Vector3//用来储存坐标数据 XYZ
    {
        constexpr Vector3(const float x = 0, const float y = 0, const float z = 0) noexcept :x(x), y(y), z(z) { }
        constexpr const Vector3 operator+(const Vector3 other) const noexcept { return Vector3{ x + other.x, y + other.y, z + other.z }; }
        constexpr const Vector3 operator-(const Vector3 other) const noexcept { return Vector3{ x - other.x, y - other.y, z - other.z }; }
        constexpr const Vector3 operator*(const float factor) const noexcept { return Vector3{ x * factor, y * factor, z * factor }; }
        constexpr const Vector3 operator/(const float factor) const noexcept { return Vector3{ x / factor, y / factor, z / factor }; }
        constexpr const Vector3 ToAngle() const noexcept { return Vector3{ atan2(-z, hypot(x, y)) * (180.0f / (float)acos(-1)),atan2(y, x) * (180.0f / (float)acos(-1)),0 }; }
        constexpr const BOOL IsZero() const noexcept { return x == 0 && y == 0 && z == 0; }//判断是否为0
        float x, y, z;//初始化变量
    };
    struct Vector4//用来储存颜色数据 RGBA
    {
        constexpr Vector4(const int r = 0, const int g = 0, const int b = 0, const int a = 255) noexcept :r(r), g(g), b(b), a(a) {}
        constexpr const Vector4 operator+(const Vector4 other) const noexcept { return Vector4{ r + other.r, g + other.g, b + other.b, a }; }
        constexpr const Vector4 operator-(const Vector4 other) const noexcept { return Vector4{ r - other.r, g - other.g, b - other.b, a }; }
        constexpr const Vector4 operator*(const int factor) const noexcept { return Vector4{ r * factor, g * factor, b * factor, a }; }
        constexpr const Vector4 operator/(const int factor) const noexcept { return Vector4{ r / factor, g / factor, b / factor, a }; }
        constexpr const Vector4 operator*(const float factor) const noexcept { return Vector4{ (int)(r * factor), (int)(g * factor), (int)(b * factor), a }; }
        constexpr const Vector4 operator/(const float factor) const noexcept { return Vector4{ (int)(r / factor), (int)(g / factor), (int)(b / factor), a }; }
        constexpr const Vector4 operator*(const double factor) const noexcept { return Vector4{ (int)(r * factor), (int)(g * factor), (int)(b * factor), a }; }
        constexpr const Vector4 operator/(const double factor) const noexcept { return Vector4{ (int)(r / factor), (int)(g / factor), (int)(b / factor), a }; }
        constexpr const BOOL IsZero() const noexcept { return r == 0 && g == 0 && b == 0; }//判断是否为0
        constexpr const Vector4 D_Alpha(const int Alpha, const int Limit_s = 0) const noexcept { if (Alpha <= Limit_s)return { r,g,b,Limit_s }; else return { r,g,b,Alpha }; }//原有基础上设置特定透明度
        constexpr const Vector4 Re_Col() const noexcept//限制颜色值过量 (0~255)
        {
            Vector4 Color_Var = Vector4{ r,g,b,a };
            if (Color_Var.r <= 0)Color_Var.r = 0; else if (Color_Var.r >= 255)Color_Var.r = 255;
            if (Color_Var.g <= 0)Color_Var.g = 0; else if (Color_Var.g >= 255)Color_Var.g = 255;
            if (Color_Var.b <= 0)Color_Var.b = 0; else if (Color_Var.b >= 255)Color_Var.b = 255;
            if (Color_Var.a <= 0)Color_Var.a = 0; else if (Color_Var.a >= 255)Color_Var.a = 255;
            return Color_Var;
        }
        constexpr const Vector4 Min_Bri(const int Bri = 0) const noexcept//最小亮度
        {
            Vector4 Color_Var = Vector4{ r,g,b,a };
            if (Color_Var.r < Bri)Color_Var.r = Bri;
            if (Color_Var.g < Bri)Color_Var.g = Bri;
            if (Color_Var.b < Bri)Color_Var.b = Bri;
            return Color_Var;
        }
        constexpr const Vector4 Max_Bri(const int Bri = 0) const noexcept//最大亮度
        {
            Vector4 Color_Var = Vector4{ r,g,b,a };
            if (Color_Var.r > Bri)Color_Var.r = Bri;
            if (Color_Var.g > Bri)Color_Var.g = Bri;
            if (Color_Var.b > Bri)Color_Var.b = Bri;
            return Color_Var;
        }
        int r, g, b, a;//初始化变量
    };
    Vector4 BW_COLOR(int Color = 255, int Alpha = 255) noexcept { return { Color ,Color ,Color ,Alpha }; }//统一颜色 灰色
    Vector3 CalculateAngle(Vector3 localPosition, Vector3 enemyPosition, Vector3 viewAngles = { 0,0,0 }) noexcept { return ((enemyPosition - localPosition).ToAngle() - viewAngles); }
    struct view_matrix_t { float* operator[](int index) { return matrix[index]; }float matrix[4][4]; };//世界坐标转换屏幕坐标矩阵
    Vector3 WorldToScreen(int X, int Y, Vector3 Pos, view_matrix_t Matrix) noexcept//世界坐标转换屏幕坐标
    {
        float _x = Matrix[0][0] * Pos.x + Matrix[0][1] * Pos.y + Matrix[0][2] * Pos.z + Matrix[0][3];
        float _y = Matrix[1][0] * Pos.x + Matrix[1][1] * Pos.y + Matrix[1][2] * Pos.z + Matrix[1][3];
        float w = Matrix[3][0] * Pos.x + Matrix[3][1] * Pos.y + Matrix[3][2] * Pos.z + Matrix[3][3];
        _x *= 1.f / w; _y *= 1.f / w;
        float x = X / 2; float y = Y / 2;
        x += 0.5f * _x * X + 0.5f; y -= 0.5f * _y * Y + 0.5f;
        if (w >= 0.01f)return { x,y,w };
        else return { 9999,9999,9999 };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class CreateClassName>
    Vector2 Animation_Vec2(Vector2 To_VAlue, float Speed = 10) noexcept//Vector2坐标动画
    {
        if (Speed == 1)return To_VAlue;//无动画时直接返回
        static Vector2 ReturnValue = To_VAlue;
        if (To_VAlue.x > ReturnValue.x)ReturnValue.x += (To_VAlue.x - ReturnValue.x) / Speed + 1;
        else if (To_VAlue.x < ReturnValue.x)ReturnValue.x -= (ReturnValue.x - To_VAlue.x) / Speed + 1;
        if (To_VAlue.y > ReturnValue.y)ReturnValue.y += (To_VAlue.y - ReturnValue.y) / Speed + 1;
        else if (To_VAlue.y < ReturnValue.y)ReturnValue.y -= (ReturnValue.y - To_VAlue.y) / Speed + 1;
        return ReturnValue;
    }
    template<class CreateClassName>
    Vector3 Animation_Vec3(Vector3 To_VAlue, float Speed = 10) noexcept//Vector3坐标动画
    {
        if (Speed == 1)return To_VAlue;//无动画时直接返回
        static Vector3 ReturnValue = To_VAlue;
        if (To_VAlue.x > ReturnValue.x)ReturnValue.x += (To_VAlue.x - ReturnValue.x) / Speed + 1;
        else if (To_VAlue.x < ReturnValue.x)ReturnValue.x -= (ReturnValue.x - To_VAlue.x) / Speed + 1;
        if (To_VAlue.y > ReturnValue.y)ReturnValue.y += (To_VAlue.y - ReturnValue.y) / Speed + 1;
        else if (To_VAlue.y < ReturnValue.y)ReturnValue.y -= (ReturnValue.y - To_VAlue.y) / Speed + 1;
        if (To_VAlue.z > ReturnValue.z)ReturnValue.z += (To_VAlue.z - ReturnValue.z) / Speed + 1;
        else if (To_VAlue.z < ReturnValue.z)ReturnValue.z -= (ReturnValue.z - To_VAlue.z) / Speed + 1;
        return ReturnValue;
    }
    template<class CreateClassName>
    Vector4 Animation_Vec4(Vector4 To_VAlue, float Speed = 10) noexcept//Vector4颜色动画
    {
        if (Speed == 1)return To_VAlue;//无动画时直接返回
        if (Speed < 1)Speed = 1;//防止过量
        static Vector4 ReturnValue = To_VAlue;
        if (To_VAlue.r > ReturnValue.r)ReturnValue.r += (To_VAlue.r - ReturnValue.r) / Speed + 1;
        else if (To_VAlue.r < ReturnValue.r)ReturnValue.r -= (ReturnValue.r - To_VAlue.r) / Speed + 1;
        if (To_VAlue.g > ReturnValue.g)ReturnValue.g += (To_VAlue.g - ReturnValue.g) / Speed + 1;
        else if (To_VAlue.g < ReturnValue.g)ReturnValue.g -= (ReturnValue.g - To_VAlue.g) / Speed + 1;
        if (To_VAlue.b > ReturnValue.b)ReturnValue.b += (To_VAlue.b - ReturnValue.b) / Speed + 1;
        else if (To_VAlue.b < ReturnValue.b)ReturnValue.b -= (ReturnValue.b - To_VAlue.b) / Speed + 1;
        if (To_VAlue.a > ReturnValue.a)ReturnValue.a += (To_VAlue.a - ReturnValue.a) / Speed + 1;
        else if (To_VAlue.a < ReturnValue.a)ReturnValue.a -= (ReturnValue.a - To_VAlue.a) / Speed + 1;
        return ReturnValue;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<float> Ang_Pos(float 距离, float 角度) noexcept//角度转坐标2D (用于绘制或是计算)
    {//Variable::Ang_Pos(150, 180);
        float radian = ((角度) * 3.1415926535) / 180;
        return { 距离 * sin(radian),距离 * cos(radian) };
    }
    //-------------------------------------------------------
    vector<float> Ang_Pos_(int X, int Y, int Dis, float Ang, float Ang_ = 0) noexcept//角度距离转坐标
    {//Variable::Ang_Pos_(0, 0, 10, 10, 10);
        const float radian = ((Ang + Ang_) * 3.1415926535) / 180;
        vector<float> ReturnValue = { X + Dis * sin(radian),Y + Dis * cos(radian) };
        return ReturnValue;
    }
    //-------------------------------------------------------
    Vector3 Ang_Pos_Vec(Vector3 OG_Pos, int Dis, float Ang, float Ang_ = 0) noexcept//角度距离转坐标
    {//Variable::Ang_Pos_Vec({ 100,100,100 }, 10, 10, 10);
        const float radian = ((Ang + Ang_) * 3.1415926535) / 180;
        return { OG_Pos.x + Dis * sin(radian),OG_Pos.y + Dis * cos(radian),OG_Pos.z };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    float Pos_Angle(Vector3 Local_Pos, Vector3 Target_Pos, BOOL Fix360 = false) noexcept//坐标转角度
    {//Variable::Pos_Angle({ 0,0,0 }, { 10,10,10 });//Return 45
        const auto Point_Dis = Target_Pos - Local_Pos;
        auto ReturnValue = atan2(Point_Dis.y, Point_Dis.x) * (180.0f / (float)acos(-1)); if (Fix360 && ReturnValue < 0)ReturnValue += 360;//角度归一
        return ReturnValue;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//防止冲突
    float Animation(float 目标值, float Speed = 10, BOOL FixOff = false) noexcept//快到慢动画 Speed是百分比
    {//Variable::Animation<class Fast_to_Slow>(255);
        static float ReturnValue = 目标值;
        if (FixOff) { if (目标值 > ReturnValue)ReturnValue += (目标值 - ReturnValue) / Speed + 1; else if (目标值 < ReturnValue)ReturnValue -= (ReturnValue - 目标值) / Speed + 1; }
        else { if (目标值 > ReturnValue)ReturnValue += (目标值 - ReturnValue) / Speed; else if (目标值 < ReturnValue)ReturnValue -= (ReturnValue - 目标值) / Speed; }//修复偏值问题
        return ReturnValue;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    Vector4 Color_RE(Vector4 Color) noexcept//转换反色
    {//Variable::Color_RE({ 255,255,255 });
        return { 255 - Color.r,255 - Color.g, 255 - Color.b };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    float Coor_Dis_3D(Vector3 Pos_1, Vector3 Pos_2 = { 0,0,0 }) noexcept//3D坐标计算距离
    {//Variable::Coor_Dis_3D({ 100,100,100 }, { 10,10,10 });
        return hypot(hypot(Pos_1.x - Pos_2.x, Pos_1.y - Pos_2.y), Pos_1.z - Pos_2.z);
    }
    //-------------------------------------------------------
    float Coor_Dis_2D(Vector3 Pos_1, Vector3 Pos_2 = { 0,0,0 }) noexcept//2D坐标计算距离
    {//Variable::Coor_Dis_2D({ 100,100,100 }, { 10,10,10 });
        return hypot(Pos_1.x - Pos_2.x, Pos_1.y - Pos_2.y);
    }
    //-------------------------------------------------------
    float Coor_Dis_2D_Vec2(Variable::Vector2 Pos_1, Variable::Vector2 Pos_2) noexcept//2D坐标计算距离 Vector2版
    {//Variable::Coor_Dis_2D_Vec2({ 100,100 }, { 10,10 });
        return hypot(Pos_1.x - Pos_2.x, Pos_1.y - Pos_2.y);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Hex_String(uintptr_t Value) noexcept//10进制整数转换16进制字符转
    {//Variable::Hex_String(16); //return 0x10
        char Hex_str[1024];
        sprintf(Hex_str, "0x%X", Value);
        return Hex_str;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Float_Precision(float m_fValue, short Pre = 2) noexcept//保留小数值 (防止字符串过长)
    {//Variable::Float_Precision(0.12344); return 0.12
        stringstream Float_Value__;
        Float_Value__ << fixed << setprecision(Pre) << m_fValue;
        Float_Value__ >> m_fValue;
        return Float_Value__.str();
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL String_Find(string Str, string Find_Str) noexcept//查找字符串内是否有特定字符串
    {//Variable::String_Find("Hello Bro", "Hello"); return true
        if (Str.find(Find_Str) != string::npos)return true;
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string String_Upper(string Str) noexcept//英文字符串转大写
    {//Variable::String_Upper("Abc"); return "ABC"
        string STR = Str; transform(STR.begin(), STR.end(), STR.begin(), toupper);
        return STR;
    }
    //-------------------------------------------------------
    string String_Lower(string Str) noexcept//英文字符串转小写
    {//Variable::String_Lower("Abc"); return "abc"
        string STR = Str; transform(STR.begin(), STR.end(), STR.begin(), tolower);
        return STR;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class CLASS>//变量类型
    BOOL Dif_Value_Ran(CLASS Value_1, CLASS Value_2, CLASS Dif) noexcept//判断两个值之间的差值范围 (判断范围大于差值或是小于差值)
    {//Variable::Dif_Value_Ran(10, 15, 5);
        return abs(Value_1 - Value_2) < Dif;//True在范围内 False不在范围内
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string String_Delete(string Str, string DeleteStr = "") noexcept//删除特定字符
    {//Variable::String_Delete("Heello", "e");   return "hello";
        if (Str.find(DeleteStr) != string::npos)Str.erase(Str.find(DeleteStr), DeleteStr.length());//查找是否含有要删除的字符
        return Str;//未找到则返回默认字符
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    Variable::Vector3 Get_Move_Pos(Variable::Vector3 Pos) noexcept//获取指定坐标移动距离
    {//System::Get_Move_Pos({ 10, 100 }).x;
        static auto Old_Pos = Pos;
        if (Pos.x != Old_Pos.x || Pos.y != Old_Pos.y)
        {
            const Variable::Vector3 ReturnValue = { Pos.x - Old_Pos.x,Pos.y - Old_Pos.y };
            Old_Pos = Pos;
            return ReturnValue;
        }
        else return { 0,0 };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
}
namespace Window//窗口
{
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//防止同窗口冲突  不同的窗口改不同的类
    Variable::Vector4 Get_PixelColor(int X, int Y, HWND Window_HWND = 0) noexcept//采取屏幕颜色
    {//Window::Get_PixelColor<class Get_PixelColor>(100, 100).r;
        static auto Window_HDC = GetWindowDC(Window_HWND);
        const auto Pixel = GetPixel(Window_HDC, X, Y);
        return { GetRValue(Pixel), GetGValue(Pixel), GetBValue(Pixel) };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//防止同窗口冲突  不同的窗口改不同的类
    HDC GetDC(HWND Window_HWND, BOOL Reload = false) noexcept//无内存泄漏的窗口HDC获取
    {//Window::GetDC(NULL);
        static auto Window_HDC = GetDC(Window_HWND);
        if (Reload) { Window_HDC = GetDC(Window_HWND); Reload = false; }
        return Window_HDC;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    Variable::Vector2 Get_Resolution() noexcept//获取屏幕分辨率（像素）
    {//Window::Get_Resolution().x;
        return { GetSystemMetrics(SM_CXSCREEN) ,GetSystemMetrics(SM_CYSCREEN) };//[0]==X [1]==Y
    }
    //-------------------------------------------------------
    void Set_Resolution(int X, int Y) noexcept//模拟英伟达控制台更改像素 (只适用于系统已经创建的像素搭配!)
    {//Window::Set_Resolution(1440,1080);
        if (X != GetSystemMetrics(SM_CXSCREEN) || Y != GetSystemMetrics(SM_CYSCREEN))//设立条件防止放入循环崩溃
        {
            DEVMODE DevMode = {};
            EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &DevMode);
            DevMode.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT;
            DevMode.dmPelsWidth = X;
            DevMode.dmPelsHeight = Y;
            ChangeDisplaySettings(&DevMode, 0);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    Variable::Vector4 Get_WindowResolution(HWND WindowHWND) noexcept//获取窗口分辨率
    {//Window::Get_WindowResolution(FindWindow(NULL, L"WindowName")).r;
        RECT Window_Rect; GetWindowRect(WindowHWND, &Window_Rect);//窗口坐标 (包括标题栏)
        RECT Client_Rect; GetClientRect(WindowHWND, &Client_Rect);//显示区域坐标
        if ((Window_Rect.bottom - Window_Rect.top) != Client_Rect.bottom)return { Client_Rect.right, Client_Rect.bottom,  Window_Rect.left + 7, Window_Rect.bottom - Client_Rect.bottom - 8 };//窗口状态时 (带有标题栏)
        else return { Window_Rect.right - Window_Rect.left, Window_Rect.bottom - Window_Rect.top, Window_Rect.left, Window_Rect.top };//全屏窗口时
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_WindowResolution(HWND WindowHWND, int X, int Y, int W, int H) noexcept//修改窗口大小以及坐标
    {//Window::Set_WindowResolution(FindWindow(NULL, L"TestWindow"), 0, 0, 100, 100);
        MoveWindow(WindowHWND, X, Y, W, H, true);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_WindowLayeredColor(HWND WindowHWND, Variable::Vector4 Color, int Alpha, int Flags) noexcept//修改分层窗口属性颜色
    {//Window::Set_WindowLayeredColor(FindWindow(NULL, L"TestWindow"), { 0,0,0 }, 200, LWA_ALPHA | LWA_COLORKEY);
        if (Alpha < 0)Alpha = 0; else if (Alpha > 255)Alpha = 255;//限制透明度
        SetLayeredWindowAttributes(WindowHWND, RGB(Color.r, Color.g, Color.b), Alpha, Flags);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Get_WindowPID(string processName) noexcept//获取窗口PID   *如果快速循环使用占用高*
    {//Window::Get_WindowPID("explorer.exe");  //特定窗口名要任务管理器里面的
        uintptr_t processId = 0;
        PROCESSENTRY32 entrys = { };
        entrys.dwSize = sizeof(PROCESSENTRY32);
        const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//问题
        while (Process32Next(snapShot, &entrys))
        {
            if (wcscmp(entrys.szExeFile, wstring(processName.begin(), processName.end()).c_str()) == 0)
            {
                processId = entrys.th32ProcessID;
                OpenProcess(PROCESS_ALL_ACCESS, 0, processId);//开通权限
                break;
            }
        }
        CloseHandle(snapShot);
        return processId;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Get_ForegroundWindowName() noexcept//获取您正在活动时的窗口标题
    {//Window::Get_ForegroundWindowName();
        char NM[MAX_PATH]; GetWindowTextA(GetForegroundWindow(), NM, MAX_PATH);//获取窗口标题
        return NM;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_WindowEnable(HWND WindowHwnd) noexcept//获取您正在活动时的特定窗口标题是否为真
    {//Window::Get_WindowEnable(FindWindow(NULL, L"WindowName"));
        if (GetForegroundWindow() == WindowHwnd)return true; else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_WindowEnable_s(string processName) noexcept//获取您正在活动时的特定窗口标题是否为真(特定窗口名要任务管理器里面的)   *占用高*
    {//Window::Get_WindowEnable_s("explorer.exe");
        uintptr_t processId = 0;
        PROCESSENTRY32 entrys = { };
        entrys.dwSize = sizeof(PROCESSENTRY32);
        const auto snapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);//问题
        while (Process32Next(snapShot, &entrys))
        {
            if (wcscmp(entrys.szExeFile, wstring(processName.begin(), processName.end()).c_str()) == 0)
            {
                processId = entrys.th32ProcessID;
                OpenProcess(PROCESS_ALL_ACCESS, 0, processId);//开通权限
                break;
            }
        }
        CloseHandle(snapShot);
        DWORD ProcessID; GetWindowThreadProcessId(GetForegroundWindow(), &ProcessID);
        if (processId == ProcessID)return true;
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_WindowName(HWND WindowHWND, string Title) noexcept//修改特定窗口标题 修改之后再次修改要修改修改后的标题
    {//Window::Set_WindowName(FindWindow(NULL, L"TestWindow"),"Test Window 1");
        SetWindowText(WindowHWND, wstring(Title.begin(), Title.end()).c_str());//修改窗口标题
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    Variable::Vector2 Get_WindowPos(HWND WindowHWND) noexcept//获取窗口坐标
    {
        RECT Windowrect; GetWindowRect(WindowHWND, &Windowrect);
        return { Windowrect.left ,Windowrect.top };
    }
    Variable::Vector2 Get_WindowSize(HWND WindowHWND) noexcept//获取窗口大小
    {
        RECT Windowrect; GetWindowRect(WindowHWND, &Windowrect);
        return { Windowrect.right - Windowrect.left ,Windowrect.bottom - Windowrect.top };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Mini_Window(HWND Window_HWND) noexcept//最小化指定窗口
    {//Window::Mini_Window(FindWindowA(NULL, "Test Windows"));
        ShowWindow(Window_HWND, SW_MINIMIZE);
    }
    void Show_Window(HWND Window_HWND) noexcept//显示指定窗口
    {//Window::Show_Window(FindWindowA(NULL, "Test Windows"));
        SetForegroundWindow(Window_HWND);
        ShowWindow(Window_HWND, true);
    }
    void Hide_Window(HWND Window_HWND) noexcept//隐藏指定窗口
    {//Window::Hide_Window(FindWindowA(NULL, "Test Windows"));
        ShowWindow(Window_HWND, false);
    }
    void Kill_Window(HWND Window_HWND) noexcept//关闭指定窗口
    {//Window::Kill_Window(FindWindowA(NULL, "Test Windows"));
        DWORD ProcessID; GetWindowThreadProcessId(Window_HWND, &ProcessID);
        HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessID);
        TerminateProcess(hProcess, 0); CloseHandle(hProcess);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Message_Box(string Title, string Content, UINT MS = MB_OK) noexcept//弹出提示框(更方便选择返回值) 说明：https://blog.csdn.net/yuyan987/article/details/78558648
    {//Window::Message_Box("提示", "你的头上有点绿");
        return MessageBoxW(0, wstring(Content.begin(), Content.end()).c_str(), wstring(Title.begin(), Title.end()).c_str(), MS);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Hide_ConsoleWindow() noexcept//隐藏原控制台窗口
    {//Window::Hide_ConsoleWindow();
        ShowWindow(GetConsoleWindow(), false);//隐藏
    }
    void Show_ConsoleWindow() noexcept//显示原控制台窗口
    {//Window::Show_ConsoleWindow();
        ShowWindow(GetConsoleWindow(), true);//显示
    }
    void Set_ConsoleWindowTitle(string title) noexcept//修改原控制台窗口标题
    {//Window::Set_ConsoleWindowTitle("ah");
        system(("title " + title).c_str());
    }
    void Initialization_ConsoleWindow() noexcept//初始化控制台窗口 (初始化窗口大小, 清除字符)
    {//Window::Initialization_ConsoleWindow();
        system("cls");
        MoveWindow(GetConsoleWindow(), 10, 10, 600, 400, true);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    LRESULT WINAPI Window_Process_Loop(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) noexcept//窗口消息循环
    {
        switch (msg)
        {
        case WM_ERASEBKGND: return true; break;
        case WM_PAINT: return true; break;
        case WM_CLOSE: exit(0); break;
        }
        return DefWindowProcW(hwnd, msg, wp, lp);//定义回调函数的返回值
    }
    class Windows//更加方便的 窗口创建
    {
    private:
        int BKX, BKY; HWND Window_Hwnd;//GUI Window HWND
    public:
        //----------------------------------------------------------------------------------------
        HWND Create_Window(int Size_X, int Size_Y, string WindowName, BOOL IfTop, int WindowStyle = WS_POPUP, HWND hWndParent = 0) noexcept//创建窗口
        {
            int 窗口类型 = (WS_EX_LAYERED | WS_EX_TOOLWINDOW);
            if (IfTop)窗口类型 = (WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW);
            WNDCLASS RenderWindowM;
            memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = Window_Process_Loop;//关联消息处理函数,告诉操作系统，如果有事件发生调用这个函数
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(0);//实例句柄
            RenderWindowM.hIcon = LoadIcon(0, IDI_SHIELD);//图标
            RenderWindowM.hCursor = LoadCursor(0, IDC_ARROW);//光标样式
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//画刷
            RenderWindowM.lpszMenuName = 0;
            RenderWindowM.lpszClassName = wstring(WindowName.begin(), WindowName.end()).c_str();//窗口类的名称，操作系统根据类的名称做映射
            RegisterClass(&RenderWindowM);//将这个窗体注册（告诉）到操作系统
            const HWND hWnd = CreateWindowEx(//创建窗口
                窗口类型//窗口的扩展风格 不显示窗口图标
                , wstring(WindowName.begin(), WindowName.end()).c_str()//窗口类的名称，必须和上面的lpszClassName一致
                , wstring(WindowName.begin(), WindowName.end()).c_str()//窗口的标题
                , WindowStyle//窗口的风格 透明WS_POPUP 正常WS_CAPTION
                , GetSystemMetrics(SM_CXSCREEN) / 2 - Size_X / 2 //屏幕位置
                , GetSystemMetrics(SM_CYSCREEN) / 2 - Size_Y / 2
                , Size_X//宽高
                , Size_Y
                , hWndParent//父窗口
                , 0//系统菜单
                , GetModuleHandle(0)
                , 0//用户数据
            );
            if (hWnd)//更新显示
            {
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_ALPHA);
                Window_Hwnd = hWnd;
                BKX = Size_X;
                BKY = Size_Y;
            }
            return hWnd;
        }
        //----------------------------------------------------------------------------------------
        HWND Create_RenderBlock_Alpha(int Size_X, int Size_Y, string WindowName, HWND hWndParent = 0) noexcept//创建绘制画板(专门用于绘制的窗口 支持阿尔法 不支持颜色为0,0,0的图形绘制)
        {
            WNDCLASS RenderWindowM;
            memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = Window_Process_Loop;
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(0);
            RenderWindowM.hIcon = LoadIcon(0, IDI_SHIELD);
            RenderWindowM.hCursor = LoadCursor(0, IDC_ARROW);
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
            RenderWindowM.lpszMenuName = 0;
            RenderWindowM.lpszClassName = wstring(WindowName.begin(), WindowName.end()).c_str();
            RegisterClass(&RenderWindowM);
            const HWND hWnd = CreateWindowEx((WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW), wstring(WindowName.begin(), WindowName.end()).c_str(), wstring(WindowName.begin(), WindowName.end()).c_str(), WS_POPUP, 0, 0, Size_X, Size_Y, hWndParent, 0, GetModuleHandle(NULL), 0);
            if (hWnd)//更新显示
            {
                DWM_BLURBEHIND bb = { 0 };
                bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
                bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
                bb.fEnable = true;
                DwmEnableBlurBehindWindow(hWnd, &bb);
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
                Window_Hwnd = hWnd;
                BKX = Size_X;
                BKY = Size_Y;
            }
            return hWnd;
        }
        //----------------------------------------------------------------------------------------
        HWND Create_RenderBlock(int Size_X, int Size_Y, string WindowName, HWND hWndParent = 0) noexcept//创建绘制画板(专门用于绘制的窗口 不支持阿尔法 不支持颜色为0,0,0的图形绘制)
        {
            WNDCLASS RenderWindowM;
            memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = Window_Process_Loop;
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(0);
            RenderWindowM.hIcon = LoadIcon(0, IDI_SHIELD);
            RenderWindowM.hCursor = LoadCursor(0, IDC_ARROW);
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
            RenderWindowM.lpszMenuName = 0;
            RenderWindowM.lpszClassName = wstring(WindowName.begin(), WindowName.end()).c_str();
            RegisterClass(&RenderWindowM);
            const HWND hWnd = CreateWindowEx((WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW), wstring(WindowName.begin(), WindowName.end()).c_str(), wstring(WindowName.begin(), WindowName.end()).c_str(), WS_POPUP, 0, 0, Size_X, Size_Y, hWndParent, 0, GetModuleHandle(NULL), 0);
            if (hWnd)//更新显示
            {
                UpdateWindow(hWnd);
                ShowWindow(hWnd, SW_SHOW);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 0, LWA_COLORKEY);
            }
            Window_Hwnd = hWnd;
            BKX = Size_X;
            BKY = Size_Y;
            return hWnd;
        }
        //----------------------------------------------------------------------------------------
        void UpdateRenderBlock() noexcept//DeleteColor(Put in the while() and Update < Render)
        {
            static const auto WindowDC = GetWindowDC(Window_Hwnd);
            BitBlt(WindowDC, 0, 0, 99999, 99999, WindowDC, 0, 0, BLACKNESS);
        }
        //----------------------------------------------------------------------------------------
        void BackGround_Color(Variable::Vector4 Color = { 0,0,0,0 }) noexcept//绘制颜色背景
        {
            static const auto WindowDC = GetWindowDC(Window_Hwnd);
            const auto Color_Object = SelectObject(WindowDC, CreateSolidBrush(RGB(Color.r, Color.g, Color.b)));//颜色画笔
            BitBlt(WindowDC, 0, 0, 99999, 99999, WindowDC, 0, 0, PATCOPY);
            DeleteObject(Color_Object);//释放内存
        }
        //----------------------------------------------------------------------------------------
        HWND Get_HWND() noexcept { return Window_Hwnd; }//获取窗口HWND
        void Set_HWND(HWND WindowHWND) noexcept { Window_Hwnd = WindowHWND; }//修改窗口HWND
        //----------------------------------------------------------------------------------------
        Variable::Vector2 Get_WindowPos() noexcept//获取窗口坐标
        {
            RECT Windowrect;
            GetWindowRect(Window_Hwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            return { Windowrect.left ,Windowrect.top };
        }
        void Set_WindowPos(int X, int Y) noexcept//移动窗口到指定坐标
        {
            RECT Windowrect;
            GetWindowRect(Window_Hwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            MoveWindow(Window_Hwnd, X, Y, Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, TRUE);
        }
        //----------------------------------------------------------------------------------------
        Variable::Vector2 Get_WindowSize() noexcept//获取窗口大小
        {
            RECT Windowrect;
            GetWindowRect(Window_Hwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            return { Windowrect.right - Windowrect.left ,Windowrect.bottom - Windowrect.top };
        }
        void Set_WindowSize(int XX, int YY) noexcept//修改窗口大小
        {
            RECT Windowrect;
            GetWindowRect(Window_Hwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            BKY = Windowrect.bottom - Windowrect.top;
            MoveWindow(Window_Hwnd, Windowrect.left, Windowrect.top, XX, YY, true);
        }
        //----------------------------------------------------------------------------------------
        string Get_WindowTitle() noexcept//获取窗口标题
        {
            CHAR pszMem[MAX_PATH] = { 0 }; GetWindowTextA(Window_Hwnd, pszMem, GetWindowTextLength(Window_Hwnd) + 1);
            return pszMem;
        }
        void Set_WindowTitle(string WindowTitle) noexcept//修改窗口标题
        {
            SetWindowTextA(Window_Hwnd, WindowTitle.c_str());
        }
        //----------------------------------------------------------------------------------------
        void Set_WindowDeleteColor(Variable::Vector4 Color = { 0,0,0 }) noexcept//遍历删除特定颜色像素
        {
            SetLayeredWindowAttributes(Window_Hwnd, RGB(Color.r, Color.g, Color.b), 0, LWA_COLORKEY);
        }
        //----------------------------------------------------------------------------------------
        void Set_WindowAlpha(int Alpha = 255) noexcept//窗口整体阿尔法通道
        {
            if (Alpha <= 0)Alpha = 0; else if (Alpha >= 255)Alpha = 255;//限制
            SetLayeredWindowAttributes(Window_Hwnd, RGB(0, 0, 0), Alpha, LWA_ALPHA);
        }
        //----------------------------------------------------------------------------------------
        void Set_WindowAttributes(Variable::Vector4 Color = { 1,0,0 }, int Alpha = 200, DWORD Flags = LWA_COLORKEY | LWA_ALPHA) noexcept//修改分层窗口属性
        {
            SetLayeredWindowAttributes(Window_Hwnd, RGB(Color.r, Color.g, Color.b), Alpha, Flags);
        }
        //----------------------------------------------------------------------------------------
        void Show_Window() noexcept//强制显示窗口
        {
            SetForegroundWindow(Window_Hwnd);
            ShowWindow(Window_Hwnd, true);
        }
        void Hide_Window() noexcept//强制隐藏窗口
        {
            ShowWindow(Window_Hwnd, false);
        }
        //----------------------------------------------------------------------------------------
        BOOL Window_Move(int KD = 30) noexcept//移动窗口 KD = 宽度（放在循环）
        {
            MSG msg = { 0 };
            if (GetMessageW(&msg, 0, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            //-----------------------------以上为消息循环
            static BOOL 防止脱离 = false;
            static int OldX, OldY;
            POINT MousePos; RECT Windowrect;
            GetCursorPos(&MousePos); GetWindowRect(Window_Hwnd, &Windowrect);
            BKX = Windowrect.right - Windowrect.left;
            static BOOL 保存鼠标坐标 = false;
            if (GetForegroundWindow() == Window_Hwnd)//检测窗口是否在最前端
            {
                if ((MousePos.x - Windowrect.left >= 0 && MousePos.x - Windowrect.left <= BKX && MousePos.y - Windowrect.top >= 0 && MousePos.y - Windowrect.top <= KD) && GetAsyncKeyState(VK_LBUTTON) && !防止脱离)
                {
                    if (保存鼠标坐标)
                    {
                        OldX = (MousePos.x - Windowrect.left);
                        OldY = (MousePos.y - Windowrect.top);
                        保存鼠标坐标 = false;
                    }
                    MoveWindow(Window_Hwnd, MousePos.x - OldX, MousePos.y - OldY, Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, true);//移动窗口到鼠标坐标
                    防止脱离 = true;
                }
                else if (防止脱离 && GetAsyncKeyState(VK_LBUTTON))
                {
                    MoveWindow(Window_Hwnd, MousePos.x - OldX, MousePos.y - OldY, Windowrect.right - Windowrect.left, Windowrect.bottom - Windowrect.top, true);//移动窗口到鼠标坐标
                    return true;
                }
                else {
                    防止脱离 = false;
                    保存鼠标坐标 = true;
                    return false;
                }
            }
            else return false;
        }
        //----------------------------------------------------------------------------------------
        void Fix_inWhile() noexcept//修复窗口转圈
        {
            MSG msg = { 0 };
            if (GetMessageW(&msg, 0, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        //----------------------------------------------------------------------------------------
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    HWND Get_PIDtoHWND(DWORD dwProcessID) noexcept//通过pid获取窗口句柄
    {//Window::Get_PIDtoHWND(8102);
        HWND h = GetTopWindow(0);
        HWND retHwnd = 0;
        while (h)
        {
            DWORD pid = 0;
            DWORD dwTheardId = GetWindowThreadProcessId(h, &pid);
            if (dwTheardId != 0 && pid == dwProcessID && GetParent(h) == NULL && IsWindowVisible(h))retHwnd = h;
            h = GetNextWindow(h, GW_HWNDNEXT);
        }
        return retHwnd;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    DWORD Get_WindowPID(HWND dwHWND) noexcept//通过窗口HWND句柄获取窗口PID
    {//Window::Get_WindowPID(FindWindow(NULL, NULL));
        DWORD ProcessIDReturnValue;//进程
        GetWindowThreadProcessId(dwHWND, &ProcessIDReturnValue);//获取进程id
        return ProcessIDReturnValue;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    class Render//双缓冲2D绘制类 （将绘制信息转移到图像内一并绘制）
    {
        /*
        int main()
        {
            Window::Windows Window_Var;//window class
            Window_Var.Create_Window(500, 500, "Test Windows", true);//Create
            Window::Render Render_DoubleBuffer_BL;//render class
            Render_DoubleBuffer_BL.CreatePaint(Window_Var.Get_HWND(), 0, 0, 500, 500);//Create
            while (1)
            {
                Render_DoubleBuffer_BL.Render_SolidRect(0, 0, 99999, 99999, { 255,255,255 });
                Render_DoubleBuffer_BL.Render_Line(0, 0, 300, 200, { 0,0,0 });
                Render_DoubleBuffer_BL.Render_SmpStr(5, 5, "Hello my bro! 123456789 ABCabc !@#$%^&*().", { 255,200,0 });
                Render_DoubleBuffer_BL.Render_SolidRect(100, 400, 100, 100, { 255,0,0 });
                Render_DoubleBuffer_BL.RenderA_GradientCircle(150, 150, 200, { 255,255,255,255 }, { 0,0,0,255 }, 0.5);
                Render_DoubleBuffer_BL.DrawPaint();
                Window_Var.Fix_inWhile();//**
                Sleep(1);
            }
        }
        */
    private:
        HDC HdcWind, hMenDC;
        Variable::Vector2 StartPos, EndPos;
        int Draw_FPS;
    public:
        //--------------------------------------------------------------------------------------------------------
        HDC CreatePaint(HWND WindowHWND, int X, int Y, int XX, int YY) noexcept//创建画布 (画布大小设置的越高CPU占用也就越高)
        {
            //-----------------------------------------------------------初始化GDI+
            Gdiplus::GdiplusStartupInput gdiplusstartupinput; ULONG_PTR gdiplusToken;
            Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusstartupinput, nullptr);
            //---------------------------------------------------------------------
            StartPos = { X,Y }; EndPos = { XX,YY };
            HdcWind = GetWindowDC(WindowHWND);
            hMenDC = CreateCompatibleDC(HdcWind);
            SelectObject(hMenDC, CreateCompatibleBitmap(HdcWind, EndPos.x, EndPos.y));
            return hMenDC;
        }
        HDC Get_HDC() noexcept { return hMenDC; }//获取绘制HDC
        void Set_HDC(HDC WindowHDC) noexcept { HdcWind = WindowHDC; }//修改绘制HDC
        void DrawPaint(BOOL MessageLoop = false) noexcept//绘制画布（如果单单绘制到屏幕NULL依然会闪烁但是不会出现上下图层闪烁*）
        {
            BitBlt(HdcWind, StartPos.x, StartPos.y, EndPos.x, EndPos.y, hMenDC, 0, 0, SRCCOPY);
            //--------------------------------帧数计算
            static int m_fps = 0; m_fps++;
            const int Tick = GetTickCount64(); static int Tick_Old = Tick;
            if (Tick >= Tick_Old + 1000) { Tick_Old = Tick; Draw_FPS = m_fps; m_fps = 0; }
            //--------------------------------消息循环
            if (MessageLoop)
            {
                MSG msg = { 0 };
                if (GetMessageW(&msg, 0, 0, 0))
                {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }
            //----------------------------------------
        }
        int FPS() noexcept { return Draw_FPS; }//获取绘制帧数
        //--------------------------------------------------------------------------------------------------------以下为绘制函数
        void RenderA_Line(int X, int Y, int XX, int YY, Variable::Vector4 Color, int LineThickness = 1) noexcept//屏幕画线(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::Pen pen(Gdiplus::Color(Color.a, Color.r, Color.g, Color.b), LineThickness);
            HDCwind.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);//抗锯齿 https://blog.csdn.net/hgy413/article/details/6692932
            HDCwind.DrawLine(&pen, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientLine(int X, int Y, int XX, int YY, Variable::Vector4 Color_1, Variable::Vector4 Color_2, int LineThickness = 1) noexcept//屏幕画渐变直线(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::LinearGradientBrush linGrBrush(Gdiplus::Point(X, Y), Gdiplus::Point(XX + 1, YY + 1), Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b), Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b));
            Gdiplus::Pen pen(&linGrBrush, LineThickness);
            HDCwind.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);//抗锯齿 https://blog.csdn.net/hgy413/article/details/6692932
            HDCwind.DrawLine(&pen, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_SolidRect(int X, int Y, int XX, int YY, Variable::Vector4 Color) noexcept//绘制实心矩形(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::SolidBrush Pen(Gdiplus::Color(Color.a, Color.r, Color.g, Color.b));
            HDCwind.FillRectangle(&Pen, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_HollowRect(int X, int Y, int XX, int YY, Variable::Vector4 Color, int LineThickness = 1) noexcept//绘制空心矩形(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::Pen Pen(Gdiplus::Color(Color.a, Color.r, Color.g, Color.b), LineThickness);
            HDCwind.DrawRectangle(&Pen, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientRect(int X, int Y, int XX, int YY, Variable::Vector4 Color_1, Variable::Vector4 Color_2, BOOL Style = 0) noexcept//绘制渐变色矩形(包含Alpha) 0横向渐变 1竖向渐变
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            if (!Style)
            {
                Gdiplus::LinearGradientBrush Pen(Gdiplus::Point(X - 1, 0), Gdiplus::Point(X + XX + 1, 0), Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b), Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b));
                HDCwind.FillRectangle(&Pen, X, Y, XX, YY);
            }
            else {
                Gdiplus::LinearGradientBrush Pen(Gdiplus::Point(0, Y - 1), Gdiplus::Point(0, Y + YY + 1), Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b), Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b));
                HDCwind.FillRectangle(&Pen, X, Y, XX, YY);
            }
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_String(int X, int Y, string String, string Font, int FontSize, Variable::Vector4 Color, BOOL AntiAlias = true) noexcept//文字绘制(包含Alpha)
        {
            if (Font == "0" || Font == "NONE")Font = "Lucida Console";//默认字体
            Gdiplus::Graphics HDCwind(hMenDC);//HDC
            Gdiplus::FontFamily  fontFamily(wstring(Font.begin(), Font.end()).c_str());
            if (AntiAlias)HDCwind.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);//抗锯齿 https://learn.microsoft.com/en-us/windows/win32/api/gdiplusenums/ne-gdiplusenums-textrenderinghint
            else HDCwind.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);
            Gdiplus::Font font(&fontFamily, FontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);//字体状况(大小or斜体) https://learn.microsoft.com/en-us/windows/win32/api/gdiplusenums/ne-gdiplusenums-fontstyle
            const auto len = MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, 0, 0);//转码 UTF-8 (为了显示中文)
            wchar_t* wide_text = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, wide_text, len);//转码 UTF-8 (为了显示中文)
            Gdiplus::SolidBrush Brush_Shadow(Gdiplus::Color(Color.a / 1.5, 0, 0, 0));//阴影颜色
            HDCwind.DrawString(wide_text, -1, &font, Gdiplus::PointF(X + 1, Y + 1), &Brush_Shadow);
            Gdiplus::SolidBrush Brush_Text(Gdiplus::Color(Color.a, Color.r, Color.g, Color.b));//文字颜色
            HDCwind.DrawString(wide_text, -1, &font, Gdiplus::PointF(X, Y), &Brush_Text);
            delete[] wide_text;//释放
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientString(int X, int Y, string String, string Font, int FontSize, Variable::Vector4 Color_1, Variable::Vector4 Color_2, int GradientOffset = 0, BOOL AntiAlias = true) noexcept//渐变文字绘制(包含Alpha)
        {
            if (Font == "0" || Font == "NONE")Font = "Lucida Console";//默认字体
            Gdiplus::Graphics HDCwind(hMenDC);//HDC
            Gdiplus::FontFamily  fontFamily(wstring(Font.begin(), Font.end()).c_str());
            if (AntiAlias)HDCwind.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);//抗锯齿 https://learn.microsoft.com/en-us/windows/win32/api/gdiplusenums/ne-gdiplusenums-textrenderinghint
            else HDCwind.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);
            Gdiplus::Font font(&fontFamily, FontSize, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);//字体状况(大小or斜体) https://learn.microsoft.com/en-us/windows/win32/api/gdiplusenums/ne-gdiplusenums-fontstyle
            const auto len = MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, 0, 0);//转码 UTF-8 (为了显示中文)
            wchar_t* wide_text = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, wide_text, len);//转码 UTF-8 (为了显示中文)
            Gdiplus::SolidBrush Brush_Shadow(Gdiplus::Color(Color_1.a / 1.5, 0, 0, 0));//阴影颜色
            HDCwind.DrawString(wide_text, -1, &font, Gdiplus::PointF(X + 1, Y + 1), &Brush_Shadow);
            Gdiplus::LinearGradientBrush Brush_Text(Gdiplus::Point(X, 0), Gdiplus::Point(X + String.size() * FontSize / 1.7 + GradientOffset, 0), Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b), Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b));
            HDCwind.DrawString(wide_text, -1, &font, Gdiplus::PointF(X, Y), &Brush_Text);
            delete[] wide_text;//释放
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientCircle(int X, int Y, int Size, Variable::Vector4 Color_1, Variable::Vector4 Color_2, float Focus = 0.5f) noexcept//绘制路径渐变圆形(包含Alpha) 内到外
        {
            if (Size > 1000)return;
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::GraphicsPath m_Path;//构造空路径
            m_Path.AddEllipse(X - Size / 2, Y - Size / 2, Size, Size);//添加椭圆
            Gdiplus::PathGradientBrush pathBrush(&m_Path);//使用路径创建画刷
            pathBrush.SetCenterColor(Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b));//设置中心颜色
            Gdiplus::Color colors[] = { Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b) };//边界颜色
            int i = 1; pathBrush.SetSurroundColors(colors, &i);
            pathBrush.SetFocusScales(Focus, Focus);//设置聚焦缩放0-1 float
            HDCwind.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);//抗锯齿 https://blog.csdn.net/hgy413/article/details/6692932
            HDCwind.FillEllipse(&pathBrush, X - Size / 2, Y - Size / 2, Size, Size);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientEllipse(int X, int Y, int Size_X, int Size_Y, Variable::Vector4 Color_1, Variable::Vector4 Color_2, float Focus = 0.5f) noexcept//绘制路径渐变椭圆形(包含Alpha) 内到外
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::GraphicsPath m_Path;//构造空路径
            m_Path.AddEllipse(X - Size_X / 2, Y - Size_Y / 2, Size_X, Size_Y);//添加椭圆
            Gdiplus::PathGradientBrush pathBrush(&m_Path);//使用路径创建画刷
            pathBrush.SetCenterColor(Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b));//设置中心颜色
            Gdiplus::Color colors[] = { Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b) };//边界颜色
            int i = 1; pathBrush.SetSurroundColors(colors, &i);
            pathBrush.SetFocusScales(Focus, Focus);//设置聚焦缩放0-1 float
            HDCwind.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);//抗锯齿 https://blog.csdn.net/hgy413/article/details/6692932
            HDCwind.FillEllipse(&pathBrush, X - Size_X / 2, Y - Size_Y / 2, Size_X, Size_Y);
        }
        //------------------------------------------------------------------------------------------------
        void RenderA_GradientEllipse_2P(int X, int Y, int XX, int YY, Variable::Vector4 Color_1, Variable::Vector4 Color_2, float Focus = 0.5f) noexcept//绘制路径渐变椭圆形(包含Alpha) 内到外
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::GraphicsPath m_Path;//构造空路径
            m_Path.AddEllipse(X, Y, XX, YY);//添加椭圆
            Gdiplus::PathGradientBrush pathBrush(&m_Path);//使用路径创建画刷
            pathBrush.SetCenterColor(Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b));//设置中心颜色
            Gdiplus::Color colors[] = { Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b) };//边界颜色
            int i = 1; pathBrush.SetSurroundColors(colors, &i);
            pathBrush.SetFocusScales(Focus, Focus);//设置聚焦缩放0-1 float
            HDCwind.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);//抗锯齿 https://blog.csdn.net/hgy413/article/details/6692932
            HDCwind.FillEllipse(&pathBrush, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        void Render_Image(string ImageFile, int X, int Y, int XX, int YY) noexcept//屏幕图像绘制  CPU占用高 绘制慢*
        {
            Gdiplus::Graphics HDCwind(hMenDC);
            Gdiplus::Bitmap bmp(wstring(ImageFile.begin(), ImageFile.end()).c_str());
            HDCwind.DrawImage(&bmp, X, Y, XX, YY);
        }
        //------------------------------------------------------------------------------------------------
        int Render_String(int X, int Y, string String, string FontName, int FontSize, Variable::Vector4 Color, BOOL AntiAlias = true) noexcept//文字绘制(不包含Alpha)
        {
            const HDC HMS = hMenDC;
            auto Font_Style = DEFAULT_QUALITY;
            if (AntiAlias)Font_Style = NONANTIALIASED_QUALITY;
            const HGDIOBJ FontPen = SelectObject(HMS, CreateFont(FontSize, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, Font_Style, FF_DONTCARE, wstring(FontName.begin(), FontName.end()).c_str()));
            SetTextColor(HMS, RGB(Color.r, Color.g, Color.b));//文字颜色
            SetBkMode(HMS, TRANSPARENT);//背景透明
            TextOutA(HMS, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);//About CreateFont(): https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfonta
            return strlen(String.c_str());
        }
        //------------------------------------------------------------------------------------------------
        int Render_String_UTT(int X, int Y, string String, string FontName, int FontSize, Variable::Vector4 Color, BOOL AntiAlias = true) noexcept//文字绘制(不包含Alpha 可绘制中文)
        {
            const HDC HMS = hMenDC;
            auto Font_Style = DEFAULT_QUALITY;
            if (AntiAlias)Font_Style = NONANTIALIASED_QUALITY;
            const HGDIOBJ FontPen = SelectObject(HMS, CreateFont(FontSize, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, Font_Style, FF_DONTCARE, wstring(FontName.begin(), FontName.end()).c_str()));
            SetTextColor(HMS, RGB(Color.r, Color.g, Color.b));//文字颜色
            SetBkMode(HMS, TRANSPARENT);//背景透明
            const auto len = MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, 0, 0);//转码 UTF-8 (为了显示中文)
            wchar_t* wide_text = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, wide_text, len);//转码 UTF-8 (为了显示中文)
            TextOutW(HMS, X, Y, wide_text, len - 1);
            DeleteObject(FontPen);//About CreateFont(): https://learn.microsoft.com/en-us/windows/win32/api/wingdi/nf-wingdi-createfonta
            delete[] wide_text;
            return strlen(String.c_str());
        }
        //------------------------------------------------------------------------------------------------
        void Render_Line(int X, int Y, int XX, int YY, Variable::Vector4 Color, int LineThickness = 1) noexcept//屏幕画线(不包含Alpha 无抗锯齿)
        {
            const HDC DC = hMenDC;
            const HGDIOBJ LineColor = SelectObject(DC, CreatePen(PS_SOLID, LineThickness, RGB(Color.r, Color.g, Color.b)));
            MoveToEx(DC, X, Y, NULL);
            LineTo(DC, XX, YY);
            DeleteObject(LineColor);
        }
        //------------------------------------------------------------------------------------------------
        void Render_SolidRect(int X, int Y, int XX, int YY, Variable::Vector4 Color) noexcept//屏幕画实心矩形带颜色(不包含Alpha)
        {
            const HDC HMS = hMenDC;
            const HGDIOBJ BIANKUANG = SelectObject(HMS, CreatePen(PS_SOLID, 1, RGB(Color.r, Color.g, Color.b)));
            const HGDIOBJ TIANCHONG = SelectObject(HMS, CreateSolidBrush(RGB(Color.r, Color.g, Color.b)));
            Rectangle(HMS, X, Y, X + XX, Y + YY);
            DeleteObject(BIANKUANG);
            DeleteObject(TIANCHONG);
        }
        //------------------------------------------------------------------------------------------------
        void Render_HollowRect(int X, int Y, int XX, int YY, Variable::Vector4 Color, int LineThickness = 1) noexcept//屏幕画空心矩形带颜色(不包含Alpha)
        {
            const HDC HMS = hMenDC;
            const HGDIOBJ BIANKUANG = SelectObject(HMS, CreatePen(PS_SOLID, LineThickness, RGB(Color.r, Color.g, Color.b)));
            const HGDIOBJ TIANCHONG = SelectObject(HMS, (HBRUSH)GetStockObject(NULL_BRUSH));
            Rectangle(HMS, X, Y, X + XX, Y + YY);
            DeleteObject(BIANKUANG);
            DeleteObject(TIANCHONG);
        }
        //------------------------------------------------------------------------------------------------
        void Render_GradientRect(int X, int Y, int XX, int YY, Variable::Vector4 Color_1, Variable::Vector4 Color_2, BOOL Style = 0) noexcept//绘制渐变色矩形(不包含Alpha) 0横向渐变 1竖向渐变
        {
            TRIVERTEX vert[2];
            GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000;
            vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0;
            gRect.LowerRight = 1;
            const COLORREF Color1 = RGB(Color_1.r, Color_1.g, Color_1.b);
            const COLORREF Color2 = RGB(Color_2.r, Color_2.g, Color_2.b);
            vert[0].x = X;
            vert[0].y = Y;
            vert[1].x = X + XX;
            vert[1].y = Y + YY;
            vert[0].Red = GetRValue(Color1) << 8;
            vert[0].Green = GetGValue(Color1) << 8;
            vert[0].Blue = GetBValue(Color1) << 8;
            vert[1].Red = GetRValue(Color2) << 8;
            vert[1].Green = GetGValue(Color2) << 8;
            vert[1].Blue = GetBValue(Color2) << 8;
            if (!Style)GradientFill(hMenDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
            else GradientFill(hMenDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
        }
        //------------------------------------------------------------------------------------------------
        void Render_HollowCircle(int X, int Y, int Size, Variable::Vector4 Color, int LineThickness = 1) noexcept//绘制空心圆形(不包含Alpha 无抗锯齿)
        {
            const HDC wind = hMenDC;
            const HGDIOBJ BIANKUANG = SelectObject(wind, CreatePen(PS_SOLID, LineThickness, RGB(Color.r, Color.g, Color.b)));
            const HGDIOBJ TIANCHONG = SelectObject(wind, (HBRUSH)GetStockObject(NULL_BRUSH));
            Ellipse(wind, X - Size / 2, Y - Size / 2, X + Size / 2, Y + Size / 2);//通过绘制曲线来绘制圆*
            DeleteObject(BIANKUANG);
            DeleteObject(TIANCHONG);
        }
        //------------------------------------------------------------------------------------------------
        void Render_SolidCircle(int X, int Y, int Size, Variable::Vector4 Color_1, Variable::Vector4 Color_2, int LineThickness = 1) noexcept//绘制实心圆形(不包含Alpha 无抗锯齿)
        {
            const HDC wind = hMenDC;
            const HGDIOBJ BIANKUANG = SelectObject(wind, CreatePen(PS_SOLID, LineThickness, RGB(Color_1.r, Color_1.g, Color_1.b)));
            const HGDIOBJ TIANCHONG = SelectObject(wind, CreateSolidBrush(RGB(Color_2.r, Color_2.g, Color_2.b)));
            Ellipse(wind, X - Size / 2, Y - Size / 2, X + Size / 2, Y + Size / 2);//通过绘制曲线来绘制圆*
            DeleteObject(BIANKUANG);
            DeleteObject(TIANCHONG);
        }
        //------------------------------------------------------------------------------------------------
        void Render_GradientTriangle(vector<int> Pos_3Point, Variable::Vector4 Color_1, Variable::Vector4 Color_2, Variable::Vector4 Color_3) noexcept//绘制渐变色三角形（3种颜色）(不包含Alpha 无抗锯齿)
        {
            TRIVERTEX vert[3];
            GRADIENT_TRIANGLE gTRi;
            const COLORREF Color1 = RGB(Color_1.r, Color_1.g, Color_1.b);
            const COLORREF Color2 = RGB(Color_2.r, Color_2.g, Color_2.b);
            const COLORREF Color3 = RGB(Color_3.r, Color_3.g, Color_3.b);
            vert[0].x = Pos_3Point[0];
            vert[0].y = Pos_3Point[1];
            vert[1].x = Pos_3Point[2];
            vert[1].y = Pos_3Point[3];
            vert[2].x = Pos_3Point[4];
            vert[2].y = Pos_3Point[5];
            vert[0].Red = GetRValue(Color1) << 8;
            vert[0].Green = GetGValue(Color1) << 8;
            vert[0].Blue = GetBValue(Color1) << 8;
            vert[0].Alpha = 0x0000;
            vert[1].Red = GetRValue(Color2) << 8;
            vert[1].Green = GetGValue(Color2) << 8;
            vert[1].Blue = GetBValue(Color2) << 8;
            vert[1].Alpha = 0x0000;
            vert[2].Red = GetRValue(Color3) << 8;
            vert[2].Green = GetGValue(Color3) << 8;
            vert[2].Blue = GetBValue(Color3) << 8;
            vert[2].Alpha = 0x0000;
            gTRi.Vertex1 = 0;
            gTRi.Vertex2 = 1;
            gTRi.Vertex3 = 2;
            GradientFill(hMenDC, vert, 3, &gTRi, 1, GRADIENT_FILL_TRIANGLE);
        }
        //------------------------------------------------------------------------------------------------
        void Render_SmpStr(int X, int Y, string String, Variable::Vector4 Color_1, Variable::Vector4 Color_2 = { 0,0,0 }, BOOL Frame = true, int Font_Size = 9) noexcept//文字绘制(简单样式)(不包含Alpha)
        {
            const HDC Hdc = hMenDC;
            const HGDIOBJ FontPen = SelectObject(Hdc, CreateFont(Font_Size, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, L"Small Fonts"));
            SetBkMode(Hdc, TRANSPARENT);//背景透明
            if (Frame)
            {
                SetTextColor(Hdc, RGB(Color_2.r, Color_2.g, Color_2.b));//文字颜色
                TextOutA(Hdc, X + 1, Y + 1, String.c_str(), strlen(String.c_str()));
                TextOutA(Hdc, X - 1, Y - 1, String.c_str(), strlen(String.c_str()));
                TextOutA(Hdc, X + 1, Y - 1, String.c_str(), strlen(String.c_str()));
                TextOutA(Hdc, X - 1, Y + 1, String.c_str(), strlen(String.c_str()));
                TextOutA(Hdc, X + 1, Y, String.c_str(), strlen(String.c_str()));
                TextOutA(Hdc, X - 1, Y, String.c_str(), strlen(String.c_str()));
                TextOutA(Hdc, X, Y - 1, String.c_str(), strlen(String.c_str()));
                TextOutA(Hdc, X, Y + 1, String.c_str(), strlen(String.c_str()));
            }
            SetTextColor(Hdc, RGB(Color_1.r, Color_1.g, Color_1.b));//文字颜色
            TextOutA(Hdc, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        //--------------------------------------------------------------------------------------------------------
        void RenderA_SmpStr(int X, int Y, string String, Variable::Vector4 Color_1, Variable::Vector4 Color_2 = { 0,0,0 }, int Font_Size = 12) noexcept//文字绘制(简单样式)(包含Alpha)
        {
            Gdiplus::Graphics HDCwind(hMenDC);//HDC
            HDCwind.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);//不应用抗锯齿
            Gdiplus::FontFamily fontFamily(L"Calibri");//字体名字
            Gdiplus::Font font(&fontFamily, Font_Size, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);//字体状况
            if (Color_2.a != 0)
            {
                Gdiplus::SolidBrush Black_Brush(Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b));//文字颜色(边框)
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X + 1, Y + 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X - 1, Y - 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X + 1, Y - 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X - 1, Y + 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X + 1, Y), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X - 1, Y), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X, Y + 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X, Y - 1), &Black_Brush);
            }
            Gdiplus::SolidBrush Color_Brush(Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b));//文字颜色
            Gdiplus::PointF pointF(X, Y);//文字绘制坐标
            HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, pointF, &Color_Brush);//最终绘制
        }
        //--------------------------------------------------------------------------------------------------------
        void RenderA_SmpStr_Gra(int X, int Y, string String, Variable::Vector4 Color_1, Variable::Vector4 Color_2, Variable::Vector4 Color_3 = { 0,0,0 }, int Font_Size = 12, int GradientOffset = 0) noexcept//文字绘制(简单样式)(包含Alpha)(渐变版本)
        {
            Gdiplus::Graphics HDCwind(hMenDC);//HDC
            HDCwind.SetTextRenderingHint(Gdiplus::TextRenderingHintSingleBitPerPixelGridFit);//不应用抗锯齿
            Gdiplus::FontFamily fontFamily(L"Calibri");//字体名字
            Gdiplus::Font font(&fontFamily, Font_Size, Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);//字体状况
            if (Color_2.a != 0)
            {
                Gdiplus::SolidBrush Black_Brush(Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b));//文字颜色(边框)
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X + 1, Y + 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X - 1, Y - 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X + 1, Y - 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X - 1, Y + 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X + 1, Y), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X - 1, Y), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X, Y + 1), &Black_Brush);
                HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, Gdiplus::PointF(X, Y - 1), &Black_Brush);
            }
            Gdiplus::LinearGradientBrush Color_Brush(Gdiplus::Point(X, 0), Gdiplus::Point(X + String.size() * Font_Size / 1.7 + GradientOffset, 0), Gdiplus::Color(Color_1.a, Color_1.r, Color_1.g, Color_1.b), Gdiplus::Color(Color_2.a, Color_2.r, Color_2.g, Color_2.b));//文字颜色
            Gdiplus::PointF pointF(X, Y);//文字绘制坐标
            HDCwind.DrawString(wstring(String.begin(), String.end()).c_str(), -1, &font, pointF, &Color_Brush);//最终绘制
        }
        //--------------------------------------------------------------------------------------------------------
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    class D2D_Render
    {
    private://初始化D2D
        ID2D1HwndRenderTarget* Render_Target;//绘制目标
        HWND Render_Window_HWND;//绘制窗口HWND
        int Draw_FPS;//绘制帧数
        D2D1::ColorF D2DCol(Variable::Vector4 Color) noexcept { return D2D1::ColorF((float)Color.r / 255, (float)Color.g / 255, (float)Color.b / 255, (float)Color.a / 255); };
    public:
        //--------------------------------------------------------------------------------------------------------
        D2D_Render(HWND Render_HWND) noexcept//初始化Direct2D
        {
            if (!Render_HWND)return;
            Render_Window_HWND = Render_HWND;
            ID2D1Factory* Render_Factory; D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, &Render_Factory);
            RECT rc; GetClientRect(Render_Window_HWND, &rc);
            Render_Factory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(Render_Window_HWND, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top), D2D1_PRESENT_OPTIONS_IMMEDIATELY), &Render_Target);
            Render_Factory->Release();
        }
        HWND HWND() noexcept { return Render_Window_HWND; }//返回窗口HWND
        int FPS() noexcept { return Draw_FPS; }//返回绘制帧数
        ID2D1HwndRenderTarget* Target() noexcept { return Render_Target; }//返回绘制目标
        void Draw(BOOL State = false) noexcept//绘制画板函数
        {
            if (State)//0:开始绘制 1:结束绘制
            {
                Render_Target->EndDraw();
                static int m_fps = 0; m_fps++;
                const int Tick = GetTickCount64(); static int Tick_Old = Tick;
                if (Tick >= Tick_Old + 1000) { Tick_Old = Tick; Draw_FPS = m_fps; m_fps = 0; }
            }
            else Render_Target->BeginDraw();
        }
        void Anti_Alias(BOOL Anti = true) noexcept//抗锯齿设置
        {
            if (Anti)//开启抗锯齿
            {
                Render_Target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_FORCE_DWORD);//图形
                Render_Target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_DEFAULT);//文本
            }
            else//关闭抗锯齿
            {
                Render_Target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
                Render_Target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);
            }
        }
        //--------------------------------------------------------------------------------------------------------
        void Render_Clear(Variable::Vector4 Color = { 0,0,0 }) noexcept//清除画面
        {
            Render_Target->Clear(D2DCol(Color));
        }
        //--------------------------------------------------------------------------------------------------------
        void Render_Line(int X, int Y, int XX, int YY, Variable::Vector4 Color, int LineThickness = 1) noexcept//绘制线条
        {
            ID2D1SolidColorBrush* Brush; Render_Target->CreateSolidColorBrush(D2DCol(Color), &Brush);
            Render_Target->DrawLine(D2D1::Point2F(X, Y), D2D1::Point2F(XX, YY), Brush, LineThickness);
            Brush->Release();
        }
        void Render_GradientLine(int X, int Y, int XX, int YY, Variable::Vector4 Color_1, Variable::Vector4 Color_2, int LineThickness = 1) noexcept//绘制渐变线条
        {
            D2D1_GRADIENT_STOP gradientStops[2];
            gradientStops[0].color = D2DCol(Color_1); gradientStops[0].position = 0;
            gradientStops[1].color = D2DCol(Color_2); gradientStops[1].position = 1;
            ID2D1GradientStopCollection* pGradientStops; Render_Target->CreateGradientStopCollection(gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops);
            ID2D1LinearGradientBrush* Brush = 0; Render_Target->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(X, Y), D2D1::Point2F(XX, YY)), pGradientStops, &Brush);
            Render_Target->DrawLine(D2D1::Point2F(X, Y), D2D1::Point2F(XX, YY), Brush, LineThickness);
            Brush->Release();
            pGradientStops->Release();
        }
        //--------------------------------------------------------------------------------------------------------
        void Render_SolidRect(int X, int Y, int XX, int YY, Variable::Vector4 Color) noexcept//绘制实心矩形
        {
            ID2D1SolidColorBrush* Brush; Render_Target->CreateSolidColorBrush(D2DCol(Color), &Brush);
            Render_Target->FillRectangle(D2D1::RectF(X, Y, XX + X, YY + Y), Brush);
            Brush->Release();
        }
        void Render_HollowRect(int X, int Y, int XX, int YY, Variable::Vector4 Color, int LineThickness = 1) noexcept//绘制空心矩形
        {
            ID2D1SolidColorBrush* Brush; Render_Target->CreateSolidColorBrush(D2DCol(Color), &Brush);
            Render_Target->DrawRectangle(D2D1::RectF(X, Y, XX + X, YY + Y), Brush, LineThickness);
            Brush->Release();
        }
        void Render_GradientRect(int X, int Y, int XX, int YY, Variable::Vector4 Color_1, Variable::Vector4 Color_2, BOOL Style = 0) noexcept//绘制渐变矩形
        {
            D2D1_GRADIENT_STOP gradientStops[2];
            gradientStops[0].color = D2DCol(Color_1); gradientStops[0].position = 0;
            gradientStops[1].color = D2DCol(Color_2); gradientStops[1].position = 1;
            ID2D1GradientStopCollection* pGradientStops; Render_Target->CreateGradientStopCollection(gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops);
            ID2D1LinearGradientBrush* Brush = 0;
            if (Style)Render_Target->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(X, Y), D2D1::Point2F(X, YY)), pGradientStops, &Brush);
            else Render_Target->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(X, Y), D2D1::Point2F(XX, Y)), pGradientStops, &Brush);
            Render_Target->FillRectangle(D2D1::RectF(X, Y, XX + X, YY + Y), Brush);
            Brush->Release();
            pGradientStops->Release();
        }
        //--------------------------------------------------------------------------------------------------------
        void Render_SolidCircle(int X, int Y, int Size, Variable::Vector4 Color) noexcept//绘制实心圆
        {
            ID2D1SolidColorBrush* Brush; Render_Target->CreateSolidColorBrush(D2DCol(Color), &Brush);
            Render_Target->FillEllipse(D2D1::Ellipse(D2D1::Point2F(X, Y), Size / 2, Size / 2), Brush);
            Brush->Release();
        }
        void Render_HollowCircle(int X, int Y, int Size, Variable::Vector4 Color, int LineThickness = 1) noexcept//绘制空心圆
        {
            ID2D1SolidColorBrush* Brush; Render_Target->CreateSolidColorBrush(D2DCol(Color), &Brush);
            Render_Target->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(X, Y), Size / 2, Size / 2), Brush, LineThickness);
            Brush->Release();
        }
        void Render_GradientCircle(int X, int Y, int Size, Variable::Vector4 Color_1, Variable::Vector4 Color_2) noexcept//绘制渐变圆
        {
            D2D1_GRADIENT_STOP gradientStops[2];
            gradientStops[0].color = D2DCol(Color_1); gradientStops[0].position = 0;
            gradientStops[1].color = D2DCol(Color_2); gradientStops[1].position = 1;
            ID2D1GradientStopCollection* pGradientStops; Render_Target->CreateGradientStopCollection(gradientStops, 2, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_CLAMP, &pGradientStops);
            ID2D1RadialGradientBrush* Brush = 0; Render_Target->CreateRadialGradientBrush(D2D1::RadialGradientBrushProperties(D2D1::Point2F(X, Y), D2D1::Point2F(0, 0), Size / 2, Size / 2), pGradientStops, &Brush);
            Render_Target->FillEllipse(D2D1::Ellipse(D2D1::Point2F(X, Y), Size, Size), Brush);
            Brush->Release();
            pGradientStops->Release();
        }
        //--------------------------------------------------------------------------------------------------------
        void Render_String(int X, int Y, string String, Variable::Vector4 Color, string FontName = "Tahoma", int FontSize = 15)//绘制文字
        {
            Render_Target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_DEFAULT);
            ID2D1SolidColorBrush* Brush; IDWriteFactory* WriteFactory; IDWriteTextFormat* TextFormat;
            DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(WriteFactory), reinterpret_cast<IUnknown**>(&WriteFactory));
            WriteFactory->CreateTextFormat(wstring(FontName.begin(), FontName.end()).c_str(), 0, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, FontSize, L"", &TextFormat);
            const auto len = MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, 0, 0);
            wchar_t* wide_text = new wchar_t[len];
            MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, wide_text, len);
            Render_Target->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, Color.a / 255 / 2), &Brush);
            Render_Target->DrawText(wide_text, wcslen(wide_text), TextFormat, D2D1::RectF(X + 1, Y + 1, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Brush->Release();
            Render_Target->CreateSolidColorBrush(D2DCol(Color), &Brush);
            Render_Target->DrawText(wide_text, wcslen(wide_text), TextFormat, D2D1::RectF(X, Y, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Brush->Release();
            delete[] wide_text;
            WriteFactory->Release();
            TextFormat->Release();
        }
        //--------------------------------------------------------------------------------------------------------
        void Render_SimpStr(int X, int Y, string String, Variable::Vector4 Color_1, Variable::Vector4 Color_2 = { 0,0,0,200 })
        {
            Render_Target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_ALIASED);
            ID2D1SolidColorBrush* Brush; IDWriteFactory* WriteFactory; IDWriteTextFormat* TextFormat;
            DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(WriteFactory), reinterpret_cast<IUnknown**>(&WriteFactory));
            WriteFactory->CreateTextFormat(L"Ebrima", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 9, L"", &TextFormat);
            Render_Target->CreateSolidColorBrush(D2DCol(Color_2), &Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X + 1, Y + 1, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X - 1, Y - 1, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X + 1, Y - 1, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X - 1, Y + 1, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X + 1, Y, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X, Y + 1, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X - 1, Y, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X, Y - 1, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Brush->Release();
            Render_Target->CreateSolidColorBrush(D2DCol(Color_1), &Brush);
            Render_Target->DrawText(wstring(String.begin(), String.end()).c_str(), wcslen(wstring(String.begin(), String.end()).c_str()), TextFormat, D2D1::RectF(X, Y, Render_Target->GetSize().width, Render_Target->GetSize().height), Brush);
            Brush->Release();
            WriteFactory->Release();
            TextFormat->Release();
        }
        //--------------------------------------------------------------------------------------------------------
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    HWND NVIDIA_Overlay(Variable::Vector2 InitialSize = { 0,0 }) noexcept//英伟达覆盖绘制初始化(在上绘制不会导致背后窗口掉帧) 详细可查看: https://github.com/iraizo/nvidia-overlay-hijack/blob/master/src/overlay.cpp
    {//const auto Window_Render = Window::NVIDIA_Overlay();
        const auto Window_HWND = FindWindowW(L"CEF-OSC-WIDGET", L"NVIDIA GeForce Overlay");
        if (!Window_HWND)return 0;
        SetWindowLongPtrA(Window_HWND, -20, (LONG_PTR)(GetWindowLongA(Window_HWND, -20) | 0x20));
        MARGINS margin; margin.cyBottomHeight = margin.cyTopHeight = margin.cxLeftWidth = margin.cxRightWidth = -1;
        DwmExtendFrameIntoClientArea(Window_HWND, &margin);
        SetLayeredWindowAttributes(Window_HWND, RGB(0, 0, 0), 255, LWA_ALPHA);
        for (short i = 0; i <= 8; ++i)SetWindowPos(Window_HWND, HWND_TOPMOST, 0, 0, InitialSize.x, InitialSize.y, 0x0002 | 0x0001);
        MoveWindow(Window_HWND, 0, 0, InitialSize.x, InitialSize.y, true);
        ShowWindow(Window_HWND, SW_SHOW);
        return Window_HWND;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_Topmost_Status(HWND Window_HWND, BOOL IS_TOP = true) noexcept//修改窗口为最前端覆盖窗口 (可覆盖全屏游戏)
    {//Window::Set_Topmost_Status(WIndowHWND);
        SetWindowPos(Window_HWND, IS_TOP ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        CheckDlgButton(Window_HWND, 102, (DWORD)GetWindowLongPtr(Window_HWND, GWL_EXSTYLE) & WS_EX_TOPMOST);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_LimitWindowShow(HWND Window_HWND, BOOL Limit = false) noexcept//限制窗口显示 (绕过OBS捕捉)
    {//Window::Set_LimitWindowShow(WIndowHWND);
        if (Limit)SetWindowDisplayAffinity(Window_HWND, WDA_EXCLUDEFROMCAPTURE);
        else SetWindowDisplayAffinity(Window_HWND, WDA_NONE);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    HWND FindWindow_Name(string WindowName) noexcept//通过String字符串名称查找窗口
    {//Window::FindWindow_Name("Windowsaa");
        return FindWindow(0, wstring(WindowName.begin(), WindowName.end()).c_str());
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    namespace ScreenEffects//特殊屏幕抽象效果
    {
        const auto w = GetSystemMetrics(0), h = GetSystemMetrics(1);//显示器像素
        void PixelOffset(int Size = 300, int Distance = 10) noexcept//区块像素偏移
        {
            static const auto Scr_DC = GetWindowDC(0);
            srand(GetTickCount64()); auto size = rand() % Size; auto wsrc = rand() % w; auto hsrc = rand() % h;
            BitBlt(Scr_DC, wsrc + rand() % Distance, hsrc + rand() % Distance, size, size, Scr_DC, wsrc, hsrc, SRCCOPY);
            size = rand() % Size; wsrc = rand() % w; hsrc = rand() % h;
            BitBlt(Scr_DC, wsrc - rand() % Distance, hsrc - rand() % Distance, size, size, Scr_DC, wsrc, hsrc, SRCCOPY);
        }
        void Shake(int Amplitude = 30) noexcept//屏幕整体震动
        {
            static const auto Scr_DC = GetWindowDC(0); static const auto dcCopy = CreateCompatibleDC(Scr_DC); srand(GetTickCount64());
            SelectObject(dcCopy, CreateCompatibleBitmap(Scr_DC, w, h));
            StretchBlt(dcCopy, rand() % Amplitude, rand() % Amplitude, w, h, Scr_DC, rand() % Amplitude, rand() % Amplitude, w, h, SRCCOPY);
            StretchBlt(Scr_DC, 0, 0, w, h, dcCopy, 0, 0, w, h, SRCCOPY);
        }
        void ReloadScreen(int RowPixel = 10) noexcept//老式显示器刷新屏幕效果
        {
            static const auto Scr_DC = GetWindowDC(0); srand(GetTickCount64());
            for (int y = 0; y < h; y += RowPixel)
            {
                const auto zx = 10 * sin(2 * 3.1415 * y * (rand() % 70 - 40) / h);
                BitBlt(Scr_DC, 0, y, w - zx, RowPixel, Scr_DC, zx, y, SRCCOPY);
            }
        }
        void Blur(int Alpha = 150) noexcept//渐渐模糊
        {
            static const auto Scr_DC = GetWindowDC(0); static const auto dcCopy = CreateCompatibleDC(Scr_DC);
            srand(GetTickCount64()); SelectObject(dcCopy, CreateCompatibleBitmap(Scr_DC, w, h));
            BLENDFUNCTION blur = { 0 }; blur.BlendOp = AC_SRC_OVER; blur.BlendFlags = 0; blur.AlphaFormat = 0; blur.SourceConstantAlpha = Alpha;
            StretchBlt(dcCopy, rand() % 10, rand() % 10, w, h, Scr_DC, rand() % -10, rand() % -10, w, h, SRCCOPY);
            AlphaBlend(Scr_DC, 0, 0, w, h, dcCopy, 0, 0, w, h, blur);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
}
namespace System//系统
{
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    ULONGLONG Tick() noexcept//本地系统滴答值
    {//System::Tick();
        return GetTickCount64();
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    Variable::Vector4 RainbowColor(int Speed, const float Follo = 0) noexcept//彩虹色值
    {//System::RainbowColor(100);//颜色变换速度 (越大越慢)
        return { (int)floor(sin((float)GetTickCount64() / (Speed * 100) * 2 - Follo) * 127 + 128), (int)floor(sin((float)GetTickCount64() / (Speed * 100) * 2 + 2 - Follo) * 127 + 128), (int)floor(sin((float)GetTickCount64() / (Speed * 100) * 2 + 4 - Follo) * 127 + 128),255 };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Source_ExecuteCommand(string String, const HWND m_hEngine = FindWindow(L"Valve001", 0)) noexcept//起源引擎游戏执行命令
    {//System::Source_ExecuteCommand("kill");
        COPYDATASTRUCT m_cData; m_cData.cbData = strlen(String.c_str()) + 1; m_cData.dwData = 0; m_cData.lpData = (void*)String.c_str();
        SendMessage(m_hEngine, WM_COPYDATA, 0, (LPARAM)&m_cData);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Get_SystemMetrics(int Index = 0) noexcept//获取鼠标指针状态 https://learn.microsoft.com/ko-kr/windows/win32/api/winuser/nf-winuser-getsystemmetrics
    {//System::Get_SystemMetrics();
        return GetSystemMetrics(Index);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Mouse_Move(int X, int Y, BOOL HighSensitivity = false) noexcept//移动鼠标至附加坐标(可实现游戏内改变视觉角度)
    {//System::Mouse_Move(100, 100);
        if (HighSensitivity) { X /= 3; Y /= 3; }//高DPI移动过大问题
        mouse_event(MOUSEEVENTF_MOVE, X, Y, 0, 0);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Key_Click(int VK_CODE, BOOL Sleep_ = false, int SCAN_CODE = 0) noexcept//按下弹起键盘上的某个键位 VK_CODE: https://docs.microsoft.com/zh-cn/windows/win32/inputdev/virtual-key-codes
    {//System::Key_Click(VK_RETURN);
        //https://www.win.tue.nl/~aeb/linux/kbd/scancodes-1.html
        keybd_event(VK_CODE, SCAN_CODE, 0, 0);
        if (Sleep_)Sleep(1);
        keybd_event(VK_CODE, SCAN_CODE, KEYEVENTF_KEYUP, 0);
        if (Sleep_)Sleep(1);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Key_Click_HWND(HWND Window_HWND, int VK_CODE, BOOL Sleep_ = false) noexcept//向指定窗口按下弹起键盘上的某个键位
    {//System::Key_Click_HWND(0, VK_RETURN);
        SendMessage(Window_HWND, WM_KEYDOWN, VK_CODE, 0);
        if (Sleep_)Sleep(1);
        SendMessage(Window_HWND, WM_KEYUP, VK_CODE, 0);
        if (Sleep_)Sleep(1);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Mouse_Click(int VK_CODE, BOOL Sleep_ = false) noexcept//按下弹起鼠标上的某个键位
    {//System::Mouse_Click(1);
        if (VK_CODE == 1)
        {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            if (Sleep_)Sleep(1);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            if (Sleep_)Sleep(1);
        }
        else if (VK_CODE == 2)
        {
            mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            if (Sleep_)Sleep(1);
            mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
            if (Sleep_)Sleep(1);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Key_Con(int VK_CODE, BOOL WAY = false, int SCAN_CODE = 0) noexcept//按下或松开按键 SCAN_CODE: https://www.cnblogs.com/sherlockhomles/archive/2013/05/21/3090050.html
    {//System::Key_Con(VK_SPACE);//release space key
        if (WAY)keybd_event(VK_CODE, SCAN_CODE, 0, 0);
        else keybd_event(VK_CODE, SCAN_CODE, KEYEVENTF_KEYUP, 0);
    }
    void Key_Con_HWND(HWND Window_HWND, int VK_CODE, BOOL WAY = false) noexcept//向指定窗口按下或松开按键
    {//System::Key_Con_HWND(0, VK_SPACE);//release space key
        if (WAY)SendMessage(Window_HWND, WM_KEYDOWN, VK_CODE, 0);
        else SendMessage(Window_HWND, WM_KEYUP, VK_CODE, 0);
    }
    void Mouse_Con(int VK_CODE, BOOL WAY = false) noexcept//按下或松开鼠标按键 (不需要扫描码)
    {//System::Mouse_Con(0x1);//release mouseleft key
        if (VK_CODE == 1)
        {
            if (WAY)mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            else mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        }
        else if (VK_CODE == 2)
        {
            if (WAY)mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
            else mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    Variable::Vector2 Get_MousePos() noexcept//获取鼠标坐标
    {//System::GetMousePos().x;
        POINT XY; GetCursorPos(&XY);
        return { XY.x, XY.y };
    }
    void Set_MousePos(Variable::Vector2 Pos = { 0,0 }) noexcept//修改鼠标坐标
    {//System::Set_MousePos({100, 100});
        SetCursorPos(Pos.x, Pos.y);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Play_Sound_WAV(string Str_WAV) noexcept//播放WAV文件（声音）（同时播放2个文件会中断）
    {//System::Play_Sound_WAV("D:\\SteamLibrary\\steamapps\\common\\Counter-Strike Global Offensive\\55.wav");
        PlaySound(wstring(Str_WAV.begin(), Str_WAV.end()).c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Open_Website(string Link) noexcept//打开浏览器网址
    {//System::Open_Website("https://www.baidu.com/");
        system(("start " + Link).c_str());
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<int> Time() noexcept//获取系统时间
    {//System::Time()[0];
        SYSTEMTIME sys; GetLocalTime(&sys);
        return { sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute, sys.wSecond,sys.wMilliseconds,sys.wDayOfWeek };//0=年份 1=月份 2=天 3=小时 4=分钟 5=秒 6=毫秒 7=星期几
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Time_String() noexcept//获取系统时间(有了格式的String)
    {//string Time = System::Time_String();
        SYSTEMTIME sys;
        GetLocalTime(&sys);
        string Hour = to_string(sys.wHour);
        string Minute = to_string(sys.wMinute);
        string Second = to_string(sys.wSecond);
        if (sys.wHour < 10)Hour = "0" + Hour;
        if (sys.wMinute < 10)Minute = "0" + Minute;
        if (sys.wSecond < 10)Second = "0" + Second;
        return Hour + ":" + Minute + ":" + Second;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Create_Folder(string filename) noexcept//创建文件夹(空文件夹)
    {//System::Create_Folder("Test Folder");
        system(("mkdir " + filename).c_str());
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Judge_File(string FileName) noexcept//判断 文件or夹 是否存在
    {//System::Judge_File("Test File.txt");
        return _access(FileName.c_str(), 0) != -1;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    void Create_File(string FileName, string Content = "") noexcept//生成任何文件 详细: https://blog.csdn.net/qq_29406323/article/details/81261926
    {//System::Create_File("Test File.txt","1\n2\n3\n");
        if (_access(FileName.c_str(), 0) == -1)//当文件不存在时
        {
            fstream foundfile(FileName.c_str(), ios::out);
            if (foundfile.is_open())foundfile << Content.c_str(); foundfile.close();
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    string Get_File(string FileName, int Row = 1) noexcept//获取文件信息中的特定行数
    {//System::Get_File("Test File.txt", 2);
        if (_access(FileName.c_str(), 0) != -1)//当文件存在时
        {
            ifstream infile; infile.open(FileName, ios::in);//将文件流对象与文件连接起来 
            static char str[2048];//初始化缓冲区
            for (int i = 0; i < Row; i++)infile.getline(str, sizeof(str));//遍历
            infile.close();//关闭文件输入流 
            return str;
        }
        else return "";
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_File(string FileName, string Content = "", BOOL Append = false) noexcept//改写任何文件 详细: https://blog.csdn.net/qq_29406323/article/details/81261926
    {//System::Set_File("Test File.txt","1\n2\n3\n");
        if (_access(FileName.c_str(), 0) != -1)//当文件存在时
        {
            if (Append)//继续上文写入
            {
                fstream foundfile(FileName.c_str(), ios::app);
                if (foundfile.is_open())foundfile << Content.c_str(); foundfile.close();
            }
            else {//修改
                fstream foundfile(FileName.c_str(), ios::out);
                if (foundfile.is_open())foundfile << Content.c_str(); foundfile.close();
            }
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    void Delete_File(string FileName) noexcept//删除任何文件
    {//System::Delete_File("Test File.txt");
        remove(FileName.c_str());
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//为了防止双函数同步
    BOOL Key_Toggle(int key) noexcept//切换模式按键触发 另一种写法：GetKeyState(VK_TAB)
    {//System::Key_Toggle<class Key_Toggle>(VK_TAB);
        static BOOL keys = false;
        if (!keys && (GetAsyncKeyState(key) & 0x8000))
        {
            keys = true;
            keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
        }
        else if (keys && (GetAsyncKeyState(key) & 0x8000))
        {
            keys = false;
            keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
        }
        return keys;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Copy(string String) noexcept//复制指定内容到剪贴板 (汉子会乱码 解决方法：输入法调成中文)
    {//System::Copy("汉子 中 !@# abc");
        OpenClipboard(NULL);//打开剪切板
        EmptyClipboard();//清空剪切板
        const HANDLE hHandle = GlobalAlloc(GMEM_FIXED, strlen(String.c_str()) + 1);//分配内存
        char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
        strcpy_s(pData, strlen(String.c_str()) + 1, String.c_str());//或strcpy(pData, "this is a ClipBoard Test.");
        SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
        GlobalUnlock(hHandle);//解除锁定
        CloseClipboard();//关闭剪切板
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Stickup() noexcept//粘贴剪切板内容 (按键脚本)
    {//System::Stickup();
        keybd_event(VK_CONTROL, 0, 0, 0);//按下ctrl
        keybd_event(0x56, 0x2F, 0, 0);//按下v
        keybd_event(0x56, 0x2F, KEYEVENTF_KEYUP, 0);//松开v
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);//松开ctrl
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Copy_Stickup(string String) noexcept//复制粘贴 (汉子会乱码 解决方法：输入法调成中文)
    {//System::Copy_Stickup("汉子 中 !@# abc");
        OpenClipboard(0);//打开剪切板
        EmptyClipboard();//清空剪切板
        const HANDLE hHandle = GlobalAlloc(GMEM_FIXED, strlen(String.c_str()) + 1);//分配内存
        char* pData = (char*)GlobalLock(hHandle);//锁定内存，返回申请内存的首地址
        strcpy_s(pData, strlen(String.c_str()) + 1, String.c_str());//或strcpy(pData, "this is a ClipBoard Test.");
        SetClipboardData(CF_TEXT, hHandle);//设置剪切板数据
        GlobalUnlock(hHandle);//解除锁定
        CloseClipboard();//关闭剪切板
        keybd_event(VK_CONTROL, 0, 0, 0);//按下ctrl
        keybd_event(0x56, 0x2F, 0, 0);//按下v
        keybd_event(0x56, 0x2F, KEYEVENTF_KEYUP, 0);//松开v
        keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);//松开ctrl
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Rand_Number(int 以上, int 以下, int Srand_ = 0) noexcept//随机数（每次都不同）
    {//System::Rand_Number(0, 1000);//返回0~1000随机整数
        srand(GetTickCount64() + time(0) * GetTickCount64() + Srand_);//防止一样的函数同步
        return rand() % (以下 - 以上 + 1) + 以上;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Get_UserName() noexcept//获取电脑用户名
    {//System::Get_UserName();
        char szBuffer[256];
        DWORD dwNameLen = 256;
        GetUserNameA(szBuffer, &dwNameLen);
        return (string)szBuffer;
    }
    string Get_ComputerName() noexcept//获取电脑名
    {//System::Get_ComputerName();
        char szBuffer[256];
        DWORD dwNameLen = 256;
        GetComputerNameA(szBuffer, &dwNameLen);
        return (string)szBuffer;
    }
    string Get_IPv4Address() noexcept//获取电脑IPv4地址
    {//System::Get_IPv4Address();
        WSADATA WSAData;//WSADATA结构被用来储存调用AfxSocketInit全局函数返回的Windows Sockets初始化信息。
        WSAStartup(MAKEWORD(2, 0), &WSAData);//初始化Windows sockets API
        char hostName[256];
        gethostname(hostName, sizeof(hostName));
        return inet_ntoa(*(struct in_addr*)*gethostbyname(hostName)->h_addr_list);
        //WSACleanup();
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Anti_click() noexcept//防止控制台程序选择暂停(控制台窗口内绘制菜单需要它(虽然人们不会在控制台窗口内绘制XD))
    {//System::Anti_click();
        DWORD mode; GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
        mode &= ~ENABLE_QUICK_EDIT_MODE; SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Self_Delete(string SelfName = "*.exe") noexcept//程序自删除 输入自身程序名即可删除掉自身
    {//System::Self_Delete();
        const auto DeleteBatFile = fopen("...bat", "w");
        fputs(("del " + SelfName + "\ndel ...bat\n").c_str(), DeleteBatFile);
        system("start ...bat\n");
        exit(0);//结束进程
    }
    void Self_Restart() noexcept//重启自身程序
    {//System::Self_Restart();
        TCHAR szPath[MAX_PATH]; GetModuleFileName(0, szPath, MAX_PATH);
        STARTUPINFO StartInfo; PROCESS_INFORMATION procStruct;
        memset(&StartInfo, 0, sizeof(STARTUPINFO));
        StartInfo.cb = sizeof(STARTUPINFO);
        if (!CreateProcess((LPCTSTR)szPath, 0, 0, 0, 0, NORMAL_PRIORITY_CLASS, 0, 0, &StartInfo, &procStruct));//创建自身克隆体
        CloseHandle(procStruct.hProcess); CloseHandle(procStruct.hThread);
        exit(0);//关闭自身
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL MousePos_RectRegion(int StartPosX, int StartPosY, int EndPosX, int EndPosY) noexcept//检测鼠标是否在一个矩形区域内
    {//System::MousePos_RectRegion(100,100,200,200);
        POINT MousePos; GetCursorPos(&MousePos);
        if (MousePos.x >= StartPosX && MousePos.x <= StartPosX + EndPosX && MousePos.y >= StartPosY && MousePos.y <= StartPosY + EndPosY)return true; else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Get_Hold_VKKey() noexcept//获取当前按下的键（VK码 16进制）
    {//printf("0x%X\n", System::Get_Hold_VKKey());
        for (int i = 0x01; i < 0xFE; ++i)if (GetAsyncKeyState(i) & 0x8000)return i; return 0;//vk键码遍历 返回按下的键的vk码
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_Mouse_Move() noexcept//获取鼠标是否移动
    {//System::Get_Mouse_Move();
        POINT MousePos; GetCursorPos(&MousePos);
        static POINT Old_MousePos = MousePos;
        if (MousePos.x != Old_MousePos.x || MousePos.y != Old_MousePos.y) { Old_MousePos = MousePos; return true; }
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    Variable::Vector2 Get_Mouse_Move_Pos() noexcept//获取鼠标移动距离
    {//System::Get_Mouse_Move_Pos().x;
        POINT MousePos; GetCursorPos(&MousePos);
        static POINT Old_MousePos = MousePos;
        if (MousePos.x != Old_MousePos.x || MousePos.y != Old_MousePos.y)
        {
            const Variable::Vector2 ReturnValue = { MousePos.x - Old_MousePos.x,MousePos.y - Old_MousePos.y };
            Old_MousePos = MousePos;
            return ReturnValue;
        }
        else return { 0,0 };
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void DownloadToPath(string Str_URL, string Str_DownloadPath) noexcept//下载文件到目录 当返回true则下载成功 如果要下载的文件大于300kb那么下载的几率会很低
    {//System::DownloadToPath("https://codeload.github.com/cazzwastaken/internal-bhop/zip/refs/heads/main", "C:\\TestFile.zip")
        byte Temp[1024]; ULONG Number = 1; FILE* stream; HINTERNET hSession = InternetOpen(L"RookIE/1.0", INTERNET_OPEN_TYPE_PRECONFIG, 0, 0, 0);
        if (hSession)
        {
            HINTERNET handle2 = InternetOpenUrl(hSession, wstring(Str_URL.begin(), Str_URL.end()).c_str(), 0, 0, INTERNET_FLAG_DONT_CACHE, 0);
            if (handle2)
            {
                if ((stream = fopen(Str_DownloadPath.c_str(), "wb")) != 0)
                {
                    while (Number > 0)
                    {
                        InternetReadFile(handle2, Temp, 1024, &Number);
                        fwrite(Temp, sizeof(char), Number, stream);
                    }
                    fclose(stream);
                }
                InternetCloseHandle(handle2); handle2 = 0;
            }
            InternetCloseHandle(hSession); hSession = 0;
        }
        Sleep(1000);//缓冲时间 (给与一定的下载时间)
        if (_access(Str_DownloadPath.c_str(), 0) == -1)return;//如果在第一个下载方式上成功那么直接返回
        //两种下载方式相结合 (为了降低下载失败的几率)
        for (short i = 0; i <= 5; ++i)//下载循环 (防止下载失败)
        {
            const auto Download_State = URLDownloadToFile(0, wstring(Str_URL.begin(), Str_URL.end()).c_str(), wstring(Str_DownloadPath.begin(), Str_DownloadPath.end()).c_str(), 0, 0);//下载函数
            if (Download_State != S_OK)continue;//未下载成功则重来
            Sleep(1500);//缓冲时间 (给与一定的下载时间)
            if (_access(Str_DownloadPath.c_str(), 0) == -1)continue;//未找到下载的文件则重来
            return;//以上条件全部通过则返回函数 (终止循环)
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Sleep_ns(int ns) noexcept//纳秒单位等待函数 10000 = 1毫秒 比Sleep(1);更低的延时(前提设置的值在10000以内*)
    {//System::Sleep_ns(100); //= Sleep(0.1);
        this_thread::sleep_for(chrono::nanoseconds(ns));//纳秒单位等待函数
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    class PlaySounds
    {
        /*
        System::PlaySounds ss;
        ss.Open("TestWAV.mp3");
        ss.Play();
        */
    public:
        //-------------------------------------------------------
        void Open(string File) noexcept//打开音频文件(必须项* 如果放到循环需要把Sleep函数值设置到100以上*)
        {
            WCHAR wszClassName[1024];//转换
            memset(wszClassName, 0, sizeof(wszClassName));
            MultiByteToWideChar(CP_ACP, 0, ("open " + File + " alias SoundP").c_str(), strlen(("open " + File + " alias SoundP").c_str()) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
            mciSendString(wszClassName, 0, 0, 0);//https://stackoverflow.com/questions/38154985/string-to-lpcwstr-in-c
        }
        //-------------------------------------------------------
        void Play() noexcept//播放打开的音频文件
        {
            mciSendString(L"play SoundP", 0, 0, 0);
        }
        //-------------------------------------------------------
        void Play_Repeat() noexcept//循环播放打开的音频文件
        {
            mciSendString(L"play SoundP repeat", 0, 0, 0);
        }
        //-------------------------------------------------------
        void Stop() noexcept//暂停播放
        {
            mciSendString(L"pause SoundP", 0, 0, 0);
        }
        //-------------------------------------------------------
        void Resume() noexcept//继续播放
        {
            mciSendString(L"resume SoundP", 0, 0, 0);
        }
        //-------------------------------------------------------
        void Seek(int Ms) noexcept//快进快退
        {
            WCHAR wszClassName[1024];//转换
            memset(wszClassName, 0, sizeof(wszClassName));
            MultiByteToWideChar(CP_ACP, 0, ("seek SoundP to " + to_string(Ms)).c_str(), strlen(("seek SoundP to " + to_string(Ms)).c_str()) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
            mciSendString(wszClassName, 0, 0, 0);
            mciSendString(L"play SoundP", 0, 0, 0);
        }
        //-------------------------------------------------------
        void Volume(int Ints) noexcept//设置音量(百分比)
        {
            WCHAR wszClassName[1024];//转换
            memset(wszClassName, 0, sizeof(wszClassName));
            MultiByteToWideChar(CP_ACP, 0, ("setaudio SoundP volume to " + to_string(Ints) + "0").c_str(), strlen(("setaudio SoundP volume to " + to_string(Ints) + "0").c_str()) + 1, wszClassName, sizeof(wszClassName) / sizeof(wszClassName[0]));
            mciSendString(wszClassName, 0, 0, 0);
        }
        //-------------------------------------------------------
        void Close() noexcept//释放音频文件(终止播放)
        {
            mciSendString(L"close SoundP", 0, 0, 0);
        }
        //-------------------------------------------------------
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_Key_Onest(int VK_KeyCode) noexcept//获取按键按下只瞬间返回
    {//Get_Key_Onest(VK_INSERT);
        if (GetAsyncKeyState(VK_KeyCode) & 0x8000) { keybd_event(VK_KeyCode, 0, KEYEVENTF_KEYUP, 0); return true; }
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class A>//防止同函数同步
    BOOL Sleep_Tick(int Time_MS) noexcept//不受线程影响的Sleep函数
    {//System::Sleep_Tick<class oiduwaj>(500);
        const long Tick = GetTickCount64();
        static long OldTick = Tick;
        if (Tick - OldTick >= Time_MS) { OldTick = Tick; return true; }//当达到一定数值返回并且重写变量
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Get_Key(int VK_Code) noexcept//获取按键是否被按下（不会出现没有按下却返回true的bug）
    {//System::Get_Key(VK_INSERT);
        if (!VK_Code)return false;//排除0
        if (GetAsyncKeyState(VK_Code) & 0x8000)return true; else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Read_String(string Str, Variable::Vector2 Volume_Rate = { 100, 0 }) noexcept//字符串通过语音播放 问题: 会内存泄漏导致程序暂停
    {//System::Read_String("Hello", {100, 0});
        wstring wszStr;
        const int nLength = MultiByteToWideChar(CP_ACP, 0, Str.c_str(), -1, 0, 0);
        wszStr.resize(nLength);
        LPWSTR lpwszStr = new wchar_t[nLength];
        MultiByteToWideChar(CP_ACP, 0, Str.c_str(), -1, lpwszStr, nLength);
        wszStr = lpwszStr;
        delete[] lpwszStr;
        //------------------转换
        ISpVoice* pVoice = 0;
        CoInitialize(0);
        CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&pVoice);//获取SpVoice接口
        pVoice->SetVolume((USHORT)Volume_Rate.x);//范围: 0~100
        pVoice->SetRate(Volume_Rate.y);//范围: -10~10
        pVoice->Speak(wszStr.c_str(), 0, 0);
        pVoice->Release();
        pVoice = 0;
        CoUninitialize();//释放com资源
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Log(string Str = "", BOOL b_Error = false, ...) noexcept//带有时间标题的打印控制台
    {//System::Log("Fuck you!!!!", true);
        SYSTEMTIME sys; GetLocalTime(&sys);
        string Hour = to_string(sys.wHour);
        string Minute = to_string(sys.wMinute);
        string Second = to_string(sys.wSecond);
        string Millisecond = to_string(sys.wMilliseconds);
        if (sys.wHour < 10)Hour = "0" + Hour;
        if (sys.wMinute < 10)Minute = "0" + Minute;
        if (sys.wSecond < 10)Second = "0" + Second;
        if (sys.wMilliseconds < 10)Millisecond = "00" + Millisecond;
        else if (sys.wMilliseconds < 100)Millisecond = "0" + Millisecond;
        if (b_Error)SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);//报错时修改红色文字
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);//默认修改绿色文字
        printf(("[" + Hour + ":" + Minute + ":" + Second + "." + Millisecond + "] " + Str + "\n").c_str());
        Sleep(1); SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);//修改回白色文字
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    string Rand_String(int len = 10, int Offsets = 0) noexcept//随机字符串 (Offsets一样可以做到多进程同步)
    {//System::Rand_String(20);//生成20个字符的字符串
        string str; char c;
        srand(GetTickCount64() * GetTickCount64() * 1337 + Offsets * GetTickCount64());//修复产生相同的随机字符
        for (short idx = 0; idx < len; idx++)
        {
            const int Rand = rand();
            if ((Rand % 4) == 0)c = 'a' + Rand % 26;
            else if ((Rand % 4) == 1)c = 'A' + Rand % 26;
            else if ((Rand % 4) == 2)c = '0' + Rand % 10;
            else if ((Rand % 4) == 3)c = '!' + Rand % 30;
            str.push_back(c);
        }
        return str;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    class Memory//内存类
    {
        /*
        int main()//Bunny Hup
        {
            System::Memory CS_Mem = { "csgo.exe" };//Create
            const auto Client_dll = CS_Mem.Get_Module("client.dll");
            cout << "client.dll -> 0x" << hex << Client_dll << endl;
            while (1)
            {
                const auto LocalPlayer = CS_Mem.Read<uintptr_t>(Client_dll + 0xDEA98C);//Localplayer
                if (CS_Mem.Read<BOOL>(LocalPlayer + 0x104) & (1 << 0) && (GetAsyncKeyState(VK_SPACE) & 0x8000))//Spacebar localplayer in ground
                {
                    System::Source_ExecuteCommand("+jump");//jump
                    Sleep(1);
                    System::Source_ExecuteCommand("-jump");
                }
                Sleep(1);
            }
        }
        */
    private:
        uintptr_t ProcessID = 0;//进程ID
        HANDLE HProcessID = 0;
    public:
        //-----------------------------------------------------------------------------------------
        Memory(string ProcessName) noexcept//获取进程ID 用来内存函数(可以用来初始化不放在循环)
        {
            PROCESSENTRY32 entry = { }; entry.dwSize = sizeof(PROCESSENTRY32);
            const auto Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
            while (Process32Next(Snapshot, &entry))
            {
                if (wcscmp(entry.szExeFile, wstring(ProcessName.begin(), ProcessName.end()).c_str()) == 0)//判断字符串是否相等
                {
                    ProcessID = entry.th32ProcessID;
                    HProcessID = OpenProcess(PROCESS_ALL_ACCESS, 0, ProcessID);
                    break;
                }
            }
            CloseHandle(Snapshot);
        }
        //-----------------------------------------------------------------------------------------
        uintptr_t Get_Module(string ModuleName) noexcept//读取模块地址
        {
            MODULEENTRY32 entry = { }; entry.dwSize = sizeof(MODULEENTRY32);
            const auto Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, ProcessID);//获取所有模块
            uintptr_t dwModuleBaseAddress = 0;//返回值
            while (Module32Next(Snapshot, &entry))//遍历所有模块
            {
                if (wcscmp(entry.szModule, wstring(ModuleName.begin(), ModuleName.end()).c_str()) == 0)//判断字符串是否相等
                {
                    dwModuleBaseAddress = reinterpret_cast<uintptr_t>(entry.modBaseAddr);
                    break;
                }
            }
            CloseHandle(Snapshot);//删除遍历
            return dwModuleBaseAddress;//返回地址
        }
        //-----------------------------------------------------------------------------------------
        template<class T>
        T Write(uintptr_t Address, T value) noexcept//写入内存
        {
            WriteProcessMemory(HProcessID, (LPVOID)(Address), &value, sizeof(T), 0);
            return value;
        }
        //-----------------------------------------------------------------------------------------
        template<class T>
        T Read(uintptr_t Address) noexcept//读取内存
        {
            T Value = {};
            ReadProcessMemory(HProcessID, (LPVOID)(Address), &Value, sizeof(T), 0);
            return Value;
        }
        //-----------------------------------------------------------------------------------------
        template<class T>
        T Write_Level(uintptr_t Address, vector<uintptr_t>Offsets, T value) noexcept//修改地址的内存(等级地址版本)
        {
            uintptr_t F = {};
            ReadProcessMemory(HProcessID, (LPVOID)(Address), &F, sizeof(uintptr_t), 0);
            for (short i = 0; i <= Offsets.size() - 1; ++i)ReadProcessMemory(HProcessID, (LPVOID)(F + Offsets[i - 1]), &F, sizeof(uintptr_t), 0);//计算等级
            WriteProcessMemory(HProcessID, (LPVOID)(F + Offsets[Offsets.size() - 1]), &value, sizeof(T), 0);
            return value;
        }
        //-----------------------------------------------------------------------------------------
        template<class T>
        T Read_Level(uintptr_t Address, vector<uintptr_t>Offsets) noexcept//获取地址的内存(等级地址版本)
        {
            uintptr_t F = {}; T Returnvalue = {};
            ReadProcessMemory(HProcessID, (LPVOID)(Address), &F, sizeof(uintptr_t), 0);
            for (short i = 0; i <= Offsets.size() - 1; ++i)ReadProcessMemory(HProcessID, (LPVOID)(F + Offsets[i - 1]), &F, sizeof(uintptr_t), 0);//计算等级
            ReadProcessMemory(HProcessID, (LPVOID)(F + Offsets[Offsets.size() - 1]), &Returnvalue, sizeof(T), 0);
            return Returnvalue;
        }
        //-----------------------------------------------------------------------------------------
        string Read_str(uintptr_t Address) noexcept//读取内存(字符串)
        {
            char Buffer[MAX_PATH]{};
            ReadProcessMemory(HProcessID, (LPVOID)(Address), &Buffer, MAX_PATH, 0);
            return Buffer;
        }
        //-----------------------------------------------------------------------------------------
        uintptr_t Get_ProcessID() noexcept { return ProcessID; }//获取进程ID
        HWND Get_ProcessHWND() noexcept//获取进程HWND
        {
            HWND h = GetTopWindow(0), retHwnd = 0;
            while (h)
            {
                DWORD pid = 0; uintptr_t dwTheardId = GetWindowThreadProcessId(h, &pid);
                if (dwTheardId != 0 && pid == ProcessID && GetParent(h) == 0 && IsWindowVisible(h))retHwnd = h;
                h = GetNextWindow(h, GW_HWNDNEXT);
            }
            return retHwnd;
        }
        //-----------------------------------------------------------------------------------------
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Post_Message(HWND Window_HWND, WPARAM Message_Value, UINT Message_Type = WM_CHAR) noexcept//向指定窗口发送消息 https://blog.51cto.com/csnd/5480626
    {//System::Post_Message(NULL, 'A');
        if (Window_HWND == 0)PostMessage(GetForegroundWindow(), Message_Type, Message_Value, 0);//如果Window_HWND值为0则发送到最前端窗口
        else PostMessage(Window_HWND, Message_Type, Message_Value, 0);//WM_KEYDOWN WM_KEYUP WM_RBUTTONDOWN WM_CHAR
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    class URL_READ//读取URL字符串
    {
        /*
        System::URL_READ UR_;
        if (UR_.StoreMem("https://abc.com//abc.txt"))
        {
            Beep(100, 100);
            for (short i = 1; i <= 100; ++i)cout << UR_.Read(i) << endl;
            UR_.Release();
        }
        */
    private:
        string File_Name = "URLREAD";
    public:
        URL_READ(string FileName = "URLREAD") noexcept { File_Name = FileName; }//初始化写入文件名称
        BOOL StoreMem(string URL) noexcept//将字符串存入内存用来读取(下载)
        {
            const auto DownLoad = URLDownloadToFile(0, wstring(URL.begin(), URL.end()).c_str(), wstring(File_Name.begin(), File_Name.end()).c_str(), 0, 0);
            return DownLoad == S_OK;
        }
        string Read(int line) noexcept//获取文件信息中的特定行数
        {
            if (line == 0)line = 1;
            ifstream infile; infile.open(File_Name, ios::in);
            char str[2048];
            for (int i = 0; i < line; i++)infile.getline(str, sizeof(str));
            infile.close();
            return str;
        }
        void Release() noexcept { system(((string)"del " + File_Name).c_str()); }//释放字符串(删除)
    };
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class CLASS>CLASS In_G(const uintptr_t Address) noexcept { return *reinterpret_cast<CLASS*>(Address); }//内部内存地址获取
    template<class CLASS>void In_S(const uintptr_t Address, CLASS Value) noexcept { *reinterpret_cast<CLASS*>(Address) = Value; }//内部内存地址调用
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    template<class ValueClass, class CreateClassName>
    BOOL Get_ValueChangeState(ValueClass Value) noexcept//检测值是否变化
    {//System::Get_ValueChangeState<int, class CLASS_Funtion_Test>(Variable);
        static auto Old_Value = Value;
        if (Old_Value != Value) { Old_Value = Value; return true; }
        else return false;
    }
    template<class ValueClass, class CreateClassName>
    BOOL Get_ValueBigger(ValueClass Value) noexcept//检测值是否变化 (变大)
    {//System::Get_ValueBigger<int, class CLASS_Funtion_Test>(Variable);
        static auto Old_Value = Value;
        if (Old_Value < Value) { Old_Value = Value; return true; }
        else if (Old_Value != Value) { Old_Value = Value; return false; }
    }
    template<class ValueClass, class CreateClassName>
    BOOL Get_ValueSmaller(ValueClass Value) noexcept//检测值是否变化 (变小)
    {//System::Get_ValueSmaller<int, class CLASS_Funtion_Test>(Variable);
        static auto Old_Value = Value;
        if (Old_Value > Value) { Old_Value = Value; return true; }
        else if (Old_Value != Value) { Old_Value = Value; return false; }
    }
    template<class ValueClass, class CreateClassName>
    BOOL Get_ValueChangeState_t(ValueClass Value, ValueClass threshold) noexcept//检测值是否变化 (附加检测变化的量 阈值)
    {//System::Get_ValueChangeState_t<int, class CLASS_Funtion_Test>(Variable, 10);
        static auto Old_Value = Value;
        if (Old_Value >= Value + threshold || Old_Value <= Value - threshold) { Old_Value = Value; return true; }
        else return false;
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    BOOL Is_MousePos_InMid(HWND Window_Hwnd = 0) noexcept//检测光标是否在窗口最中间
    {//System::Is_MousePos_InMid();
        RECT Window_Pos; POINT Mouse_Pos; GetWindowRect(Window_Hwnd, &Window_Pos); GetCursorPos(&Mouse_Pos);
        return (Mouse_Pos.x == Window_Pos.left + (Window_Pos.right - Window_Pos.left) / 2 && Mouse_Pos.y == Window_Pos.top + (Window_Pos.bottom - Window_Pos.top) / 2);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Anti_Debugger(string Log = "", BOOL BEEP = false) noexcept//反调试 (防止程序被逆向破解 可放入循环)
    {//System::Anti_Debugger();
        if (IsDebuggerPresent())
        {
            if (Log != "")printf((Log + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n").c_str());
            ShowWindow(GetConsoleWindow(), false);//隐藏控制台窗口
            if (BEEP)Beep(100, 100);//反馈音效
            exit(0);//检测调试状态 (缺点是会被Hook绕过)
        }
        else {//防止控制台被选中从而暂停执行
            DWORD mode; GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &mode);
            mode &= ~ENABLE_QUICK_EDIT_MODE; SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), mode);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Lock_Cursor(BOOL Lock = true) noexcept//锁定鼠标光标
    {//System::Lock_Cursor();
        RECT rect = {};//不可以使用LPRECT定义
        rect.bottom = 1; rect.right = 1;
        if (Lock)ClipCursor(&rect);//锁定鼠标
        else ClipCursor(0);//释放鼠标
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void BEEP(short dwFreq, short dwDuration) noexcept//蜂鸣 (安全版本)
    {//System::BEEP(-100, 100);
        if (dwDuration <= 0)return;
        Beep(abs(dwFreq), dwDuration);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    int Get_DefaultLanguage() noexcept//获取系统默认语言 https://blog.csdn.net/duke56/article/details/103847999
    {//System::Get_DefaultLanguage();
        return GetUserDefaultLangID();
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    void Set_ProcessPriority(DWORD Priority_Level = HIGH_PRIORITY_CLASS) noexcept//修改自身进程优先级 https://blog.51cto.com/fish/6102640
    {//System::Set_ProcessPriority(REALTIME_PRIORITY_CLASS);
        SetPriorityClass(GetCurrentProcess(), Priority_Level);
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
    vector<string> Traversal_FindFile(string FileName = "*", string Format = "", BOOL Erase_Format = false,string Attach = "") noexcept//通过遍历的方式获取目录下的所有文件
    {//System::Traversal_FindFile("*", ".exe");
        vector<string> FileList = {}; _finddata64i32_t FileInfo; const auto hFile = _findfirst(FileName.c_str(), &FileInfo);
        if (hFile == -1)return {};
        do {
            string FileName = FileInfo.name;//未知类型转换为字符串
            if (FileName.find(Format) != string::npos)
            {
                if (Erase_Format)FileName.erase(FileName.find(Format), Format.length());//擦除格式 只输出名称
                FileList.push_back(FileName + Attach);//只输出指定格式
            }
        } while (_findnext(hFile, &FileInfo) == 0);//遍历所有文件
        return FileList;//最终返回文件列表
    }
    //-----------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------
}
namespace EasyGUI//控件
{
    /*
    int main()
    {
        ShowWindow(GetConsoleWindow(), true);//Show Console Window
        system("cls"); printf("EasyGUI-Lightweight\nGithub: https://github.com/Coslly/EasyGUI-Lightweight.git\n");
        EasyGUI::EasyGUI GUI_Variable;//Initialize GUI variables
        GUI_Variable.Window_Create(590, 360, "Test Windows", true);
        GUI_Variable.Window_SetAlpha(250);
        while (true)
        {
            static BOOL UI_Checkbox = false;
            static int UI_Slider_int = 5;
            static float UI_Slider_float = 5;
            static BOOL UI_Button = false;
            static BOOL UI_Button_Small = false;
            static int UI_KeySelector = 4;
            static BOOL UI_InvertScreenColor = false;
            static EasyGUI::Vector4 UI_ColorSelector = { 255,255,255 };
            static EasyGUI::Vector3 UI_PosSelector = { 0.23,100,1000 };
            static int UI_PanelSelector = 0;
            static string UI_InputText = "Input text";
            static int UI_List = 0;
            EasyGUI::EasyGUI_IO GUI_IO = GUI_Variable.Get_IO();//Get Global Input/Output Value
            if (!GUI_Variable.Window_Move())//MoveWindow Funtion (You must add!! cause it have MessageLoop)
            {
                GUI_Variable.GUI_BackGround(true);//BackGround
                GUI_Variable.GUI_Block_Panel(30, 30, 100, 300, "Panel", { "Panel 1","Panel 2","Panel 3" }, UI_PanelSelector);
                if (UI_PanelSelector == 0)//Panel 1 Screen
                {
                    const auto Block = GUI_Variable.GUI_Block(160, 30, 300, "Block");//Block
                    GUI_Variable.GUI_Checkbox(Block, 1, "This is a Checkbox", UI_Checkbox);
                    GUI_Variable.GUI_KeySelector<class CALSS_EasyGUI_1>(Block, 1, UI_KeySelector);
                    GUI_Variable.GUI_Slider<int, class CALSS_EasyGUI_2>(Block, 2, "Slider int", 0, 10, UI_Slider_int);
                    GUI_Variable.GUI_Slider<float, class CALSS_EasyGUI_3>(Block, 3, "Slider float", 0, 10, UI_Slider_float);
                    GUI_Variable.GUI_Button(Block, 4, "Button", UI_Button);
                    static auto ButtonClick = 0;
                    if (UI_Button || UI_Button_Small)ButtonClick++;
                    GUI_Variable.GUI_Text(Block, 5, "Button hit: " + to_string(ButtonClick));
                    GUI_Variable.GUI_Checkbox(Block, 6, "Invert screen color", UI_InvertScreenColor);
                    GUI_Variable.GUI_Text(Block, 7, "Main color");
                    GUI_Variable.GUI_ColorSelector(Block, 7, UI_ColorSelector);
                    GUI_Variable.Global_Set_EasyGUI_Color(UI_ColorSelector);
                    GUI_Variable.GUI_Text(Block, 8, "Pos selector");
                    GUI_Variable.GUI_PosSelector(Block, 8, UI_PosSelector);
                    GUI_Variable.GUI_Button_Small(Block, 2, UI_Button_Small);
                    GUI_Variable.GUI_Text(Block, 9, "FPS: " + to_string(GUI_IO.DrawFPS));
                    GUI_Variable.GUI_Tips(Block, 1, "Some tips");
                }
                else if (UI_PanelSelector == 1)//Panel 2 Screen
                {
                    const auto Block = GUI_Variable.GUI_Block(160, 30, 300, "Block");//Block
                    GUI_Variable.GUI_InputText<class CALSS_EasyGUI_4>(Block, 1, UI_InputText);
                    GUI_Variable.GUI_List(Block, 2, { "Hello","C++","Java","CS","Windows" }, UI_List);
                }
                GUI_Variable.Draw_GUI(UI_InvertScreenColor);
            }
        }
    }
    */
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    LRESULT CALLBACK WndProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam) noexcept//消息循环(用于解决窗口未响应问题 接收窗口消息)
    {
        switch (Message)
        {
        case WM_ERASEBKGND:return true; break;
        case WM_PAINT:return true; break;//一直重绘
        case WM_CLOSE:exit(0); break;//接收到关闭窗口事件时返回全部线程
        case WM_MOUSEWHEEL://鼠标滚轮事件
        {
            const auto Delta = GET_WHEEL_DELTA_WPARAM(wParam);
            if (Delta > 0)keybd_event(VK_UP, 0, 0, 0);
            else if (Delta < 0)keybd_event(VK_DOWN, 0, 0, 0);
        } break;
        }
        return DefWindowProc(Hwnd, Message, wParam, lParam);//定义回调函数的返回值
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    /*
    struct Vector2//用来储存坐标数据 XY
    {
        constexpr Vector2(const int x = 0, const int y = 0) noexcept :x(x), y(y) { }
        constexpr const Vector2 operator+(const Vector2 other) const noexcept
        {
            return Vector2{ x + other.x, y + other.y };
        }
        constexpr const Vector2 operator-(const Vector2 other) const noexcept
        {
            return Vector2{ x - other.x, y - other.y };
        }
        constexpr const Vector2 operator*(const int factor) const noexcept
        {
            return Vector2{ x * factor, y * factor };
        }
        constexpr const Vector2 operator/(const int factor) const noexcept
        {
            return Vector2{ x / factor, y / factor };
        }
        int x, y;
    };
    struct Vector3//用来储存坐标数据 XYZ
    {
        constexpr Vector3(const float x = 0, const float y = 0, const float z = 0) noexcept :x(x), y(y), z(z) { }
        constexpr const Vector3 operator+(const Vector3 other) const noexcept
        {
            return Vector3{ x + other.x, y + other.y, z + other.z };
        }
        constexpr const Vector3 operator-(const Vector3 other) const noexcept
        {
            return Vector3{ x - other.x, y - other.y, z - other.z };
        }
        constexpr const Vector3 operator*(const float factor) const noexcept
        {
            return Vector3{ x * factor, y * factor, z * factor };
        }
        constexpr const Vector3 operator/(const float factor) const noexcept
        {
            return Vector3{ x / factor, y / factor, z / factor };
        }
        constexpr const Vector3 ToAngle() const noexcept
        {
            return Vector3{ atan2(-z, hypot(x, y)) * (180.0f / (float)acos(-1)),atan2(y, x) * (180.0f / (float)acos(-1)),0 };
        }
        float x, y, z;
    };
    struct Vector4//用来储存颜色数据 RGBA
    {
        constexpr Vector4(const int r = 0, const int g = 0, const int b = 0, const int a = 255) noexcept :r(r), g(g), b(b), a(a) {}
        constexpr const Vector4 operator+(const Vector4 other) const noexcept
        {
            return Vector4{ r + other.r, g + other.g, b + other.b, a };
        }
        constexpr const Vector4 operator-(const Vector4 other) const noexcept
        {
            return Vector4{ r - other.r, g - other.g, b - other.b, a };
        }
        constexpr const Vector4 operator*(const int factor) const noexcept
        {
            return Vector4{ r * factor, g * factor, b * factor, a };
        }
        constexpr const Vector4 operator/(const int factor) const noexcept
        {
            return Vector4{ r / factor, g / factor, b / factor, a };
        }
        int r, g, b, a;
    };
    */
    using namespace Variable;//变量类型库 Head.h
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    struct EasyGUI_IO
    {
        int DrawFPS = 0;//绘制帧数
        HWND HWND = 0;//全局GUI窗口HWND
        HDC HDC = 0;//全局GUI窗口HDC
        string FontName = "";//全局GUI字体名字
        int FontSize = 0;//全局GUI字体大小
        Vector4 GUIColor = { 0,0,0 };//全局GUI主题色
        int GUIColor_Alpha = 0;//全局GUI主题色(透明度)
        Vector2 WindowPos = { 0,0 };//全局GUI窗口坐标
        Vector2 WindowSize = { 0,0 };//全局GUI窗口大小
        string WindowTitle = "";//全局GUI窗口标题
        Vector2 MousePos = { 0,0 };//GUI检测的鼠标坐标
        vector<int> GUIColor_Rainbow = { 0,0,0,0,0,0,0,0,0 };//全局GUI彩虹颜色
    };
    //---------------------------------------------------------------------------------------------------------------------------------------------------------
    class EasyGUI
    {
    private:
        //-----------菜单风格
        string Global_EasyGUIFont = "Verdana";//全局字体名称
        int Global_EasyGUIFontSize = 13;//全局字体大小
        Vector4 Global_EasyGUIColor = { 255,255,255,250 };//全局主题颜色 (包含窗口透明度)
        //------------------
        HWND EasyGUI_WindowHWND = 0;//GUI Window HWND
        HDC EasyGUI_WindowHDC = 0;//GUI Window HDC
        Vector2 PaintSize = { 0,0 };//DoubleBufferPaint Size 画布大小
        HDC EasyGUI_DrawHDC = 0;//EasyGUI DrawHDC GUI要绘制的HDC
        POINT EasyGUI_MousePos; RECT EasyGUI_WindowPos;//EasyGUI窗口鼠标坐标
        int EasyGUI_FPS = 0;//EasyGUI绘制帧数 (需要后期计算得出)
        //------------------
        BOOL Mouse_Block_, Mouse_Slider_, Mouse_Move_ = false;//防止控件函数之间冲突的判断变量
        //------------------
    public:
        //---------------------------------------------------------------------开发者函数 (方便制作GUI)
        void In_DrawRect(int X, int Y, int Width, int Length, Vector4 Color) noexcept//绘制矩形
        {
            //------------------------初始化渐变矩阵
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000; vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            //------------------------
            const COLORREF Color_ = RGB(Color.r, Color.g, Color.b);
            vert[0].x = X; vert[0].y = Y;
            vert[1].x = X + Width; vert[1].y = Y + Length;
            vert[0].Red = GetRValue(Color_) << 8;
            vert[0].Green = GetGValue(Color_) << 8;
            vert[0].Blue = GetBValue(Color_) << 8;
            vert[1].Red = GetRValue(Color_) << 8;
            vert[1].Green = GetGValue(Color_) << 8;
            vert[1].Blue = GetBValue(Color_) << 8;
            GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);
        }
        //---------------------------------------------------------------------
        void In_DrawGradientRect(int X, int Y, int Width, int Length, Vector4 Color_1, Vector4 Color_2, BOOL Gradient_Direction = false) noexcept//绘制渐变矩形
        {
            //------------------------初始化渐变矩阵
            TRIVERTEX vert[2]; GRADIENT_RECT gRect;
            vert[0].Alpha = 0x0000; vert[1].Alpha = 0x0000;
            gRect.UpperLeft = 0; gRect.LowerRight = 1;
            //------------------------
            const COLORREF Color1 = RGB(Color_1.r, Color_1.g, Color_1.b);
            const COLORREF Color2 = RGB(Color_2.r, Color_2.g, Color_2.b);
            vert[0].x = X; vert[0].y = Y;
            vert[1].x = X + Width; vert[1].y = Y + Length;
            vert[0].Red = GetRValue(Color1) << 8;
            vert[0].Green = GetGValue(Color1) << 8;
            vert[0].Blue = GetBValue(Color1) << 8;
            vert[1].Red = GetRValue(Color2) << 8;
            vert[1].Green = GetGValue(Color2) << 8;
            vert[1].Blue = GetBValue(Color2) << 8;
            if (Gradient_Direction)GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_V);//渐变方向 (false:横向 true:竖向)
            else GradientFill(EasyGUI_DrawHDC, vert, 2, &gRect, 1, GRADIENT_FILL_RECT_H);
        }
        //---------------------------------------------------------------------
        void In_DrawLine(int X, int Y, int Way_X, int Way_Y, Vector4 Color, int Line_Thickness = 1) noexcept//绘制直线
        {
            const auto LineColor = SelectObject(EasyGUI_DrawHDC, CreatePen(0, Line_Thickness, RGB(Color.r, Color.g, Color.b)));
            MoveToEx(EasyGUI_DrawHDC, X, Y, 0);
            LineTo(EasyGUI_DrawHDC, Way_X, Way_Y);
            DeleteObject(LineColor);
        }
        //---------------------------------------------------------------------
        void In_DrawCircle(int X, int Y, int Size, Vector4 Color) noexcept//绘制圆形
        {
            const auto BIANKUANG = SelectObject(EasyGUI_DrawHDC, CreatePen(PS_SOLID, 1, RGB(Color.r, Color.g, Color.b)));
            const auto TIANCHONG = SelectObject(EasyGUI_DrawHDC, CreateSolidBrush(RGB(Color.r, Color.g, Color.b)));
            Ellipse(EasyGUI_DrawHDC, X - Size / 2, Y - Size / 2, X + Size / 2, Y + Size / 2);
            DeleteObject(BIANKUANG); DeleteObject(TIANCHONG);
        }
        //---------------------------------------------------------------------
        void In_DrawString(int X, int Y, string String, Vector4 TextColor, string Fount_Name, short Fount_Size, short Font_Width = FW_NORMAL, BOOL AntiAlias = true) noexcept//绘制文字
        {
            if (String == "" || Fount_Size == 0)return;
            if (Fount_Name == "微软雅黑")Y -= Fount_Size / 7;
            else if (Fount_Size > 15)Y -= Fount_Size / 3;//平衡上下坐标
            HGDIOBJ FontPen;
            if (AntiAlias)FontPen = SelectObject(EasyGUI_DrawHDC, CreateFontA(Fount_Size, 0, 0, 0, Font_Width, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_DONTCARE, Fount_Name.c_str()));
            else FontPen = SelectObject(EasyGUI_DrawHDC, CreateFontA(Fount_Size, 0, 0, 0, Font_Width, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, Fount_Name.c_str()));
            SetTextColor(EasyGUI_DrawHDC, RGB(TextColor.r, TextColor.g, TextColor.b));//文字颜色
            SetBkMode(EasyGUI_DrawHDC, TRANSPARENT);//背景透明
            if (String.find("UTT") != string::npos)//不转换UTF-8
            {
                String.erase(String.find("UTT"), 3);
                TextOutA(EasyGUI_DrawHDC, X, Y, String.c_str(), strlen(String.c_str()));
                DeleteObject(FontPen);
            }
            else {//转换UTF-8
                const auto len = MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, 0, 0);//转码 UTF-8 (为了显示中文)
                wchar_t* wide_text = new wchar_t[len];
                MultiByteToWideChar(CP_UTF8, 0, String.c_str(), -1, wide_text, len);//转码 UTF-8 (为了显示中文)
                TextOutW(EasyGUI_DrawHDC, X, Y, wide_text, len - 1);
                DeleteObject(FontPen);
                delete[] wide_text;
            }
        }
        //---------------------------------------------------------------------
        void In_DrawString_Simple(int X, int Y, string String, Vector4 TextColor = { 255,255,255 }) noexcept//绘制简单文字
        {
            if (String == "")return;
            HGDIOBJ FontPen = SelectObject(EasyGUI_DrawHDC, CreateFontA(12, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, NONANTIALIASED_QUALITY, FF_DONTCARE, "Small Fonts"));
            SetBkMode(EasyGUI_DrawHDC, TRANSPARENT);//背景透明
            SetTextColor(EasyGUI_DrawHDC, RGB(0, 0, 0));//文字颜色
            TextOutA(EasyGUI_DrawHDC, X + 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X + 1, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y + 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X + 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X - 1, Y, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X, Y - 1, String.c_str(), strlen(String.c_str()));
            TextOutA(EasyGUI_DrawHDC, X, Y + 1, String.c_str(), strlen(String.c_str()));
            SetTextColor(EasyGUI_DrawHDC, RGB(TextColor.r, TextColor.g, TextColor.b));//文字颜色
            TextOutA(EasyGUI_DrawHDC, X, Y, String.c_str(), strlen(String.c_str()));
            DeleteObject(FontPen);
        }
        //---------------------------------------------------------------------
        BOOL In_MouseEventJudgment(int X, int Y, int Width, int Length) noexcept//检测鼠标坐标是否在窗口矩形坐标内
        {
            if (!(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))return false;//当指针不在窗口内
            if (EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + Width && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + Length)return true;
            else return false;
        }
        //---------------------------------------------------------------------
        BOOL In_KeyEvent(int VK_CODE, BOOL Release = false) noexcept//检测按键是否被按下 (后者参数为按下后是否立马释放)
        {
            const BOOL Key_State = GetAsyncKeyState(VK_CODE) & 0x8000;
            if (Release && Key_State)//释放按键
            {
                if (VK_CODE == VK_LBUTTON)mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);//鼠标键盘判断
                else if (VK_CODE == VK_RBUTTON)mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
                else if (VK_CODE == VK_MBUTTON)mouse_event(MOUSEEVENTF_MIDDLEUP, 0, 0, 0, 0);
                else keybd_event(VK_CODE, 0, KEYEVENTF_KEYUP, 0);
            }
            return Key_State;
        }
        //---------------------------------------------------------------------
        template<class CreateClassName>//防止同函数同步
        BOOL In_TickSleep(int Time_MS) noexcept//不受线程影响的Sleep函数
        {
            const long Tick = GetTickCount64(); static long OldTick = Tick;
            if (Tick - OldTick >= Time_MS) { OldTick = Tick; return true; }//当达到一定数值返回并且重写变量
            else return false;
        }
        //---------------------------------------------------------------------
        template<class CreateClassName>//防止同函数同步
        float In_Animation(float Value, float Speed = 1.3, Vector2 Limit = { 0,0 }) noexcept//快到慢动画
        {
            if (Speed == 1)return Value;//无动画时直接返回
            static float ReturnValue = Value;
            if (Value > ReturnValue)ReturnValue += (Value - ReturnValue) / Speed; else if (Value < ReturnValue)ReturnValue -= (ReturnValue - Value) / Speed;
            if (Limit.x != 0 || Limit.y != 0) { if (Limit.x > ReturnValue)ReturnValue = Limit.x; else if (Limit.y < ReturnValue)ReturnValue = Limit.y; }
            return ReturnValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Global_Set_EasyGUI_Font(string FontName) noexcept { Global_EasyGUIFont = FontName; }//设置全局GUI字体
        void Global_Set_EasyGUI_FontSize(int FontSize) noexcept { Global_EasyGUIFontSize = FontSize; }//设置全局GUI字体大小
        void Global_Set_EasyGUI_Color(Vector4 MainColor) noexcept { Global_EasyGUIColor = MainColor; }//设置全局主题颜色
        string Global_Get_EasyGUI_Font() noexcept { return Global_EasyGUIFont; }//获取全局GUI字体
        int Global_Get_EasyGUI_FontSize() noexcept { return Global_EasyGUIFontSize; }//获取全局GUI字体大小
        Vector4 Global_Get_EasyGUI_Color() noexcept { return Global_EasyGUIColor; }//获取全局主题颜色
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL Window_Create(int Size_X, int Size_Y, string WindowTitle, BOOL IfTop = false) noexcept//创建窗口
        {
            int 窗口类型 = WS_EX_LAYERED;
            if (IfTop)窗口类型 = WS_EX_TOPMOST | WS_EX_LAYERED;
            WNDCLASS RenderWindowM; memset(&RenderWindowM, 0, sizeof(RenderWindowM));
            RenderWindowM.style = CS_HREDRAW | CS_VREDRAW;
            RenderWindowM.lpfnWndProc = WndProc;//关联消息处理函数,告诉操作系统,如果有事件发生调用这个函数
            RenderWindowM.cbClsExtra = 0;
            RenderWindowM.cbWndExtra = 0;
            RenderWindowM.hInstance = GetModuleHandle(0);//实例句柄
            RenderWindowM.hIcon = LoadIcon(0, IDI_SHIELD);//图标
            RenderWindowM.hCursor = LoadCursor(0, IDC_ARROW);//光标样式
            RenderWindowM.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//画刷
            RenderWindowM.lpszMenuName = 0;
            RenderWindowM.lpszClassName = wstring(WindowTitle.begin(), WindowTitle.end()).c_str();//窗口类的名称，操作系统根据类的名称做映射
            RegisterClass(&RenderWindowM);//将这个窗体注册（告诉）到操作系统
            const HWND hWnd = CreateWindowEx(窗口类型, wstring(WindowTitle.begin(), WindowTitle.end()).c_str(), wstring(WindowTitle.begin(), WindowTitle.end()).c_str(), WS_POPUP, GetSystemMetrics(SM_CXSCREEN) / 2 - Size_X / 2, GetSystemMetrics(SM_CYSCREEN) / 2 - Size_Y / 2, Size_X, Size_Y, 0, 0, GetModuleHandle(0), 0);
            if (hWnd)//当创建成功
            {
                UpdateWindow(hWnd); ShowWindow(hWnd, SW_SHOW); SetForegroundWindow(hWnd);
                SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), Global_EasyGUIColor.a, LWA_ALPHA);
                EasyGUI_WindowHWND = hWnd; EasyGUI_WindowHDC = GetWindowDC(hWnd);
                //---------------------------------------双缓冲开始绘制
                PaintSize = { Size_X + 400,Size_Y + 400 };//设定坐标上加上400缓冲区
                EasyGUI_DrawHDC = CreateCompatibleDC(EasyGUI_WindowHDC);//内存画板 (如果不是最终绘制 请绘制到这里!!!)
                SelectObject(EasyGUI_DrawHDC, (HBITMAP)CreateCompatibleBitmap(EasyGUI_WindowHDC, PaintSize.x, PaintSize.y));
                //---------------------------------------------
                return true;
            }
            else return false;//当创建失败
        }
        void Draw_GUI(BOOL ReverseColor = false) noexcept//双缓冲结束绘制 (绘制最终返回图片)
        {
            if (EasyGUI_MousePos.x == 0 && EasyGUI_MousePos.y == 0)In_DrawString_Simple(0, 0, "You are a unique star in the universe.", Global_EasyGUIColor);//你是宇宙中独有的一颗星 (彩蛋)
            if (ReverseColor)BitBlt(EasyGUI_DrawHDC, 0, 0, PaintSize.x, PaintSize.y, EasyGUI_DrawHDC, 0, 0, PATINVERT);//反转颜色
            BitBlt(EasyGUI_WindowHDC, 0, 0, PaintSize.x, PaintSize.y, EasyGUI_DrawHDC, 0, 0, SRCCOPY);//最终绘制内存中的图像
            //--------------------------------消息循环
            In_KeyEvent(VK_UP, true); In_KeyEvent(VK_DOWN, true);//释放滚轮消息
            MSG MSG = { 0 }; if (GetMessage(&MSG, 0, 0, 0)) { TranslateMessage(&MSG); DispatchMessage(&MSG); }
            GetCursorPos(&EasyGUI_MousePos); GetWindowRect(EasyGUI_WindowHWND, &EasyGUI_WindowPos);//刷新鼠标窗口坐标
            //--------------------------------帧数计算
            static int m_fps = 0; m_fps++;
            const int Tick = GetTickCount64(); static int Tick_Old = Tick;
            if (Tick >= Tick_Old + 1000) { Tick_Old = Tick; EasyGUI_FPS = m_fps; m_fps = 0; }//每1秒刷新 (计时器)
            //----------------------------------------
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        HWND Window_HWND() noexcept { return EasyGUI_WindowHWND; }//获取GUI窗口HWND
        HDC Window_HDC() noexcept { return EasyGUI_DrawHDC; }//获取GUI窗口HDC
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetPos(Vector2 WindowPos) noexcept//修改GUI窗口坐标
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            MoveWindow(EasyGUI_WindowHWND, WindowPos.x, WindowPos.y, m_Windowrect.right - m_Windowrect.left, m_Windowrect.bottom - m_Windowrect.top, true);
        }
        Vector2 Window_GetPos() noexcept//获取GUI窗口坐标
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            return { m_Windowrect.left ,m_Windowrect.top };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetSize(Vector2 WindowSize) noexcept//修改GUI窗口大小
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            MoveWindow(EasyGUI_WindowHWND, m_Windowrect.left, m_Windowrect.top, WindowSize.x, WindowSize.y, true);
        }
        Vector2 Window_GetSize() noexcept//获取GUI窗口大小
        {
            RECT m_Windowrect; GetWindowRect(EasyGUI_WindowHWND, &m_Windowrect);
            return { m_Windowrect.right - m_Windowrect.left ,m_Windowrect.bottom - m_Windowrect.top };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_Show() noexcept//修改GUI窗口为最前端
        {
            SetForegroundWindow(EasyGUI_WindowHWND);
            ShowWindow(EasyGUI_WindowHWND, true);
        }
        void Window_Hide() noexcept//隐藏GUI窗口
        {
            ShowWindow(EasyGUI_WindowHWND, false);
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetAlpha(short WindowAlpha = 255) noexcept//修改GUI窗口整体阿尔法通道
        {
            if (WindowAlpha >= 255)WindowAlpha = 255; else if (WindowAlpha <= 0)WindowAlpha = 0;
            SetLayeredWindowAttributes(EasyGUI_WindowHWND, RGB(0, 0, 0), WindowAlpha, LWA_ALPHA);
            Global_EasyGUIColor.a = WindowAlpha;
        }
        int Window_GetAlpha() noexcept//获取GUI窗口整体阿尔法通道
        {
            return Global_EasyGUIColor.a;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        void Window_SetTitle(string WindowTitle) noexcept//修改GUI窗口标题
        {
            SetWindowTextA(EasyGUI_WindowHWND, WindowTitle.c_str());//修改窗口标题
        }
        string Window_GetTitle() noexcept//获取GUI窗口标题
        {
            CHAR pszMem[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, pszMem, GetWindowTextLength(EasyGUI_WindowHWND) + 1); return pszMem;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        int Window_FPS() noexcept { return EasyGUI_FPS; }//获取GUI绘制帧数
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL Window_Move(short Draw_Delay = 3, BOOL Limit_Edge = false) noexcept//移动GUI窗口 (在GUI循环线程内加入此函数不需要添加延时函数来降低CPU占用)
        {
            //--------------------------------消息循环
            MSG MSG = { 0 }; if (GetMessage(&MSG, 0, 0, 0)) { TranslateMessage(&MSG); DispatchMessage(&MSG); }
            GetCursorPos(&EasyGUI_MousePos); GetWindowRect(EasyGUI_WindowHWND, &EasyGUI_WindowPos);//刷新鼠标窗口坐标
            //---------------------------------------
            static BOOL 防止脱离, 保存鼠标坐标; static Vector2 OldPos;//按下时坐标
            if (GetForegroundWindow() == EasyGUI_WindowHWND)//检测窗口是否在最前端
            {
                if (!Mouse_Block_ && In_KeyEvent(VK_LBUTTON) && !防止脱离)//触发移动窗口机制
                {
                    if (保存鼠标坐标) { OldPos = { EasyGUI_MousePos.x - EasyGUI_WindowPos.left ,EasyGUI_MousePos.y - EasyGUI_WindowPos.top }; 保存鼠标坐标 = false; }
                    防止脱离 = true;//触发移动窗口事件变量
                }
                else if (防止脱离 && In_KeyEvent(VK_LBUTTON))//移动窗口时
                {
                    Mouse_Block_ = true; Mouse_Move_ = true;
                    if (Limit_Edge)//限制窗口不超过显示器像素区域
                    {
                        Vector2 Scre = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };//系统显示器像素
                        Vector2 Move = { EasyGUI_MousePos.x - OldPos.x, EasyGUI_MousePos.y - OldPos.y };//窗口坐标
                        Vector2 Size = { EasyGUI_WindowPos.right - EasyGUI_WindowPos.left, EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top };//窗口大小
                        if (Move.x + Size.x >= Scre.x)Move.x = Scre.x - Size.x; else if (Move.x <= 0)Move.x = 0;//限制左右
                        if (Move.y + Size.y >= Scre.y)Move.y = Scre.y - Size.y; else if (Move.y <= 0)Move.y = 0;//限制上下
                        MoveWindow(EasyGUI_WindowHWND, Move.x, Move.y, Size.x, Size.y, true);//移动窗口
                    }
                    else MoveWindow(EasyGUI_WindowHWND, EasyGUI_MousePos.x - OldPos.x, EasyGUI_MousePos.y - OldPos.y, EasyGUI_WindowPos.right - EasyGUI_WindowPos.left, EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top, true);//移动窗口到鼠标坐标
                    if (In_TickSleep<class CLASS_EasyGUI_WindowMove_FPS_Delay_>(100))return false; else return true;//定时返回false (用来刷新面板)
                }
                else {//闲置时
                    防止脱离 = false; 保存鼠标坐标 = true; Mouse_Block_ = false; Mouse_Move_ = false;
                    if (!Mouse_Slider_)
                    {
                        if (In_KeyEvent(VK_LBUTTON))Sleep(1);
                        else Sleep(Draw_Delay);//降低CPU占用
                    }
                    else this_thread::sleep_for(chrono::nanoseconds(80));//纳秒休眠函数 (让滑条更加顺滑)
                    return false;
                }
            }
            else Sleep(20); return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        EasyGUI_IO Get_IO() noexcept//获取GUI数据
        {
            struct EasyGUI_IO IO;
            IO.DrawFPS = EasyGUI_FPS;
            IO.HWND = EasyGUI_WindowHWND;
            IO.HDC = EasyGUI_DrawHDC;
            IO.FontName = Global_EasyGUIFont;
            IO.FontSize = Global_EasyGUIFontSize;
            IO.GUIColor = Global_EasyGUIColor;
            RECT Windowrect; GetWindowRect(EasyGUI_WindowHWND, &Windowrect);
            IO.WindowPos = { Windowrect.left ,Windowrect.top };
            IO.WindowSize = { Windowrect.right - Windowrect.left ,Windowrect.bottom - Windowrect.top };
            CHAR Windowtitle[MAX_PATH] = { 0 }; GetWindowTextA(EasyGUI_WindowHWND, Windowtitle, GetWindowTextLength(EasyGUI_WindowHWND) + 1);
            IO.WindowTitle = Windowtitle;
            IO.MousePos = { EasyGUI_MousePos.x,EasyGUI_MousePos.y };
            IO.GUIColor_Rainbow = {
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 3) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 5) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 7) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 2) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 4) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 6) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 1) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 3) * 127 + 128),
                 (int)floor(sin((float)GetTickCount64() / 3000 * 2 + 5) * 127 + 128),
            };
            return IO;
        }
        //-------------------------------------------------------------------------------------------------------------------------------------------以下是控件函数*
        void GUI_BackGround(short BackGround_StyleCode = 0) noexcept//绘制GUI窗口背景
        {
            const Vector2 Window_Size = { EasyGUI_WindowPos.right - EasyGUI_WindowPos.left ,EasyGUI_WindowPos.bottom - EasyGUI_WindowPos.top };
            vector<int> 彩虹条颜色 = { 0,255,255,255,0,255,255,255,0 };
            vector<int> 主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,30,30,30 };
            if (BackGround_StyleCode == 0)//毛都没有
            {
                彩虹条颜色 = { 16,16,16,16,16,16,16,16,16 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,15,15,15,Global_EasyGUIColor.r / 10,Global_EasyGUIColor.g / 10,Global_EasyGUIColor.b / 10 };
            }
            else if (BackGround_StyleCode == 1)
            {
                彩虹条颜色 = { 100,255,255,255,100,255,255,255,100 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,5,5,5,Global_EasyGUIColor.r / 10,Global_EasyGUIColor.g / 10,Global_EasyGUIColor.b / 10 };
            }
            else if (BackGround_StyleCode == 2)
            {
                彩虹条颜色 = { 0,255,255,255,0,255,255,255,0 };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,Global_EasyGUIColor.r / 10,Global_EasyGUIColor.g / 10,Global_EasyGUIColor.b / 10 };
            }
            else if (BackGround_StyleCode == 3)//彩色变色渐变条
            {
                const auto Speed = 3000;//渐变条变化速度
                彩虹条颜色 = {
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 5) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 7) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 2) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 4) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 6) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 1) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 3) * 127 + 128),
                    (int)floor(sin((float)GetTickCount64() / Speed * 2 + 5) * 127 + 128),
                };
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,3,3,3,Global_EasyGUIColor.r / 10,Global_EasyGUIColor.g / 10,Global_EasyGUIColor.b / 10 };
                Global_EasyGUIColor = { 彩虹条颜色[3],彩虹条颜色[4], 彩虹条颜色[5] };
            }
            else if (BackGround_StyleCode == 4)//主题色渐变条
            {
                const auto Speed = 800;//渐变条变化速度
                const Vector3 Sins = { sin((float)GetTickCount64() / Speed), sin((float)GetTickCount64() / Speed + 1),sin((float)GetTickCount64() / Speed + 2) };
                彩虹条颜色 = {
                    (int)(Sins.z * Global_EasyGUIColor.r / 2 + Global_EasyGUIColor.r / 2),
                    (int)(Sins.z * Global_EasyGUIColor.g / 2 + Global_EasyGUIColor.g / 2),
                    (int)(Sins.z * Global_EasyGUIColor.b / 2 + Global_EasyGUIColor.b / 2),
                    (int)(Sins.y * Global_EasyGUIColor.r / 2 + Global_EasyGUIColor.r / 2),
                    (int)(Sins.y * Global_EasyGUIColor.g / 2 + Global_EasyGUIColor.g / 2),
                    (int)(Sins.y * Global_EasyGUIColor.b / 2 + Global_EasyGUIColor.b / 2),
                    (int)(Sins.x * Global_EasyGUIColor.r / 2 + Global_EasyGUIColor.r / 2),
                    (int)(Sins.x * Global_EasyGUIColor.g / 2 + Global_EasyGUIColor.g / 2),
                    (int)(Sins.x * Global_EasyGUIColor.b / 2 + Global_EasyGUIColor.b / 2)
                };
                const auto Min = 50; for (int i = 0; i <= 8; ++i)if (彩虹条颜色[i] < Min)彩虹条颜色[i] = Min;//颜色最小值
                主题颜色 = { 0,0,0,60,60,60,30,30,30,15,15,15,0,0,0,Global_EasyGUIColor.r / 10,Global_EasyGUIColor.g / 10,Global_EasyGUIColor.b / 10 };
            }
            In_DrawRect(0, 0, Window_Size.x, Window_Size.y, { 主题颜色[0], 主题颜色[1], 主题颜色[2] });
            In_DrawRect(1, 1, Window_Size.x - 2, Window_Size.y - 2, { 主题颜色[3], 主题颜色[4], 主题颜色[5] });
            In_DrawRect(2, 2, Window_Size.x - 4, Window_Size.y - 4, { 主题颜色[6], 主题颜色[7], 主题颜色[8] });
            In_DrawRect(5, 5, Window_Size.x - 10, Window_Size.y - 10, { 主题颜色[3], 主题颜色[4], 主题颜色[5] });
            In_DrawGradientRect(6, 6, Window_Size.x - 12, Window_Size.y - 12, { 主题颜色[12], 主题颜色[13], 主题颜色[14] }, { 主题颜色[15], 主题颜色[16], 主题颜色[17] }, true);//BackGround Gradient
            if (BackGround_StyleCode)//彩虹条
            {
                In_DrawGradientRect(7, 7, (Window_Size.x - 14) / 2, 2, { 彩虹条颜色[0] / 2, 彩虹条颜色[1] / 2, 彩虹条颜色[2] / 2 }, { 彩虹条颜色[3] / 2, 彩虹条颜色[4] / 2, 彩虹条颜色[5] / 2 }, false);
                In_DrawGradientRect(7 + (Window_Size.x - 14) / 2, 7, (Window_Size.x - 14) / 2, 2, { 彩虹条颜色[3] / 2, 彩虹条颜色[4] / 2, 彩虹条颜色[5] / 2 }, { 彩虹条颜色[6] / 2, 彩虹条颜色[7] / 2, 彩虹条颜色[8] / 2 }, false);
                In_DrawGradientRect(7, 7, (Window_Size.x - 14) / 2, 1, { 彩虹条颜色[0], 彩虹条颜色[1], 彩虹条颜色[2] }, { 彩虹条颜色[3], 彩虹条颜色[4], 彩虹条颜色[5] }, false);
                In_DrawGradientRect(7 + (Window_Size.x - 14) / 2, 7, (Window_Size.x - 14) / 2, 1, { 彩虹条颜色[3], 彩虹条颜色[4], 彩虹条颜色[5] }, { 彩虹条颜色[6], 彩虹条颜色[7], 彩虹条颜色[8] }, false);
            }
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector2 GUI_Block(int X, int Y, int Length, string BlockText, int Width = 400, BOOL Block_Judgment = true) noexcept//绘制按钮的区块
        {
            In_DrawRect(X, Y, Width, Length, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, Width - 2, Length - 2, { 60,60,60 });//白色外边框
            In_DrawGradientRect(X + 2, Y + 2, Width - 4, Length - 4, { 10,10,10 }, Global_EasyGUIColor / 10, true);//渐变背景
            In_DrawString(X + 21, Y - 6, BlockText.c_str(), { 0,0,0 }, "Small Fonts", 14, 700);
            In_DrawString(X + 20, Y - 7, BlockText.c_str(), { 200,200,200 }, "Small Fonts", 14, 700);
            if (Block_Judgment && ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + Width && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + Length) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom)))Mouse_Block_ = true;
            return { X,Y };
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        int GUI_Block_Panel(int X, int Y, int Width, int Length, string BlockText, vector<string>BlockText_, int& m_In_Block, short TextPos_X = 20) noexcept//区块_大区块选择器
        {
            if (m_In_Block < 0)m_In_Block = 0; else if (m_In_Block >= BlockText_.size())m_In_Block = BlockText_.size() - 1;//范围限制
            In_DrawRect(X, Y, Width, Length, { 0,0,0 });//黑色外边框
            In_DrawRect(X + 1, Y + 1, Width - 2, Length - 2, { 60,60,60 });//白色外边框
            In_DrawGradientRect(X + 2, Y + 2, Width - 4, Length - 4, Global_EasyGUIColor / 10, { 10,10,10 }, true);//主题色渐变背景
            In_DrawString(X + 16, Y - 6, BlockText.c_str(), { 0,0,0 }, "Small Fonts", 14, 700);
            In_DrawString(X + 15, Y - 7, BlockText.c_str(), { 200,200,200 }, "Small Fonts", 14, 700);
            for (short i = 0; i < BlockText_.size(); ++i)//遍历坐标
            {
                const BOOL DetectMousePos = In_MouseEventJudgment(X, Y + 14 + 30 * i, Width, 23);
                if (DetectMousePos)
                {
                    In_DrawGradientRect(X + 2, Y + 16 + 30 * i, Width - 4, 23, Global_EasyGUIColor / 5, { 20,20,20 });
                    if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)
                    {
                        if (In_KeyEvent(VK_LBUTTON, true))m_In_Block = i;//鼠标赋值选择
                        if (In_KeyEvent(VK_UP, true))--m_In_Block; else if (In_KeyEvent(VK_DOWN, true))++m_In_Block;//滚轮按键赋值
                        if (m_In_Block < 0)m_In_Block = 0; else if (m_In_Block >= BlockText_.size())m_In_Block = BlockText_.size() - 1;//范围限制
                    }
                }
                if (m_In_Block == i)
                {
                    const auto SelPos = In_Animation<CreateClassName>(Y + 16 + 30 * i, 2.5);
                    In_DrawGradientRect(X + 2, SelPos, Width - 4, 25, { 20,20,20 }, Global_EasyGUIColor / 4);
                    In_DrawGradientRect(X + 2, SelPos + 1, Width - 4, 23, Global_EasyGUIColor / 4, { 20,20,20 });
                }
                In_DrawString(X + TextPos_X + 1, Y + 21 + 30 * i, BlockText_[i], { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize + 2);
                In_DrawString(X + TextPos_X, Y + 20 + 30 * i, BlockText_[i], { 220,220,220 }, Global_EasyGUIFont, Global_EasyGUIFontSize + 2);
            }
            if ((EasyGUI_MousePos.x - EasyGUI_WindowPos.left >= X && EasyGUI_MousePos.x - EasyGUI_WindowPos.left <= X + Width && EasyGUI_MousePos.y - EasyGUI_WindowPos.top >= Y && EasyGUI_MousePos.y - EasyGUI_WindowPos.top <= Y + Length) || !(EasyGUI_MousePos.x >= EasyGUI_WindowPos.left && EasyGUI_MousePos.x <= EasyGUI_WindowPos.right && EasyGUI_MousePos.y >= EasyGUI_WindowPos.top && EasyGUI_MousePos.y <= EasyGUI_WindowPos.bottom))Mouse_Block_ = true;
            return m_In_Block;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        string GUI_Text(Vector2 BlockPos, short LineRow, string Text, Vector4 TextColor = { 200,200,200 }) noexcept//行文字
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return "";//当无block则不进行绘制
            In_DrawString(BlockPos.x + 53, BlockPos.y - 2 + 30 * LineRow, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + 52, BlockPos.y - 3 + 30 * LineRow, Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
            return Text;
        }
        //--------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Checkbox(Vector2 BlockPos, short LineRow, string Text, BOOL& m_CheckboxValue, Vector4 TextColor = { 200,200,200 }) noexcept//点击框
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 30, BlockPos.y + 30 * LineRow - 2, 140, 12);//窗口检测
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_ && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))m_CheckboxValue = !m_CheckboxValue;//当最前端窗口为GUI窗口接收按钮事件
            In_DrawRect(BlockPos.x + 29, BlockPos.y - 1 + 30 * LineRow, 10, 10, { 0,0,0 });
            In_DrawString(BlockPos.x + 53, BlockPos.y - 2 + 30 * LineRow, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + 52, BlockPos.y - 3 + 30 * LineRow, Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
            if (m_CheckboxValue)In_DrawGradientRect(BlockPos.x + 30, BlockPos.y + 30 * LineRow, 8, 8, Global_EasyGUIColor, Global_EasyGUIColor / 5, true);//绘制开关状态 (颜色主体)
            else
            {
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 30, BlockPos.y + 30 * LineRow, 8, 8, Global_EasyGUIColor / 3, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 30, BlockPos.y + 30 * LineRow, 8, 8, Global_EasyGUIColor / 4, { 30,30,30 }, true);
            }
            return m_CheckboxValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Button(Vector2 BlockPos, short LineRow, string Text, BOOL& m_ButtonValue, short TextPos = 10) noexcept//单击按钮
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            if (m_ButtonValue)Sleep(30);//更好地让其他循环线程接收
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 8, 230, 25);//窗口检测机制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)m_ButtonValue = !m_ButtonValue && DetectMousePos && In_KeyEvent(VK_LBUTTON, true);//当最前端窗口为GUI窗口接收按钮事件
            In_DrawRect(BlockPos.x + 53, BlockPos.y - 10 + 30 * LineRow, 234, 29, { 0,0,0 });
            In_DrawRect(BlockPos.x + 54, BlockPos.y - 9 + 30 * LineRow, 232, 27, { 60,60,60 });
            if (DetectMousePos && !m_ButtonValue)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 8, 230, 25, Global_EasyGUIColor / 5, { 20,20,20 }, true);
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 8, 230, 25, Global_EasyGUIColor / 7, { 20,20,20 }, true);
            In_DrawString(BlockPos.x + TextPos + 56, BlockPos.y - 1 + 30 * LineRow, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + TextPos + 55, BlockPos.y - 2 + 30 * LineRow, Text, { 200,200,200 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            return m_ButtonValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Button_Small(Vector2 BlockPos, short LineRow, BOOL& m_ButtonValue, string Text = "...") noexcept//单击按钮(小号)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            if (m_ButtonValue)Sleep(30);//更好地让其他循环线程接收
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 10, BlockPos.y + 30 * LineRow - 5, 13, 18);//窗口检测机制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)m_ButtonValue = !m_ButtonValue && DetectMousePos && In_KeyEvent(VK_LBUTTON, true);//当最前端窗口为GUI窗口接收按钮事件
            In_DrawRect(BlockPos.x + 8, BlockPos.y - 7 + 30 * LineRow, 17, 22, { 0,0,0 });
            In_DrawRect(BlockPos.x + 9, BlockPos.y - 6 + 30 * LineRow, 15, 20, { 60,60,60 });
            if (DetectMousePos && !m_ButtonValue)In_DrawGradientRect(BlockPos.x + 10, BlockPos.y + 30 * LineRow - 5, 13, 18, Global_EasyGUIColor / 5, { 20,20,20 }, true);
            else In_DrawGradientRect(BlockPos.x + 10, BlockPos.y + 30 * LineRow - 5, 13, 18, Global_EasyGUIColor / 7, { 20,20,20 }, true);
            In_DrawString_Simple(BlockPos.x + 12, BlockPos.y + 30 * LineRow - 1, Text, { 200,200,200 });
            return m_ButtonValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class ValueClass, class CreateClassName>
        ValueClass GUI_Slider(Vector2 BlockPos, short LineRow, string Text, ValueClass StartValue, ValueClass EndValue, ValueClass& m_SliderValue, string Unit = "", Vector4 TextColor = { 200,200,200 }) noexcept//滑条
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, 230, 5);//窗口检测
            static BOOL OutSide = false;//防止指针脱落时失去控制力
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件
            {
                static const ValueClass ClassValueDetect = 0.1;//检测是否是浮点值 (变量)
                if (DetectMousePos && (In_KeyEvent(VK_LEFT, true) || In_KeyEvent(VK_UP, true)))//当鼠标移动到滑条上方 按键反馈事件
                {
                    if (ClassValueDetect == 0)m_SliderValue--; else m_SliderValue -= 0.05;//检测是否是浮点值
                }
                else if (DetectMousePos && (In_KeyEvent(VK_RIGHT, true) || In_KeyEvent(VK_DOWN, true)))
                {
                    if (ClassValueDetect == 0)m_SliderValue++; else m_SliderValue += 0.05;//检测是否是浮点值
                }
                if (In_KeyEvent(VK_LBUTTON) && DetectMousePos && !OutSide)OutSide = true;
                if (OutSide && In_KeyEvent(VK_LBUTTON)) { m_SliderValue = ((EasyGUI_MousePos.x - BlockPos.x - EasyGUI_WindowPos.left - 54) * (EndValue - StartValue) / 230) + StartValue; Mouse_Block_ = true; Mouse_Slider_ = true; }
                else if (!In_KeyEvent(VK_LBUTTON)) { OutSide = false; Mouse_Slider_ = false; }
            }
            int SliderPos = (float)(m_SliderValue - StartValue) / (float)(EndValue - StartValue) * 230;
            if (SliderPos > 230)SliderPos = 230; else if (SliderPos < 0) SliderPos = 0;
            if (m_SliderValue <= StartValue)m_SliderValue = StartValue; else if (m_SliderValue >= EndValue)m_SliderValue = EndValue;//范围限制
            stringstream ss; ss << fixed << setprecision(4) << m_SliderValue; ss >> m_SliderValue;//只保留4位小数点后数
            In_DrawRect(BlockPos.x + 54, BlockPos.y + 5 + 30 * LineRow, 232, 7, { 0,0,0 });//黑色外边框
            if (DetectMousePos || OutSide)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, 230, 5, { 30,30,30 }, Global_EasyGUIColor / 4, true);//滑条背景
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, 230, 5, { 20,20,20 }, Global_EasyGUIColor / 5, true);
            In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, In_Animation<CreateClassName>(SliderPos, 10, { 0,230 }), 5, Global_EasyGUIColor / 2, Global_EasyGUIColor / 10, true);//滑条减退动画 (动画0.8果冻效果)
            In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 6 + 30 * LineRow, SliderPos, 5, Global_EasyGUIColor, Global_EasyGUIColor / 5, true);//滑条
            In_DrawString(BlockPos.x + 56, BlockPos.y - 9 + 30 * LineRow, Text, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString(BlockPos.x + 55, BlockPos.y - 10 + 30 * LineRow, Text, TextColor, Global_EasyGUIFont, Global_EasyGUIFontSize);
            In_DrawString_Simple(BlockPos.x + 295, BlockPos.y + 2 + 30 * LineRow, ss.str() + Unit, { 150,150,150 });//返回值绘制
            return m_SliderValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        int GUI_KeySelector(Vector2 BlockPos, short LineRow, int& m_KeySelectValue) noexcept//按键选取按钮
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            if (m_KeySelectValue >= 0xCCCCCCCC)m_KeySelectValue = 0;//修复过量
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 350, BlockPos.y + 26 + 30 * (LineRow - 1), 40, 12);//鼠标坐标检测
            static BOOL BoxMea = false;//只声明一次初始开关设定变量
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件
            {
                if (!BoxMea && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))BoxMea = true;
                else if (BoxMea)
                {
                    if (In_KeyEvent(VK_BACK, true) || In_KeyEvent(VK_ESCAPE, true)) { m_KeySelectValue = 0; BoxMea = false; }//默认无值
                    for (int i = 0x0; i < 0xFE; ++i)if (In_KeyEvent(i, true)) { m_KeySelectValue = i; BoxMea = false; }//当按下任意键
                }
            }
            if (!BoxMea)
            {
                string DrawString_VK = "";
                switch (m_KeySelectValue)
                {
                case 0x00: DrawString_VK = "[-]"; break;
                case 0x01: DrawString_VK = "[M1]"; break;//鼠标左键
                case 0x02: DrawString_VK = "[M2]"; break;//鼠标右键
                case 0x03: DrawString_VK = "[CAN]"; break;//鼠标中断处理
                case 0x04: DrawString_VK = "[M3]"; break;//鼠标中键
                case 0x05: DrawString_VK = "[M4]"; break;//鼠标侧键下
                case 0x06: DrawString_VK = "[M5]"; break;//鼠标侧键上
                case 0x07: DrawString_VK = "[NONE]"; break;
                case 0x08: DrawString_VK = "[BACK]"; break;
                case 0x09: DrawString_VK = "[TAB]"; break;
                case 0x0C: DrawString_VK = "[CLE]"; break;
                case 0x0D: DrawString_VK = "[ENT]"; break;
                case 0x10: DrawString_VK = "[SHF]"; break;
                case 0x11: DrawString_VK = "[CLR]"; break;
                case 0x12: DrawString_VK = "[ALT]"; break;
                case 0x13: DrawString_VK = "[PAU]"; break;
                case 0x14: DrawString_VK = "[CAP]"; break;
                case 0x15: DrawString_VK = "[KAN]"; break;
                case 0x16: DrawString_VK = "[KAN]"; break;
                case 0x17: DrawString_VK = "[JUN]"; break;
                case 0x18: DrawString_VK = "[FIN]"; break;
                case 0x19: DrawString_VK = "[HAN]"; break;
                case 0x1B: DrawString_VK = "[ESC]"; break;
                case 0x1C: DrawString_VK = "[CON]"; break;
                case 0x1D: DrawString_VK = "[NON]"; break;
                case 0x1E: DrawString_VK = "[ACC]"; break;
                case 0x1F: DrawString_VK = "[MOD]"; break;
                case 0x20: DrawString_VK = "[SPA]"; break;
                case 0x21: DrawString_VK = "[PRI]"; break;
                case 0x22: DrawString_VK = "[NEXT]"; break;
                case 0x23: DrawString_VK = "[END]"; break;
                case 0x24: DrawString_VK = "[HOME]"; break;
                case 0x25: DrawString_VK = "[LEFT]"; break;
                case 0x26: DrawString_VK = "[UP]"; break;
                case 0x27: DrawString_VK = "[RIGT]"; break;
                case 0x28: DrawString_VK = "[DOWN]"; break;
                case 0x29: DrawString_VK = "[SEL]"; break;
                case 0x2A: DrawString_VK = "[PRI]"; break;
                case 0x2B: DrawString_VK = "[EXE]"; break;
                case 0x2C: DrawString_VK = "[SNAP]"; break;
                case 0x2D: DrawString_VK = "[INS]"; break;
                case 0x2E: DrawString_VK = "[DEL]"; break;
                case 0x2F: DrawString_VK = "[HELP]"; break;
                case 0x30: DrawString_VK = "[0]"; break;
                case 0x31: DrawString_VK = "[1]"; break;
                case 0x32: DrawString_VK = "[2]"; break;
                case 0x33: DrawString_VK = "[3]"; break;
                case 0x34: DrawString_VK = "[4]"; break;
                case 0x35: DrawString_VK = "[5]"; break;
                case 0x36: DrawString_VK = "[6]"; break;
                case 0x37: DrawString_VK = "[7]"; break;
                case 0x38: DrawString_VK = "[8]"; break;
                case 0x39: DrawString_VK = "[9]"; break;
                case 0x41: DrawString_VK = "[A]"; break;
                case 0x42: DrawString_VK = "[B]"; break;
                case 0x43: DrawString_VK = "[C]"; break;
                case 0x44: DrawString_VK = "[D]"; break;
                case 0x45: DrawString_VK = "[E]"; break;
                case 0x46: DrawString_VK = "[F]"; break;
                case 0x47: DrawString_VK = "[G]"; break;
                case 0x48: DrawString_VK = "[H]"; break;
                case 0x49: DrawString_VK = "[I]"; break;
                case 0x4A: DrawString_VK = "[J]"; break;
                case 0x4B: DrawString_VK = "[K]"; break;
                case 0x4C: DrawString_VK = "[L]"; break;
                case 0x4D: DrawString_VK = "[M]"; break;
                case 0x4E: DrawString_VK = "[N]"; break;
                case 0x4F: DrawString_VK = "[O]"; break;
                case 0x50: DrawString_VK = "[P]"; break;
                case 0x51: DrawString_VK = "[Q]"; break;
                case 0x52: DrawString_VK = "[R]"; break;
                case 0x53: DrawString_VK = "[S]"; break;
                case 0x54: DrawString_VK = "[T]"; break;
                case 0x55: DrawString_VK = "[U]"; break;
                case 0x56: DrawString_VK = "[V]"; break;
                case 0x57: DrawString_VK = "[W]"; break;
                case 0x58: DrawString_VK = "[X]"; break;
                case 0x59: DrawString_VK = "[Y]"; break;
                case 0x5A: DrawString_VK = "[Z]"; break;
                case 0x5B: DrawString_VK = "[WIN]"; break;//L
                case 0x5C: DrawString_VK = "[WIN]"; break;//R
                case 0x5D: DrawString_VK = "[APP]"; break;
                case 0x5F: DrawString_VK = "[SLP]"; break;
                case 0x60: DrawString_VK = "[0]"; break;
                case 0x61: DrawString_VK = "[1]"; break;
                case 0x62: DrawString_VK = "[2]"; break;
                case 0x63: DrawString_VK = "[3]"; break;
                case 0x64: DrawString_VK = "[4]"; break;
                case 0x65: DrawString_VK = "[5]"; break;
                case 0x66: DrawString_VK = "[6]"; break;
                case 0x67: DrawString_VK = "[7]"; break;
                case 0x68: DrawString_VK = "[8]"; break;
                case 0x69: DrawString_VK = "[9]"; break;
                case 0x6A: DrawString_VK = "[*]"; break;
                case 0x6B: DrawString_VK = "[+]"; break;
                case 0x6C: DrawString_VK = "[SEP]"; break;
                case 0x6D: DrawString_VK = "[-]"; break;
                case 0x6E: DrawString_VK = "[.]"; break;
                case 0x6F: DrawString_VK = "[/]"; break;
                case 0x70: DrawString_VK = "[F1]"; break;
                case 0x71: DrawString_VK = "[F2]"; break;
                case 0x72: DrawString_VK = "[F3]"; break;
                case 0x73: DrawString_VK = "[F4]"; break;
                case 0x74: DrawString_VK = "[F5]"; break;
                case 0x75: DrawString_VK = "[F6]"; break;
                case 0x76: DrawString_VK = "[F7]"; break;
                case 0x77: DrawString_VK = "[F8]"; break;
                case 0x78: DrawString_VK = "[F9]"; break;
                case 0x79: DrawString_VK = "[F10]"; break;
                case 0x7A: DrawString_VK = "[F11]"; break;
                case 0x7B: DrawString_VK = "[F12]"; break;
                case 0x7C: DrawString_VK = "[F13]"; break;
                case 0x7D: DrawString_VK = "[F14]"; break;
                case 0x7E: DrawString_VK = "[F15]"; break;
                case 0x7F: DrawString_VK = "[F16]"; break;
                case 0x80: DrawString_VK = "[F17]"; break;
                case 0x81: DrawString_VK = "[F18]"; break;
                case 0x82: DrawString_VK = "[F19]"; break;
                case 0x83: DrawString_VK = "[F20]"; break;
                case 0x84: DrawString_VK = "[F21]"; break;
                case 0x85: DrawString_VK = "[F22]"; break;
                case 0x86: DrawString_VK = "[F23]"; break;
                case 0x87: DrawString_VK = "[F24]"; break;
                case 0x90: DrawString_VK = "[NUM]"; break;
                case 0x91: DrawString_VK = "[SCR]"; break;
                case 0xA0: DrawString_VK = "[SHF]"; break;//L
                case 0xA1: DrawString_VK = "[SHF]"; break;//R
                case 0xA2: DrawString_VK = "[CLR]"; break;//L
                case 0xA3: DrawString_VK = "[CLR]"; break;//R
                case 0xA4: DrawString_VK = "[ALT]"; break;//L
                case 0xA5: DrawString_VK = "[ALT]"; break;//R
                case 0xC0: DrawString_VK = "[~]"; break;
                case 0xBC: DrawString_VK = "[,]"; break;
                case 0xBE: DrawString_VK = "[.]"; break;
                case 0xBF: DrawString_VK = "[/]"; break;
                case 0xBA: DrawString_VK = "[;]"; break;
                case 0xDE: DrawString_VK = "[']"; break;
                case 0xDB: DrawString_VK = "[[]"; break;
                case 0xDD: DrawString_VK = "[]]"; break;
                case 0xDC: DrawString_VK = "[\]"; break;
                default: DrawString_VK = "[" + to_string(m_KeySelectValue) + "]"; break;//如果什么都不是直接返回编码
                }
                if (DetectMousePos)In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + 30 * (LineRow - 1), DrawString_VK, { 130,130,130 });
                else In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + 30 * (LineRow - 1), DrawString_VK, { 100,100,100 });
                return m_KeySelectValue;
            }
            else In_DrawString_Simple(BlockPos.x + 355, BlockPos.y + 27 + 30 * (LineRow - 1), "[-]", Global_EasyGUIColor / 2);//激活读取
            return false;//激活读取时返回false
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        BOOL GUI_Tips(Vector2 BlockPos, short LineRow, string TipsString, int BackGround_Length = 0, Vector4 TextColor = { 255,255,255 }) noexcept//鼠标指针提示 (只支持单行字符,代码写在最后为了不被覆盖绘制)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            In_DrawString_Simple(BlockPos.x + 8, BlockPos.y + 27 + 30 * (LineRow - 1), "[?]", { 100,100,100 });//GUI绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 8, BlockPos.y + 26 + 30 * (LineRow - 1), 13, 13) && !Mouse_Slider_)//当鼠标移动到问号 且GUI窗口为最顶层
            {
                short Rect_Length = strlen(TipsString.c_str()) * 6; if (BackGround_Length != 0)Rect_Length = BackGround_Length;//自定义背景方框长度
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 15, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 10, Rect_Length, 20, { 0,0,0 });
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 16, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 11, Rect_Length - 2, 18, { 60,60,60 });
                In_DrawRect(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 17, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 12, Rect_Length - 4, 16, { 15,15,15 });
                In_DrawString_Simple(EasyGUI_MousePos.x - EasyGUI_WindowPos.left + 19, EasyGUI_MousePos.y - EasyGUI_WindowPos.top + 14, TipsString, TextColor);
                return true;
            }
            else return false;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector4 GUI_ColorSelector(Vector2 BlockPos, short LineRow, Vector4& m_ColorValue) noexcept//颜色选择器
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1 };//当无block则不进行绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 360, BlockPos.y - 6 + 30 * LineRow, 20, 20) && !Mouse_Slider_ && !Mouse_Move_ && In_KeyEvent(VK_LBUTTON, true))//复制选取的颜色值
            {
                const string Color_String_Copy__ = to_string(m_ColorValue.r) + ", " + to_string(m_ColorValue.g) + ", " + to_string(m_ColorValue.b);//要复制的字符串
                OpenClipboard(0);//打开剪切板
                EmptyClipboard();//清空剪切板
                const auto hHandle = GlobalAlloc(0, strlen(Color_String_Copy__.c_str()) + 1);//分配内存
                strcpy_s((char*)GlobalLock(hHandle), strlen(Color_String_Copy__.c_str()) + 1, Color_String_Copy__.c_str());
                SetClipboardData(1, hHandle);//设置剪切板数据
                GlobalUnlock(hHandle);//解除锁定
                CloseClipboard();//关闭剪切板
            }
            for (short Color_Bl = 0; Color_Bl <= 2; ++Color_Bl)
            {
                vector<int> UsedColor = { m_ColorValue.r,m_ColorValue.g,m_ColorValue.b };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 218 + 46 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 41, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedColor[Color_Bl]++;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedColor[Color_Bl]--;
                    if (In_KeyEvent(VK_LEFT, true) || In_KeyEvent(VK_UP, true))UsedColor[Color_Bl] += 5;
                    else if (In_KeyEvent(VK_RIGHT, true) || In_KeyEvent(VK_DOWN, true))UsedColor[Color_Bl] -= 5;
                }
                if (UsedColor[Color_Bl] >= 255)UsedColor[Color_Bl] = 255;
                else if (UsedColor[Color_Bl] <= 0)UsedColor[Color_Bl] = 0;//范围限制
                m_ColorValue = { UsedColor[0],UsedColor[1],UsedColor[2] };
                In_DrawRect(BlockPos.x + 218 + 46 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 41, 20, { 0,0,0 });//Color_Block
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 219 + 46 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 39, 18, Global_EasyGUIColor / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 219 + 46 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 39, 18, Global_EasyGUIColor / 5, { 30,30,30 }, true);
            }
            In_DrawString_Simple(BlockPos.x + 223, BlockPos.y - 2 + 30 * LineRow, "R: " + to_string(m_ColorValue.r), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 269, BlockPos.y - 2 + 30 * LineRow, "G: " + to_string(m_ColorValue.g), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 315, BlockPos.y - 2 + 30 * LineRow, "B: " + to_string(m_ColorValue.b), { 150,150,150 });
            In_DrawRect(BlockPos.x + 360, BlockPos.y - 6 + 30 * LineRow, 20, 20, { 0,0,0 });//Color
            In_DrawGradientRect(BlockPos.x + 361, BlockPos.y - 5 + 30 * LineRow, 18, 18, m_ColorValue, m_ColorValue / 4, true);
            return m_ColorValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector4 GUI_ColorSelector_a(Vector2 BlockPos, short LineRow, Vector4& m_ColorValue) noexcept//颜色选择器(包含Alpha 透明度值)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1,-1 };//当无block则不进行绘制
            if (GetForegroundWindow() == EasyGUI_WindowHWND && In_MouseEventJudgment(BlockPos.x + 360, BlockPos.y - 6 + 30 * LineRow, 20, 20) && !Mouse_Slider_ && !Mouse_Move_ && In_KeyEvent(VK_LBUTTON, true))//复制选取的颜色值
            {
                const string Color_String_Copy__ = to_string(m_ColorValue.r) + ", " + to_string(m_ColorValue.g) + ", " + to_string(m_ColorValue.b) + ", " + to_string(m_ColorValue.a);//要复制的字符串
                OpenClipboard(0);//打开剪切板
                EmptyClipboard();//清空剪切板
                const auto hHandle = GlobalAlloc(0, strlen(Color_String_Copy__.c_str()) + 1);//分配内存
                strcpy_s((char*)GlobalLock(hHandle), strlen(Color_String_Copy__.c_str()) + 1, Color_String_Copy__.c_str());
                SetClipboardData(1, hHandle);//设置剪切板数据
                GlobalUnlock(hHandle);//解除锁定
                CloseClipboard();//关闭剪切板
            }
            for (short Color_Bl = 0; Color_Bl <= 3; ++Color_Bl)
            {
                vector<int> UsedColor = { m_ColorValue.r,m_ColorValue.g,m_ColorValue.b,m_ColorValue.a };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 172 + 46 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 41, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedColor[Color_Bl]++;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedColor[Color_Bl]--;
                    if (In_KeyEvent(VK_LEFT, true) || In_KeyEvent(VK_UP, true))UsedColor[Color_Bl] += 5;
                    else if (In_KeyEvent(VK_RIGHT, true) || In_KeyEvent(VK_DOWN, true))UsedColor[Color_Bl] -= 5;
                }
                if (UsedColor[Color_Bl] >= 255)UsedColor[Color_Bl] = 255;//范围限制
                else if (UsedColor[Color_Bl] <= 0)UsedColor[Color_Bl] = 0;
                m_ColorValue = { UsedColor[0],UsedColor[1],UsedColor[2],UsedColor[3] };
                In_DrawRect(BlockPos.x + 172 + 46 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 41, 20, { 0,0,0 });
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 173 + 46 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 39, 18, Global_EasyGUIColor / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 173 + 46 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 39, 18, Global_EasyGUIColor / 5, { 30,30,30 }, true);
            }
            In_DrawString_Simple(BlockPos.x + 177, BlockPos.y - 2 + 30 * LineRow, "R: " + to_string(m_ColorValue.r), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 223, BlockPos.y - 2 + 30 * LineRow, "G: " + to_string(m_ColorValue.g), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 269, BlockPos.y - 2 + 30 * LineRow, "B: " + to_string(m_ColorValue.b), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 315, BlockPos.y - 2 + 30 * LineRow, "A: " + to_string(m_ColorValue.a), { 150,150,150 });
            In_DrawRect(BlockPos.x + 360, BlockPos.y - 6 + 30 * LineRow, 20, 20, { 0,0,0 });
            In_DrawGradientRect(BlockPos.x + 361, BlockPos.y - 5 + 30 * LineRow, 18, 18, m_ColorValue, m_ColorValue / 4, true);//Color
            return m_ColorValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        Vector3 GUI_PosSelector(Vector2 BlockPos, short LineRow, Vector3& m_PosValue) noexcept//坐标选择器
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return { -1,-1,-1 };//当无block则不进行绘制
            for (short Color_Bl = 0; Color_Bl <= 2; ++Color_Bl)
            {
                vector<float> UsedPos = { m_PosValue.x,m_PosValue.y,m_PosValue.z };
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 180 + 70 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 68, 20);
                if (GetForegroundWindow() == EasyGUI_WindowHWND && DetectMousePos && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收按钮事件 当鼠标移动到滑条上方 按键反馈事件
                {
                    if (In_KeyEvent(VK_LBUTTON, true))UsedPos[Color_Bl] += 0.03;
                    else if (In_KeyEvent(VK_RBUTTON, true))UsedPos[Color_Bl] -= 0.03;
                    if (In_KeyEvent(VK_LEFT, true))UsedPos[Color_Bl] += 1;
                    else if (In_KeyEvent(VK_RIGHT, true))UsedPos[Color_Bl] -= 1;
                    if (In_KeyEvent(VK_UP, true))UsedPos[Color_Bl] += 10;//快速变值
                    else if (In_KeyEvent(VK_DOWN, true))UsedPos[Color_Bl] -= 10;
                    m_PosValue = { UsedPos[0],UsedPos[1],UsedPos[2] };
                }
                In_DrawRect(BlockPos.x + 180 + 70 * Color_Bl, BlockPos.y - 6 + 30 * LineRow, 70, 20, { 0,0,0 });
                if (DetectMousePos)In_DrawGradientRect(BlockPos.x + 181 + 70 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 68, 18, Global_EasyGUIColor / 4, { 30,30,30 }, true);
                else In_DrawGradientRect(BlockPos.x + 181 + 70 * Color_Bl, BlockPos.y - 5 + 30 * LineRow, 68, 18, Global_EasyGUIColor / 5, { 30,30,30 }, true);
            }
            stringstream Float_X_; Float_X_ << fixed << setprecision(2) << m_PosValue.x; Float_X_ >> m_PosValue.x;//只保留2位小数点后数
            stringstream Float_Y_; Float_Y_ << fixed << setprecision(2) << m_PosValue.y; Float_Y_ >> m_PosValue.y;
            stringstream Float_Z_; Float_Z_ << fixed << setprecision(2) << m_PosValue.z; Float_Z_ >> m_PosValue.z;
            In_DrawString_Simple(BlockPos.x + 185, BlockPos.y - 2 + 30 * LineRow, "X: " + Float_X_.str(), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 255, BlockPos.y - 2 + 30 * LineRow, "Y: " + Float_Y_.str(), { 150,150,150 });
            In_DrawString_Simple(BlockPos.x + 325, BlockPos.y - 2 + 30 * LineRow, "Z: " + Float_Z_.str(), { 150,150,150 });
            return m_PosValue;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        int GUI_List(Vector2 BlockPos, short StartLineRow, vector<string>LineString, int& m_InLine, short LimitLine = 0) noexcept//选择列表(缩小版 Panel)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return false;//当无block则不进行绘制
            if (m_InLine < 0)m_InLine = 0; else if (m_InLine >= LineString.size())m_InLine = LineString.size() - 1;//范围限制
            if (!LimitLine)LimitLine = LineString.size(); if (LineString.size() == 0)m_InLine = -1;
            In_DrawRect(BlockPos.x + 53, BlockPos.y - 10 + 30 * StartLineRow, 234, LimitLine * 25 + 5, { 0,0,0 });//黑色外边框
            In_DrawGradientRect(BlockPos.x + 54, BlockPos.y - 9 + 30 * StartLineRow, 232, LimitLine * 25 + 3, Global_EasyGUIColor / 10, { 10,10,10 }, true);//主题色渐变背景
            for (short i = 0; i < LineString.size(); ++i)
            {
                if (i >= LimitLine)continue;//限制行数
                const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + i * 25 - 5, 232, 20);//光标检测范围
                if (DetectMousePos)//当光标选择时(在上方时)
                {
                    if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)
                    {
                        if (In_KeyEvent(VK_LBUTTON, true))m_InLine = i;//鼠标赋值选择
                        if (In_KeyEvent(VK_UP, true))--m_InLine; else if (In_KeyEvent(VK_DOWN, true))++m_InLine;//滚轮按键赋值
                        if (m_InLine < 0)m_InLine = 0; else if (m_InLine >= LineString.size())m_InLine = LineString.size() - 1;//范围限制
                    }
                    In_DrawGradientRect(BlockPos.x + 54, BlockPos.y + StartLineRow * 30 + i * 25 - 5, 232, 20, Global_EasyGUIColor / 7, { 15,15,15 });
                }
                if (m_InLine == i)
                {
                    const auto SelPos = In_Animation<CreateClassName>(BlockPos.y + StartLineRow * 30 + i * 25, 2);
                    In_DrawGradientRect(BlockPos.x + 54, SelPos - 5, 232, 20, Global_EasyGUIColor / 6, { 15,15,15 });
                    In_DrawString(BlockPos.x + 66, SelPos, LineString[i], { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize, 600);
                    In_DrawString(BlockPos.x + 65, SelPos - 1, LineString[i], Global_EasyGUIColor, Global_EasyGUIFont, Global_EasyGUIFontSize, 600);
                }
                else {
                    In_DrawString(BlockPos.x + 66, BlockPos.y + StartLineRow * 30 + i * 25, LineString[i], { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
                    if (LineString[i] == "None" || LineString[i] == "none" || LineString[i] == "NONE" || LineString[i] == "NULL")In_DrawString(BlockPos.x + 65, BlockPos.y + StartLineRow * 30 + i * 25 - 1, LineString[i], { 80,80,80 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
                    else In_DrawString(BlockPos.x + 65, BlockPos.y + StartLineRow * 30 + i * 25 - 1, LineString[i], { 200,200,200 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
                }
            }
            return m_InLine;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
        template<class CreateClassName>
        string GUI_InputText(Vector2 BlockPos, short LineRow, string& m_String, string NormalText = "") noexcept//字符串输入框 (英文数字 不支持UTF-8 最多30个字符)
        {
            if (BlockPos.x == 0 && BlockPos.y == 0)return "";//当无block则不进行绘制
            const BOOL DetectMousePos = In_MouseEventJudgment(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 9, 230, 25);//窗口检测机制
            static BOOL IsInput = false;//判断是否在输入变量
            string DrawString = m_String;//绘制字符串
            if (GetForegroundWindow() == EasyGUI_WindowHWND && !Mouse_Slider_ && !Mouse_Move_)//当最前端窗口为GUI窗口接收输入框事件
            {
                if (!IsInput && DetectMousePos && In_KeyEvent(VK_LBUTTON, true))IsInput = true;//进入输入状态
                else if (IsInput)//在输入状态时
                {
                    string PressedKey = "";//按键记录变量
                    if (In_KeyEvent(VK_LCONTROL) || In_KeyEvent(VK_RCONTROL))//Ctrl键脚本
                    {
                        if (In_KeyEvent(0x43, true))//Ctrl + C 复制
                        {
                            OpenClipboard(0);//打开剪切板
                            EmptyClipboard();//清空剪切板
                            const auto hHandle = GlobalAlloc(0, strlen(m_String.c_str()) + 1);//分配内存
                            strcpy_s((char*)GlobalLock(hHandle), strlen(m_String.c_str()) + 1, m_String.c_str());
                            SetClipboardData(1, hHandle);//设置剪切板数据
                            GlobalUnlock(hHandle);//解除锁定
                            CloseClipboard();//关闭剪切板
                        }
                        if (In_KeyEvent(0x56, true))//Ctrl + V 粘贴
                        {
                            OpenClipboard(0);//打开剪贴板
                            if (IsClipboardFormatAvailable(1))
                            {
                                const auto h = GetClipboardData(1);//获取剪切板数据
                                m_String += ((char*)GlobalLock(h));//在尾部粘贴字符串内容
                                GlobalUnlock(h);//解除锁定
                            }
                            CloseClipboard();//关闭剪贴板
                        }
                    }
                    for (int i = 0x8; i < 0xFE; ++i)//VK键码遍历 (检测按下了什么键)
                    {
                        if (In_KeyEvent(VK_LCONTROL) || In_KeyEvent(VK_RCONTROL))continue;//不阻止Ctrl脚本事件
                        if (In_KeyEvent(i, true))
                        {
                            switch (i)//相比if函数执行更快
                            {
                            case 0x20:PressedKey = " "; break;
                            case 0x30:PressedKey = "0"; break;
                            case 0x31:PressedKey = "1"; break;
                            case 0x32:PressedKey = "2"; break;
                            case 0x33:PressedKey = "3"; break;
                            case 0x34:PressedKey = "4"; break;
                            case 0x35:PressedKey = "5"; break;
                            case 0x36:PressedKey = "6"; break;
                            case 0x37:PressedKey = "7"; break;
                            case 0x38:PressedKey = "8"; break;
                            case 0x39:PressedKey = "9"; break;
                            case 0x41:PressedKey = "a"; break;
                            case 0x42:PressedKey = "b"; break;
                            case 0x43:PressedKey = "c"; break;
                            case 0x44:PressedKey = "d"; break;
                            case 0x45:PressedKey = "e"; break;
                            case 0x46:PressedKey = "f"; break;
                            case 0x47:PressedKey = "g"; break;
                            case 0x48:PressedKey = "h"; break;
                            case 0x49:PressedKey = "i"; break;
                            case 0x4A:PressedKey = "j"; break;
                            case 0x4B:PressedKey = "k"; break;
                            case 0x4C:PressedKey = "l"; break;
                            case 0x4D:PressedKey = "m"; break;
                            case 0x4E:PressedKey = "n"; break;
                            case 0x4F:PressedKey = "o"; break;
                            case 0x50:PressedKey = "p"; break;
                            case 0x51:PressedKey = "q"; break;
                            case 0x52:PressedKey = "r"; break;
                            case 0x53:PressedKey = "s"; break;
                            case 0x54:PressedKey = "t"; break;
                            case 0x55:PressedKey = "u"; break;
                            case 0x56:PressedKey = "v"; break;
                            case 0x57:PressedKey = "w"; break;
                            case 0x58:PressedKey = "x"; break;
                            case 0x59:PressedKey = "y"; break;
                            case 0x5A:PressedKey = "z"; break;
                            case 0xBE:PressedKey = "."; break;
                            case 0xBF:PressedKey = "/"; break;
                            case 0x60:PressedKey = "0"; break;//以下小键盘按键**
                            case 0x61:PressedKey = "1"; break;
                            case 0x62:PressedKey = "2"; break;
                            case 0x63:PressedKey = "3"; break;
                            case 0x64:PressedKey = "4"; break;
                            case 0x65:PressedKey = "5"; break;
                            case 0x66:PressedKey = "6"; break;
                            case 0x67:PressedKey = "7"; break;
                            case 0x68:PressedKey = "8"; break;
                            case 0x69:PressedKey = "9"; break;
                            case 0x6A:PressedKey = "*"; break;
                            case 0x6B:PressedKey = "+"; break;
                            case 0x6D:PressedKey = "-"; break;
                            case 0x6E:PressedKey = "."; break;
                            case 0x6F:PressedKey = "/"; break;//以上小键盘按键**
                            //===================================================
                            case VK_BACK:if (m_String.size() > 0)m_String.erase(m_String.end() - 1); break;//擦除最后一个字符
                            case VK_DELETE:m_String = ""; break;//清除全部字符
                            case VK_ESCAPE:case VK_RETURN:IsInput = false; break;//按键解除输入状态
                            }
                            if (GetKeyState(0x14))transform(PressedKey.begin(), PressedKey.end(), PressedKey.begin(), toupper);//转换大写 (仅限CAPSLOCK)
                            m_String += PressedKey;//返回按下
                        }
                    }
                    m_String = m_String.substr(0, 30);//防止过量 (防止绘制在非绘制区域)
                    DrawString += "_";//输入中 绘制标识
                    if (!DetectMousePos && (In_KeyEvent(VK_LBUTTON) || In_KeyEvent(VK_RBUTTON)))IsInput = false;//鼠标解除输入状态
                }
            }
            In_DrawRect(BlockPos.x + 53, BlockPos.y - 9 + 30 * LineRow, 234, 27, { 0,0,0 });
            In_DrawRect(BlockPos.x + 54, BlockPos.y - 8 + 30 * LineRow, 232, 25, { 60,60,60 });
            if (DetectMousePos || IsInput)In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 7, 230, 23, { 15,15,15 }, Global_EasyGUIColor / 6, true);
            else In_DrawGradientRect(BlockPos.x + 55, BlockPos.y + 30 * LineRow - 7, 230, 23, { 15,15,15 }, Global_EasyGUIColor / 8, true);
            if (DrawString == "")In_DrawString(BlockPos.x + 64, BlockPos.y - 1 + 30 * LineRow, NormalText, { 50,50,50 }, Global_EasyGUIFont, Global_EasyGUIFontSize);//默认显示文字
            else {//已输入的文字
                In_DrawString(BlockPos.x + 64, BlockPos.y - 1 + 30 * LineRow, DrawString, { 0,0,0 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
                In_DrawString(BlockPos.x + 63, BlockPos.y - 2 + 30 * LineRow, DrawString, { 200,200,200 }, Global_EasyGUIFont, Global_EasyGUIFontSize);
            }
            return m_String;
        }
        //---------------------------------------------------------------------------------------------------------------------------------------------------------
    };
}