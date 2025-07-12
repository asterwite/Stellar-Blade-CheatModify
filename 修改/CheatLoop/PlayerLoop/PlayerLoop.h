#pragma once
#include "PlayerUI/PlayerScreenAndSettings.h"
#define IsKeyHeld(key) (GetAsyncKeyState(key) & 0x8000)
class PlayerCheat
{
public:
	struct EffectCheat
	{
		bool 启动 = false;
		bool 一次 = false;
		int WaitTime = false;
	};

	EffectCheat 无人机扫描无延迟 = { false,false,0 }; 

private:
	char  名称[255];


public:
	void DrawPlayerUI();
	void PlayerCheatStar();
};
inline PlayerCheat Player;

inline void DrawBoneName()
{
	for (int i = 0;i < 999;i++)
	{
		printf("对象名称: [%s]\t%d\n", GetCharacter()->Mesh->GetBoneName(i).ToString().c_str(),i);
	}
}

inline void PlayerCheat::DrawPlayerUI()
{
	USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
	UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
	if (ImGui::CollapsingHeader((const char*)u8"人物设置（如果开启了融合模式和使用迅驰装备就不要再修改服装了会导致模型卡没，需要重新进存档才能还原）"))
	{
		PlayerScreenAndSettingsUI.DrawPlayerScreenAndSettingsCheatUI(SBCheatManager, lib);
	}
	ImGui::Checkbox((const char*)u8"无人机扫描无延迟", &无人机扫描无延迟.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"谁说无人机扫描有等待的？注意：我把按键写死了，Tab键才会扫描");
	if (ImGui::Button((const char*)u8"移除无人机"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_SummonDrone_Dispel")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"我无人机呢，你告诉我我无人机呢？？？需要自杀或重新进存档还原，记得先保存");

	if (ImGui::CollapsingHeader((const char*)u8"设置"))
	{
		ImGui::InputText((const char*)u8"名称", 名称, sizeof(名称));
		if (ImGui::Button((const char*)u8"设置Effect", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
		{
			if (!SBCheatManager)
				printf("没有找到SBCheatManager");
			if (SBCheatManager && 名称[0] != '\0')
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar(名称)));
				SBCheatManager->SBApplyEffectMe(Name);
				printf("执行成功");
			}
		}
	}
}


inline void PlayerCheat::PlayerCheatStar()
{
		UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
		USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();


		PlayerScreenAndSettingsUI.PlayerScreenAndSettingsCheatStar(SBCheatManager, lib);

		#pragma region 无人机扫描无延迟
			if (无人机扫描无延迟.启动&& GetAsyncKeyState(VK_TAB)&&1)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("N_Drone_Scan")));
				SBCheatManager->SBApplyEffectMe(Name);
				无人机扫描无延迟.一次 = true;
			}
			if (!无人机扫描无延迟.启动 && 无人机扫描无延迟.一次)
				无人机扫描无延迟.一次 = false;
		#pragma endregion

}

#pragma region MyRegion

#pragma endregion
