#pragma once
#include "..\Cheat\Cheat.h"
#include "..\遍历.h"
#include "..\GameLoop\GameLoop.h"
class WorldLoopCheat
{
public:
    bool 箱子透视 = false;
    bool 箱子透视未打开 = false;
    bool 箱子透视已打开 = false;
    bool 物品透视 = false;
    bool 拍照贴纸透视 = false;
    bool 传送点透视 = false;
    bool 营地透视 = false;
    bool 世界无重力 = false;
    float 游戏速度 = 1.f;
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
    ImGui::SliderFloat((const char*)u8"游戏速度", &游戏速度, 1.f, 20.f);

    ImGui::Checkbox((const char*)u8"箱子透视（垃圾透视）", &箱子透视);
    if (箱子透视)
    {
        ImGui::Checkbox((const char*)u8"箱子透视未打开（注意部分可能依旧是已打开的）", &箱子透视未打开);
        ImGui::SameLine();
        ImGui::Checkbox((const char*)u8"箱子透视已打开（注意部分可能是未打开的箱子）", &箱子透视已打开);
    }
    ImGui::Checkbox((const char*)u8"物品透视", &物品透视);
    ImGui::Checkbox((const char*)u8"拍照贴纸透视", &拍照贴纸透视);
    ImGui::Checkbox((const char*)u8"传送点透视", &传送点透视);
    ImGui::Checkbox((const char*)u8"营地透视", &营地透视);
    ImGui::Checkbox((const char*)u8"世界无重力（如果本人跳跃浮空按shift冲刺即可正常降落）", &世界无重力);
}

inline void WorldLoopCheat::WorldCheat()
{
    GetUWorld()->PersistentLevel->WorldSettings->TimeDilation = 游戏速度;
    if (!Bonce)
        WorldZ = GetUWorld()->PersistentLevel->WorldSettings->WorldGravityZ;
    if (世界无重力)
    {
        Bonce = true;
        GetUWorld()->PersistentLevel->WorldSettings->bWorldGravitySet = (uint8)1;
        GetUWorld()->PersistentLevel->WorldSettings->WorldGravityZ = 0;
    }
    if(!世界无重力&& Bonce)
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


        #pragma region 箱子透视
         if (Myactor->Name.ToString().contains("Env_SupplyBox"))
         {
         
             if (箱子透视)
             {
                 auto Box = reinterpret_cast<ASBZoneEnvActor*>(Myactor);
                 if (Box->bActiveActor && 箱子透视未打开)
                 {
                     if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                     {
                         GameLoop.ESPForLineDraw(Myactor, Top);
                         char data[0x256];
                         const char* liwojuliStringData = (const char*)u8"\n距离: [%.0fm]\n地址: [%p]\r";
                         auto draw = ImGui::GetBackgroundDrawList();
                         float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                         sprintf_s(data, liwojuliStringData, distanceTo, Myactor, Box->HaveBufferData());
                         ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                         draw->AddText(screen, White, (const char*)u8"未打开的箱子");
                         draw->AddText(screen, White, data);
                     }
                 }
                 if (!Box->bActiveActor && 箱子透视已打开)
                 {
                     if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                     {
                         GameLoop.ESPForLineDraw(Myactor, Top);
                         char data[0x256];
                         const char* liwojuliStringData = (const char*)u8"\n距离: [%.0fm]\n地址: [%p]\r";
                         auto draw = ImGui::GetBackgroundDrawList();
                         float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                         sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                         ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                         draw->AddText(screen, White, (const char*)u8"已打开的箱子");
                         draw->AddText(screen, White, data);
                     }
                 }
             }
         }
        #pragma endregion


        #pragma region 物品透视
         if (Myactor->Name.ToString().contains("BP_Item"))
         {
             if (物品透视)
             {
                 if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                 {
                     GameLoop.ESPForLineDraw(Myactor, Top);
                     char data[0x256];
                     const char* liwojuliStringData = (const char*)u8"\n距离: [%.0fm]\n地址: [%p]\r";
                     auto draw = ImGui::GetBackgroundDrawList();
                     float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                     sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                     ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                     draw->AddText(screen, White, (const char*)u8"可拾取物品");
                     draw->AddText(screen, White, data);
                 }
             }
         }
        #pragma endregion
      

        #pragma region 拍照贴纸透视
                 if (Myactor->Name.ToString().contains("PhotoChallengeDecal"))
                 {
                     if (拍照贴纸透视)
                     {
                         if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                         {
                             GameLoop.ESPForLineDraw(Myactor, Top);
                             char data[0x256];
                             const char* liwojuliStringData = (const char*)u8"\n距离: [%.0fm]\n地址: [%p]\r";
                             auto draw = ImGui::GetBackgroundDrawList();
                             float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                             sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                             ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                             draw->AddText(screen, White, (const char*)u8"可拍摄贴纸");
                             draw->AddText(screen, White, data);
                         }
                     }
                 }
        #pragma endregion


        #pragma region 传送点透视
               if (Myactor->Name.ToString().contains("TeleportMachine"))
               {
                   if (传送点透视)
                   {
                       if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                       {
                           GameLoop.ESPForLineDraw(Myactor, Top);
                           char data[0x256];
                           const char* liwojuliStringData = (const char*)u8"\n距离: [%.0fm]\n地址: [%p]\r";
                           auto draw = ImGui::GetBackgroundDrawList();
                           float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                           sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                           ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                           draw->AddText(screen, White, (const char*)u8"传送点");
                           draw->AddText(screen, White, data);
                       }
                   }
               }
        #pragma endregion
                 
     
        #pragma region 营地透视
           if (Myactor->Name.ToString().contains("SkillMachine"))
           {
               if (营地透视)
               {
                   if (GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false) && GetPlayerController()->ProjectWorldLocationToScreen(actorLocation, &Top, false))
                   {
                       GameLoop.ESPForLineDraw(Myactor, Top);
                       char data[0x256];
                       const char* liwojuliStringData = (const char*)u8"\n距离: [%.0fm]\n地址: [%p]\r";
                       auto draw = ImGui::GetBackgroundDrawList();
                       float distanceTo = ESPDEBUG.GetDistanceToActor(GetCharacter(), Myactor);
                       sprintf_s(data, liwojuliStringData, distanceTo, Myactor);
                       ImVec2 screen = ImVec2(static_cast<float>(Top.X), static_cast<float>(Top.Y));
                       draw->AddText(screen, White, (const char*)u8"营地");
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

