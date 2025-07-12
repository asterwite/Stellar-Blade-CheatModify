#include "MeleeWeaponLoop.h"
class GunWeaponLoopCheat
{
public:
    bool 无限子弹 = false;
    bool 点射无延迟 = false;
    int SpawnAmmoCount = 1;
    bool 枪械切割启动 = false;
    bool 枪械允许打洞 = false;
    bool 枪械允许肢解 = false;
    bool 枪械允许剪切 = false;
    bool 枪械允许平分 = false;

    bool 枪械一击必杀 = false;
    bool 枪械敌人稳定一击必倒 = false;
    bool 枪械百分百暴击 = false;

    ABP_Base_RangedWeaponItem_C* PlayerGunWeapon;
private:
    bool 打印枪械地址 = false;
    bool 添加当前武器备用弹药 = false;
    bool 添加当前武器 = false;
    int SetAmmoWaitTime = 0;
    int SetDamageWaitTime = 0;
    int SetForceWaitTime = 0;
    int SetCriticalWaitTime = 0;
public:
    void DrawGunWeaponUI();
    void GunWeaponCheat();

}; inline GunWeaponLoopCheat GunWeaponLoop;


inline void GunWeaponLoopCheat::DrawGunWeaponUI()
{
    if (ImGui::Button((const char*)u8"打印当前枪械地址"))
    {
        打印枪械地址 = true;
    }
    ImGui::Checkbox((const char*)u8"无限子弹）",&无限子弹);
    ImGui::SameLine();
    ImGui::Checkbox((const char*)u8"点射无延迟（注意:会导致连射会无法射击，使用大巨弹武器不要频繁射击会崩溃）", &点射无延迟);
    if (ImGui::Button((const char*)u8"补满当前武器备弹"))
    {
        添加当前武器备用弹药 = true;
    }
    ImGui::Checkbox((const char*)u8"枪械切割启动", &枪械切割启动);
    if (枪械切割启动)
    {
        ImGui::Checkbox((const char*)u8"枪械允许打洞", &枪械允许打洞);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"枪械允许肢解", &枪械允许肢解);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"枪械允许剪切", &枪械允许剪切);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"枪械允许平分", &枪械允许平分);
    }
    ImGui::Checkbox((const char*)u8"枪械一击必杀", &枪械一击必杀);
    ImGui::Checkbox((const char*)u8"枪械敌人稳定一击必倒", &枪械敌人稳定一击必倒);
    ImGui::SameLine();
    ImGui::Checkbox((const char*)u8"枪械百分百暴击", &枪械百分百暴击);

}
inline void GunWeaponLoopCheat::GunWeaponCheat()
{
    ACharacter* pLocalPlayer = GetCharacter();
    if (!pLocalPlayer)
        return;
    std::vector<AActor*> Actors;
    if (!GetAllActorsofType(AActor::StaticClass(), &Actors, true, true))
        return;

    for (AActor* Actor : Actors)
    {

        if (Actor && Actor->IsA(ABP_Base_RangedWeaponItem_C::StaticClass()))
        {
            auto GunWeapon = reinterpret_cast<ABP_Base_RangedWeaponItem_C*>(Actor);
            PlayerGunWeapon = GunWeapon;
            if (GunWeapon&& GunWeapon->Character == GetCharacter()&& GunWeapon->RangedWeaponModulesComponent->CurrentUser==GetActor())
            {

                if (打印枪械地址)
                {
                    printf("枪械地址: [%p]\t", Actor);
                    打印枪械地址 = false;
                }

                #pragma region 设置
                #pragma endregion

                #pragma region 添加备弹，无限子弹，点射无延迟
                auto InventoryClipAmmoHandler = reinterpret_cast<UInventoryClipAmmoHandler*>(GunWeapon->RangedWeaponModulesComponent->CurrentWeaponConfiguration.SelectedAmmoHandler);
                if (添加当前武器备用弹药 && InventoryClipAmmoHandler)
                {
                    GunWeapon->RangedWeaponModulesComponent->CurrentUserInventory->ServerAddItemByArchetype(InventoryClipAmmoHandler->RequiredAmmoType, InventoryClipAmmoHandler->RequiredAmmoType->StackSize, true);
                    添加当前武器备用弹药 = false;
                }
                if (无限子弹)
                {
                    SetAmmoWaitTime++;
                    if (SetAmmoWaitTime > 100)
                    {
                        InventoryClipAmmoHandler->ServerRequestAmmoSetToValue(99);
                        SetAmmoWaitTime = 0;
                    }
                }

                auto AttributeValue = GunWeapon->AttributesComponent->AttributeValueSet;
                if (点射无延迟 && AttributeValue.DelayBetweenShotsAttribute.Type->ModifierType->DefaultValueOverride == 1.f)
                    AttributeValue.DelayBetweenShotsAttribute.Type->ModifierType->DefaultValueOverride = 0;
                if (!点射无延迟 && AttributeValue.DelayBetweenShotsAttribute.Type->ModifierType->DefaultValueOverride == 0)
                    AttributeValue.DelayBetweenShotsAttribute.Type->ModifierType->DefaultValueOverride = 1.f;
                #pragma endregion

                #pragma region 子弹伤害，切割，敌人稳定一击必倒，百分百暴击
                auto Project = reinterpret_cast<UHitscanProjectileSpawnModule*>(GunWeapon->ShootActionParams->ShotHandler->ProjectileSpawner);
                if (Project)
                {
                    if (枪械一击必杀&& Project->DistanceBasedDamageFalloff.ScaleMultiplierAppliedAtStartRange!=9999.f)
                            Project->DistanceBasedDamageFalloff.ScaleMultiplierAppliedAtStartRange = 9999.f;
                    if(!枪械一击必杀 && Project->DistanceBasedDamageFalloff.ScaleMultiplierAppliedAtStartRange == 9999.f)
                        Project->DistanceBasedDamageFalloff.ScaleMultiplierAppliedAtStartRange = 1.f;
                    if (枪械切割启动)
                    {
                        if (枪械允许打洞)
                            Project->ImpactData.bCanCauseBreak = true;
                        if (枪械允许肢解)
                            Project->ImpactData.bCanCauseDismember = true;
                        if (枪械允许剪切)
                            Project->ImpactData.bCanCut = true;
                        if (枪械允许平分)
                            Project->ImpactData.bCanCauseBisection = true;
                    }
                    if (枪械敌人稳定一击必倒 && Project->DistanceBasedForceFalloff.ScaleMultiplierAppliedAtStartRange == 1.f)
                    {
                        SetForceWaitTime++;
                        if (SetForceWaitTime > 20)
                        {
                            Project->DistanceBasedForceFalloff.ScaleMultiplierAppliedAtStartRange = 999.f;
                            SetForceWaitTime = 0;
                        }
                    }
                    else
                    {
                        SetForceWaitTime++;
                        if (SetForceWaitTime > 20 && Project->DistanceBasedForceFalloff.ScaleMultiplierAppliedAtStartRange == 999.f)
                        {
                            Project->DistanceBasedForceFalloff.ScaleMultiplierAppliedAtStartRange = 1.f;
                            SetForceWaitTime = 0;
                        }
                    }
                    if (GunWeapon->CriticalHitEventGenerator!=nullptr)
                    {
                        if (枪械百分百暴击)
                        {
                            GunWeapon->CriticalHitEventGenerator->RegisteredChanceValue = 999.f;
                            GunWeapon->CriticalHitEventGenerator->InitializationCount = (uint16)0;
                        }
                        if (!枪械百分百暴击 && GunWeapon->CriticalHitEventGenerator->RegisteredChanceValue == 999.f)
                        {
                            GunWeapon->CriticalHitEventGenerator->RegisteredChanceValue = 0;
                            GunWeapon->CriticalHitEventGenerator->InitializationCount = (uint16)1;
                        }
                    }
                }
                #pragma endregion

              
             

            }
        }
    }
}


