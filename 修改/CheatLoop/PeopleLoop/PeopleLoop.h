#include "..\遍历.h"
class PeopleLoopCheat
{
public:
	bool 怪物速度清零 = false;
	bool 吸怪物 = false;
	bool 删除怪物 = false;
	bool 杀戮光环 = false;
	bool 友好的怪物 = false;
	bool 怪物稳定清零 = false;
	bool 眩晕敌人 = false;
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
		ImGui::Checkbox((const char*)u8"怪物速度清零", &怪物速度清零);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"你怎么不能走路了？？");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"删除怪物", &删除怪物);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"奶奶的我全给你们删了，注意容易崩溃");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"杀戮光环", &杀戮光环);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"所到之处寸草不生");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"友好的怪物", &友好的怪物);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"你是我的我是你的谁，再多看一眼就会爆炸");
		ImGui::SameLine();
		ImGui::Checkbox((const char*)u8"怪物稳定清零", &怪物稳定清零);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"跪下！！！");
		ImGui::Checkbox((const char*)u8"眩晕敌人", &眩晕敌人);
		ImGui::SameLine();
		ImGuiHelpMarker((const char*)u8"不许站着，全部跪下！！！（一定范围内）");
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
	if (杀戮光环)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("Test_EnemyKill")));
		SBCheatManager->SBApplyEffectMe(Name);
	}

	if (友好的怪物)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("TribeChange_MonsterSupporter")));
		SBCheatManager->SBApplyEffectMe(Name);
		WaitEnemyFriend = 0;
	}

	if (!友好的怪物)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("TribeChange_MonsterEnemy")));
		WaitEnemyFriend++;
		if (WaitEnemyFriend < 50)
		{
		SBCheatManager->SBApplyEffectMe(Name);
		}
	}

	if (怪物稳定清零)
	{
		FName Name = lib->Conv_StringToName(FString(charToWchar("Test_EnemyStaminaSet0")));
		SBCheatManager->SBApplyEffectMe(Name);
		WaitEnemyFriend = 0;
	}

	if (眩晕敌人)
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
				if (怪物速度清零 && Myactor->CustomTimeDilation != 0)
				{
					Myactor->CustomTimeDilation = 0;
				}
				if (!怪物速度清零 && Myactor->CustomTimeDilation != 1.f)
				{
					Myactor->CustomTimeDilation = 1.f;
				}
				if (删除怪物)
				{
					SBCharacter->K2_DestroyActor();
				}
			}
			
			//}	
		}
	}
}