#include "PlayerWasBeHit.h"
class PlayerSpecialEffects
{
public:
    bool �������Ч���� = false;
    bool ѭ��ִ�� = false;
    int ��ִ֡��һ�� = 30;
    int WaitTime = 0;
    void DrawPlayerSpecialEffectsUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void DrawNewPlayerSpecialEffectsUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  ʹ����Ч������[255];
    int ��ǰѡ����Ч = -1;
    bool ��Ч������ = false;
    bool ��Ч������� = false;
    float ��Ч���ؽ��� = 0.0f;
    size_t ��ǰ�������� = 0;
    std::vector<const char*> ���ص���Ч�б�;
    char ������Ч[256] = { 0 };
    bool ��Ч����� = false;
    size_t ��ǰ������� = 0;
    size_t ��ʼ��Ч���� = 0;
    bool �����ͣ�� = false;
    bool ���뷨��Ҫ���� = false;
    char ��ʱ�����ı�[256] = { 0 };
    bool �ϴ������۽� = false;
    bool ���ش��� = false;
    const char* ������Ϣ = "";
    const char* NameForAction = "";
    bool  ��ʾʹ����ʲô��Ч = false;
};
inline PlayerSpecialEffects PlayerSpecialEffectsShow;



inline void PlayerSpecialEffects::DrawPlayerSpecialEffectsUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    PlayerBeHitShow.DrawPlayerWasHitUI(CheatManager, lib);
    ImGui::Checkbox((const char*)u8"�������Ч����", &�������Ч����);
    if (�������Ч����)
    {
        DrawNewPlayerSpecialEffectsUI(CheatManager, lib);
        FixUseAction(1.f);
    }

}

