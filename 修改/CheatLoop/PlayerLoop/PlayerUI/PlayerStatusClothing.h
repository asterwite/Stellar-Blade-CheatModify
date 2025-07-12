#include "PlayerAttribute.h"
#include "..\ModeName.h"
class PlayerStatusClothingUICheat
{
public:
	struct EffectCheat
	{
		bool ���� = false;
		bool һ�� = false;
		int WaitTime = false;
	};
	bool �滻��װ���� = false;
	bool ֻ�޸��ں�״̬���޸ķ�װ = false;
	bool �޸��ں�״̬Ҳ�޸ķ�װ = false;
	EffectCheat ʹ��Ѹ��װ�� = { false,false,0 };
	EffectCheat �����ں���̬ = { false,false,0 };
	const char* ClothModeName = "";
public:
	void DrawPlayerStatusClothingCheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
	void PlayerStatusClothingUICheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
};
inline PlayerStatusClothingUICheat  PlayerStatusClothingUI;

inline void PlayerStatusClothingUICheat::DrawPlayerStatusClothingCheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	PlayerAttributeUI.DrawPlayerAttributeUICheatUI( SBCheatManager, lib);
	ImGui::Checkbox((const char*)u8"ʹ��Ѹ��װ��������ս��ģʽŶ������رպ�����ģ�Ϳ�û���Ϳ����ں���̬�ٹرռ��ɣ�", &ʹ��Ѹ��װ��.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"��Ҫ��װ���ˣ�Ϊʲôû��װ����Ч��������");
	ImGui::Checkbox((const char*)u8"�����ں���̬���������Ƿ��Ѿ��������������Ӧ�ļ��ܣ�", &�����ں���̬.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"ԭ����������������");
	if (�����ں���̬.����)
	{
		ImGui::Checkbox((const char*)u8"ֻ�޸��ں�״̬���޸ķ�װ", &ֻ�޸��ں�״̬���޸ķ�װ);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"ΪʲôҪ���·����Լ��Ĳ��ÿ���");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"�޸��ں�״̬Ҳ�޸ķ�װ", &�޸��ں�״̬Ҳ�޸ķ�װ);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"���׺��壬��������Ůսʿ������");
	}
	ImGui::Checkbox((const char*)u8"�滻��װ����", &�滻��װ����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"���ǻ�װС��Ϸ��");
	if (�滻��װ����)
	{
		static int selected_item = -1;  // Ĭ��û��ѡ���κ���
		if (ImGui::ListBox((const char*)u8"�滻��װΪ��̬��װ", &selected_item, AllPlayerClothModeNameShow, IM_ARRAYSIZE(AllPlayerClothModeNameShow), IM_ARRAYSIZE(AllPlayerClothModeNameShow)))
		{
			ClothModeName = AllPlayerClothModeName[selected_item];
		}
		if (ImGui::Button((const char*)u8"�滻��װ", ImVec2(ImGui::GetContentRegionAvail().x - 3, 40)) && GetCharacter() && GetPawn() && GetGameStateBase()->HasBegunPlay())
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar(ClothModeName)));
			SBCheatManager->SBApplyEffectMe(Name);
		}
		if (ImGui::Button((const char*)u8"��ԭȫ����װ", ImVec2(ImGui::GetContentRegionAvail().x - 3, 40)) && GetCharacter() && GetPawn() && GetGameStateBase()->HasBegunPlay())
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

		#pragma region ʹ��Ѹ��װ��
			if (ʹ��Ѹ��װ��.���� && !ʹ��Ѹ��װ��.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyModeWeapon")));
				FName Name1 = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyModeWing")));
				FName Name2 = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyModeNanoSuit")));
				SBCheatManager->SBApplyEffectMe(Name);
				SBCheatManager->SBApplyEffectMe(Name1);
				SBCheatManager->SBApplyEffectMe(Name2);
				ʹ��Ѹ��װ��.һ�� = true;
			}
			if (!ʹ��Ѹ��װ��.���� && ʹ��Ѹ��װ��.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_TachyMode")));
				SBCheatManager->SBApplyEffectMe(Name);
				ʹ��Ѹ��װ��.һ�� = false;
			}
		#pragma endregion
		
		
		#pragma region �����ں���̬
			if (�����ں���̬.���� && !�����ں���̬.һ��)
			{
				if (�޸��ں�״̬Ҳ�޸ķ�װ)
				{
					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Fusion2_Stance")));
					SBCheatManager->SBApplyEffectMe(Name);
					�����ں���̬.һ�� = true;
				}
				if (ֻ�޸��ں�״̬���޸ķ�װ)
				{
					FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Fusion2Mode")));
					SBCheatManager->SBApplyEffectMe(Name);
					�����ں���̬.һ�� = true;
				}
			}
			if (!�����ں���̬.���� && �����ں���̬.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("P_Eve_Fusion2_Stance_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				�����ں���̬.һ�� = false;
			}
		#pragma endregion
}
