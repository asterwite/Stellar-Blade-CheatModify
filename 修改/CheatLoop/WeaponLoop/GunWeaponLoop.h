#include "MeleeWeaponLoop.h"
class GunWeaponLoopCheat
{
public:
    bool �����ӵ� = false;
    bool �������ӳ� = false;
    int SpawnAmmoCount = 1;
    bool ǹе�и����� = false;
    bool ǹе����� = false;
    bool ǹе����֫�� = false;
    bool ǹе������� = false;
    bool ǹе����ƽ�� = false;

    bool ǹеһ����ɱ = false;
    bool ǹе�����ȶ�һ���ص� = false;
    bool ǹе�ٷְٱ��� = false;

    ABP_Base_RangedWeaponItem_C* PlayerGunWeapon;
private:
    bool ��ӡǹе��ַ = false;
    bool ��ӵ�ǰ�������õ�ҩ = false;
    bool ��ӵ�ǰ���� = false;
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
    if (ImGui::Button((const char*)u8"��ӡ��ǰǹе��ַ"))
    {
        ��ӡǹе��ַ = true;
    }
    ImGui::Checkbox((const char*)u8"�����ӵ���",&�����ӵ�);
    ImGui::SameLine();
    ImGui::Checkbox((const char*)u8"�������ӳ٣�ע��:�ᵼ��������޷������ʹ�ô�޵�������ҪƵ������������", &�������ӳ�);
    if (ImGui::Button((const char*)u8"������ǰ��������"))
    {
        ��ӵ�ǰ�������õ�ҩ = true;
    }
    ImGui::Checkbox((const char*)u8"ǹе�и�����", &ǹе�и�����);
    if (ǹе�и�����)
    {
        ImGui::Checkbox((const char*)u8"ǹе�����", &ǹе�����);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"ǹе����֫��", &ǹе����֫��);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"ǹе�������", &ǹе�������);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"ǹе����ƽ��", &ǹе����ƽ��);
    }
    ImGui::Checkbox((const char*)u8"ǹеһ����ɱ", &ǹеһ����ɱ);
    ImGui::Checkbox((const char*)u8"ǹе�����ȶ�һ���ص�", &ǹе�����ȶ�һ���ص�);
    ImGui::SameLine();
    ImGui::Checkbox((const char*)u8"ǹе�ٷְٱ���", &ǹе�ٷְٱ���);

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

                if (��ӡǹе��ַ)
                {
                    printf("ǹе��ַ: [%p]\t", Actor);
                    ��ӡǹе��ַ = false;
                }

                #pragma region ����
                #pragma endregion

                #pragma region ��ӱ����������ӵ����������ӳ�
                auto InventoryClipAmmoHandler = reinterpret_cast<UInventoryClipAmmoHandler*>(GunWeapon->RangedWeaponModulesComponent->CurrentWeaponConfiguration.SelectedAmmoHandler);
                if (��ӵ�ǰ�������õ�ҩ && InventoryClipAmmoHandler)
                {
                    GunWeapon->RangedWeaponModulesComponent->CurrentUserInventory->ServerAddItemByArchetype(InventoryClipAmmoHandler->RequiredAmmoType, InventoryClipAmmoHandler->RequiredAmmoType->StackSize, true);
                    ��ӵ�ǰ�������õ�ҩ = false;
                }
                if (�����ӵ�)
                {
                    SetAmmoWaitTime++;
                    if (SetAmmoWaitTime > 100)
                    {
                        InventoryClipAmmoHandler->ServerRequestAmmoSetToValue(99);
                        SetAmmoWaitTime = 0;
                    }
                }

                auto AttributeValue = GunWeapon->AttributesComponent->AttributeValueSet;
                if (�������ӳ� && AttributeValue.DelayBetweenShotsAttribute.Type->ModifierType->DefaultValueOverride == 1.f)
                    AttributeValue.DelayBetweenShotsAttribute.Type->ModifierType->DefaultValueOverride = 0;
                if (!�������ӳ� && AttributeValue.DelayBetweenShotsAttribute.Type->ModifierType->DefaultValueOverride == 0)
                    AttributeValue.DelayBetweenShotsAttribute.Type->ModifierType->DefaultValueOverride = 1.f;
                #pragma endregion

                #pragma region �ӵ��˺����и�����ȶ�һ���ص����ٷְٱ���
                auto Project = reinterpret_cast<UHitscanProjectileSpawnModule*>(GunWeapon->ShootActionParams->ShotHandler->ProjectileSpawner);
                if (Project)
                {
                    if (ǹеһ����ɱ&& Project->DistanceBasedDamageFalloff.ScaleMultiplierAppliedAtStartRange!=9999.f)
                            Project->DistanceBasedDamageFalloff.ScaleMultiplierAppliedAtStartRange = 9999.f;
                    if(!ǹеһ����ɱ && Project->DistanceBasedDamageFalloff.ScaleMultiplierAppliedAtStartRange == 9999.f)
                        Project->DistanceBasedDamageFalloff.ScaleMultiplierAppliedAtStartRange = 1.f;
                    if (ǹе�и�����)
                    {
                        if (ǹе�����)
                            Project->ImpactData.bCanCauseBreak = true;
                        if (ǹе����֫��)
                            Project->ImpactData.bCanCauseDismember = true;
                        if (ǹе�������)
                            Project->ImpactData.bCanCut = true;
                        if (ǹе����ƽ��)
                            Project->ImpactData.bCanCauseBisection = true;
                    }
                    if (ǹе�����ȶ�һ���ص� && Project->DistanceBasedForceFalloff.ScaleMultiplierAppliedAtStartRange == 1.f)
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
                        if (ǹе�ٷְٱ���)
                        {
                            GunWeapon->CriticalHitEventGenerator->RegisteredChanceValue = 999.f;
                            GunWeapon->CriticalHitEventGenerator->InitializationCount = (uint16)0;
                        }
                        if (!ǹе�ٷְٱ��� && GunWeapon->CriticalHitEventGenerator->RegisteredChanceValue == 999.f)
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


