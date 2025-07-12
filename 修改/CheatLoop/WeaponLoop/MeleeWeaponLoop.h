#pragma once
#include "..\遍历.h"
class MeleeWeaponLoop
{
public:
    bool 无限耐久 = false;
    bool 近战切割启动 = false;
    bool 近战允许打洞 = false;
    bool 近战允许肢解 = false;
    bool 近战允许剪切 = false;
    bool 近战允许平分 = false;
    bool 近战百分百暴击 = false;
    bool 近战敌人稳定一击必倒 = false;
    bool 近战超远刀距 = false;
    bool 近战全屏攻击 = false;
    ABP_Base_MeleeWeaponItem_C* PlayerMeleeWeapon;
private:
    bool 打印近战地址;
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
        //if (ImGui::Button((const char*)u8"打印当前近战武器地址"))
        //打印近战地址 = true;
	    ImGui::Checkbox((const char*)u8"无限耐久", &无限耐久);
        ImGui::Checkbox((const char*)u8"近战切割启动", &近战切割启动);
        if(近战切割启动)
        {
            ImGui::Checkbox((const char*)u8"近战允许打洞", &近战允许打洞);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"近战允许肢解", &近战允许肢解);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"近战允许剪切", &近战允许剪切);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"近战允许平分", &近战允许平分);
        }     
        ImGui::Checkbox((const char*)u8"近战敌人稳定一击必倒", &近战敌人稳定一击必倒);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"近战百分百暴击", &近战百分百暴击);
        ImGui::Checkbox((const char*)u8"近战超远刀距（切刀或攀爬还原）", &近战超远刀距);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"近战全屏攻击（切刀或攀爬还原）", &近战全屏攻击);
}
inline void MeleeWeaponLoop::MeleeWeaponCheat()
{
    if (近战超远刀距 && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance != NULL && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance != 9999.f && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.StabTraceDistance != 9999.f)
    {
        GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance = 9999.f;
        GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.StabTraceDistance = 9999.f;
    }
    if (近战全屏攻击 && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance != NULL && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.TraceDistance != 9999.f && GetABPBasePlayerC()->BPC_Player_MeleeSweep->SweepParams.StabTraceDistance != 9999.f)
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
                if (打印近战地址)
                {
                    printf("近战武器地址: [%p]\t", Actor);
                    打印近战地址 = false;
                }

                if (无限耐久)
                    MeleeWeapon->ServerSetCurrentDurabilityToMax();
                if (近战切割启动)
                {
                    if (近战允许打洞)
                        MeleeWeapon->MeleeArchetypeData.ImpactData.bCanCauseBreak = true;
                    if (近战允许肢解)
                        MeleeWeapon->MeleeArchetypeData.ImpactData.bCanCauseDismember = true;
                    if (近战允许剪切)
                        MeleeWeapon->MeleeArchetypeData.ImpactData.bCanCut = true;
                    if (近战允许平分)
                        MeleeWeapon->MeleeArchetypeData.ImpactData.bCanCauseBisection = true;
                }


                #pragma region 击倒，百分百暴击
                auto AttributeValue = MeleeWeapon->AttributesComponent->AttributeValueSet;
                if (近战敌人稳定一击必倒)
                     AttributeValue.ForceAttribute.Type->ModifierType->DefaultValueOverride = 999.f;
                else
                        AttributeValue.ForceAttribute.Type->ModifierType->DefaultValueOverride = 1.f;

                if (近战百分百暴击 && MeleeWeapon->CriticalHitEventGenerator->RegisteredChanceValue == 0)
                {
                    MeleeWeapon->CriticalHitEventGenerator->RegisteredChanceValue = 999.f;
                    MeleeWeapon->CriticalHitEventGenerator->InitializationCount = (uint16)0;
                }

                if (!近战百分百暴击 && MeleeWeapon->CriticalHitEventGenerator->RegisteredChanceValue == 999.f)
                {
                    MeleeWeapon->CriticalHitEventGenerator->RegisteredChanceValue = 0;
                    MeleeWeapon->CriticalHitEventGenerator->InitializationCount = (uint16)3;
                }
                #pragma endregion
             

            }
        }   
    }
}


