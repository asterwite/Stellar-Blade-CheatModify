#pragma once
#include "..\Vector3.h"
#include "..\Vec.h"
#include "..\ESP\ESP_DEBUG.h"
//#include "..\ESP\ESPTEXT.h"
//#include "..\ESP\Rader.h"
using namespace std;
class GameLoopCheat
{
    public:
        bool 骨骼绘制 = false;;
        bool ESPTEXTForPeople = false;
        bool ESPFor2D = false;
        bool 线条绘制 = false;
        bool ESPFor3D = false;
        bool 角盒绘制 = false;
        bool 血量显示 = false;
        bool 文本显示 = false;
        bool 启动自瞄 = false;
        bool 鼠标自瞄 = false;
        bool 显示自瞄范围 = false;
        float 自瞄FOV = 500.f;
        float 自瞄范围 = false;
        float 平滑 = 1.f;
        bool 自瞄僵尸 = false;
        bool 子弹追踪 = false;
private:
    FVector Head;
public:
    void DrawESPUI();
    float GetESPDistanceToActor(AActor* pLocal, AActor* pTarget);
    void DrawCircle(Vec2 pos, float r, ImColor color, int segments = 12, float t = 1.f);
    void DrawBoneNeed(ACharacter* character,APlayerController* PlayerController, AActor* Myactor);
    void DrawLineFVector(FVector2D posA, FVector2D posB, ImColor color, float t = 1.f);
    void Draw3DBox(FVector& center, FVector& Bounds, SDK::APlayerController* Controller, ImColor col);
    void ESPFor3DDraw(AActor* Myactor, ASBCharacter* Character, APlayerController* pPlayerController);
    void ESPFor2DDraw(AActor* Myactor,ACharacter* character, APlayerController* pPlayerController, USkeletalMeshComponent* mesh, ImVec2 DrawTop, ImVec2 DrawBottom);
    void DrawTextForPeople(AActor* Myactor, FVector2D outScreen,float hp);
    void DrawLine(Vec2 A, Vec2 B, ImColor color, float t = 1.f);
    void DrawCorneredBox(Vec2 A, Vec2 B, float w, float h, ImColor color);
    void ESPForCorneredBoxDraw(AActor* Myactor,FVector2D Top, FVector2D Bottom, double w, double h);
    void ESPForLineDraw(AActor* Myactor,FVector2D Top);
    void DrawBoxFilled(Vec2 A, Vec2 B, ImColor color, float rounding = 0.f, float t = 1.f);
    void ESPForHealthDraw(AActor* Myactor, ASBCharacter* Character, FVector2D Top, FVector2D Bottom, double w, double h);
    void MainLoop(float mDist);
};
inline GameLoopCheat GameLoop;

inline void GameLoopCheat::DrawESPUI()
{
    if (ImGui::CollapsingHeader((const char*)u8"透视"))
    {
        ESPDEBUG.DrawESP_DebugUI();
        ImGui::Checkbox((const char*)u8"线条绘制", &线条绘制);
        ImGui::SameLine();
        ImGuiHelpMarker((const char*)u8"这这这谁把线条绘我窗口上的？？");
        ImGui::Checkbox((const char*)u8"文本显示", &文本显示);
        ImGui::SameLine();
        ImGuiHelpMarker((const char*)u8"我没开");
        ImGui::Checkbox((const char*)u8"骨骼绘制", &骨骼绘制);
        ImGui::SameLine();
        ImGuiHelpMarker((const char*)u8"我真没开");

    }
    //Rader.DrawRaderUI();
    if (ImGui::CollapsingHeader((const char*)u8"自瞄"))
    {
        ImGui::Checkbox((const char*)u8"启动自瞄（由于没有找到血量判断，所以容易锁尸体）", &启动自瞄);
        ImGui::SameLine();
        ImGuiHelpMarker((const char*)u8"我引以为傲的自瞄，你们居然说我是实力");
        {
            if (启动自瞄)
            {
                ImGui::Checkbox((const char*)u8"显示范围", &显示自瞄范围);
                ImGui::SliderFloat((const char*)u8"自瞄范围", &自瞄FOV, 5.f, 3000.f);
                ImGui::Checkbox((const char*)u8"子弹追踪（按住左键）", &子弹追踪);
            }     
        }
    }
}

