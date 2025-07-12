#pragma once
#include "..\遍历.h"
#include "..\Vector3.h"
using namespace std;
class RaderCheat
{
public:
    bool   drawRadar = false;
    ImVec2   radarCenter = { 250,250 };  //雷达中心位置
    float   radarRadius = 200;     //雷达的显示半径
    int   radarCircleCount = 4;  //雷达同心圆数量
    float   radarDist = 3000;      //雷达的绘制距离，敌人超过这个距离，就不会显示在雷达上
    int   wndWidth = 1600;
    int   wndHeight = 900;
public:
    void DrawRaderUI();
    string RandomString(int32 len);
    void DrawRadarClean();
    void DrawRadarPanel();
    void DrawPlayerOnRadar(AActor* Myactor, USceneComponent* SceneComponent, ImU32 color);
    void DrawRadar();
};
inline RaderCheat Rader;
//UI绘制
inline void RaderCheat::DrawRaderUI()
{
    if (ImGui::CollapsingHeader((const char*)u8"雷达"))
    {
        ImGui::Columns(3, NULL, false);
        ImGui::Checkbox((const char*)u8"显示雷达", &drawRadar);

        static float tmpRadarDist = radarDist / 100;
        ImGui::Text((const char*)u8"最远距离:"); ImGui::SameLine(); ImGui::SetNextItemWidth(70);
        ImGui::DragFloat((const char*)u8"##radarDist", &tmpRadarDist, 0.2f, 1, 200, "%.0f");
        radarDist = tmpRadarDist * 100;
        ImGui::NextColumn();

        ImGui::Text((const char*)u8"坐标xy:"); ImGui::SameLine();
        ImGui::SetNextItemWidth(50);
        ImGui::DragFloat((const char*)u8"##radarX", &radarCenter.x, 1.f, 0, (float)wndWidth, "%.0f"); ImGui::SameLine();

        ImGui::SetNextItemWidth(50);
        ImGui::DragFloat((const char*)u8"##radarY", &radarCenter.y, 1.f, 0, (float)wndHeight, "%.0f");
        ImGui::Text((const char*)u8"圆数量:"); ImGui::SameLine(); ImGui::SetNextItemWidth(70);
        ImGui::DragInt((const char*)u8"##radarCircleCount", &radarCircleCount, 0.1f, 0, 20);
        ImGui::NextColumn();

        ImGui::Text((const char*)u8"半径:"); ImGui::SameLine(); ImGui::SetNextItemWidth(70);
        ImGui::DragFloat((const char*)u8"##radarRadius", &radarRadius, 1.f, 20, 500, "%.0f");
        ImGui::Columns(1);
    }
}

inline string RaderCheat::RandomString(int32 len)
{
    srand((uint32)time(NULL));
    string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string newstr;
    int32 pos;
    while (newstr.size() != len) {
        pos = ((rand() % (str.size() - 1)));
        newstr += str.substr(pos, 1);
    }
    return newstr;
}

inline void RaderCheat::DrawRadarClean()
{
    static auto wndName = RandomString(10);
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2((float)wndWidth, (float)wndHeight));
    ImGui::Begin(wndName.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar |
        ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
}

inline void RaderCheat::DrawRadarPanel()
{
    DrawRadarClean();
    ImVec2& center = radarCenter;
    float radius = radarRadius;
    int32 circleCount = radarCircleCount;

    //背景色和前景色
    ImU32 BG = IM_COL32(1, 1, 1, 150);
    ImU32 darkGreen = IM_COL32(0, 150, 0, 200);
    ImU32 brightGreen = IM_COL32(0, 250, 0, 200);

    ImDrawList* drawList = ImGui::GetWindowDrawList();
    drawList->AddCircleFilled(center, radius, BG); //背景

    if (circleCount > 0)
    {
        float spacing = radius / circleCount; // 两个同心圆之间的间隔
        for (int32 i = 1; i <= circleCount; ++i) {
            if (i == circleCount) {
                drawList->AddCircle(center, spacing * i, darkGreen, 0, 2.f); // 最外面的圆加粗
                continue;
            }
            drawList->AddCircle(center, spacing * i, darkGreen); // 绘制同心圆
        }
    }
    drawList->AddLine(ImVec2(center.x - radius, center.y), ImVec2(center.x + radius, center.y), brightGreen); // 水平线
    drawList->AddLine(ImVec2(center.x, center.y - radius), ImVec2(center.x, center.y + radius), brightGreen); // 垂直线

    //绘制雷达中心箭头，箭头由两个三角形组成，
    ImVec2 top, bottom, left, right;
    top = bottom = left = right = center;

    top.y -= 10;
    bottom.y += 4;
    left.x -= 8;
    left.y += 10;
    right.x += 8;
    right.y += 10;

    //drawList->AddTriangleFilled(top, bottom, left, darkGreen);
    //drawList->AddTriangleFilled(top, right, bottom, darkGreen);
}

