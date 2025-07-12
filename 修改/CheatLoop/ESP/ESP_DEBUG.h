#pragma once
#include "..\遍历.h"
#include "..\Config\CofigLoodNeed.h"

class ESP_DEBUG
{
public:
    float ESP绘制距离 = 5.f;
    bool  启动绘制对象 = false;
    bool  显示对象名称 = false;
    bool  显示类名称 = false;
    bool  显示坐标位置 = false;
    bool  显示离我的距离 = false;
    bool  显示地址 = false;
    bool  显示全部 = false;
public:
    void DrawESP_DebugUI();
    float GetDistanceToActor(AActor* pLocal, AActor* pTarget);
    void ESP_Debug(float mDist, ImVec4 color);
};
inline ESP_DEBUG ESPDEBUG;

inline void ESP_DEBUG::DrawESP_DebugUI()
{
        ImGui::SliderFloat((const char*)u8"ESP绘制距离", &ESP绘制距离, 1.f, 1000.f, "%.0f");
        ImGui::Checkbox((const char*)u8"启动绘制对象", &启动绘制对象);
        if (启动绘制对象)
        {
            ImGui::Checkbox((const char*)u8"显示全部", &显示全部);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"显示对象名称", &显示对象名称);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"显示类名称", &显示类名称);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"显示坐标位置", &显示坐标位置);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"显示离我的距离", &显示离我的距离);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"显示地址", &显示地址);
        }
}

inline float ESP_DEBUG::GetDistanceToActor(AActor* pLocal, AActor* pTarget)
{
    if (!pLocal || !pTarget)
        return -1.f;

    FVector pLocation = pLocal->K2_GetActorLocation();
    FVector pTargetLocation = pTarget->K2_GetActorLocation();
    double distance = sqrt(pow(pTargetLocation.X - pLocation.X, 2.f) + pow(pTargetLocation.Y - pLocation.Y, 2.f) + pow(pTargetLocation.Z - pLocation.Z, 2.f));

    return distance / 100.0f;
}

inline void ESP_DEBUG::ESP_Debug(float mDist, ImVec4 color)
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
    for (AActor* actor : actors)
    {
        FVector actorLocation = actor->K2_GetActorLocation();
        FVector localPlayerLocation = pLocalPlayer->K2_GetActorLocation();
        float distanceTo = ESP_DEBUG::GetDistanceToActor(pLocalPlayer, actor);
        if (distanceTo > mDist)
            continue;

        FVector2D outScreen;
        if (!pPlayerController->ProjectWorldLocationToScreen(actorLocation, &outScreen, true))
            continue;
        char data[0x256];
        const char* duixiangStringData = (const char*)u8"对象名称: [%s]]";
        const char* leiStringData = (const char*)u8"\n类名称: [%s]]";
        const char* zuobiaoStringData = (const char*)u8"\n\n坐标位置: { %0.0f, %0.0f, %0.0f }";
        const char* liwojuliStringData = (const char*)u8"\n\n\n离我的距离: [%.0fm]";
        const char* quanbuStringData = (const char*)u8"对象名称: [%s]\n类名称: [%s]\n坐标位置: { %0.0f, %0.0f, %0.0f }\n离我的距离: [%.0fm]";
        const char* dizhiStringData = (const char*)u8"\n\n\n\n地址: [%p]\r";
        if (显示对象名称)
        {
            sprintf_s(data, duixiangStringData, actor->GetName().c_str());
            printf("对象名称: [%s]]\n", actor->GetName().c_str());
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (显示类名称)
        {
            sprintf_s(data, leiStringData, actor->Class->GetFullName().c_str());
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (显示坐标位置)
        {
            sprintf_s(data, zuobiaoStringData, actorLocation.X, actorLocation.Y, actorLocation.Z);
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (显示离我的距离)
        {
            sprintf_s(data, liwojuliStringData, distanceTo);
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (显示全部)
        {
            sprintf_s(data, quanbuStringData, actor->GetName().c_str(), actor->Class->GetFullName().c_str(), actorLocation.X, actorLocation.Y, actorLocation.Z, distanceTo);
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (显示地址)
        {
            sprintf_s(data, dizhiStringData, actor);
            ImVec2 地址 = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(地址, ImColor(color), data);
        }
    }
}