inline float GameLoopCheat::GetESPDistanceToActor(AActor* pLocal, AActor* pTarget)
{
    if (!pLocal || !pTarget)
        return -1.f;

    FVector pLocation = pLocal->K2_GetActorLocation();
    FVector pTargetLocation = pTarget->K2_GetActorLocation();
    double distance = sqrt(pow(pTargetLocation.X - pLocation.X, 2.f) + pow(pTargetLocation.Y - pLocation.Y, 2.f) + pow(pTargetLocation.Z - pLocation.Z, 2.f));

    return distance / 100.0f;
}

inline void  GameLoopCheat::DrawCircle(Vec2 pos, float r, ImColor color, int segments, float t)
{
   ImGui::GetBackgroundDrawList()->AddCircle(pos.ToImVec2(), r, color, segments, t);
}

inline void  GameLoopCheat::DrawBoneNeed(ACharacter* character,APlayerController* PlayerController, AActor* Myactor)
{
    FVector2D BoneDraw1, BoneDraw2, BoneDraw3, BoneDraw4, BoneDraw5, BoneDraw6, BoneDraw7, BoneDraw8, BoneDraw9, BoneDraw10, BoneDraw11, BoneDraw12, BoneDraw13, BoneDraw14,
        BoneDraw15, BoneDraw16, BoneDraw17, BoneDraw18, BoneDraw19, BoneDraw20, BoneDraw21, BoneDraw22;
    auto draw = ImGui::GetBackgroundDrawList();

    //头到跨
    FName NeedBoneName = character->Mesh->GetSocketBoneName(StrToName("Bip001-Head"));
    FName NeedBoneName1 = character->Mesh->GetSocketBoneName(StrToName("Bip001-Neck"));
    FName NeedBoneName2 = character->Mesh->GetSocketBoneName(StrToName("Bip001-Spine2"));
    FName NeedBoneName3 = character->Mesh->GetSocketBoneName(StrToName("Bip001-Spine1"));
    FName NeedBoneName4 = character->Mesh->GetSocketBoneName(StrToName("Bip001-Spine"));
    //左手到右手
    FName NeedBoneName6 = character->Mesh->GetSocketBoneName(StrToName("Bip001-L-Hand"));
    FName NeedBoneName7 = character->Mesh->GetSocketBoneName(StrToName("Bip001-L-Forearm"));
    FName NeedBoneName8 = character->Mesh->GetSocketBoneName(StrToName("Bip001-L-UpperArm"));
    FName NeedBoneName9 = character->Mesh->GetSocketBoneName(StrToName("Bip001-Neck"));
    FName NeedBoneName10 = character->Mesh->GetSocketBoneName(StrToName("Bip001-R-UpperArm"));
    FName NeedBoneName11 = character->Mesh->GetSocketBoneName(StrToName("Bip001-R-Forearm"));
    FName NeedBoneName12 = character->Mesh->GetSocketBoneName(StrToName("Bip001-R-Hand"));
    //左脚到右脚
    FName NeedBoneName14 = character->Mesh->GetSocketBoneName(StrToName("Bip001-L-Foot"));
    FName NeedBoneName15 = character->Mesh->GetSocketBoneName(StrToName("Bip001-L-Calf"));
    FName NeedBoneName16 = character->Mesh->GetSocketBoneName(StrToName("Bip001-L-Thigh"));
    FName NeedBoneName17 = character->Mesh->GetSocketBoneName(StrToName("Bip001-Spine"));
    FName NeedBoneName18 = character->Mesh->GetSocketBoneName(StrToName("Bip001-R-Thigh"));
    FName NeedBoneName19 = character->Mesh->GetSocketBoneName(StrToName("Bip001-R-Calf"));
    FName NeedBoneName20 = character->Mesh->GetSocketBoneName(StrToName("Bip001-R-Foot"));


    //头到跨
    FVector Bone1 = character->Mesh->GetSocketLocation(NeedBoneName);
    FVector Bone2 = character->Mesh->GetSocketLocation(NeedBoneName1);
    FVector Bone3 = character->Mesh->GetSocketLocation(NeedBoneName2);
    FVector Bone4 = character->Mesh->GetSocketLocation(NeedBoneName3);
    FVector Bone5 = character->Mesh->GetSocketLocation(NeedBoneName4);

    //左手到右手
    FVector Bone7 = character->Mesh->GetSocketLocation(NeedBoneName6);
    FVector Bone8 = character->Mesh->GetSocketLocation(NeedBoneName7);
    FVector Bone9 = character->Mesh->GetSocketLocation(NeedBoneName8);
    FVector Bone10 = character->Mesh->GetSocketLocation(NeedBoneName9);
    FVector Bone11 = character->Mesh->GetSocketLocation(NeedBoneName10);
    FVector Bone12 = character->Mesh->GetSocketLocation(NeedBoneName11);
    FVector Bone13 = character->Mesh->GetSocketLocation(NeedBoneName12);
    //左脚到右脚
    FVector Bone15 = character->Mesh->GetSocketLocation(NeedBoneName14);
    FVector Bone16 = character->Mesh->GetSocketLocation(NeedBoneName15);
    FVector Bone17 = character->Mesh->GetSocketLocation(NeedBoneName16);
    FVector Bone18 = character->Mesh->GetSocketLocation(NeedBoneName17);
    FVector Bone19 = character->Mesh->GetSocketLocation(NeedBoneName18);
    FVector Bone20 = character->Mesh->GetSocketLocation(NeedBoneName19);
    FVector Bone21 = character->Mesh->GetSocketLocation(NeedBoneName20);

    //头到跨
    if (!PlayerController->ProjectWorldLocationToScreen(Bone1, &BoneDraw1, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone2, &BoneDraw2, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone3, &BoneDraw3, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone4, &BoneDraw4, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone5, &BoneDraw5, true))
        return;
    //左手到右手
    if (!PlayerController->ProjectWorldLocationToScreen(Bone7, &BoneDraw7, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone8, &BoneDraw8, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone9, &BoneDraw9, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone10, &BoneDraw10, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone11, &BoneDraw11, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone12, &BoneDraw12, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone13, &BoneDraw13, true))
        return;
    //左脚到右脚
    if (!PlayerController->ProjectWorldLocationToScreen(Bone15, &BoneDraw15, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone16, &BoneDraw16, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone17, &BoneDraw17, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone18, &BoneDraw18, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone19, &BoneDraw19, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone20, &BoneDraw20, true))
        return;
    if (!PlayerController->ProjectWorldLocationToScreen(Bone21, &BoneDraw21, true))
        return;

    //头到跨
    ImVec2 Headdraw1 = ImVec2((BoneDraw1.X), (BoneDraw1.Y));
    ImVec2 Headdraw2 = ImVec2((BoneDraw2.X), (BoneDraw2.Y));
    ImVec2 Headdraw3 = ImVec2((BoneDraw3.X), (BoneDraw3.Y));
    ImVec2 Headdraw4 = ImVec2((BoneDraw4.X), (BoneDraw4.Y));
    ImVec2 Headdraw5 = ImVec2((BoneDraw5.X), (BoneDraw5.Y));
    //左手到右手
    ImVec2 Headdraw7 = ImVec2((BoneDraw7.X), (BoneDraw7.Y));
    ImVec2 Headdraw8 = ImVec2((BoneDraw8.X), (BoneDraw8.Y));
    ImVec2 Headdraw9 = ImVec2((BoneDraw9.X), (BoneDraw9.Y));
    ImVec2 Headdraw10 = ImVec2((BoneDraw10.X), (BoneDraw10.Y));
    ImVec2 Headdraw11 = ImVec2((BoneDraw11.X), (BoneDraw11.Y));
    ImVec2 Headdraw12 = ImVec2((BoneDraw12.X), (BoneDraw12.Y));
    ImVec2 Headdraw13 = ImVec2((BoneDraw13.X), (BoneDraw13.Y));
    //左脚到右脚
    ImVec2 Headdraw15 = ImVec2((BoneDraw15.X), (BoneDraw15.Y));
    ImVec2 Headdraw16 = ImVec2((BoneDraw16.X), (BoneDraw16.Y));
    ImVec2 Headdraw17 = ImVec2((BoneDraw17.X), (BoneDraw17.Y));
    ImVec2 Headdraw18 = ImVec2((BoneDraw18.X), (BoneDraw18.Y));
    ImVec2 Headdraw19 = ImVec2((BoneDraw19.X), (BoneDraw19.Y));
    ImVec2 Headdraw20 = ImVec2((BoneDraw20.X), (BoneDraw20.Y));
    ImVec2 Headdraw21 = ImVec2((BoneDraw21.X), (BoneDraw21.Y));

        //头到跨
        draw->AddLine(Headdraw1, Headdraw2, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw2, Headdraw3, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw3, Headdraw4, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw4, Headdraw5, ImColor{ 33, 255, 0, 200 });

        //左手到右手

        draw->AddLine(Headdraw7, Headdraw8, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw8, Headdraw9, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw9, Headdraw10, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw10, Headdraw11, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw11, Headdraw12, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw12, Headdraw13, ImColor{ 33, 255, 0, 200 });

        //左脚到右脚

        draw->AddLine(Headdraw15, Headdraw16, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw16, Headdraw17, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw17, Headdraw18, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw18, Headdraw19, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw19, Headdraw20, ImColor{ 33, 255, 0, 200 });

        draw->AddLine(Headdraw20, Headdraw21, ImColor{ 33, 255, 0, 200 });
}


