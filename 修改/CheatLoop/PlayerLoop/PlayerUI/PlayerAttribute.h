#include "..\PlayerFly.h"
class PlayerAttributeUICheat
{
public:
	struct EffectCheat
	{
		bool ���� = false;
		bool һ�� = false;
		int WaitTime = false;
	};
	float �����ٶ� = 1.f;
	EffectCheat ��ģʽ = { false,false,0 };
	EffectCheat ��ð�̹� = { false,false,0 };
	EffectCheat ��ɫˮ������ = { false,false,0 };
	EffectCheat ȼ������ = { false,false,0 };
	EffectCheat ���⽣ = { false,false,0 };
	EffectCheat �޵� = { false,false,0 };
	EffectCheat ����ģʽ = { false,false,0 };
	EffectCheat ���ޱ������� = { false,false,0 };
	EffectCheat ����Ѹ�� = { false,false,0 };
	EffectCheat ����BU = { false,false,0 };
	EffectCheat ����ģʽ = { false,false,0 };
	EffectCheat ����Ч�� = { false,false,0 };
	EffectCheat �ر��������� = { false,false,0 };
	EffectCheat �������� = { false,false,0 };
	bool �������� = false;
	bool ���޻��� = false;
	char  ����[255];
public:
	void DrawPlayerAttributeUICheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
	void PlayerAttributeUICheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib);
};
inline PlayerAttributeUICheat  PlayerAttributeUI;

inline void PlayerAttributeUICheat::DrawPlayerAttributeUICheatUI(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
	ImGui::SliderFloat((const char*)u8"�����ٶ�", &�����ٶ�, 1.f, 20.f);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�����ƶ��Ķ����ٶȣ��������ɿ�Ŷ");
	PlayerFly.PlayerFlyUI();
	
	ImGui::Checkbox((const char*)u8"��ģʽ", &��ģʽ.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�����κ������˺����쳣�˺��������ֻ���ɱ���޷��رգ���Ҫ�ؽ��浵");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"��ð�̹�", &��ð�̹�.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�ⲻ����ñ�ӣ�����");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"��ɫˮ������", &��ɫˮ������.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"��TM��ʷ�ˣ�������");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"ȼ������", &ȼ������.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�������Ǵ���Ч�ģ�����");

	ImGui::Checkbox((const char*)u8"���⽣", &���⽣.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�����ս��");

	ImGui::Checkbox((const char*)u8"�޵�", &�޵�.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"����˼�壬�򲻵��ң��������Ǵ򲻶��ң�������������Ҫ���¿���");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"��������", &��������);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"Ѫ�������ˣ�Ѫ��Ҳû�ˣ�");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"����ģʽ", &����ģʽ.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"����˼�壬��������");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"���޻���", &���޻���);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"���令��");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"���ޱ�������", &���ޱ�������.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�����̵أ���");

	ImGui::Checkbox((const char*)u8"����ģʽ", &����ģʽ.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�㿴�������㿴�����ң�������ĺ�����");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"����Ч��", &����Ч��.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"�����汾��һ����ע����������Ҫ���¿���");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"����BU", &����BU.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"����˼�壬����BU");
	ImGui::SameLine();
	ImGui::Checkbox((const char*)u8"����Ѹ��", &����Ѹ��.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"����Ѹ������ʱ��");
	ImGui::SameLine();

	ImGui::Checkbox((const char*)u8"�ر���������", &�ر���������.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"���϶����������ʲô");

	ImGui::Checkbox((const char*)u8"��������", &��������.����);
	ImGui::SameLine();
	ImGuiHelpMarker((const char*)u8"������ң����ͬ�⣡��");


}

