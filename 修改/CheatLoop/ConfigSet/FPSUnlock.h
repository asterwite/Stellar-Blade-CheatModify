#pragma once
#include "..\Config\CofigLoodNeed.h"
#include "..\Cheat\Cheat.h"
#include "KeySet.h"
class FPSUnlockCheat
{
public:
	bool ���� = false;
	bool �����Զ���֡�� = false;
	float Ĭ��֡�� = 144.f;
	float �Զ���֡�� = 144.f;
	float ���֡�� = 540.0f;
	float ����֡�� = 60.0f;
	float FPS = 144;
	bool ���� = true;
	bool ����FPS = false;
	bool ��ʾFPS = true; // True by default;
	int ShowMenu = VK_INSERT;
private:
	bool bOnce = false;
public:
	void DrawFPS();
	void DrawFPSUlockUI();
	void RunFPSUlock();
};
inline FPSUnlockCheat FPSUnlock;

inline bool g_IsSettingKey = false; // �ȼ�����״̬

inline KeyBind g_LaunchKey(KeyBind::KeyCode::INSERT); // Ĭ���ȼ�ΪINSERT

inline KeyBind LastKey;

inline bool HandleKeySetting() {
	// ȡ�����ã�ESC��
	if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
		if(LastKey != g_LaunchKey)
		g_LaunchKey = KeyBind(KeyBind::KeyCode::INSERT); // �ָ�Ĭ��
		g_LaunchKey = LastKey;
		return true;
	}

	// �������а���
	for (int i = 0; i < IM_ARRAYSIZE(ImGui::GetIO().KeysDown); ++i) {
		if (ImGui::IsKeyPressed(static_cast<ImGuiKey>(i))) {
			// ����keyMap��ʹ��data()�Ƚϣ�
			auto it = std::find_if(keyMap.begin(), keyMap.end(),
				[i](const Key& k) { return k.code == i; });

			if (it != keyMap.end() && it->name != "NONE") {
				// �����ȼ���ʹ��data()��ȡ�ַ�����
				g_LaunchKey = KeyBind(it->name.data()); // ע�⣺KeyBind���캯�������const char*
				LastKey = KeyBind(it->name.data());
				return true;
			}
		}
	}
	return false;
}


inline void FPSUnlockCheat::DrawFPSUlockUI()
{
	ImGui::Checkbox((const char*)u8"��ʾFPS", &��ʾFPS);
	ImGui::SliderFloat((const char*)u8" ", &�Զ���֡��,0.f,1000.f);
	ImGui::Text((const char*)u8"�Զ�����Ϸ֡�����ޣ�����FPS���ޣ���ϷĬ�������ƣ���ֻ���������ԣ�");
	if (ImGui::Button((const char*)u8"ȷ��"))
	{
		GetGameUserSettings()->SetFrameRateLimit(�Զ���֡��);
		GetGameUserSettings()->ApplySettings(true);
	}

	if (ImGui::CollapsingHeader((const char*)u8"�����޸�"))
	{
		ImGui::Text((const char*)u8"��ǰ��������: %s", g_LaunchKey.toString());

		// �ȼ����ð�ť
		if (ImGui::Button((const char*)u8"�޸ĺ�������", ImVec2(150, 25))) {
			g_IsSettingKey = true; // ��������ģʽ
		}

		// �ȼ������߼�
		if (g_IsSettingKey) {
			ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"�����°���");
			ImGui::TextColored(ImVec4(1, 1, 1, 1), (const char*)u8"(��ESCȡ�����������ȷ�ϣ����º��رմ��ڣ����°������õİ�������)");

			// ����������
			if (HandleKeySetting())
			{
				ShowMenu = g_LaunchKey.toInt();
				g_IsSettingKey = false; // ������ú��˳�ģʽ
				printf(g_LaunchKey.toString());
			}
		}
	}

}

inline void FPSUnlockCheat::DrawFPS()
{
	if (��ʾFPS)
	{
		FPS = ("%.1f", ImGui::GetIO().Framerate);
		char fpsText[32];
		snprintf(fpsText, sizeof(fpsText), "FPS: %.1f", FPS);
		ImVec2 textSize = ImGui::CalcTextSize(fpsText);
		ImGui::SetNextWindowSize(ImVec2(textSize.x + 200, textSize.y + 15));
		ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);
		ImGui::Text((const char*)u8"%s  ��%s�������˵�", fpsText, g_LaunchKey.toString());
		ImGui::End();
	}
}

inline void FPSUnlockCheat::RunFPSUlock()
{
	if (����)
	{
		GetGameUserSettings()->SetFrameRateLimit(Ĭ��֡��);
		GetGameUserSettings()->ApplySettings(false);
		bOnce = false;
	}
	if (!���� && !bOnce)
	{
		GetGameUserSettings()->FrameRateLimit = Ĭ��֡��;
		GetGameUserSettings()->ApplySettings(false);
		bOnce = true;
	}
}

