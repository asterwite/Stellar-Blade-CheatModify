#include "..\����.h"
class PeopleLoopCheat
{
public:
	bool �����ٶ����� = false;
	bool ������ = false;
	bool ɾ������ = false;
	bool ɱ¾�⻷ = false;
	bool �ѺõĹ��� = false;
	bool �����ȶ����� = false;
	bool ѣ�ε��� = false;
private:
	int WaitEnemyFriend = 0;
public:
	float GetDistanceToActor(AActor* pLocal, AActor* pTarget);
	void DrawPeopleUI();
	void PeopleToMe(AActor* Actor);
	void PeopleLoop();

};
inline PeopleLoopCheat PeopleLoop;


inline float PeopleLoopCheat::GetDistanceToActor(AActor* pLocal, AActor* pTarget)
{
	if (!pLocal || !pTarget)
		return -1.f;

	FVector pLocation = pLocal->K2_GetActorLocation();
	FVector pTargetLocation = pTarget->K2_GetActorLocation();
	double distance = sqrt(pow(pTargetLocation.X - pLocation.X, 2.f) + pow(pTargetLocation.Y - pLocation.Y, 2.f) + pow(pTargetLocation.Z - pLocation.Z, 2.f));
	return distance / 100.0f;
}

inline void PeopleLoopCheat::DrawPeopleUI()
{
		ImGui::Checkbox((const char*)u8"�����ٶ�����", &�����ٶ�����);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"����ô������·�ˣ���");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"ɾ������", &ɾ������);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"���̵���ȫ������ɾ�ˣ�ע�����ױ���");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"ɱ¾�⻷", &ɱ¾�⻷);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"����֮����ݲ���");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"�ѺõĹ���", &�ѺõĹ���);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"�����ҵ��������˭���ٶ࿴һ�۾ͻᱬը");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"�����ȶ�����", &�����ȶ�����);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"���£�����");
		ImGui::Checkbox((const char*)u8"ѣ�ε���", &ѣ�ε���);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"����վ�ţ�ȫ�����£�������һ����Χ�ڣ�");
}
inline void PeopleLoopCheat::PeopleToMe(AActor* Actor)
{
	auto NewLocation = GetActor()->GetActorForwardVector() * 1000.f;
	auto Location = GetActor()->Instigator->RootComponent->K2_GetComponentToWorld().Translation + NewLocation;
	auto Rotation = GetPlayerController()->PlayerCameraManager->CameraCachePrivate.POV.Rotation;
	Actor->K2_TeleportTo(Location, Rotation);
	Actor->K2_SetActorLocation(Location, false,nullptr,true);
}


inline void PeopleLoopCheat::PeopleLoop()
{
	UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
	USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
	if (ɱ¾�⻷)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("Test_EnemyKill")));
		SBCheatManager->SBApplyEffectMe(Name);
	}

	if (�ѺõĹ���)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("TribeChange_MonsterSupporter")));
		SBCheatManager->SBApplyEffectMe(Name);
		WaitEnemyFriend = 0;
	}

	if (!�ѺõĹ���)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("TribeChange_MonsterEnemy")));
		WaitEnemyFriend++;
		if (WaitEnemyFriend < 50)
		{
		SBCheatManager->SBApplyEffectMe(Name);
		}
	}

	if (�����ȶ�����)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("Test_EnemyStaminaSet0")));
		SBCheatManager->SBApplyEffectMe(Name);
		WaitEnemyFriend = 0;
	}

	if (ѣ�ε���)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("Test_EnemyEffectGroggy")));
		SBCheatManager->SBApplyEffectMe(Name);
		WaitEnemyFriend = 0;
	}

	std::vector<AActor*> actors;
	if (!GetAllActorsofType(AActor::StaticClass(), &actors, true, true))
		return;
	for (AActor* Myactor : actors)
	{
		if (Myactor && Myactor->IsA(ASBCharacter::StaticClass()))
		{

			auto SBCharacter = reinterpret_cast<ASBCharacter*>(Myactor);
			if (!SBCharacter)
				continue;

			if(GetDistanceToActor(GetActor(), SBCharacter)>100.f)
				continue;
			
			//if(SBCharacter->MultiPartHealthComponent !=nullptr&&Zombie->MultiPartHealthComponent->Health > 0)
			//{
			if (Myactor->Name.ToString().contains("CH_M_NA"))
			{
				if (�����ٶ����� && Myactor->CustomTimeDilation != 0)
				{
					Myactor->CustomTimeDilation = 0;
				}
				if (!�����ٶ����� && Myactor->CustomTimeDilation != 1.f)
				{
					Myactor->CustomTimeDilation = 1.f;
				}
				if (ɾ������)
				{
					SBCharacter->K2_DestroyActor();
				}
			}
			
			//}	
		}
	}
}