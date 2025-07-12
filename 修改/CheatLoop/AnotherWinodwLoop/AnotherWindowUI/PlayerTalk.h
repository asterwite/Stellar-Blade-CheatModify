#include "SpecialEffectsShow.h"
#include "NameForLoop/TalkName.h"
class PlayerTalkLoop
{
public:
    bool ����ҶԻ����� = false;
    int WaitTime = 0;
    void DrawPlayerTalkLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void DrawNewPlayerTalkLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  ʹ�öԻ�������[255];
    int ��ǰѡ�жԻ� = -1;
    bool �Ի������� = false;
    bool �Ի�������� = false;
    float �Ի����ؽ��� = 0.0f;
    size_t ��ǰ�������� = 0;
    std::vector<const char*> ���صĶԻ��б�;
    char �����Ի�[256] = { 0 };
    bool �Ի������ = false;
    size_t ��ǰ������� = 0;
    size_t ��ʼ�Ի����� = 0;
    bool �����ͣ�� = false;
    bool ���뷨��Ҫ���� = false;
    char ��ʱ�����ı�[256] = { 0 };
    bool �ϴ������۽� = false;
    bool ���ش��� = false;
    const char* ������Ϣ = "";
    const char* NameForAction = "";
    bool  ��ʾʹ����ʲô�Ի� = false;
};
inline PlayerTalkLoop PlayerTalk;



inline void PlayerTalkLoop::DrawPlayerTalkLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    PlayerSpecialEffectsShow.DrawPlayerSpecialEffectsUI(CheatManager, lib);
    ImGui::Checkbox((const char*)u8"����ҶԻ�����", &����ҶԻ�����);
    if (����ҶԻ�����)
    {
        DrawNewPlayerTalkLoopUI(CheatManager, lib);
        FixUseAction(1.f);
    }

}

