#include "..\PlayerFly.h"
class PlayerAttributeUICheat
{
public:
	struct EffectCheat
	{
		bool 启动 = false;
		bool 一次 = false;
		int WaitTime = false;
	};
	float 人物速度 = 1.f;
	EffectCheat 神模式 = { false,false,0 };
	EffectCheat 体冒绿光 = { false,false,0 };
	EffectCheat 黄色水体行走 = { false,false,0 };
	EffectCheat 燃气附着 = { false,false,0 };
	EffectCheat 激光剑 = { false,false,0 };
	EffectCheat 无敌 = { false,false,0 };
	EffectCheat 不朽模式 = { false,false,0 };
	EffectCheat 无限贝塔能量 = { false,false,0 };
	EffectCheat 无限迅驰 = { false,false,0 };
	EffectCheat 无限BU = { false,false,0 };
	EffectCheat 隐身模式 = { false,false,0 };
	EffectCheat 隐身效果 = { false,false,0 };
	EffectCheat 关闭锁定敌人 = { false,false,0 };
	EffectCheat 快速起身 = { false,false,0 };
	bool 无限生命 = false;
	bool 无限护盾 = false;
	char  名称[255];
public:
	void DrawPlayerAttributeUICheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
	void PlayerAttributeUICheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
};
inline PlayerAttributeUICheat  PlayerAttributeUI;

inline void PlayerAttributeUICheat::DrawPlayerAttributeUICheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	ImGui::SliderFloat((const char*)u8"人物速度", &人物速度, 1.f, 20.f);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"调节移动的动作速度，跑起来飞快哦");
	PlayerFly.PlayerFlyUI();
	
	ImGui::Checkbox((const char*)u8"神模式", &神模式.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"无视任何物理伤害，异常伤害包括部分机制杀，无法关闭，需要重进存档");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"体冒绿光", &体冒绿光.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"这不是绿帽子！！！");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"黄色水体行走", &黄色水体行走.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"你TM踩史了？？？？");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"燃气附着", &燃气附着.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"来吧我是带特效的！！！");

	ImGui::Checkbox((const char*)u8"激光剑", &激光剑.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"星球大战！");

	ImGui::Checkbox((const char*)u8"无敌", &无敌.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"顾名思义，打不到我，啊不对是打不动我，人物死亡后需要重新开启");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"无限生命", &无限生命);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"血不够用了？血包也没了？");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"不朽模式", &不朽模式.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"顾名思义，不会死亡");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"无限护盾", &无限护盾);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"补充护甲");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"无限贝塔能量", &无限贝塔能量.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"你奶奶地，开");

	ImGui::Checkbox((const char*)u8"隐身模式", &隐身模式.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"你看不到我你看不到我，我是你的好朋友");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"隐身效果", &隐身效果.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"两个版本不一样，注意死亡后需要重新开启");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"无限BU", &无限BU.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"顾名思义，无限BU");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"无限迅驰", &无限迅驰.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"变身迅驰无限时间");
	ImGui::SameLine();

	ImGui::Checkbox((const char*)u8"关闭锁定敌人", &关闭锁定敌人.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"你老动我摄像机干什么");

	ImGui::Checkbox((const char*)u8"快速起身", &快速起身.启动);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"你想打倒我？妾身不同意！！");


}

