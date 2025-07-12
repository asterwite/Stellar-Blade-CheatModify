#pragma once
#include "..\����.h"
#include "..\Config\CofigLoodNeed.h"

class ESP_DEBUG
{
public:
    float ESP���ƾ��� = 5.f;
    bool  �������ƶ��� = false;
    bool  ��ʾ�������� = false;
    bool  ��ʾ������ = false;
    bool  ��ʾ����λ�� = false;
    bool  ��ʾ���ҵľ��� = false;
    bool  ��ʾ��ַ = false;
    bool  ��ʾȫ�� = false;
public:
    void DrawESP_DebugUI();
    float GetDistanceToActor(AActor* pLocal, AActor* pTarget);
    void ESP_Debug(float mDist, ImVec4 color);
};
inline ESP_DEBUG ESPDEBUG;

inline void ESP_DEBUG::DrawESP_DebugUI()
{
        ImGui::SliderFloat((const char*)u8"ESP���ƾ���", &ESP���ƾ���, 1.f, 1000.f, "%.0f");
        ImGui::Checkbox((const char*)u8"�������ƶ���", &�������ƶ���);
        if (�������ƶ���)
        {
            ImGui::Checkbox((const char*)u8"��ʾȫ��", &��ʾȫ��);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"��ʾ��������", &��ʾ��������);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"��ʾ������", &��ʾ������);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"��ʾ����λ��", &��ʾ����λ��);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"��ʾ���ҵľ���", &��ʾ���ҵľ���);
            ImGui::SameLine();
            ImGui::Checkbox((const char*)u8"��ʾ��ַ", &��ʾ��ַ);
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
        const char* duixiangStringData = (const char*)u8"��������: [%s]]";
        const char* leiStringData = (const char*)u8"\n������: [%s]]";
        const char* zuobiaoStringData = (const char*)u8"\n\n����λ��: { %0.0f, %0.0f, %0.0f }";
        const char* liwojuliStringData = (const char*)u8"\n\n\n���ҵľ���: [%.0fm]";
        const char* quanbuStringData = (const char*)u8"��������: [%s]\n������: [%s]\n����λ��: { %0.0f, %0.0f, %0.0f }\n���ҵľ���: [%.0fm]";
        const char* dizhiStringData = (const char*)u8"\n\n\n\n��ַ: [%p]\r";
        if (��ʾ��������)
        {
            sprintf_s(data, duixiangStringData, actor->GetName().c_str());
            printf("��������: [%s]]\n", actor->GetName().c_str());
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (��ʾ������)
        {
            sprintf_s(data, leiStringData, actor->Class->GetFullName().c_str());
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (��ʾ����λ��)
        {
            sprintf_s(data, zuobiaoStringData, actorLocation.X, actorLocation.Y, actorLocation.Z);
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (��ʾ���ҵľ���)
        {
            sprintf_s(data, liwojuliStringData, distanceTo);
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (��ʾȫ��)
        {
            sprintf_s(data, quanbuStringData, actor->GetName().c_str(), actor->Class->GetFullName().c_str(), actorLocation.X, actorLocation.Y, actorLocation.Z, distanceTo);
            ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(screen, ImColor(color), data);
        }
        if (��ʾ��ַ)
        {
            sprintf_s(data, dizhiStringData, actor);
            ImVec2 ��ַ = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
            draw->AddText(��ַ, ImColor(color), data);
        }
    }
}


