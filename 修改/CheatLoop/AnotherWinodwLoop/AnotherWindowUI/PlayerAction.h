#include "..\..\Config\CofigLoodNeed.h"
#include "..\..\Cheat\Cheat.h"
#include "..\ModleName.h"
class PlayerActionCheat
{
public:
	int ��ǰѡ��= -1;
	bool ����Ҷ������� = false;
    bool ѭ��ִ�� = false;
    int ��ִ֡��һ�� = 30;
    int WaitTime = 0;
	const char* ActionName = "";
	void DrawPlayerActonUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
	void DrawNewPlayerActionUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  ʹ�ö���������[255];
    int ��ǰѡ�ж��� = -1;
    bool ���������� = false;
    bool ����������� = false;
    float �������ؽ��� = 0.0f;
    size_t ��ǰ�������� = 0;
    std::vector<const char*> ���صĶ����б�;
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
inline PlayerActionCheat PlayerAction;




inline void PlayerActionCheat::DrawPlayerActonUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
	ImGui::Checkbox((const char*)u8"����Ҷ�������", &����Ҷ�������);
    if (����Ҷ�������)
    {
        DrawNewPlayerActionUI(CheatManager, lib);
        FixUseAction(1.f);
    }


}

inline void PlayerActionCheat::DrawNewPlayerActionUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!����Ҷ�������) return;

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

    if (ImGui::Begin((const char*)u8"�������ع���", &����Ҷ�������, 0))
    {
        ImGui::Checkbox((const char*)u8"�Ƿ�ѭ��ִ�ж�������������Ҫʹ�ö����Ż�ѭ��ִ�У�", &ѭ��ִ��);
        ImGui::InputInt((const char*)u8"��ִ֡��һ��", &��ִ֡��һ��);
        if (���뷨��Ҫ����) {
            if (ImGui::InputTextWithHint((const char*)u8"��������", (const char*)u8"���붯����������...",
                ��ʱ�����ı�, IM_ARRAYSIZE(��ʱ�����ı�))) {
                strcpy_s(��������, ��ʱ�����ı�);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"��������", (const char*)u8"���붯����������...",
                ��������, IM_ARRAYSIZE(��������))) {
                // ��������
            }
        }

        ImGui::BeginGroup();

        if (!���������� && !����������� && ��ǰ�������� == 0 && !��������� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ʼ��ȡ", ImVec2(100, 25))) {
                ���������� = true;
                ����������� = false;
                ��ǰ�������� = 0;
                ���صĶ����б�.clear();
                ��ǰѡ�ж��� = -1;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if ((!���������� && !����������� && !��������� && ��ǰ�������� > 0) || ���ش���) {
            if (ImGui::Button((const char*)u8"��������", ImVec2(100, 25))) {
                ���������� = true;
                ����������� = false;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (���������� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ͣ����", ImVec2(100, 25))) {
                ���������� = false;
            }
        }

        if ((!���������� && !��������� && �����������) || (!���������� && !��������� && ���ش���)) {
            if (ImGui::Button((const char*)u8"������м���", ImVec2(125, 25))) {
                ��������� = true;
                �����ͣ�� = false;
                ����������� = false;
                ��ǰ������� = 0;
                ��ʼ�������� = ���صĶ����б�.size();
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

        if ((!���������� && !��������� && �����������) || (!���������� && !��������� && ���ش���)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"���¼���", ImVec2(100, 25))) {
                ���������� = true;
                ����������� = false;
                ��ǰ�������� = 0;
                ���صĶ����б�.clear();
                ��ǰѡ�ж��� = -1;
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

        if (���������� || ��ǰ�������� > 0) {
            const size_t totalActions = sizeof(AllPlayerActionModeName) / sizeof(AllPlayerActionModeName[0]);
            float progress = (float)��ǰ�������� / (float)totalActions;

            if (����������)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (���ش���)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (����������)
                ImGui::Text((const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ������)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (���ش���)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"��������ͣ: %.1f%% (�Ѽ��� %zu/%zu ������)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (!�����������)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ������)",
                    progress * 100, ��ǰ��������, totalActions);

            ImGui::Spacing();

            if (���������� && ��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                const char* currentActionName = AllPlayerActionModeNameShow[��ǰ�������� - 1];
                ImGui::Text((const char*)u8"��ǰ����: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!���������� && !��������� && !���ش��� && ��ǰ�������� > 0 && !�����������) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"��������ͣ�������������");

                if (��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                    const char* currentActionName = AllPlayerActionModeNameShow[��ǰ�������� - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"��ǰ���ص�: %s (λ��: %zu/%zu)",
                        currentActionName, ��ǰ��������, totalActions);
                }
            }
            else if (�����������) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"�Ѽ���ȫ�� %zu ������", totalActions);
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
                    (const char*)u8"�������: %.1f%% (��ɾ�� %zu/%zu ������)",
                    clearProgress * 100, actionsRemoved, ��ʼ��������);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"�������ͣ: %.1f%% (��ɾ�� %zu/%zu ������)",
                    clearProgress * 100, actionsRemoved, ��ʼ��������);

            ImGui::Spacing();

            if (!���صĶ����б�.empty()) {
                size_t currentActionIndex = ���صĶ����б�.size() - 1;
                if (currentActionIndex < sizeof(AllPlayerActionModeNameShow) / sizeof(AllPlayerActionModeNameShow[0])) {
                    const char* currentActionName = AllPlayerActionModeNameShow[currentActionIndex];
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

        if ((!���صĶ����б�.empty() && (!��������� || �����ͣ��)) || �����������) {
            const size_t totalActions = ���صĶ����б�.size();

            if (��ǰѡ�ж��� >= 0 && ��ǰѡ�ж��� < totalActions) {
                size_t selectedItemIndex = ��ǰѡ�ж���;
                if (selectedItemIndex < sizeof(AllPlayerActionModeNameShow) / sizeof(AllPlayerActionModeNameShow[0]) &&
                    selectedItemIndex < sizeof(AllPlayerActionModeName) / sizeof(AllPlayerActionModeName[0])) {
                    const char* displayName = AllPlayerActionModeNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"��ǰѡ��: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"�����б�", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllPlayerActionModeNameShow[i];
                if (��������[0] != '\0' && strstr(displayName, ��������) == nullptr) {
                    continue;
                }

                bool is_selected = (��ǰѡ�ж��� == i);
                if (ImGui::Selectable(displayName, is_selected))
                    ��ǰѡ�ж��� = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"ʹ�ö���", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (��ǰѡ�ж��� >= 0 && ��ǰѡ�ж��� < totalActions) {
                    size_t actionIndex = ��ǰѡ�ж���;
                    if (actionIndex < sizeof(AllPlayerActionModeName) / sizeof(AllPlayerActionModeName[0])) 
                    {
                        const char* actionInternalName = AllPlayerActionModeName[actionIndex];
                        NameForAction = actionInternalName;
                        UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();                
                        FName Name = lib->Conv_StringToName(FString(charToWchar(NameForAction)));
                        SBCheatManager->SBApplyEffectMe(Name);
                    }
                }
            }
       
        }
        else if (!���������� && !����������� && !���������) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"���ȼ��ض���");
        }

        ImGui::End();
    }
}

inline void PlayerActionCheat::FixUseAction(float deltaTime)
{
    if (!���������� && (!��������� || �����ͣ��)) return;

    static float ��ʱ�� = 0.0f;
    ��ʱ�� += deltaTime;

    if (��ʱ�� >= 0.2f) {
        ��ʱ�� = 0.0f;

        if (���������� && !���ش���) {
            const size_t totalActions = sizeof(AllPlayerActionModeName) / sizeof(AllPlayerActionModeName[0]);

            if (��ǰ�������� < totalActions) {
                if (AllPlayerActionModeNameShow[��ǰ��������] == nullptr ||
                    AllPlayerActionModeNameShow[��ǰ��������][0] == '\0') {
                    ���������� = false;
                    ���ش��� = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "�������ݴ������� %zu ���� AllPlayerActionModeNameShow Ϊ null ���ֵ",
                        ��ǰ��������);
                    ������Ϣ = errorMsg;
                    ����������� = true;
                    printf("����: %s\n", errorMsg);
                    return;
                }

                ���صĶ����б�.push_back(AllPlayerActionModeNameShow[��ǰ��������]);
                ��ǰ��������++;
                �������ؽ��� = (float)��ǰ�������� / totalActions;
            }
            else {
                ���������� = false;
                ����������� = true;
            }
        }

        if (��������� && !�����ͣ��) {
            if (!���صĶ����б�.empty()) {
                size_t lastIndex = ���صĶ����б�.size() - 1;
                const char* removedAction = ���صĶ����б�[lastIndex];
                ���صĶ����б�.pop_back();
                ��ǰ�������++;

                if (��ǰѡ�ж��� >= 0 && ��ǰѡ�ж��� >= ���صĶ����б�.size()) {
                    ��ǰѡ�ж��� = -1;
                }
            }
            else {
                ��������� = false;
                �����ͣ�� = false;
                ��ǰ�������� = 0;
                ��ǰѡ�ж��� = -1;
            }
        }
    }
}