//在雷达上绘制一个其他玩家的位置
inline void RaderCheat::DrawPlayerOnRadar(AActor* Myactor, USceneComponent* SceneComponent, ImU32 color)
{

    ImVec2& center = radarCenter;
    float radius = radarRadius;

    FVector Location = GetPlayerController()->PlayerCameraManager->CameraCachePrivate.POV.Location;
    float myYaw = GetPlayerController()->PlayerCameraManager->CameraCachePrivate.POV.Rotation.Yaw;
    //cout << "myPos x=" << myPos.x << ", y=" << myPos.y << ", z=" << myPos.z << endl;
    FVector Translation = SceneComponent->K2_GetComponentToWorld().Translation;

    float dX = Translation.X - Location.X;
    float dY = Translation.Y - Location.Y;
    float dist = (float)sqrt(dX * dX + dY * dY);
    if (dist > radarDist) {
        return;
    }

    //世界中的距离转换为屏幕像素距离
    dist = dist / radarDist * radius;


    //计算相对于相机的角度
    float angleRadian = (float)atan2(dX, dY);
    float angleDegree = ToDegree(angleRadian);

    //考虑到相机的 Yaw
    angleDegree = AnglesAdd(angleDegree, myYaw);

    //计算这个玩家距离雷达中心点的偏移，然后得到最终坐标
    angleRadian = ToRadian(angleDegree);
    float offsetCos = dist * cos(angleRadian);
    float offsetSin = dist * sin(angleRadian);
    ImVec2 finalPos = ImVec2(center.x + offsetCos, center.y - offsetSin);

    auto Zombie = reinterpret_cast<ABP_Base_Zombie_C*>(Myactor);
    if (!Zombie->MultiPartHealthComponent)
        return;
    if (Zombie ->MultiPartHealthComponent->Health <=0)
    {
        ImVec2 p = finalPos;
        ImGui::GetWindowDrawList()->AddLine(ImVec2(p.x - 5, p.y - 5), ImVec2(p.x + 5, p.y + 5), color);
        ImGui::GetWindowDrawList()->AddLine(ImVec2(p.x + 5, p.y - 5), ImVec2(p.x - 5, p.y + 5), color);
        return;
    }
    ImGui::GetWindowDrawList()->AddCircleFilled(finalPos, 5.0f, color);
    //计算这个玩家的朝向
    float playerYaw = SceneComponent->K2_GetComponentRotation().Yaw; // -180 到 180

    //修正朝向，这里是相减的
    playerYaw = AnglesAdd(playerYaw, myYaw * -1.0f);

    dist = 20;//向角色面向的方向绘制 20 像素的线
    angleRadian = ToRadian(playerYaw);
    offsetCos = dist * cos(angleRadian);
    offsetSin = dist * sin(angleRadian);
    ImVec2 faceTo = ImVec2(finalPos.x + offsetSin, finalPos.y - offsetCos);

    ImGui::GetWindowDrawList()->AddLine(finalPos, faceTo, color);
}

inline void RaderCheat::DrawRadar()
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
        if(!Myactor->IsA(ABP_Base_Zombie_C::StaticClass()))
            continue;
        if (Myactor->Instigator)
        {
            auto SceneComponent = Myactor->Instigator->RootComponent;
            DrawPlayerOnRadar(Myactor, SceneComponent, Red);
        }

    }
}
