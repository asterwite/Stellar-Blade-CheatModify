#pragma once
#include "..\����.h"
#include "..\Config\CofigLoodNeed.h"
class ESP_TEXT
{
public:
    bool ��ʾ���� = false;
public:
    void DrawESPTEXTUI();
    void ESPTXTE();
};
inline ESP_TEXT ESPTEXT;

inline void ESP_TEXT::DrawESPTEXTUI()
{
    ImGui::Checkbox((const char*)u8"��ʾ����", &��ʾ����);
}

inline void ESP_TEXT::ESPTXTE()
{
    ACharacter* pLocalPlayer = GetCharacter();
    if (!pLocalPlayer)
        return;
    APlayerController* pPlayerController = static_cast<APlayerController*>(pLocalPlayer->Controller);
    if (!pPlayerController)
        return;

    std::vector<AActor*> actors;
    if (!GetAllActorsofType(AActor::StaticClass(), &actors, true, true))
        return;

    auto draw = ImGui::GetBackgroundDrawList();

    auto actorsCount = actors.size();
    if (��ʾ����)
    {
         for (AActor* actor : actors)
         {
             
             if (actor && actor->IsA(ABP_Base_Zombie_C::StaticClass()))
             {
                 FVector actorLocation = actor->K2_GetActorLocation();
                 FVector localPlayerLocation = pLocalPlayer->K2_GetActorLocation();
                 FVector2D outScreen;
                 if (!pPlayerController->ProjectWorldLocationToScreen(actorLocation, &outScreen, true))
                     continue;
                 char data[0x256];
                 const char* ceshiStringData = (const char*)u8"��������: [%s]\n��ַ: [%p]\r";

                 sprintf_s(data, ceshiStringData, actor->GetName().c_str(), actor);
                 ImVec2 λ�� = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
                 draw->AddText(λ��, ImColor(255, 255, 255), data);
             }
         }
    }
}