inline void PlayerTalkLoop::DrawNewPlayerTalkLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!����ҶԻ�����) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool ��ǰ�����۽� = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (��ǰ�����۽� && !�ϴ������۽�) {
        ���뷨��Ҫ���� = true;
        strcpy_s(��ʱ�����ı�, �����Ի�);
    }

    if (!��ǰ�����۽� && �ϴ������۽�) {
        strcpy_s(�����Ի�, ��ʱ�����ı�);
    }

    �ϴ������۽� = ��ǰ�����۽�;

    if (ImGui::Begin((const char*)u8"�Ի�״̬���ع���", &����ҶԻ�����, 0))
    {
        if (���뷨��Ҫ����) {
            if (ImGui::InputTextWithHint((const char*)u8"�����Ի�״̬", (const char*)u8"����Ի�״̬��������...",
                ��ʱ�����ı�, IM_ARRAYSIZE(��ʱ�����ı�))) {
                strcpy_s(�����Ի�, ��ʱ�����ı�);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"�����Ի�״̬", (const char*)u8"����Ի�״̬��������...",
                �����Ի�, IM_ARRAYSIZE(�����Ի�))) {
                // ��������
            }
        }

        ImGui::BeginGroup();

        if (!�Ի������� && !�Ի�������� && ��ǰ�������� == 0 && !�Ի������ && !���ش���) {
            if (ImGui::Button((const char*)u8"��ʼ��ȡ", ImVec2(100, 25))) {
                �Ի������� = true;
                �Ի�������� = false;
                ��ǰ�������� = 0;
                ���صĶԻ��б�.clear();
                ��ǰѡ�жԻ� = -1;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if ((!�Ի������� && !�Ի�������� && !�Ի������ && ��ǰ�������� > 0) || ���ش���) {
            if (ImGui::Button((const char*)u8"��������", ImVec2(100, 25))) {
                �Ի������� = true;
                �Ի�������� = false;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (�Ի������� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ͣ����", ImVec2(100, 25))) {
                �Ի������� = false;
            }
        }

        if ((!�Ի������� && !�Ի������ && �Ի��������) || (!�Ի������� && !�Ի������ && ���ش���)) {
            if (ImGui::Button((const char*)u8"������м���", ImVec2(125, 25))) {
                �Ի������ = true;
                �����ͣ�� = false;
                �Ի�������� = false;
                ��ǰ������� = 0;
                ��ʼ�Ի����� = ���صĶԻ��б�.size();
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (�Ի������ && !�����ͣ��) {
            if (ImGui::Button((const char*)u8"��ͣ���", ImVec2(100, 25))) {
                �����ͣ�� = true;
            }
        }
        else if (�Ի������ && �����ͣ��) {
            if (ImGui::Button((const char*)u8"�������", ImVec2(100, 25))) {
                �����ͣ�� = false;
            }
        }

        if ((!�Ի������� && !�Ի������ && �Ի��������) || (!�Ի������� && !�Ի������ && ���ش���)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"���¼���", ImVec2(100, 25))) {
                �Ի������� = true;
                �Ի�������� = false;
                ��ǰ�������� = 0;
                ���صĶԻ��б�.clear();
                ��ǰѡ�жԻ� = -1;
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

        if (�Ի������� || ��ǰ�������� > 0) {
            const size_t totalActions = sizeof(AllPlayerTalkLoopName) / sizeof(AllPlayerTalkLoopName[0]);
            float progress = (float)��ǰ�������� / (float)totalActions;

            if (�Ի�������)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (���ش���)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (�Ի�������)
                ImGui::Text((const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ���Ի�״̬)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (���ش���)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"��������ͣ: %.1f%% (�Ѽ��� %zu/%zu ���Ի�״̬)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (!�Ի��������)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ���Ի�״̬)",
                    progress * 100, ��ǰ��������, totalActions);

            ImGui::Spacing();

            if (�Ի������� && ��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                const char* currentActionName = AllPlayerTalkLoopNameShow[��ǰ�������� - 1];
                ImGui::Text((const char*)u8"��ǰ����: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!�Ի������� && !�Ի������ && !���ش��� && ��ǰ�������� > 0 && !�Ի��������) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"��������ͣ�������������");

                if (��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                    const char* currentActionName = AllPlayerTalkLoopNameShow[��ǰ�������� - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"��ǰ���ص�: %s (λ��: %zu/%zu)",
                        currentActionName, ��ǰ��������, totalActions);
                }
            }
            else if (�Ի��������) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"�Ѽ���ȫ�� %zu ���Ի�״̬", totalActions);
            }
        }

        if (�Ի������) {
            float clearProgress = (float)��ǰ������� / (float)��ʼ�Ի�����;
            size_t actionsRemoved = ��ǰ�������;

            if (!�����ͣ��)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!�����ͣ��)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"�������: %.1f%% (��ɾ�� %zu/%zu ���Ի�״̬)",
                    clearProgress * 100, actionsRemoved, ��ʼ�Ի�����);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"�������ͣ: %.1f%% (��ɾ�� %zu/%zu ���Ի�״̬)",
                    clearProgress * 100, actionsRemoved, ��ʼ�Ի�����);

            ImGui::Spacing();

            if (!���صĶԻ��б�.empty()) {
                size_t currentActionIndex = ���صĶԻ��б�.size() - 1;
                if (currentActionIndex < sizeof(AllPlayerTalkLoopNameShow) / sizeof(AllPlayerTalkLoopNameShow[0])) {
                    const char* currentActionName = AllPlayerTalkLoopNameShow[currentActionIndex];
                    size_t originalPosition = ��ʼ�Ի����� - ��ǰ�������;

                    if (!�����ͣ��)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"����ɾ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ�Ի�����);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"�������ͣ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ�Ի�����);
                }
            }
        }

        ImGui::Separator();

        if ((!���صĶԻ��б�.empty() && (!�Ի������ || �����ͣ��)) || �Ի��������) {
            const size_t totalActions = ���صĶԻ��б�.size();

            if (��ǰѡ�жԻ� >= 0 && ��ǰѡ�жԻ� < totalActions) {
                size_t selectedItemIndex = ��ǰѡ�жԻ�;
                if (selectedItemIndex < sizeof(AllPlayerTalkLoopNameShow) / sizeof(AllPlayerTalkLoopNameShow[0]) &&
                    selectedItemIndex < sizeof(AllPlayerTalkLoopName) / sizeof(AllPlayerTalkLoopName[0])) {
                    const char* displayName = AllPlayerTalkLoopNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"��ǰѡ��: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"�Ի�״̬�б�", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllPlayerTalkLoopNameShow[i];
                if (�����Ի�[0] != '\0' && strstr(displayName, �����Ի�) == nullptr) {
                    continue;
                }

                bool is_selected = (��ǰѡ�жԻ� == i);
                if (ImGui::Selectable(displayName, is_selected))
                    ��ǰѡ�жԻ� = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"ʹ�öԻ�״̬", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (��ǰѡ�жԻ� >= 0 && ��ǰѡ�жԻ� < totalActions) {
                    size_t actionIndex = ��ǰѡ�жԻ�;
                    if (actionIndex < sizeof(AllPlayerTalkLoopName) / sizeof(AllPlayerTalkLoopName[0])) {
                        const char* actionInternalName = AllPlayerTalkLoopName[actionIndex];
                        NameForAction = actionInternalName;
                        ��ʾʹ����ʲô�Ի� = true;
                        UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
                        FName Name = lib->Conv_StringToName(FString(charToWchar(NameForAction)));
                        SBCheatManager->SBApplyEffectMe(Name);
                    }
                }
            }

        }
        else if (!�Ի������� && !�Ի�������� && !�Ի������) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"���ȼ��ضԻ�״̬");
        }

        ImGui::End();
    }
}
inline void PlayerTalkLoop::FixUseAction(float deltaTime)
{
    if (!�Ի������� && (!�Ի������ || �����ͣ��)) return;

    static float ��ʱ�� = 0.0f;
    ��ʱ�� += deltaTime;

    if (��ʱ�� >= 0.2f) {
        ��ʱ�� = 0.0f;

        if (�Ի������� && !���ش���) {
            const size_t totalActions = sizeof(AllPlayerTalkLoopName) / sizeof(AllPlayerTalkLoopName[0]);

            if (��ǰ�������� < totalActions) {
                if (AllPlayerTalkLoopNameShow[��ǰ��������] == nullptr ||
                    AllPlayerTalkLoopNameShow[��ǰ��������][0] == '\0') {
                    �Ի������� = false;
                    ���ش��� = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "�Ի����ݴ������� %zu ���� AllPlayerTalkLoopNameShow Ϊ null ���ֵ",
                        ��ǰ��������);
                    ������Ϣ = errorMsg;
                    �Ի�������� = true;
                    printf("����: %s\n", errorMsg);
                    return;
                }

                ���صĶԻ��б�.push_back(AllPlayerTalkLoopNameShow[��ǰ��������]);
                ��ǰ��������++;
                �Ի����ؽ��� = (float)��ǰ�������� / totalActions;
            }
            else {
                �Ի������� = false;
                �Ի�������� = true;
            }
        }

        if (�Ի������ && !�����ͣ��) {
            if (!���صĶԻ��б�.empty()) {
                size_t lastIndex = ���صĶԻ��б�.size() - 1;
                const char* removedAction = ���صĶԻ��б�[lastIndex];
                ���صĶԻ��б�.pop_back();
                ��ǰ�������++;

                if (��ǰѡ�жԻ� >= 0 && ��ǰѡ�жԻ� >= ���صĶԻ��б�.size()) {
                    ��ǰѡ�жԻ� = -1;
                }
            }
            else {
                �Ի������ = false;
                �����ͣ�� = false;
                ��ǰ�������� = 0;
                ��ǰѡ�жԻ� = -1;
            }
        }
    }
}