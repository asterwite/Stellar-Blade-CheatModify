#pragma once
#include "..\Config\CofigLoodNeed.h"
#include "..\Cheat\Cheat.h"
#include "KeySet.h"
class FPSUnlockCheat
{
public:
	bool 启动 = false;
	bool 设置自定义帧数 = false;
	float 默认帧数 = 144.f;
	float 自定义帧数 = 144.f;
	float 最大帧数 = 540.0f;
	float 正常帧数 = 60.0f;
	float FPS = 144;
	bool 无限 = true;
	bool 启用FPS = false;
	bool 显示FPS = true; // True by default;
	int ShowMenu = VK_INSERT;
private:
	bool bOnce = false;
public:
	void DrawFPS();
	void DrawFPSUlockUI();
	void RunFPSUlock();
};
inline FPSUnlockCheat FPSUnlock;

inline bool g_IsSettingKey = false; // 热键设置状态

inline KeyBind g_LaunchKey(KeyBind::KeyCode::INSERT); // 默认热键为INSERT

inline KeyBind LastKey;

inline bool HandleKeySetting() {
	// 取消设置（ESC）
	if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
		if(LastKey != g_LaunchKey)
		g_LaunchKey = KeyBind(KeyBind::KeyCode::INSERT); // 恢复默认
		g_LaunchKey = LastKey;
		return true;
	}

	// 遍历所有按键
	for (int i = 0; i < IM_ARRAYSIZE(ImGui::GetIO().KeysDown); ++i) {
		if (ImGui::IsKeyPressed(static_cast<ImGuiKey>(i))) {
			// 查找keyMap（使用data()比较）
			auto it = std::find_if(keyMap.begin(), keyMap.end(),
				[i](const Key& k) { return k.code == i; });

			if (it != keyMap.end() && it->name != "NONE") {
				// 更新热键（使用data()获取字符串）
				g_LaunchKey = KeyBind(it->name.data()); // 注意：KeyBind构造函数需接受const char*
				LastKey = KeyBind(it->name.data());
				return true;
			}
		}
	}
	return false;
}


inline void FPSUnlockCheat::DrawFPSUlockUI()
{
	ImGui::Checkbox((const char*)u8"显示FPS", &显示FPS);
	ImGui::SliderFloat((const char*)u8" ", &自定义帧数,0.f,1000.f);
	ImGui::Text((const char*)u8"自定义游戏帧数上限（解锁FPS上限，游戏默认无限制，我只是做个测试）");
	if (ImGui::Button((const char*)u8"确认"))
	{
		GetGameUserSettings()->SetFrameRateLimit(自定义帧数);
		GetGameUserSettings()->ApplySettings(true);
	}

	if (ImGui::CollapsingHeader((const char*)u8"按键修改"))
	{
		ImGui::Text((const char*)u8"当前呼出按键: %s", g_LaunchKey.toString());

		// 热键设置按钮
		if (ImGui::Button((const char*)u8"修改呼出按键", ImVec2(150, 25))) {
			g_IsSettingKey = true; // 进入设置模式
		}

		// 热键设置逻辑
		if (g_IsSettingKey) {
			ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"按下新按键");
			ImGui::TextColored(ImVec4(1, 1, 1, 1), (const char*)u8"(按ESC取消，按任意键确认，按下后会关闭窗口，重新按你设置的按键即可)");

			// 处理按键输入
			if (HandleKeySetting())
			{
				ShowMenu = g_LaunchKey.toInt();
				g_IsSettingKey = false; // 完成设置后退出模式
				printf(g_LaunchKey.toString());
			}
		}
	}

}

inline void FPSUnlockCheat::DrawFPS()
{
	if (显示FPS)
	{
		FPS = ("%.1f", ImGui::GetIO().Framerate);
		char fpsText[32];
		snprintf(fpsText, sizeof(fpsText), "FPS: %.1f", FPS);
		ImVec2 textSize = ImGui::CalcTextSize(fpsText);
		ImGui::SetNextWindowSize(ImVec2(textSize.x + 200, textSize.y + 15));
		ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::Text((const char*)u8"%s  按%s键呼出菜单", fpsText, g_LaunchKey.toString());
		ImGui::End();
	}
}

inline void FPSUnlockCheat::RunFPSUlock()
{
	if (启动)
	{
		GetGameUserSettings()->SetFrameRateLimit(默认帧数);
		GetGameUserSettings()->ApplySettings(false);
		bOnce = false;
	}
	if (!启动 && !bOnce)
	{
		GetGameUserSettings()->FrameRateLimit = 默认帧数;
		GetGameUserSettings()->ApplySettings(false);
		bOnce = true;
	}
}

