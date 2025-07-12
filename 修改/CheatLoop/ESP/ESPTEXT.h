#pragma once
#include "..\遍历.h"
#include "..\Config\CofigLoodNeed.h"
class ESP_TEXT
{
public:
    bool 显示测试 = false;
public:
    void DrawESPTEXTUI();
    void ESPTXTE();
};
inline ESP_TEXT ESPTEXT;

inline void ESP_TEXT::DrawESPTEXTUI()
{
    ImGui::Checkbox((const char*)u8"显示测试", &显示测试);
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
    if (显示测试)
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
                 const char* ceshiStringData = (const char*)u8"对象名称: [%s]\n地址: [%p]\r";

                 sprintf_s(data, ceshiStringData, actor->GetName().c_str(), actor);
                 ImVec2 位置 = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
                 draw->AddText(位置, ImColor(255, 255, 255), data);
             }
         }
    }
}