#pragma once
#include "CheatLoop/Cheat/MyCheat.h"
#include "CheatLoop/Config/Config.h"
#include "main.h"
LPCSTR static lpWindowName = (const char*)u8"�����޸�\nby:�������� V1.3";
ImVec2 static vWindowSize = { 1000, 750 };
ImGuiWindowFlags static WindowFlags = ImGuiWindowFlags_NoTitleBar;
bool static greetings = true;
bool static ���ز˵�����һ������ = true;
inline bool ShowMenu = true;
enum Headers {
	���,
	��������,
	����,
	��Ʒ,
	����,
	͸��,
	����,
	ҳ��λ��
};

inline ImFont* font_regular;
inline ImFont* font_medium;
inline ImFont* font_bold;
inline ImFont* font_title;
inline ImFont* font_icons;


#pragma region UI����


void static DrawImGui()
{
	if (AllocConsole())
	{
		SetConsoleTitleA("�����޸ģ����԰汾");

		freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);

		printf("����ing������Bug��\n");
	}

	if (���ز˵�����һ������)
	{
		MessageBoxA(NULL, "�޸ļ������ף����Ϸ��죬�ʵ��޸����ܽ�����Ϸÿһ��", "�����޸�", MB_OK);
		LoadConfig((const char*)u8"�����޸��޸�����.SAVE");
		���ز˵�����һ������ = false;
	}			

	ImVec2 wndSize = ImGui::GetWindowSize();
	float minWidth = 120;

	ImGui::SetNextWindowSize(vWindowSize, ImGuiCond_Once);
	ImGui::SetNextWindowBgAlpha(1.0f);
	if (ImGui::Begin(lpWindowName, &ShowMenu, ImGuiWindowFlags_NoTitleBar))
	{
		static Headers tab = ���;
		const char* tab_names[] = { (const char*)u8"���",(const char*)u8"��������",(const char*)u8"����",(const char*)u8"��Ʒ",(const char*)u8"����",(const char*)u8"͸��", (const char*)u8"����", /*"DEBUG"*/};
		ImVec2 wndSize = ImGui::GetWindowSize();
		float minWidth = 120;
		ImVec2 mainLeftSize = ImVec2(ImGui::GetContentRegionAvail().x * 0.16f, ImGui::GetContentRegionAvail().y);
		mainLeftSize.x = ImClamp(mainLeftSize.x, minWidth, wndSize.x);
		ImGui::BeginChild((const char*)"ҳ��", mainLeftSize, 0);
		{
			ImVec2 leftTopChildSize = ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y * 0.16f);
			ImGui::BeginChild((const char*)u8"ҳ�����", leftTopChildSize, false);
			ImGui::PushFont(font_title);

			ImVec2 textSize = ImGui::CalcTextSize((const char*)u8"�����޸�V1.3\nby:��������");

			float posX = (leftTopChildSize.x - textSize.x) * 0.5f;
			float posY = (leftTopChildSize.y - textSize.y) * 0.5f;

			ImGui::SetCursorPos(ImVec2(posX, posY));

			ImGui::TextColored(ImColor(84, 160, 227), (const char*)u8"�����޸�V1.3\nby:��������");

			ImGui::PopFont();
			ImGui::EndChild();


			if (ImGui::BeginChild((const char*)"ҳ�����2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), 0))
			{
				for (unsigned int i = 0; i < ҳ��λ��; ++i)
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

		ImGui::BeginChild((const char*)u8"ҳ���ұ�", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), 0);

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Indent(10.0f);
		switch (tab)
		{
		case ���:
			Player.DrawPlayerUI();
			break;
		case ��������:
			AnotherWindowLoop.DrawAnotherWindowCheatUI();
			break;
		case ����:
			WorldLoop.DrawWorldUI();
			break;
		case ��Ʒ:
			ItemLoop.DrawItemUI();
			break;
		case ����:
			PeopleLoop.DrawPeopleUI();
			break;
		case ͸��:
			//ESPDEBUG.DrawESP_DebugUI();
			GameLoop.DrawESPUI();
			break;
		case ����:
			if (ImGui::Button((const char*)u8"���ñ���"))
				SaveConfig("�����޸��޸�����.SAVE");
			ImGui::SameLine();
			if (ImGui::Button((const char*)u8"��������"))
				LoadConfig("�����޸��޸�����.SAVE");

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