inline void PlayerSpecialEffects::DrawNewPlayerSpecialEffectsUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!�������Ч����) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool ��ǰ�����۽� = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (��ǰ�����۽� && !�ϴ������۽�) {
        ���뷨��Ҫ���� = true;
        strcpy_s(��ʱ�����ı�, ������Ч);
    }

    if (!��ǰ�����۽� && �ϴ������۽�) {
        strcpy_s(������Ч, ��ʱ�����ı�);
    }

    �ϴ������۽� = ��ǰ�����۽�;

    if (ImGui::Begin((const char*)u8"��Ч״̬���ع���", &�������Ч����, 0))
    {
        ImGui::Checkbox((const char*)u8"�Ƿ�ѭ��ִ�ж�������������Ҫʹ�ö����Ż�ѭ��ִ�У�", &ѭ��ִ��);
        ImGui::InputInt((const char*)u8"��ִ֡��һ��", &��ִ֡��һ��);
        if (���뷨��Ҫ����) {
            if (ImGui::InputTextWithHint((const char*)u8"������Ч״̬", (const char*)u8"������Ч״̬��������...",
                ��ʱ�����ı�, IM_ARRAYSIZE(��ʱ�����ı�))) {
                strcpy_s(������Ч, ��ʱ�����ı�);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"������Ч״̬", (const char*)u8"������Ч״̬��������...",
                ������Ч, IM_ARRAYSIZE(������Ч))) {
                // ��������
            }
        }

        ImGui::BeginGroup();

        if (!��Ч������ && !��Ч������� && ��ǰ�������� == 0 && !��Ч����� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ʼ��ȡ", ImVec2(100, 25))) {
                ��Ч������ = true;
                ��Ч������� = false;
                ��ǰ�������� = 0;
                ���ص���Ч�б�.clear();
                ��ǰѡ����Ч = -1;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if ((!��Ч������ && !��Ч������� && !��Ч����� && ��ǰ�������� > 0) || ���ش���) {
            if (ImGui::Button((const char*)u8"��������", ImVec2(100, 25))) {
                ��Ч������ = true;
                ��Ч������� = false;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (��Ч������ && !���ش���) {
            if (ImGui::Button((const char*)u8"��ͣ����", ImVec2(100, 25))) {
                ��Ч������ = false;
            }
        }

        if ((!��Ч������ && !��Ч����� && ��Ч�������) || (!��Ч������ && !��Ч����� && ���ش���)) {
            if (ImGui::Button((const char*)u8"������м���", ImVec2(125, 25))) {
                ��Ч����� = true;
                �����ͣ�� = false;
                ��Ч������� = false;
                ��ǰ������� = 0;
                ��ʼ��Ч���� = ���ص���Ч�б�.size();
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (��Ч����� && !�����ͣ��) {
            if (ImGui::Button((const char*)u8"��ͣ���", ImVec2(100, 25))) {
                �����ͣ�� = true;
            }
        }
        else if (��Ч����� && �����ͣ��) {
            if (ImGui::Button((const char*)u8"�������", ImVec2(100, 25))) {
                �����ͣ�� = false;
            }
        }

        if ((!��Ч������ && !��Ч����� && ��Ч�������) || (!��Ч������ && !��Ч����� && ���ش���)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"���¼���", ImVec2(100, 25))) {
                ��Ч������ = true;
                ��Ч������� = false;
                ��ǰ�������� = 0;
                ���ص���Ч�б�.clear();
                ��ǰѡ����Ч = -1;
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

        if (��Ч������ || ��ǰ�������� > 0) {
            const size_t totalActions = sizeof(AllPlayerSpecialEffectsName) / sizeof(AllPlayerSpecialEffectsName[0]);
            float progress = (float)��ǰ�������� / (float)totalActions;

            if (��Ч������)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (���ش���)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (��Ч������)
                ImGui::Text((const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ����Ч״̬)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (���ش���)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"��������ͣ: %.1f%% (�Ѽ��� %zu/%zu ����Ч״̬)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (!��Ч�������)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ����Ч״̬)",
                    progress * 100, ��ǰ��������, totalActions);

            ImGui::Spacing();

            if (��Ч������ && ��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                const char* currentActionName = AllPlayerSpecialEffectsNameShow[��ǰ�������� - 1];
                ImGui::Text((const char*)u8"��ǰ����: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!��Ч������ && !��Ч����� && !���ش��� && ��ǰ�������� > 0 && !��Ч�������) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"��������ͣ�������������");

                if (��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                    const char* currentActionName = AllPlayerSpecialEffectsNameShow[��ǰ�������� - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"��ǰ���ص�: %s (λ��: %zu/%zu)",
                        currentActionName, ��ǰ��������, totalActions);
                }
            }
            else if (��Ч�������) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"�Ѽ���ȫ�� %zu ����Ч״̬", totalActions);
            }
        }

        if (��Ч�����) {
            float clearProgress = (float)��ǰ������� / (float)��ʼ��Ч����;
            size_t actionsRemoved = ��ǰ�������;

            if (!�����ͣ��)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!�����ͣ��)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"�������: %.1f%% (��ɾ�� %zu/%zu ����Ч״̬)",
                    clearProgress * 100, actionsRemoved, ��ʼ��Ч����);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"�������ͣ: %.1f%% (��ɾ�� %zu/%zu ����Ч״̬)",
                    clearProgress * 100, actionsRemoved, ��ʼ��Ч����);

            ImGui::Spacing();

            if (!���ص���Ч�б�.empty()) {
                size_t currentActionIndex = ���ص���Ч�б�.size() - 1;
                if (currentActionIndex < sizeof(AllPlayerSpecialEffectsNameShow) / sizeof(AllPlayerSpecialEffectsNameShow[0])) {
                    const char* currentActionName = AllPlayerSpecialEffectsNameShow[currentActionIndex];
                    size_t originalPosition = ��ʼ��Ч���� - ��ǰ�������;

                    if (!�����ͣ��)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"����ɾ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ��Ч����);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"�������ͣ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ��Ч����);
                }
            }
        }

        ImGui::Separator();

        if ((!���ص���Ч�б�.empty() && (!��Ч����� || �����ͣ��)) || ��Ч�������) {
            const size_t totalActions = ���ص���Ч�б�.size();

            if (��ǰѡ����Ч >= 0 && ��ǰѡ����Ч < totalActions) {
                size_t selectedItemIndex = ��ǰѡ����Ч;
                if (selectedItemIndex < sizeof(AllPlayerSpecialEffectsNameShow) / sizeof(AllPlayerSpecialEffectsNameShow[0]) &&
                    selectedItemIndex < sizeof(AllPlayerSpecialEffectsName) / sizeof(AllPlayerSpecialEffectsName[0])) {
                    const char* displayName = AllPlayerSpecialEffectsNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"��ǰѡ��: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"��Ч״̬�б�", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllPlayerSpecialEffectsNameShow[i];
                if (������Ч[0] != '\0' && strstr(displayName, ������Ч) == nullptr) {
                    continue;
                }

                bool is_selected = (��ǰѡ����Ч == i);
                if (ImGui::Selectable(displayName, is_selected))
                    ��ǰѡ����Ч = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"ʹ����Ч״̬", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (��ǰѡ����Ч >= 0 && ��ǰѡ����Ч < totalActions) {
                    size_t actionIndex = ��ǰѡ����Ч;
                    if (actionIndex < sizeof(AllPlayerSpecialEffectsName) / sizeof(AllPlayerSpecialEffectsName[0])) {
                        const char* actionInternalName = AllPlayerSpecialEffectsName[actionIndex];
                        NameForAction = actionInternalName;
                        ��ʾʹ����ʲô��Ч = true;
                        UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
                        FName Name = lib->Conv_StringToName(FString(charToWchar(NameForAction)));
                        SBCheatManager->SBApplyEffectMe(Name);
                    }
                }
            }

        }
        else if (!��Ч������ && !��Ч������� && !��Ч�����) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"���ȼ�����Ч״̬");
        }

        ImGui::End();
    }
}
inline void PlayerSpecialEffects::FixUseAction(float deltaTime)
{
    if (!��Ч������ && (!��Ч����� || �����ͣ��)) return;

    static float ��ʱ�� = 0.0f;
    ��ʱ�� += deltaTime;

    if (��ʱ�� >= 0.2f) {
        ��ʱ�� = 0.0f;

        if (��Ч������ && !���ش���) {
            const size_t totalActions = sizeof(AllPlayerSpecialEffectsName) / sizeof(AllPlayerSpecialEffectsName[0]);

            if (��ǰ�������� < totalActions) {
                if (AllPlayerSpecialEffectsNameShow[��ǰ��������] == nullptr ||
                    AllPlayerSpecialEffectsNameShow[��ǰ��������][0] == '\0') {
                    ��Ч������ = false;
                    ���ش��� = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "��Ч���ݴ������� %zu ���� AllPlayerSpecialEffectsNameShow Ϊ null ���ֵ",
                        ��ǰ��������);
                    ������Ϣ = errorMsg;
                    ��Ч������� = true;
                    printf("����: %s\n", errorMsg);
                    return;
                }

                ���ص���Ч�б�.push_back(AllPlayerSpecialEffectsNameShow[��ǰ��������]);
                ��ǰ��������++;
                ��Ч���ؽ��� = (float)��ǰ�������� / totalActions;
            }
            else {
                ��Ч������ = false;
                ��Ч������� = true;
            }
        }

        if (��Ч����� && !�����ͣ��) {
            if (!���ص���Ч�б�.empty()) {
                size_t lastIndex = ���ص���Ч�б�.size() - 1;
                const char* removedAction = ���ص���Ч�б�[lastIndex];
                ���ص���Ч�б�.pop_back();
                ��ǰ�������++;

                if (��ǰѡ����Ч >= 0 && ��ǰѡ����Ч >= ���ص���Ч�б�.size()) {
                    ��ǰѡ����Ч = -1;
                }
            }
            else {
                ��Ч����� = false;
                �����ͣ�� = false;
                ��ǰ�������� = 0;
                ��ǰѡ����Ч = -1;
            }
        }
    }
}