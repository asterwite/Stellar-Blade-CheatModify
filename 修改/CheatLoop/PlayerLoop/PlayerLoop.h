#pragma once
#include "PlayerUI/PlayerScreenAndSettings.h"
#define IsKeyHeld(key) (GetAsyncKeyState(key) & 0x8000)
class PlayerCheat
{
public:
	struct EffectCheat
	{
		bool ���� = false;
		bool һ�� = false;
		int WaitTime = false;
	};

	EffectCheat ���˻�ɨ�����ӳ� = { false,false,0 }; 

private:
	char  ����[255];


public:
	void DrawPlayerUI();
	void PlayerCheatStar();
};
inline PlayerCheat Player;

inline void DrawBoneName()
{
	for (int i = 0;i < 999;i++)
	{
		printf("��������: [%s]\t%d\n", GetCharacter()->Mesh->GetBoneName(i).ToString().c_str(),i);
	}
}

inline void PlayerCheat::DrawPlayerUI()
{
	USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
	UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
	if (ImGui::CollapsingHeader((const char*)u8"�������ã�����������ں�ģʽ��ʹ��Ѹ��װ���Ͳ�Ҫ���޸ķ�װ�˻ᵼ��ģ�Ϳ�û����Ҫ���½��浵���ܻ�ԭ��"))
	{
		PlayerScreenAndSettingsUI.DrawPlayerScreenAndSettingsCheatUI(SBCheatManager, lib);
	}
	ImGui::Checkbox((const char*)u8"���˻�ɨ�����ӳ�", &���˻�ɨ�����ӳ�.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"˭˵���˻�ɨ���еȴ��ģ�ע�⣺�ҰѰ���д���ˣ�Tab���Ż�ɨ��");
	if (ImGui::Button((const char*)u8"�Ƴ����˻�"))
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("LV_SummonDrone_Dispel")));
		SBCheatManager->SBApplyEffectMe(Name);
	}
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�����˻��أ�������������˻��أ�������Ҫ��ɱ�����½��浵��ԭ���ǵ��ȱ���");

	if (ImGui::CollapsingHeader((const char*)u8"����"))
	{
		ImGui::InputText((const char*)u8"����", ����, sizeof(����));
		if (ImGui::Button((const char*)u8"����Effect", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
		{
			if (!SBCheatManager)
				printf("û���ҵ�SBCheatManager");
			if (SBCheatManager && ����[0] != '\0')
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar(����)));
				SBCheatManager->SBApplyEffectMe(Name);
				printf("ִ�гɹ�");
			}
		}
	}
}


inline void PlayerCheat::PlayerCheatStar()
{
		UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
		USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();


		PlayerScreenAndSettingsUI.PlayerScreenAndSettingsCheatStar(SBCheatManager, lib);

		#pragma region ���˻�ɨ�����ӳ�
			if (���˻�ɨ�����ӳ�.����&& GetAsyncKeyState(VK_TAB)&&1)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("N_Drone_Scan")));
				SBCheatManager->SBApplyEffectMe(Name);
				���˻�ɨ�����ӳ�.һ�� = true;
			}
			if (!���˻�ɨ�����ӳ�.���� && ���˻�ɨ�����ӳ�.һ��)
				���˻�ɨ�����ӳ�.һ�� = false;
		#pragma endregion

}

#pragma region MyRegion

#pragma endregion
