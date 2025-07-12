#include "QuickItemUse.h"
class WeaponLoopCheat
{
public:
	struct EffectCheat
	{
		bool 启动 = false;
		bool 一次 = false;
		bool 快速 = false;
		int WaitTime = false;
	};
	bool 打开玩家武器窗口 = false;
	EffectCheat 无限子弹 = { false,false,false,0 };
	EffectCheat 近战武器伤害附魔 = { false,false,false,0 };
	EffectCheat 近战攻击速度附魔 = { false,false,false,0 };
	EffectCheat 远程武器伤害附魔 = { false,false,false,0 };

	int 当前选中 = -1;
	void DrawWeaponLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
	void DrawNewWeaponLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
	void DrawWeaponLoopCheat(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
};
inline WeaponLoopCheat WeaponLoop;

inline void WeaponLoopCheat::DrawWeaponLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
	QuickItemUse.DrawQuickItemUseLoopUI(CheatManager, lib);
	ImGui::Checkbox((const char*)u8"打开玩家武器窗口", &打开玩家武器窗口);
	if (打开玩家武器窗口)
	DrawNewWeaponLoopUI(CheatManager, lib);

}

inline void WeaponLoopCheat::DrawNewWeaponLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
	ImVec2 minSize(300, 200);
	ImVec2 maxSize(1920, 1080);
	ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
	ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

	if (ImGui::Begin((const char*)u8"武器管理器", &打开玩家武器窗口, 0))
	{
		ImGui::Checkbox((const char*)u8"无限子弹", &无限子弹.启动);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"妈妈再也不用担心我的子弹不够用了");
		ImGui::Checkbox((const char*)u8"近战武器伤害附魔", &近战武器伤害附魔.启动);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"循环附魔，会产生特效，有点小帅");
		if (近战武器伤害附魔.启动)
		{
			ImGui::Checkbox((const char*)u8"快速近战伤害附魔（加速附魔会导致掉帧，循环刷特效，会掉十多帧）", &近战武器伤害附魔.快速);
			ImGui::SameLine();
			ImGuiHelpMarker((const char*)u8"奶奶地，为什么掉帧");
		}
		ImGui::Checkbox((const char*)u8"近战攻击速度微加速", &近战攻击速度附魔.启动);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"加速加速");
		ImGui::Checkbox((const char*)u8"远程武器伤害附魔", &远程武器伤害附魔.启动);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"谁说枪伤害不高的？");
		if (远程武器伤害附魔.启动)
		{
			ImGui::Checkbox((const char*)u8"快速远程武器伤害附魔", &远程武器伤害附魔.快速);
			ImGui::SameLine();
			ImGuiHelpMarker((const char*)u8"这一枪，开了的伤害，你挡的住吗");
		}
	}
	ImGui::End();
}

inline void WeaponLoopCheat::DrawWeaponLoopCheat(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerAction.WaitTime++;
	if (PlayerAction.循环执行 && PlayerAction.WaitTime > PlayerAction.几帧执行一次)
	{

		FName Name = lib->Conv_StringToName(FString(charToWchar(PlayerAction.NameForAction)));
		SBCheatManager->SBApplyEffectMe(Name);
		PlayerAction.WaitTime = 0;
	}
	if(!PlayerAction.循环执行)
		PlayerAction.NameForAction = "";


	PlayerSpecialEffectsShow.WaitTime++;
	if (PlayerSpecialEffectsShow.循环执行 && PlayerSpecialEffectsShow.WaitTime > PlayerSpecialEffectsShow.几帧执行一次)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar(PlayerSpecialEffectsShow.NameForAction)));
		SBCheatManager->SBApplyEffectMe(Name);
		PlayerSpecialEffectsShow.WaitTime = 0;
	}
	if (!PlayerSpecialEffectsShow.循环执行)
		PlayerSpecialEffectsShow.NameForAction = "";

	if (GetAsyncKeyState(QuickItemUse.UseKey) & 1)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar(QuickItemUse.NameForAction)));
		SBCheatManager->SBApplyEffectMe(Name);
	}



		#pragma region 无限子弹
			if (无限子弹.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Bullet1_Refill")));
				SBCheatManager->SBApplyEffectMe(Name);
				无限子弹.一次 = true;
		
			}
			if (!无限子弹.启动 && 无限子弹.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Bullet1_Refill")));
				SBCheatManager->SBApplyEffectMe(Name);
				无限子弹.一次 = false;
		
			}
		#pragma endregion


		#pragma region 近战武器伤害附魔
			if (近战武器伤害附魔.启动)
			{
				近战武器伤害附魔.WaitTime++;
				if (近战武器伤害附魔.WaitTime > 20 || 近战武器伤害附魔.快速)
				{

					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_PhysicAttackPower")));
					SBCheatManager->SBApplyEffectMe(Name);
					近战武器伤害附魔.一次 = true;
					近战武器伤害附魔.WaitTime = 0;
				}
			}	
			if (!近战武器伤害附魔.启动 && 近战武器伤害附魔.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_PhysicAttackPower")));
				SBCheatManager->SBApplyEffectMe(Name);
				近战武器伤害附魔.一次 = false;	
			}
		#pragma endregion


		#pragma region 近战攻击速度附魔

			if (近战攻击速度附魔.启动)
			{
					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_AttackSpeed")));
					SBCheatManager->SBApplyEffectMe(Name);
					近战攻击速度附魔.一次 = true;
					近战攻击速度附魔.WaitTime = 0;
			}
		#pragma endregion


		#pragma region 远程武器伤害附魔				
			if (远程武器伤害附魔.启动)
			{
				远程武器伤害附魔.WaitTime++;
				if (远程武器伤害附魔.WaitTime > 20 || 远程武器伤害附魔.快速)
				{

					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_RangeAttackPower")));
					SBCheatManager->SBApplyEffectMe(Name);
					远程武器伤害附魔.一次 = true;
					远程武器伤害附魔.WaitTime = 0;
				}
			}
			if (!远程武器伤害附魔.启动 && 远程武器伤害附魔.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_RangeAttackPower")));
				SBCheatManager->SBApplyEffectMe(Name);
				远程武器伤害附魔.一次 = false;
			}
		#pragma endregion


}