inline void  GameLoopCheat::DrawLineFVector(FVector2D posA, FVector2D posB, ImColor color, float t)
{
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(posA.X, posA.Y), ImVec2(posB.X, posB.Y), ImColor(0.f, 0.f, 0.f), t + 1.f);
    ImGui::GetBackgroundDrawList()->AddLine(ImVec2(posA.X, posA.Y), ImVec2(posB.X, posB.Y), color, t);
}

inline void GameLoopCheat::Draw3DBox(FVector& center, FVector& Bounds, SDK::APlayerController* Controller, ImColor col)
{
    const float wX = (center.X + Bounds.X) - (center.X - Bounds.X);
    const float wY = (center.Y + Bounds.Y) - (center.Y - Bounds.Y);

    FVector Top{ center.X, center.Y, center.Z + Bounds.Z };
    FVector Bottom{ center.X, center.Y, center.Z - Bounds.Z };

    FVector a1 = { center.X - wX / 2, center.Y + wY / 2, Bottom.Z };
    FVector a2 = { center.X + wX / 2, center.Y + wY / 2, Bottom.Z };
    FVector a3 = { center.X - wX / 2, center.Y - wY / 2, Bottom.Z };
    FVector a4 = { center.X + wX / 2, center.Y - wY / 2, Bottom.Z };

    FVector b1 = { center.X - wX / 2, center.Y + wY / 2, Top.Z };
    FVector b2 = { center.X + wX / 2, center.Y + wY / 2, Top.Z };
    FVector b3 = { center.X - wX / 2, center.Y - wY / 2, Top.Z };
    FVector b4 = { center.X + wX / 2, center.Y - wY / 2, Top.Z };

    FVector2D a1w2s{};
    FVector2D a2w2s{};
    FVector2D a3w2s{};
    FVector2D a4w2s{};

    FVector2D b1w2s{};
    FVector2D b2w2s{};
    FVector2D b3w2s{};
    FVector2D b4w2s{};

    if (Controller->ProjectWorldLocationToScreen(a1, &a1w2s, false) && Controller->ProjectWorldLocationToScreen(a2, &a2w2s, false)
        && Controller->ProjectWorldLocationToScreen(a3, &a3w2s, false) && Controller->ProjectWorldLocationToScreen(a4, &a4w2s, false)
        && Controller->ProjectWorldLocationToScreen(b1, &b1w2s, false) && Controller->ProjectWorldLocationToScreen(b2, &b2w2s, false)
        && Controller->ProjectWorldLocationToScreen(b3, &b3w2s, false) && Controller->ProjectWorldLocationToScreen(b4, &b4w2s, false))
    {
        DrawLineFVector(a1w2s, a2w2s, col, 1.f);
        DrawLineFVector(a2w2s, a4w2s, col, 1.f);
        DrawLineFVector(a4w2s, a3w2s, col, 1.f);
        DrawLineFVector(a3w2s, a1w2s, col, 1.f);

        DrawLineFVector(b1w2s, b2w2s, col, 1.f);
        DrawLineFVector(b2w2s, b4w2s, col, 1.f);
        DrawLineFVector(b4w2s, b3w2s, col, 1.f);
        DrawLineFVector(b3w2s, b1w2s, col, 1.f);

        DrawLineFVector(a1w2s, b1w2s, col, 1.f);
        DrawLineFVector(a2w2s, b2w2s, col, 1.f);
        DrawLineFVector(a3w2s, b3w2s, col, 1.f);
        DrawLineFVector(a4w2s, b4w2s, col, 1.f);
    }
}

