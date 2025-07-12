#include "PlayerAttribute.h"
#include "..\ModeName.h"
class PlayerStatusClothingUICheat
{
public:
	struct EffectCheat
	{
		bool 启动 = false;
		bool 一次 = false;
		int WaitTime = false;
	};
	bool 替换服装启动 = false;
	bool 只修改融合状态不修改服装 = false;
	bool 修改融合状态也修改服装 = false;
	EffectCheat 使用迅驰装备 = { false,false,0 };
	EffectCheat 进入融合姿态 = { false,false,0 };
	const char* ClothModeName = "";
public:
	void DrawPlayerStatusClothingCheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
	void PlayerStatusClothingUICheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
};
inline PlayerStatusClothingUICheat  PlayerStatusClothingUI;

inline void PlayerStatusClothingUICheat::DrawPlayerStatusClothingCheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerAttributeUI.DrawPlayerAttributeUICheatUI( SBCheatManager, lib);
	ImGui::Checkbox((const char*)u8"使用迅驰装备（不是战术模式哦，如果关闭后人物模型卡没，就开启融合姿态再关闭即可）", &使用迅驰装备.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"我要换装备了，为什么没有装备的效果？？？");
	ImGui::Checkbox((const char*)u8"进入融合姿态（不管你是否已经解锁都会解锁对应的技能）", &进入融合姿态.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"原神启动！！！！！");
	if (进入融合姿态.启动)
	{
		ImGui::Checkbox((const char*)u8"只修改融合状态不修改服装", &只修改融合状态不修改服装);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"为什么要换衣服，自己的不好看吗");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"修改融合状态也修改服装", &修改融合状态也修改服装);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"铠甲合体，变身美少女战士！！！");
	}
	ImGui::Checkbox((const char*)u8"替换服装启动", &替换服装启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"这是换装小游戏吗？");
	if (替换服装启动)
	{
		static int selected_item = -1;  // 默认没有选中任何项
		if (ImGui::ListBox((const char*)u8"替换服装为姿态服装", &selected_item, AllPlayerClothModeNameShow, IM_ARRAYSIZE(AllPlayerClothModeNameShow), IM_ARRAYSIZE(AllPlayerClothModeNameShow)))
		{
			ClothModeName = AllPlayerClothModeName[selected_item];
		}
		if (ImGui::Button((const char*)u8"替换服装", ImVec2(ImGui::GetContentRegionAvail().x - 3, 40)) && GetCharacter() && GetPawn() && GetGameStateBase()->HasBegunPlay())
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar(ClothModeName)));
			SBCheatManager->SBApplyEffectMe(Name);
		}
		if (ImGui::Button((const char*)u8"还原全部服装", ImVec2(ImGui::GetContentRegionAvail().x - 3, 40)) && GetCharacter() && GetPawn() && GetGameStateBase()->HasBegunPlay())
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyMode")));
			FName Name1 = lib->Conv_StringToName(FString(charToWchar("P_Eve_Fusion2_Stance_Dispel")));
			SBCheatManager->SBApplyEffectMe(Name);
			SBCheatManager->SBApplyEffectMe(Name1);
		}
	}
}

inline void PlayerStatusClothingUICheat::PlayerStatusClothingUICheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerAttributeUI.PlayerAttributeUICheatStar(SBCheatManager,lib);

		#pragma region 使用迅驰装备
			if (使用迅驰装备.启动 && !使用迅驰装备.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyModeWeapon")));
				FName Name1 = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyModeWing")));
				FName Name2 = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyModeNanoSuit")));
				SBCheatManager->SBApplyEffectMe(Name);
				SBCheatManager->SBApplyEffectMe(Name1);
				SBCheatManager->SBApplyEffectMe(Name2);
				使用迅驰装备.一次 = true;
			}
			if (!使用迅驰装备.启动 && 使用迅驰装备.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyMode")));
				SBCheatManager->SBApplyEffectMe(Name);
				使用迅驰装备.一次 = false;
			}
		#pragma endregion
		
		
		#pragma region 进入融合姿态
			if (进入融合姿态.启动 && !进入融合姿态.一次)
			{
				if (修改融合状态也修改服装)
				{
					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Fusion2_Stance")));
					SBCheatManager->SBApplyEffectMe(Name);
					进入融合姿态.一次 = true;
				}
				if (只修改融合状态不修改服装)
				{
					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Fusion2Mode")));
					SBCheatManager->SBApplyEffectMe(Name);
					进入融合姿态.一次 = true;
				}
			}
			if (!进入融合姿态.启动 && 进入融合姿态.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Fusion2_Stance_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				进入融合姿态.一次 = false;
			}
		#pragma endregion
}