inline void PlayerAttributeUICheat::PlayerAttributeUICheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
		if (无限生命)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("T_SetEveStat_HPRecover")));
			SBCheatManager->SBApplyEffectMe(Name);
		}
		GetPawn()->CustomTimeDilation = 人物速度;
		PlayerFly.PlayerFly();
		#pragma region 神模式
			if (神模式.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Test_ImmunePhysicDamageMe")));
				FName Name1 = lib->Conv_StringToName(FString(charToWchar("Test_ImmuneAbnormal")));
				SBCheatManager->SBApplyEffectMe(Name);
				SBCheatManager->SBApplyEffectMe(Name1);
			}
		#pragma endregion


		#pragma region 体冒绿光
			if (体冒绿光.启动)
			{			
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_DataDrone_Nikke_FXShow")));
				SBCheatManager->SBApplyEffectMe(Name);
			}
		#pragma endregion


		#pragma region 黄色水体行走
			if (黄色水体行走.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_GorillaB_S24_PowerUpBuff")));
				SBCheatManager->SBApplyEffectMe(Name);
		
				黄色水体行走.一次 = true;
			}
			if (!黄色水体行走.启动 && 黄色水体行走.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_GorillaB_S24_PowerUpBuff_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				黄色水体行走.一次 = false;
			}
		#pragma endregion


		#pragma region 燃气附着
			if (燃气附着.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_Behemoth_BuffFX2")));
				SBCheatManager->SBApplyEffectMe(Name);
		
				燃气附着.一次 = true;
			}
			if (!燃气附着.启动 && 燃气附着.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_Behemoth_BuffFX2_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				燃气附着.一次 = false;
			}
		#pragma endregion


		#pragma region 激光剑
			激光剑.WaitTime++;
					if (激光剑.启动&& 激光剑.WaitTime>100)
					{
						FName Name = lib->Conv_StringToName(FString(charToWchar("M_Raven_BuffFX_OFF")));
						SBCheatManager->SBApplyEffectMe(Name);
						激光剑.WaitTime = 0;
						激光剑.一次 = true;
					}
					if (!激光剑.启动 && 激光剑.一次)
					{
						FName Name = lib->Conv_StringToName(FString(charToWchar("M_Raven_BuffFX_Dispel")));
						SBCheatManager->SBApplyEffectMe(Name);
						激光剑.一次 = false;
					}
		#pragma endregion

			
		#pragma region 无敌
			if (无敌.启动 && !无敌.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("NoDamageNoHitImmuneAbnormal_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
				无敌.一次 = true;
			}
			if (!无敌.启动 && 无敌.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("NoDamageNoHitImmuneAbnormal_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				无敌.一次 = false;
			}
		#pragma endregion
		
		
		#pragma region 不朽模式
			if (不朽模式.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Passive_Immortal")));
				SBCheatManager->SBApplyEffectMe(Name);
		
				不朽模式.一次 = true;
			}
			if (!不朽模式.启动 && 不朽模式.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Passive_Immortal_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				不朽模式.一次 = false;
			}
		#pragma endregion
		
		
		#pragma region 无限护盾
			if (无限护盾)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("RecoverShield_100p")));
				SBCheatManager->SBApplyEffectMe(Name);
			}
		#pragma endregion
		
		
		#pragma region 无限贝塔能量
			if (无限贝塔能量.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Item_Buff_HP2MP_GainMP")));
				SBCheatManager->SBApplyEffectMe(Name);
			}
		#pragma endregion


		#pragma region 隐身模式
			if (隐身模式.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("NotTargeted_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
				隐身模式.一次 = true;
			}
			if (!隐身模式.启动 && 隐身模式.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("NotTargeted_Step")));
				SBCheatManager->SBApplyEffectMe(Name);
				隐身模式.一次 = false;
			}
		#pragma endregion
		
		
		#pragma region 隐身效果
			if (隐身效果.启动&&!隐身效果.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Test_Stealth")));
				SBCheatManager->SBApplyEffectMe(Name);
				隐身效果.一次 = true;
			}
			if (!隐身效果.启动 && 隐身效果.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Test_Stealth")));
				SBCheatManager->SBApplyEffectMe(Name);
				隐身效果.一次 = false;
			}

		#pragma endregion
		
		
		#pragma region 无限BU
			if (无限BU.启动 && !无限BU.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("T_Eve_Burst_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
		
				无限BU.一次 = true;
			}
			if (!无限BU.启动 && 无限BU.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("T_Eve_Burst_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
				无限BU.一次 = false;
			}
		#pragma endregion
		
		
		#pragma region 无限迅驰
			if (无限迅驰.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Eve_TachyGaugeRegen")));
				SBCheatManager->SBApplyEffectMe(Name);
				无限迅驰.一次 = true;
			}
			if (!无限迅驰.启动 && 无限迅驰.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Eve_TachyGaugeRegen")));
				SBCheatManager->SBApplyEffectMe(Name);
				无限迅驰.一次 = false;
			}
		#pragma endregion
		
		
		#pragma region 关闭锁定敌人
			if (关闭锁定敌人.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("DisableLockOnControl_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
				关闭锁定敌人.一次 = true;
			}
			if (!关闭锁定敌人.启动 && 关闭锁定敌人.一次)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("DisableLockOnControl_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				关闭锁定敌人.一次 = false;
			}
		#pragma endregion


		#pragma region 快速起身
			if (快速起身.启动)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("FastGetup")));
				SBCheatManager->SBApplyEffectMe(Name);
				关闭锁定敌人.一次 = true;
			}
			if (!快速起身.启动 && 快速起身.一次)
				快速起身.一次 = false;
		#pragma endregion
}