inline void GameLoopCheat::ESPFor3DDraw(AActor* Myactor, ASBCharacter* Character, APlayerController* pPlayerController)
{

    FVector ActorCenter{};
    FVector ActorBoundsExtent{};
    Character->GetActorBounds(true, &ActorCenter, &ActorBoundsExtent, false);
     Draw3DBox(ActorCenter, ActorBoundsExtent, pPlayerController, White);

}

inline void GameLoopCheat::ESPFor2DDraw(AActor* Myactor, ACharacter* character, APlayerController* pPlayerController, USkeletalMeshComponent* mesh, ImVec2 DrawTop, ImVec2 DrawBottom)
{
        ImGui::GetBackgroundDrawList()->AddRect(DrawTop, DrawBottom, White, true);
}

inline void GameLoopCheat::DrawTextForPeople(AActor* Myactor, FVector2D outScreen,float dis)
{
        char data[0x256];
        const char* Text = (const char*)u8"\n名称:%s\n距离: [%.0fm]";
        sprintf_s(data, Text, Myactor->Name.ToString().c_str(), dis);
        ImVec2 screen = ImVec2(static_cast<float>(outScreen.X), static_cast<float>(outScreen.Y));
        ImGui::GetBackgroundDrawList()->AddText(screen, Bule, data);
}

