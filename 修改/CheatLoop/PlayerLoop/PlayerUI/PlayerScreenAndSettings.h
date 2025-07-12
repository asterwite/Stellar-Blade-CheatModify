#include "PlayerStatusClothing.h"
class PlayerScreenAndSettingsUICheat
{
public:
	struct EffectCheat
	{
		bool 启动 = false;
		bool 一次 = false;
		int WaitTime = false;
	};
	EffectCheat 强制进入射击状态 = { false,false,0 };
	EffectCheat 解锁射击模式 = { false,false,0 };
	EffectCheat 濒死屏幕特效 = { false,false,0 };
public:
	void DrawPlayerScreenAndSettingsCheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
	void PlayerScreenAndSettingsCheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
};
inline PlayerScreenAndSettingsUICheat  PlayerScreenAndSettingsUI;

inline void PlayerScreenAndSettingsUICheat::DrawPlayerScreenAndSettingsCheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerStatusClothingUI.DrawPlayerStatusClothingCheatUI(SBCheatManager,lib);

	ImGui::Checkbox((const char*)u8"脱离目标状态红屏", &濒死屏幕特效.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"我哪脱离了？？");
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"触发开局脱离任务目标状态（版本1）"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_RestartRule_Beach_FrontEffectVol")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"版本1和版本2的对话不一样，看情况选择，注意无法关闭会直接重新加载，不要在没保存的情况下启动！！！");
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"触发开局脱离任务目标状态（版本2）"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_RestartRule_Beach_BackEffectVol")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"版本1和版本2的对话不一样，看情况选择，注意无法关闭会直接重新加载，不要在没保存的情况下启动！！！");
	if (ImGui::Button((const char*)u8"装死"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_N_GuideA_Dead")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"不是我装死了你为什么还要打我，注意无法还原需要自杀或者重新进存档");
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"角色粉碎死亡效果"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_Dead_Grinder_Show")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"关闭角色粉碎死亡效果"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_Dead_Grinder_Show_Dispel")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"斩杀金刚动画"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("M_Gorilla_FinishStart")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"不是哥们你给我干哪来了");

	if (ImGui::Button((const char*)u8"强制进入未拿到核心动画"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("M_Gorgon_FinishReady")));
		FName Name1 = lib->Conv_StringToName(FString(charToWchar("M_Gorgon_Finish")));
		SBCheatManager->SBApplyEffectMe(Name);
		SBCheatManager->SBApplyEffectMe(Name1);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"（直接看剧情但是不会让你的剧情跳转到该地方）场景为当前你所处地图的场景，不同的场景同一个动画，唉，不错");


	ImGui::Checkbox((const char*)u8"强制进入射击状态（不管你是否已经解锁了射击模式，缺陷就是无法移动）", &强制进入射击状态.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"大人时代变了！！！");
	ImGui::Checkbox((const char*)u8"解锁射击模式（直接解锁按Ctrl键瞄准）", &解锁射击模式.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"谁说我没枪的？？");

	if (ImGui::Button((const char*)u8"玩家自杀", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)) && GetCharacter() && GetPawn() && GetGameStateBase()->HasBegunPlay())
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("ImmediateDeath")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"你等着，我重开");
}

inline void PlayerScreenAndSettingsUICheat::PlayerScreenAndSettingsCheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerStatusClothingUI.PlayerStatusClothingUICheatStar(SBCheatManager,lib);

	#pragma region 射击状态
		if (强制进入射击状态.启动 && !强制进入射击状态.一次)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Stance_GunTutorial")));
			SBCheatManager->SBApplyEffectMe(Name);
			强制进入射击状态.一次 = true;
		}
		if (!强制进入射击状态.启动 && 强制进入射击状态.一次)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Stance_GunTutorial_End")));
			SBCheatManager->SBApplyEffectMe(Name);
			强制进入射击状态.一次 = false;
		}
	#pragma endregion
	
	
	#pragma region 解锁射击模式
		if (解锁射击模式.启动 && !解锁射击模式.一次)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("Eve_ModeOpen_TPS_Eff")));
			SBCheatManager->SBApplyEffectMe(Name);
			解锁射击模式.一次 = true;
		}
		if (!强制进入射击状态.启动 && 强制进入射击状态.一次)
		{
			强制进入射击状态.一次 = false;
		}
	#pragma endregion
	

	#pragma region 濒死屏幕特效
		if (濒死屏幕特效.启动)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("ScreenEffect_RestartRule_Beach")));
			SBCheatManager->SBApplyEffectMe(Name);
			濒死屏幕特效.一次 = true;
		}
		if (!濒死屏幕特效.启动 && 濒死屏幕特效.一次)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("ScreenEffect_RestartRule_Beach_Dispel")));
			SBCheatManager->SBApplyEffectMe(Name);
			濒死屏幕特效.一次 = false;
		}
	
	#pragma endregion
}
