#pragma once
#include "CheatLoop/Cheat/MyCheat.h"
#include "CheatLoop/Config/Config.h"
#include "main.h"
LPCSTR static lpWindowName = (const char*)u8"剑星修改\nby:无云五蕴 V1.3";
ImVec2 static vWindowSize = { 1000, 750 };
ImGuiWindowFlags static WindowFlags = ImGuiWindowFlags_NoTitleBar;
bool static greetings = true;
bool static 加载菜单加载一次配置 = true;
inline bool ShowMenu = true;
enum Headers {
	玩家,
	其他窗口,
	世界,
	物品,
	敌人,
	透视,
	设置,
	页面位置
};

inline ImFont* font_regular;
inline ImFont* font_medium;
inline ImFont* font_bold;
inline ImFont* font_title;
inline ImFont* font_icons;


#pragma region UI设置


void static DrawImGui()
{
	if (AllocConsole())
	{
		SetConsoleTitleA("剑星修改，测试版本");

		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

		printf("测试ing，会有Bug呢\n");
	}

	if (加载菜单加载一次配置)
	{
		MessageBoxA(NULL, "修改加载完成祝你游戏愉快，适当修改享受健康游戏每一天", "剑星修改", MB_OK);
		LoadConfig((const char*)u8"剑星修改修改配置.SAVE");
		加载菜单加载一次配置 = false;
	}			

	ImVec2 wndSize = ImGui::GetWindowSize();
	float minWidth = 120;

	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	if (ImGui::Begin(lpWindowName, &ShowMenu, ImGuiWindowFlags_NoTitleBar))
	{
		static Headers tab = 玩家;
		const char* tab_names[] = { (const char*)u8"玩家",(const char*)u8"其他窗口",(const char*)u8"世界",(const char*)u8"物品",(const char*)u8"敌人",(const char*)u8"透视", (const char*)u8"设置", /*"DEBUG"*/};
		ImVec2 wndSize = ImGui::GetWindowSize();
		float minWidth = 120;
		ImVec2 mainLeftSize = ImVec2(ImGui::GetContentRegionAvail().x * 0.16f, ImGui::GetContentRegionAvail().y);
		mainLeftSize.x = ImClamp(mainLeftSize.x, minWidth, wndSize.x);
		ImGui::BeginChild((const char*)"页面", mainLeftSize, 0);
		{
			ImVec2 leftTopChildSize = ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y * 0.16f);
			ImGui::BeginChild((const char*)u8"页面左侧", leftTopChildSize, false);
			ImGui::PushFont(font_title);

			ImVec2 textSize = ImGui::CalcTextSize((const char*)u8"剑星修改V1.3\nby:无云五蕴");

			float posX = (leftTopChildSize.x - textSize.x) * 0.5f;
			float posY = (leftTopChildSize.y - textSize.y) * 0.5f;

			ImGui::SetCursorPos(ImVec2(posX, posY));

			ImGui::TextColored(ImColor(84, 160, 227), (const char*)u8"剑星修改V1.3\nby:无云五蕴");

			ImGui::PopFont();
			ImGui::EndChild();


			if (ImGui::BeginChild((const char*)"页面左边2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), 0))
			{
				for (unsigned int i = 0; i < 页面位置; ++i)
				{
					bool selected = (tab == static_cast<Headers>(i));
					auto windowvars = ImGuiStyleVar_SelectableTextAlign;

					ImGui::PushStyleVar(windowvars, ImVec2(0.5f, 0.5f));

					if (ImGui::Selectable(tab_names[i], &selected, 0, ImVec2(ImGui::GetContentRegionAvail().x, 24)))
						tab = static_cast<Headers>(i);

					ImGui::PopStyleVar();

					if (selected)
						ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndChild();
		}
		ImGui::EndChild();
		ImGui::SameLine(0);

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(20, 20));

		ImGui::BeginChild((const char*)u8"页面右边", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), 0);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Indent(10.0f);
		switch (tab)
		{
		case 玩家:
			Player.DrawPlayerUI();
			break;
		case 其他窗口:
			AnotherWindowLoop.DrawAnotherWindowCheatUI();
			break;
		case 世界:
			WorldLoop.DrawWorldUI();
			break;
		case 物品:
			ItemLoop.DrawItemUI();
			break;
		case 敌人:
			PeopleLoop.DrawPeopleUI();
			break;
		case 透视:
			//ESPDEBUG.DrawESP_DebugUI();
			GameLoop.DrawESPUI();
			break;
		case 设置:
			if (ImGui::Button((const char*)u8"配置保存"))
				SaveConfig("剑星修改修改配置.SAVE");
			ImGui::SameLine();
			if (ImGui::Button((const char*)u8"加载配置"))
				LoadConfig("剑星修改修改配置.SAVE");

			Config.ConfigUI();

			break;
		}
		ImGui::Unindent();
		ImGui::Spacing();
		ImGui::Spacing();

		ImGui::EndChild();
		ImGui::PopStyleVar();
		ImGui::End();
	}
}


#pragma endregion



