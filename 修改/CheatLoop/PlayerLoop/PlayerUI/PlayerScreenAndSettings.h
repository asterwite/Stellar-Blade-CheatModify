#include "PlayerStatusClothing.h"
class PlayerScreenAndSettingsUICheat
{
public:
	struct EffectCheat
	{
		bool ���� = false;
		bool һ�� = false;
		int WaitTime = false;
	};
	EffectCheat ǿ�ƽ������״̬ = { false,false,0 };
	EffectCheat �������ģʽ = { false,false,0 };
	EffectCheat ������Ļ��Ч = { false,false,0 };
public:
	void DrawPlayerScreenAndSettingsCheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
	void PlayerScreenAndSettingsCheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
};
inline PlayerScreenAndSettingsUICheat  PlayerScreenAndSettingsUI;

inline void PlayerScreenAndSettingsUICheat::DrawPlayerScreenAndSettingsCheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerStatusClothingUI.DrawPlayerStatusClothingCheatUI(SBCheatManager,lib);

	ImGui::Checkbox((const char*)u8"����Ŀ��״̬����", &������Ļ��Ч.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"���������ˣ���");
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"����������������Ŀ��״̬���汾1��"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_RestartRule_Beach_FrontEffectVol")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�汾1�Ͱ汾2�ĶԻ���һ���������ѡ��ע���޷��رջ�ֱ�����¼��أ���Ҫ��û��������������������");
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"����������������Ŀ��״̬���汾2��"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_RestartRule_Beach_BackEffectVol")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�汾1�Ͱ汾2�ĶԻ���һ���������ѡ��ע���޷��رջ�ֱ�����¼��أ���Ҫ��û��������������������");
	if (ImGui::Button((const char*)u8"װ��"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_N_GuideA_Dead")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"������װ������Ϊʲô��Ҫ���ң�ע���޷���ԭ��Ҫ��ɱ�������½��浵");
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"��ɫ��������Ч��"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_Dead_Grinder_Show")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"�رս�ɫ��������Ч��"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_Dead_Grinder_Show_Dispel")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	if (ImGui::Button((const char*)u8"նɱ��ն���"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("M_Gorilla_FinishStart")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"���Ǹ�������Ҹ�������");

	if (ImGui::Button((const char*)u8"ǿ�ƽ���δ�õ����Ķ���"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("M_Gorgon_FinishReady")));
		FName Name1 = lib->Conv_StringToName(FString(charToWchar("M_Gorgon_Finish")));
		SBCheatManager->SBApplyEffectMe(Name);
		SBCheatManager->SBApplyEffectMe(Name1);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"��ֱ�ӿ����鵫�ǲ�������ľ�����ת���õط�������Ϊ��ǰ��������ͼ�ĳ�������ͬ�ĳ���ͬһ����������������");


	ImGui::Checkbox((const char*)u8"ǿ�ƽ������״̬���������Ƿ��Ѿ����������ģʽ��ȱ�ݾ����޷��ƶ���", &ǿ�ƽ������״̬.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"����ʱ�����ˣ�����");
	ImGui::Checkbox((const char*)u8"�������ģʽ��ֱ�ӽ�����Ctrl����׼��", &�������ģʽ.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"˭˵��ûǹ�ģ���");

	if (ImGui::Button((const char*)u8"�����ɱ", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)) && GetCharacter() && GetPawn() && GetGameStateBase()->HasBegunPlay())
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("ImmediateDeath")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"����ţ����ؿ�");
}

inline void PlayerScreenAndSettingsUICheat::PlayerScreenAndSettingsCheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerStatusClothingUI.PlayerStatusClothingUICheatStar(SBCheatManager,lib);

	#pragma region ���״̬
		if (ǿ�ƽ������״̬.���� && !ǿ�ƽ������״̬.һ��)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Stance_GunTutorial")));
			SBCheatManager->SBApplyEffectMe(Name);
			ǿ�ƽ������״̬.һ�� = true;
		}
		if (!ǿ�ƽ������״̬.���� && ǿ�ƽ������״̬.һ��)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Stance_GunTutorial_End")));
			SBCheatManager->SBApplyEffectMe(Name);
			ǿ�ƽ������״̬.һ�� = false;
		}
	#pragma endregion
	
	
	#pragma region �������ģʽ
		if (�������ģʽ.���� && !�������ģʽ.һ��)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("Eve_ModeOpen_TPS_Eff")));
			SBCheatManager->SBApplyEffectMe(Name);
			�������ģʽ.һ�� = true;
		}
		if (!ǿ�ƽ������״̬.���� && ǿ�ƽ������״̬.һ��)
		{
			ǿ�ƽ������״̬.һ�� = false;
		}
	#pragma endregion
	

	#pragma region ������Ļ��Ч
		if (������Ļ��Ч.����)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("ScreenEffect_RestartRule_Beach")));
			SBCheatManager->SBApplyEffectMe(Name);
			������Ļ��Ч.һ�� = true;
		}
		if (!������Ļ��Ч.���� && ������Ļ��Ч.һ��)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("ScreenEffect_RestartRule_Beach_Dispel")));
			SBCheatManager->SBApplyEffectMe(Name);
			������Ļ��Ч.һ�� = false;
		}
	
	#pragma endregion
}
