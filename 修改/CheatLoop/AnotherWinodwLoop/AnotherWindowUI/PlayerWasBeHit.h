#include "PlayerAction.h"
class PlayerWasHit
{
public:
	bool ��������˴��� = false;
	void DrawPlayerWasHitUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
	void DrawNewPlayerWasHitUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
	void FixUseAction(float deltaTime);
    char  ʹ�����˵�����[255];
    int ��ǰѡ������ = -1;
   bool ���˼����� = false;
   bool ���˼������ = false;
   float ���˼��ؽ��� = 0.0f;
   size_t ��ǰ�������� = 0;
   std::vector<const char*> ���ص������б�;
   char ��������[256] = { 0 };
   bool ��������� = false;
   size_t ��ǰ������� = 0;
   size_t ��ʼ�������� = 0;
   bool �����ͣ�� = false;
   bool ���뷨��Ҫ���� = false;
   char ��ʱ�����ı�[256] = { 0 };
   bool �ϴ������۽� = false;
   bool ���ش��� = false;
   const char* ������Ϣ = "";
   const char* NameForAction = "";
   bool  ��ʾʹ����ʲô���� = false;
};
inline PlayerWasHit PlayerBeHitShow;



inline void PlayerWasHit::DrawPlayerWasHitUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
	PlayerAction.DrawPlayerActonUI(CheatManager, lib);
	ImGui::Checkbox((const char*)u8"��������˴���", &��������˴���);
	if (��������˴���)
	{
		DrawNewPlayerWasHitUI(CheatManager, lib);
		FixUseAction(1.f);
	}

}