inline void GameLoopCheat::DrawLine(Vec2 A, Vec2 B, ImColor color, float t)
{
    ImGui::GetBackgroundDrawList()->AddLine(A.ToImVec2(), B.ToImVec2(), Black, t + 1);
    ImGui::GetBackgroundDrawList()->AddLine(A.ToImVec2(), B.ToImVec2(), color, t);
}

inline void GameLoopCheat::DrawCorneredBox(Vec2 A, Vec2 B, float w, float h, ImColor color)
{
    const float wi = w / 3;
    const float hi = h / 3;

    DrawLine({ A.x - w, A.y }, { A.x - w + wi, A.y }, color);
    DrawLine({ A.x + w, A.y }, { A.x + w - wi, A.y }, color);

    DrawLine({ A.x - w, A.y }, { A.x - w, A.y + hi }, color);
    DrawLine({ A.x + w, A.y }, { A.x + w, A.y + hi }, color);

    DrawLine({ B.x - w, B.y }, { B.x - w + wi, B.y }, color);
    DrawLine({ B.x + w, B.y }, { B.x + w - wi, B.y }, color);

    DrawLine({ B.x - w, B.y }, { B.x - w, B.y - hi }, color);
    DrawLine({ B.x + w, B.y }, { B.x + w, B.y - hi }, color);
}

inline void GameLoopCheat::ESPForCorneredBoxDraw(AActor* Myactor,FVector2D Top, FVector2D Bottom, double w, double h)
{
        DrawCorneredBox(Vec2(Top.X + 1, Top.Y + 1), Vec2(Bottom.X - 1, Bottom.Y - 1), w, h, Black);
        DrawCorneredBox(Vec2(Top.X - 1, Top.Y - 1), Vec2(Bottom.X + 1, Bottom.Y + 1), w, h, Black);
        DrawCorneredBox(Vec2(Top.X, Top.Y), Vec2(Bottom.X, Bottom.Y), w, h, White);
}

inline void GameLoopCheat::ESPForLineDraw(AActor* Myactor,FVector2D Top)
{
            ImVec2 Draw1 = ImVec2(1920 / 2, 0);
            ImVec2 Draw2 = ImVec2((Top.X), (Top.Y));
            ImGui::GetBackgroundDrawList()->AddLine(Draw1, Draw2, White, true);
}

inline void GameLoopCheat::DrawBoxFilled(Vec2 A, Vec2 B, ImColor color, float rounding , float t)
{
    ImGui::GetBackgroundDrawList()->AddRectFilled(A.ToImVec2(), B.ToImVec2(), color, rounding);
}

inline void GameLoopCheat::ESPForHealthDraw(AActor* Myactor, ASBCharacter* Character, FVector2D Top, FVector2D Bottom, double w, double h)
{

        DrawBoxFilled(Vec2(Top.X - w - 6, Top.Y - 1), Vec2(Top.X - w - 3, Bottom.Y + 1), Black);
        //DrawBoxFilled(Vec2(Top.X - w - 5, Bottom.Y - (h * (Zombie->MultiPartHealthComponent->Health * 0.0001) / 3.5f)), Vec2(Top.X - w - 4, Bottom.Y), Green);
}

