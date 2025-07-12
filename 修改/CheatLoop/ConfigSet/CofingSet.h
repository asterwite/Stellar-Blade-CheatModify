#pragma once
#include "FPSUnlock.h"
#include "KeySet.h"
class ConfigSet
{
public:
	int 主题颜色 = 0;
    bool ImGuiinit = false;
public:
	void ConfigUI();
	void ConfigUIColorBule(ImGuiStyle& style, ImVec4* colors);

};
inline ConfigSet Config;



inline void ConfigSet::ConfigUI()
{
	FPSUnlock.DrawFPSUlockUI();
    if(ImGui::Button((const char*)u8"清理控制台"))
        system("cls");
	ImGui::PushStyleVar(ImGuiStyleVar_ChildBorderSize, 0.0f);
	ImGui::SetCursorPosY(ImGui::GetWindowHeight() - ImGui::GetFrameHeight() - 20);
	ImGui::PopStyleVar();
}

inline void ConfigSet::ConfigUIColorBule(ImGuiStyle& style, ImVec4* colors)
{
    ImColor hovered = { 31, 110, 171 };
    ImColor Transparented = { 0, 0, 0, 255 };
    colors[ImGuiCol_WindowBg] = ImColor(20, 23, 25);
    colors[ImGuiCol_ChildBg] = ImColor(24, 28, 30);
    colors[ImGuiCol_Text] = ImColor(255, 255, 255);

    //头部
    colors[ImGuiCol_Header] = ImColor(30, 138, 200);
    colors[ImGuiCol_HeaderHovered] = hovered;
    colors[ImGuiCol_HeaderActive] = ImColor(30, 116, 215);

    //按钮
    colors[ImGuiCol_Button] = ImColor(25, 145, 215);
    colors[ImGuiCol_ButtonHovered] = hovered;
    colors[ImGuiCol_ButtonActive] = ImColor(100, 161, 222);

    //选项
    colors[ImGuiCol_CheckMark] = ImColor(0, 0, 0);
    colors[ImGuiCol_FrameBg] = ImColor(25, 158, 215, 200);
    colors[ImGuiCol_FrameBgActive] = ImColor(25, 164, 215);
    colors[ImGuiCol_FrameBgHovered] = ImColor(20, 212, 250);

    colors[ImGuiCol_Border] = Transparented;
    //选项卡
    colors[ImGuiCol_Tab]  = ImColor(25, 145, 215);
    colors[ImGuiCol_TabHovered] = hovered; 
    colors[ImGuiCol_TabActive]  = ImColor(20, 212, 250);
    //下拉栏
    colors[ImGuiCol_PopupBg] = ImColor(25, 145, 215);

    style.WindowRounding = 10.0f;
    style.FrameRounding = 5.0f;
    style.ScrollbarRounding = 5.0f;
    style.GrabRounding = 2.3f;
    style.TabRounding = 2.3f;

    //style.WindowMinSize = { 600,300 };
    style.ChildRounding = 5.0f;
}