inline void PlayerWasHit::DrawNewPlayerWasHitUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!��������˴���) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool ��ǰ�����۽� = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (��ǰ�����۽� && !�ϴ������۽�) {
        ���뷨��Ҫ���� = true;
        strcpy_s(��ʱ�����ı�, ��������);
    }

    if (!��ǰ�����۽� && �ϴ������۽�) {
        strcpy_s(��������, ��ʱ�����ı�);
    }

    �ϴ������۽� = ��ǰ�����۽�;

    if (ImGui::Begin((const char*)u8"����״̬���ع���", &��������˴���, 0))
    {
        if (���뷨��Ҫ����) {
            if (ImGui::InputTextWithHint((const char*)u8"��������״̬", (const char*)u8"��������״̬��������...",
                ��ʱ�����ı�, IM_ARRAYSIZE(��ʱ�����ı�))) {
                strcpy_s(��������, ��ʱ�����ı�);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"��������״̬", (const char*)u8"��������״̬��������...",
                ��������, IM_ARRAYSIZE(��������))) {
                // ��������
            }
        }

        ImGui::BeginGroup();

        if (!���˼����� && !���˼������ && ��ǰ�������� == 0 && !��������� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ʼ��ȡ", ImVec2(100, 25))) {
                ���˼����� = true;
                ���˼������ = false;
                ��ǰ�������� = 0;
                ���ص������б�.clear();
                ��ǰѡ������ = -1;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if ((!���˼����� && !���˼������ && !��������� && ��ǰ�������� > 0) || ���ش���) {
            if (ImGui::Button((const char*)u8"��������", ImVec2(100, 25))) {
                ���˼����� = true;
                ���˼������ = false;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (���˼����� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ͣ����", ImVec2(100, 25))) {
                ���˼����� = false;
            }
        }

        if ((!���˼����� && !��������� && ���˼������) || (!���˼����� && !��������� && ���ش���)) {
            if (ImGui::Button((const char*)u8"������м���", ImVec2(125, 25))) {
                ��������� = true;
                �����ͣ�� = false;
                ���˼������ = false;
                ��ǰ������� = 0;
                ��ʼ�������� = ���ص������б�.size();
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (��������� && !�����ͣ��) {
            if (ImGui::Button((const char*)u8"��ͣ���", ImVec2(100, 25))) {
                �����ͣ�� = true;
            }
        }
        else if (��������� && �����ͣ��) {
            if (ImGui::Button((const char*)u8"�������", ImVec2(100, 25))) {
                �����ͣ�� = false;
            }
        }

        if ((!���˼����� && !��������� && ���˼������) || (!���˼����� && !��������� && ���ش���)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"���¼���", ImVec2(100, 25))) {
                ���˼����� = true;
                ���˼������ = false;
                ��ǰ�������� = 0;
                ���ص������б�.clear();
                ��ǰѡ������ = -1;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }

        ImGui::EndGroup();
        ImGui::Separator();

        if (���ش��� && ������Ϣ[0] != '\0') {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), (const char*)u8"���ش���: %s", ������Ϣ);
            ImGui::Separator();
        }

        if (���˼����� || ��ǰ�������� > 0) {
            const size_t totalActions = sizeof(AllPlayerHitModeName) / sizeof(AllPlayerHitModeName[0]);
            float progress = (float)��ǰ�������� / (float)totalActions;

            if (���˼�����)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (���ش���)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (���˼�����)
                ImGui::Text((const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ������״̬)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (���ش���)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"��������ͣ: %.1f%% (�Ѽ��� %zu/%zu ������״̬)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (!���˼������)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ������״̬)",
                    progress * 100, ��ǰ��������, totalActions);

            ImGui::Spacing();

            if (���˼����� && ��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                const char* currentActionName = AllPlayerHitModeNameShow[��ǰ�������� - 1];
                ImGui::Text((const char*)u8"��ǰ����: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!���˼����� && !��������� && !���ش��� && ��ǰ�������� > 0 && !���˼������) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"��������ͣ�������������");

                if (��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                    const char* currentActionName = AllPlayerHitModeNameShow[��ǰ�������� - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"��ǰ���ص�: %s (λ��: %zu/%zu)",
                        currentActionName, ��ǰ��������, totalActions);
                }
            }
            else if (���˼������) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"�Ѽ���ȫ�� %zu ������״̬", totalActions);
            }
        }

        if (���������) {
            float clearProgress = (float)��ǰ������� / (float)��ʼ��������;
            size_t actionsRemoved = ��ǰ�������;

            if (!�����ͣ��)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!�����ͣ��)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"�������: %.1f%% (��ɾ�� %zu/%zu ������״̬)",
                    clearProgress * 100, actionsRemoved, ��ʼ��������);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"�������ͣ: %.1f%% (��ɾ�� %zu/%zu ������״̬)",
                    clearProgress * 100, actionsRemoved, ��ʼ��������);

            ImGui::Spacing();

            if (!���ص������б�.empty()) {
                size_t currentActionIndex = ���ص������б�.size() - 1;
                if (currentActionIndex < sizeof(AllPlayerHitModeNameShow) / sizeof(AllPlayerHitModeNameShow[0])) {
                    const char* currentActionName = AllPlayerHitModeNameShow[currentActionIndex];
                    size_t originalPosition = ��ʼ�������� - ��ǰ�������;

                    if (!�����ͣ��)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"����ɾ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ��������);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"�������ͣ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ��������);
                }
            }
        }

        ImGui::Separator();

        if ((!���ص������б�.empty() && (!��������� || �����ͣ��)) || ���˼������) {
            const size_t totalActions = ���ص������б�.size();

            if (��ǰѡ������ >= 0 && ��ǰѡ������ < totalActions) {
                size_t selectedItemIndex = ��ǰѡ������;
                if (selectedItemIndex < sizeof(AllPlayerHitModeNameShow) / sizeof(AllPlayerHitModeNameShow[0]) &&
                    selectedItemIndex < sizeof(AllPlayerHitModeName) / sizeof(AllPlayerHitModeName[0])) {
                    const char* displayName = AllPlayerHitModeNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"��ǰѡ��: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"����״̬�б�", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllPlayerHitModeNameShow[i];
                if (��������[0] != '\0' && strstr(displayName, ��������) == nullptr) {
                    continue;
                }

                bool is_selected = (��ǰѡ������ == i);
                if (ImGui::Selectable(displayName, is_selected))
                    ��ǰѡ������ = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"ʹ������״̬", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) 
            {
                if (��ǰѡ������ >= 0 && ��ǰѡ������ < totalActions) {
                    size_t actionIndex = ��ǰѡ������;
                    if (actionIndex < sizeof(AllPlayerHitModeName) / sizeof(AllPlayerHitModeName[0])) {
                        const char* actionInternalName = AllPlayerHitModeName[actionIndex];
                        NameForAction = actionInternalName;
                        ��ʾʹ����ʲô���� = true;
                        UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
                        FName Name = lib->Conv_StringToName(FString(charToWchar(NameForAction)));
                        SBCheatManager->SBApplyEffectMe(Name);
                    }
                }
            }

        }
        else if (!���˼����� && !���˼������ && !���������) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"���ȼ�������״̬");
        }

        ImGui::End();
    }
}
inline void PlayerWasHit::FixUseAction(float deltaTime)
{
    if (!���˼����� && (!��������� || �����ͣ��)) return;

    static float ��ʱ�� = 0.0f;
    ��ʱ�� += deltaTime;

    if (��ʱ�� >= 0.2f) {
        ��ʱ�� = 0.0f;

        if (���˼����� && !���ش���) {
            const size_t totalActions = sizeof(AllPlayerHitModeName) / sizeof(AllPlayerHitModeName[0]);

            if (��ǰ�������� < totalActions) {
                if (AllPlayerHitModeNameShow[��ǰ��������] == nullptr ||
                    AllPlayerHitModeNameShow[��ǰ��������][0] == '\0') {
                    ���˼����� = false;
                    ���ش��� = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "�������ݴ������� %zu ���� AllPlayerHitModeNameShow Ϊ null ���ֵ",
                        ��ǰ��������);
                    ������Ϣ = errorMsg;
                    ���˼������ = true;
                    printf("����: %s\n", errorMsg);
                    return;
                }

                ���ص������б�.push_back(AllPlayerHitModeNameShow[��ǰ��������]);
                ��ǰ��������++;
                ���˼��ؽ��� = (float)��ǰ�������� / totalActions;
            }
            else {
                ���˼����� = false;
                ���˼������ = true;
            }
        }

        if (��������� && !�����ͣ��) {
            if (!���ص������б�.empty()) {
                size_t lastIndex = ���ص������б�.size() - 1;
                const char* removedAction = ���ص������б�[lastIndex];
                ���ص������б�.pop_back();
                ��ǰ�������++;

                if (��ǰѡ������ >= 0 && ��ǰѡ������ >= ���ص������б�.size()) {
                    ��ǰѡ������ = -1;
                }
            }
            else {
                ��������� = false;
                �����ͣ�� = false;
                ��ǰ�������� = 0;
                ��ǰѡ������ = -1;
            }
        }
    }
}