#include "QuickItemUse.h"
class WeaponLoopCheat
{
public:
	struct EffectCheat
	{
		bool ���� = false;
		bool һ�� = false;
		bool ���� = false;
		int WaitTime = false;
	};
	bool ������������� = false;
	EffectCheat �����ӵ� = { false,false,false,0 };
	EffectCheat ��ս�����˺���ħ = { false,false,false,0 };
	EffectCheat ��ս�����ٶȸ�ħ = { false,false,false,0 };
	EffectCheat Զ�������˺���ħ = { false,false,false,0 };

	int ��ǰѡ�� = -1;
	void DrawWeaponLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
	void DrawNewWeaponLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
	void DrawWeaponLoopCheat(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
};
inline WeaponLoopCheat WeaponLoop;

inline void WeaponLoopCheat::DrawWeaponLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
	QuickItemUse.DrawQuickItemUseLoopUI(CheatManager, lib);
	ImGui::Checkbox((const char*)u8"�������������", &�������������);
	if (�������������)
	DrawNewWeaponLoopUI(CheatManager, lib);

}

inline void WeaponLoopCheat::DrawNewWeaponLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
	ImVec2 minSize(300, 200);
	ImVec2 maxSize(1920, 1080);
	ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
	ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

	if (ImGui::Begin((const char*)u8"����������", &�������������, 0))
	{
		ImGui::Checkbox((const char*)u8"�����ӵ�", &�����ӵ�.����);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"������Ҳ���õ����ҵ��ӵ���������");
		ImGui::Checkbox((const char*)u8"��ս�����˺���ħ", &��ս�����˺���ħ.����);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"ѭ����ħ���������Ч���е�С˧");
		if (��ս�����˺���ħ.����)
		{
			ImGui::Checkbox((const char*)u8"���ٽ�ս�˺���ħ�����ٸ�ħ�ᵼ�µ�֡��ѭ��ˢ��Ч�����ʮ��֡��", &��ս�����˺���ħ.����);
			ImGui::SameLine();
			ImGuiHelpMarker((const char*)u8"���̵أ�Ϊʲô��֡");
		}
		ImGui::Checkbox((const char*)u8"��ս�����ٶ�΢����", &��ս�����ٶȸ�ħ.����);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"���ټ���");
		ImGui::Checkbox((const char*)u8"Զ�������˺���ħ", &Զ�������˺���ħ.����);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"˭˵ǹ�˺����ߵģ�");
		if (Զ�������˺���ħ.����)
		{
			ImGui::Checkbox((const char*)u8"����Զ�������˺���ħ", &Զ�������˺���ħ.����);
			ImGui::SameLine();
			ImGuiHelpMarker((const char*)u8"��һǹ�����˵��˺����㵲��ס��");
		}
	}
	ImGui::End();
}

inline void WeaponLoopCheat::DrawWeaponLoopCheat(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerAction.WaitTime++;
	if (PlayerAction.ѭ��ִ�� && PlayerAction.WaitTime > PlayerAction.��ִ֡��һ��)
	{

		FName Name = lib->Conv_StringToName(FString(charToWchar(PlayerAction.NameForAction)));
		SBCheatManager->SBApplyEffectMe(Name);
		PlayerAction.WaitTime = 0;
	}
	if(!PlayerAction.ѭ��ִ��)
		PlayerAction.NameForAction = "";


	PlayerSpecialEffectsShow.WaitTime++;
	if (PlayerSpecialEffectsShow.ѭ��ִ�� && PlayerSpecialEffectsShow.WaitTime > PlayerSpecialEffectsShow.��ִ֡��һ��)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar(PlayerSpecialEffectsShow.NameForAction)));
		SBCheatManager->SBApplyEffectMe(Name);
		PlayerSpecialEffectsShow.WaitTime = 0;
	}
	if (!PlayerSpecialEffectsShow.ѭ��ִ��)
		PlayerSpecialEffectsShow.NameForAction = "";

	if (GetAsyncKeyState(QuickItemUse.UseKey) & 1)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar(QuickItemUse.NameForAction)));
		SBCheatManager->SBApplyEffectMe(Name);
	}



		#pragma region �����ӵ�
			if (�����ӵ�.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Bullet1_Refill")));
				SBCheatManager->SBApplyEffectMe(Name);
				�����ӵ�.һ�� = true;
		
			}
			if (!�����ӵ�.���� && �����ӵ�.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Bullet1_Refill")));
				SBCheatManager->SBApplyEffectMe(Name);
				�����ӵ�.һ�� = false;
		
			}
		#pragma endregion


		#pragma region ��ս�����˺���ħ
			if (��ս�����˺���ħ.����)
			{
				��ս�����˺���ħ.WaitTime++;
				if (��ս�����˺���ħ.WaitTime > 20 || ��ս�����˺���ħ.����)
				{

					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_PhysicAttackPower")));
					SBCheatManager->SBApplyEffectMe(Name);
					��ս�����˺���ħ.һ�� = true;
					��ս�����˺���ħ.WaitTime = 0;
				}
			}	
			if (!��ս�����˺���ħ.���� && ��ս�����˺���ħ.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_PhysicAttackPower")));
				SBCheatManager->SBApplyEffectMe(Name);
				��ս�����˺���ħ.һ�� = false;	
			}
		#pragma endregion


		#pragma region ��ս�����ٶȸ�ħ

			if (��ս�����ٶȸ�ħ.����)
			{
					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_AttackSpeed")));
					SBCheatManager->SBApplyEffectMe(Name);
					��ս�����ٶȸ�ħ.һ�� = true;
					��ս�����ٶȸ�ħ.WaitTime = 0;
			}
		#pragma endregion


		#pragma region Զ�������˺���ħ				
			if (Զ�������˺���ħ.����)
			{
				Զ�������˺���ħ.WaitTime++;
				if (Զ�������˺���ħ.WaitTime > 20 || Զ�������˺���ħ.����)
				{

					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_RangeAttackPower")));
					SBCheatManager->SBApplyEffectMe(Name);
					Զ�������˺���ħ.һ�� = true;
					Զ�������˺���ħ.WaitTime = 0;
				}
			}
			if (!Զ�������˺���ħ.���� && Զ�������˺���ħ.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_RangeAttackPower")));
				SBCheatManager->SBApplyEffectMe(Name);
				Զ�������˺���ħ.һ�� = false;
			}
		#pragma endregion


}