#pragma once
#include "..\����.h"
class MeleeWeaponLoop
{
public:
    bool �����;� = false;
    bool ��ս�и����� = false;
    bool ��ս����� = false;
    bool ��ս����֫�� = false;
    bool ��ս������� = false;
    bool ��ս����ƽ�� = false;
    bool ��ս�ٷְٱ��� = false;
    bool ��ս�����ȶ�һ���ص� = false;
    bool ��ս��Զ���� = false;
    bool ��սȫ������ = false;
    ABP_Base_MeleeWeaponItem_C* PlayerMeleeWeapon;
private:
    bool ��ӡ��ս��ַ;
    int SetCriticalWaitTime = 0;
    int SetDamageWaitTime = 0;
    int SetForceWaitTime = 0;
public:
    ABP_Base_Zombie_C* GetZombie(AActor* Actor);
	void DrawMeleeWeaponUI();
	void MeleeWeaponCheat();

}; inline MeleeWeaponLoop MeleeWeapon;

inline ABP_Base_Zombie_C* MeleeWeaponLoop::GetZombie(AActor* Actor)
{
    if (Actor && Actor->IsA(ABP_Base_Zombie_C::StaticClass()))
    {
        auto Zombie = reinterpret_cast<ABP_Base_Zombie_C*>(Actor);
        if (!Zombie)
            return nullptr;
        if(Zombie->MultiPartHealthComponent->Health<=0)
            return nullptr;
        return Zombie;
    }
}

inline void MeleeWeaponLoop::DrawMeleeWeaponUI()
{
        //if (ImGui::Button((const char*)u8"��ӡ��ǰ��ս������ַ"))
        //��ӡ��ս��ַ = true;
	    ImGui::Checkbox((const char*)u8"�����;�", &�����;�);
        ImGui::Checkbox((const char*)u8"��ս�и�����", &��ս�и�����);
        if(��ս�и�����)
        {
            ImGui::Checkbox((const char*)u8"��ս�����", &��ս�����);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"��ս����֫��", &��ս����֫��);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"��ս�������", &��ս�������);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"��ս����ƽ��", &��ս����ƽ��);
        }     
        ImGui::Checkbox((const char*)u8"��ս�����ȶ�һ���ص�", &��ս�����ȶ�һ���ص�);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"��ս�ٷְٱ���", &��ս�ٷְٱ���);
        ImGui::Checkbox((const char*)u8"��ս��Զ���ࣨ�е���������ԭ��", &��ս��Զ����);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"��սȫ���������е���������ԭ��", &��սȫ������);
}
inline void MeleeWeaponLoop::MeleeWeaponCheat()
{
    if (��ս��Զ���� && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance != NULL && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance != 9999.f && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.StabTraceDistance != 9999.f)
    {
        GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance = 9999.f;
        GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.StabTraceDistance = 9999.f;
    }
    if (��սȫ������ && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance != NULL && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance != 9999.f && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.StabTraceDistance != 9999.f)
    {
        GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance = 9999.f;
        GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceHeight = 500.f;
        GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.StabTraceDistance = 9999.f;
        GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.StabSphereRadius = 500.f;
    }
    UAutoAimSettingsComponent;
    ACharacter* pLocalPlayer = GetCharacter();
    if (!pLocalPlayer)
        return;
    std::vector<AActor*> Actors;
    if (!GetAllActorsofType(AActor::StaticClass(), &Actors, true, true))
        return;

    for (AActor* Actor : Actors)
    {
        
        if (Actor && Actor->IsA(ABP_Base_MeleeWeaponItem_C::StaticClass()))
        {
            auto MeleeWeapon = reinterpret_cast<ABP_Base_MeleeWeaponItem_C*>(Actor);

            if (MeleeWeapon->Player != nullptr && MeleeWeapon->Player == GetABPBasePlayerC() && MeleeWeapon->CurrentMeleeSweep != nullptr && MeleeWeapon->CurrentMeleeSweep == GetABPBasePlayerC()->BPC_Player_MeleeSweep)
            {
                PlayerMeleeWeapon = MeleeWeapon;
                if (��ӡ��ս��ַ)
                {
                    printf("��ս������ַ: [%p]\t", Actor);
                    ��ӡ��ս��ַ = false;
                }

                if (�����;�)
                    MeleeWeapon->ServerSetCurrentDurabilityToMax();
                if (��ս�и�����)
                {
                    if (��ս�����)
                        MeleeWeapon->MeleeArchetypeData.ImpactData.bCanCauseBreak = true;
                    if (��ս����֫��)
                        MeleeWeapon->MeleeArchetypeData.ImpactData.bCanCauseDismember = true;
                    if (��ս�������)
                        MeleeWeapon->MeleeArchetypeData.ImpactData.bCanCut = true;
                    if (��ս����ƽ��)
                        MeleeWeapon->MeleeArchetypeData.ImpactData.bCanCauseBisection = true;
                }


                #pragma region �������ٷְٱ���
                auto AttributeValue = MeleeWeapon->AttributesComponent->AttributeValueSet;
                if (��ս�����ȶ�һ���ص�)
                     AttributeValue.ForceAttribute.Type->ModifierType->DefaultValueOverride = 999.f;
                else
                        AttributeValue.ForceAttribute.Type->ModifierType->DefaultValueOverride = 1.f;

                if (��ս�ٷְٱ��� && MeleeWeapon->CriticalHitEventGenerator->RegisteredChanceValue == 0)
                {
                    MeleeWeapon->CriticalHitEventGenerator->RegisteredChanceValue = 999.f;
                    MeleeWeapon->CriticalHitEventGenerator->InitializationCount = (uint16)0;
                }

                if (!��ս�ٷְٱ��� && MeleeWeapon->CriticalHitEventGenerator->RegisteredChanceValue == 999.f)
                {
                    MeleeWeapon->CriticalHitEventGenerator->RegisteredChanceValue = 0;
                    MeleeWeapon->CriticalHitEventGenerator->InitializationCount = (uint16)3;
                }
                #pragma endregion
             

            }
        }   
    }
}


