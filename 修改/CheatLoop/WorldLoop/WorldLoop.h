#pragma once
#include "..\Cheat\Cheat.h"
#include "..\����.h"
#include "..\GameLoop\GameLoop.h"
class WorldLoopCheat
{
public:
    bool ����͸�� = false;
    bool ����͸��δ�� = false;
    bool ����͸���Ѵ� = false;
    bool ��Ʒ͸�� = false;
    bool ������ֽ͸�� = false;
    bool ���͵�͸�� = false;
    bool Ӫ��͸�� = false;
    bool ���������� = false;
    float ��Ϸ�ٶ� = 1.f;
private:
    bool Bonce = false;
    float WorldZ = false;
    float PlayerGravityScale = 0;
public:
    void DrawWorldUI();
    void WorldCheat();

}; inline WorldLoopCheat WorldLoop;
inline void WorldLoopCheat::DrawWorldUI()
{
    ImGui::SliderFloat((const char*)u8"��Ϸ�ٶ�", &��Ϸ�ٶ�, 1.f, 20.f);

    ImGui::Checkbox((const char*)u8"����͸�ӣ�����͸�ӣ�", &����͸��);
    if (����͸��)
    {
        ImGui::Checkbox((const char*)u8"����͸��δ�򿪣�ע�ⲿ�ֿ����������Ѵ򿪵ģ�", &����͸��δ��);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"����͸���Ѵ򿪣�ע�ⲿ�ֿ�����δ�򿪵����ӣ�", &����͸���Ѵ�);
    }
    ImGui::Checkbox((const char*)u8"��Ʒ͸��", &��Ʒ͸��);
    ImGui::Checkbox((const char*)u8"������ֽ͸��", &������ֽ͸��);
    ImGui::Checkbox((const char*)u8"���͵�͸��", &���͵�͸��);
    ImGui::Checkbox((const char*)u8"Ӫ��͸��", &Ӫ��͸��);
    ImGui::Checkbox((const char*)u8"���������������������Ծ���հ�shift��̼����������䣩", &����������);
}

inline void WorldLoopCheat::WorldCheat()
{
    GetUWorld()->PersistentLevel->WorldSettings->TimeDilation = ��Ϸ�ٶ�;
    if (!Bonce)
        WorldZ = GetUWorld()->PersistentLevel->WorldSettings->WorldGravityZ;
    if (����������)
    {
        Bonce = true;
        GetUWorld()->PersistentLevel->WorldSettings->bWorldGravitySet = (uint8)1;
        GetUWorld()->PersistentLevel->WorldSettings->WorldGravityZ = 0;
    }
    if(!����������&& Bonce)
    {
        Bonce = false;
        GetUWorld()->PersistentLevel->WorldSettings->bWorldGravitySet = (uint8)0;
    }

    std::vector<AActor*> actors;
    if (!GetAllActorsofType(AActor::StaticClass(), &actors, true, true))
        return;
    for (AActor* Myactor : actors)
    {
        FVector actorLocation = Myactor->K2_GetActorLocation();
        FVector2D Top{};


        #pragma region ����͸��
         if (Myactor->Name.ToString().contains("Env_SupplyBox"))
         {
         
             if (����͸��)
             {
                 auto Box = reinterpret_cast<ASBZoneEnvActor*>(Myactor);
                 if (Box->bActiveActor && ����͸��δ��)
                 {
                     if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                     {
                         GameLoop.ESPForLineDraw(Myactor, Top);
                         char data[0x256];
                         const char* liwojuliStringData = (const char*)u8"\n����: [%.0fm]\n��ַ: [%p]\r";
                         auto draw = ImGui::GetBackgroundDrawList();
                         float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                         sprintf_s(data, liwojuliStringData, distanceTo, Myactor, Box->HaveBufferData());
                         ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                         draw->AddText(screen, White, (const char*)u8"δ�򿪵�����");
                         draw->AddText(screen, White, data);
                     }
                 }
                 if (!Box->bActiveActor && ����͸���Ѵ�)
                 {
                     if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                     {
                         GameLoop.ESPForLineDraw(Myactor, Top);
                         char data[0x256];
                         const char* liwojuliStringData = (const char*)u8"\n����: [%.0fm]\n��ַ: [%p]\r";
                         auto draw = ImGui::GetBackgroundDrawList();
                         float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                         sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                         ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                         draw->AddText(screen, White, (const char*)u8"�Ѵ򿪵�����");
                         draw->AddText(screen, White, data);
                     }
                 }
             }
         }
        #pragma endregion


        #pragma region ��Ʒ͸��
         if (Myactor->Name.ToString().contains("BP_Item"))
         {
             if (��Ʒ͸��)
             {
                 if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                 {
                     GameLoop.ESPForLineDraw(Myactor, Top);
                     char data[0x256];
                     const char* liwojuliStringData = (const char*)u8"\n����: [%.0fm]\n��ַ: [%p]\r";
                     auto draw = ImGui::GetBackgroundDrawList();
                     float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                     sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                     ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                     draw->AddText(screen, White, (const char*)u8"��ʰȡ��Ʒ");
                     draw->AddText(screen, White, data);
                 }
             }
         }
        #pragma endregion
      

        #pragma region ������ֽ͸��
                 if (Myactor->Name.ToString().contains("PhotoChallengeDecal"))
                 {
                     if (������ֽ͸��)
                     {
                         if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                         {
                             GameLoop.ESPForLineDraw(Myactor, Top);
                             char data[0x256];
                             const char* liwojuliStringData = (const char*)u8"\n����: [%.0fm]\n��ַ: [%p]\r";
                             auto draw = ImGui::GetBackgroundDrawList();
                             float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                             sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                             ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                             draw->AddText(screen, White, (const char*)u8"��������ֽ");
                             draw->AddText(screen, White, data);
                         }
                     }
                 }
        #pragma endregion


        #pragma region ���͵�͸��
               if (Myactor->Name.ToString().contains("TeleportMachine"))
               {
                   if (���͵�͸��)
                   {
                       if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                       {
                           GameLoop.ESPForLineDraw(Myactor, Top);
                           char data[0x256];
                           const char* liwojuliStringData = (const char*)u8"\n����: [%.0fm]\n��ַ: [%p]\r";
                           auto draw = ImGui::GetBackgroundDrawList();
                           float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                           sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                           ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                           draw->AddText(screen, White, (const char*)u8"���͵�");
                           draw->AddText(screen, White, data);
                       }
                   }
               }
        #pragma endregion
                 
     
        #pragma region Ӫ��͸��
           if (Myactor->Name.ToString().contains("SkillMachine"))
           {
               if (Ӫ��͸��)
               {
                   if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                   {
                       GameLoop.ESPForLineDraw(Myactor, Top);
                       char data[0x256];
                       const char* liwojuliStringData = (const char*)u8"\n����: [%.0fm]\n��ַ: [%p]\r";
                       auto draw = ImGui::GetBackgroundDrawList();
                       float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                       sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                       ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                       draw->AddText(screen, White, (const char*)u8"Ӫ��");
                       draw->AddText(screen, White, data);
                   }
               }
           }
        #pragma endregion
    }
}
UListView;
UWorldSubsystem;
UKismetGuidLibrary;

#pragma region MyRegion

#pragma endregion