inline void PlayerAttributeUICheat::PlayerAttributeUICheatStar(USBCheatManager* SBCheatManager, UKismetStringLibrary* lib)
{
		if (��������)
		{
			FName Name = lib->Conv_StringToName(FString(charToWchar("T_SetEveStat_HPRecover")));
			SBCheatManager->SBApplyEffectMe(Name);
		}
		GetPawn()->CustomTimeDilation = �����ٶ�;
		PlayerFly.PlayerFly();
		#pragma region ��ģʽ
			if (��ģʽ.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Test_ImmunePhysicDamageMe")));
				FName Name1 = lib->Conv_StringToName(FString(charToWchar("Test_ImmuneAbnormal")));
				SBCheatManager->SBApplyEffectMe(Name);
				SBCheatManager->SBApplyEffectMe(Name1);
			}
		#pragma endregion


		#pragma region ��ð�̹�
			if (��ð�̹�.����)
			{			
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_DataDrone_Nikke_FXShow")));
				SBCheatManager->SBApplyEffectMe(Name);
			}
		#pragma endregion


		#pragma region ��ɫˮ������
			if (��ɫˮ������.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_GorillaB_S24_PowerUpBuff")));
				SBCheatManager->SBApplyEffectMe(Name);
		
				��ɫˮ������.һ�� = true;
			}
			if (!��ɫˮ������.���� && ��ɫˮ������.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_GorillaB_S24_PowerUpBuff_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				��ɫˮ������.һ�� = false;
			}
		#pragma endregion


		#pragma region ȼ������
			if (ȼ������.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_Behemoth_BuffFX2")));
				SBCheatManager->SBApplyEffectMe(Name);
		
				ȼ������.һ�� = true;
			}
			if (!ȼ������.���� && ȼ������.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("M_Behemoth_BuffFX2_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				ȼ������.һ�� = false;
			}
		#pragma endregion


		#pragma region ���⽣
			���⽣.WaitTime++;
					if (���⽣.����&& ���⽣.WaitTime>100)
					{
						FName Name = lib->Conv_StringToName(FString(charToWchar("M_Raven_BuffFX_OFF")));
						SBCheatManager->SBApplyEffectMe(Name);
						���⽣.WaitTime = 0;
						���⽣.һ�� = true;
					}
					if (!���⽣.���� && ���⽣.һ��)
					{
						FName Name = lib->Conv_StringToName(FString(charToWchar("M_Raven_BuffFX_Dispel")));
						SBCheatManager->SBApplyEffectMe(Name);
						���⽣.һ�� = false;
					}
		#pragma endregion

			
		#pragma region �޵�
			if (�޵�.���� && !�޵�.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("NoDamageNoHitImmuneAbnormal_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
				�޵�.һ�� = true;
			}
			if (!�޵�.���� && �޵�.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("NoDamageNoHitImmuneAbnormal_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				�޵�.һ�� = false;
			}
		#pragma endregion
		
		
		#pragma region ����ģʽ
			if (����ģʽ.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Passive_Immortal")));
				SBCheatManager->SBApplyEffectMe(Name);
		
				����ģʽ.һ�� = true;
			}
			if (!����ģʽ.���� && ����ģʽ.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Passive_Immortal_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				����ģʽ.һ�� = false;
			}
		#pragma endregion
		
		
		#pragma region ���޻���
			if (���޻���)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("RecoverShield_100p")));
				SBCheatManager->SBApplyEffectMe(Name);
			}
		#pragma endregion
		
		
		#pragma region ���ޱ�������
			if (���ޱ�������.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Item_Buff_HP2MP_GainMP")));
				SBCheatManager->SBApplyEffectMe(Name);
			}
		#pragma endregion


		#pragma region ����ģʽ
			if (����ģʽ.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("NotTargeted_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
				����ģʽ.һ�� = true;
			}
			if (!����ģʽ.���� && ����ģʽ.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("NotTargeted_Step")));
				SBCheatManager->SBApplyEffectMe(Name);
				����ģʽ.һ�� = false;
			}
		#pragma endregion
		
		
		#pragma region ����Ч��
			if (����Ч��.����&&!����Ч��.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Test_Stealth")));
				SBCheatManager->SBApplyEffectMe(Name);
				����Ч��.һ�� = true;
			}
			if (!����Ч��.���� && ����Ч��.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Test_Stealth")));
				SBCheatManager->SBApplyEffectMe(Name);
				����Ч��.һ�� = false;
			}

		#pragma endregion
		
		
		#pragma region ����BU
			if (����BU.���� && !����BU.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("T_Eve_Burst_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
		
				����BU.һ�� = true;
			}
			if (!����BU.���� && ����BU.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("T_Eve_Burst_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
				����BU.һ�� = false;
			}
		#pragma endregion
		
		
		#pragma region ����Ѹ��
			if (����Ѹ��.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Eve_TachyGaugeRegen")));
				SBCheatManager->SBApplyEffectMe(Name);
				����Ѹ��.һ�� = true;
			}
			if (!����Ѹ��.���� && ����Ѹ��.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("Eve_TachyGaugeRegen")));
				SBCheatManager->SBApplyEffectMe(Name);
				����Ѹ��.һ�� = false;
			}
		#pragma endregion
		
		
		#pragma region �ر���������
			if (�ر���������.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("DisableLockOnControl_Infinite")));
				SBCheatManager->SBApplyEffectMe(Name);
				�ر���������.һ�� = true;
			}
			if (!�ر���������.���� && �ر���������.һ��)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("DisableLockOnControl_Dispel")));
				SBCheatManager->SBApplyEffectMe(Name);
				�ر���������.һ�� = false;
			}
		#pragma endregion


		#pragma region ��������
			if (��������.����)
			{
				FName Name = lib->Conv_StringToName(FString(charToWchar("FastGetup")));
				SBCheatManager->SBApplyEffectMe(Name);
				�ر���������.һ�� = true;
			}
			if (!��������.���� && ��������.һ��)
				��������.һ�� = false;
		#pragma endregion
}