inline void GameLoopCheat::MainLoop(float mDist)
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

    for (AActor* Myactor : actors)
    {
        if (Myactor && Myactor->IsA(ASBProjectile::StaticClass()) && 子弹追踪)
        {
            auto Project = reinterpret_cast<ASBProjectile*>(Myactor);
            Project->K2_SetActorLocation(Head, false, nullptr, true);
            FRotator Rotator = { 1.f,1.f,1.f };
            Project->K2_TeleportTo(Head, Rotator);
        }
        if (Myactor && Myactor->IsA(ASBCharacter::StaticClass()))
        {
            float MaxDistance = FLT_MAX;
            bool 可以自瞄 = false;
            auto character = reinterpret_cast<ACharacter*>(Myactor);
            FVector localPlayerLocation = pLocalPlayer->K2_GetActorLocation();
            USkeletalMeshComponent* mesh = character->Mesh;
            auto Character = reinterpret_cast<ASBCharacter*>(Myactor);
            if (!mesh)
                continue;
            if (!Myactor->Name.ToString().contains("CH_M_NA"))
                continue;
            if (启动自瞄)
            {
                if (pPlayerController->LineOfSightTo(Myactor, pPlayerController->PlayerCameraManager->CameraCachePrivate.POV.Location, false))
                    可以自瞄 = true;
                else
                    可以自瞄 = false;
                auto CameraLocation = pPlayerController->PlayerCameraManager->GetCameraLocation();
                FVector head_bone_pos = mesh->GetSocketLocation(StrToName("Bip001-Spine1"));
                auto rot = UKismetMathLibrary::FindLookAtRotation(CameraLocation, Myactor->K2_GetActorLocation());
                FVector2D screen_middle = { 1920 / 2, 1080 / 2 };
                FVector2D Top;
                FRotator closest_actor_rotation;
                FVector closest_actor_head;
                AActor* closest_actor{};
                if (!pPlayerController->ProjectWorldLocationToScreen(head_bone_pos, &Top, false))
                    continue;

                自瞄范围 = UKismetMathLibrary::Distance2D(Top, screen_middle);
                if (自瞄范围 < MaxDistance && 自瞄范围 <= 自瞄FOV)
                {
                     closest_actor = Myactor;
                    closest_actor_rotation = rot;
                    closest_actor_head = head_bone_pos;
                }
                if (closest_actor && GetAsyncKeyState(VK_LBUTTON) && 可以自瞄 && 子弹追踪)
                    Head = closest_actor_head;

             }


            float distanceTo = GetESPDistanceToActor(pLocalPlayer, Myactor);
            if (distanceTo > mDist)
                continue;
            if(骨骼绘制)
               DrawBoneNeed(character, pPlayerController, Myactor);
            FVector2D outScreen;
            FVector2D Bottom{};
            FVector2D Top{};
            FVector2D Middle{};
            FVector  Location = character->K2_GetActorLocation();
            if (!pPlayerController->ProjectWorldLocationToScreen(Location, &Middle, false)) continue;
            FVector feet = mesh->GetSocketLocation(StrToName("Bip001-R-Foot"));
            FVector Head = mesh->GetSocketLocation(StrToName("Bip001-L-Head"));
            if (pPlayerController->ProjectWorldLocationToScreen(feet, &Bottom, false) && pPlayerController->ProjectWorldLocationToScreen(Head, &Top, false))
            {
                double h = std::abs(Top.Y - Bottom.Y);
                double w = h * 0.2;
                ImVec2 DrawTop = ImVec2((Top.X - w), (Top.Y));
                ImVec2 DrawBottom = ImVec2((Bottom.X + w), (Bottom.Y));
                if (角盒绘制)
                ESPForCorneredBoxDraw(Myactor,Top, Bottom, w, h);
                if (文本显示)
                DrawTextForPeople(Myactor,Top,distanceTo);
                //if (血量显示)
                //ESPForHealthDraw(Myactor, Zombie, Top, Bottom, w, h);
                if (线条绘制)
                ESPForLineDraw(Myactor,Top);
            }
        }
    }
}