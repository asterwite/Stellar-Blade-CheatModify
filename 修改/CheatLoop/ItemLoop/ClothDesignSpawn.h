#include "..\����.h"
#include "ClothDesignName.h"
class ClothDesignLoop
{
public:
    bool ����ҷ�װ���ͼ���� = false;
    void DrawClothDesignLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void DrawNewClothDesignLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  ʹ�÷�װ���ͼ������[255];
    int ��ǰѡ�з�װ���ͼ = -1;
    bool ��װ���ͼ������ = false;
    bool ��װ���ͼ������� = false;
    float ��װ���ͼ���ؽ��� = 0.0f;
    size_t ��ǰ�������� = 0;
    std::vector<const char*> ���صķ�װ���ͼ�б�;
    char ������װ���ͼ[256] = { 0 };
    bool ��װ���ͼ����� = false;
    size_t ��ǰ������� = 0;
    size_t ��ʼ��װ���ͼ���� = 0;
    bool �����ͣ�� = false;
    bool ���뷨��Ҫ���� = false;
    char ��ʱ�����ı�[256] = { 0 };
    bool �ϴ������۽� = false;
    bool ���ش��� = false;
    const char* ������Ϣ = "";
    const char* NameForAction = "";
    bool  ��ʾʹ����ʲô��װ���ͼ = false;
};
inline ClothDesignLoop ClothDesignSpawn;



inline void ClothDesignLoop::DrawClothDesignLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    ImGui::Checkbox((const char*)u8"����ҷ�װ���ͼ����", &����ҷ�װ���ͼ����);
    if (����ҷ�װ���ͼ����)
    {
        DrawNewClothDesignLoopUI(CheatManager, lib);
        FixUseAction(1.f);
    }

}

inline void ClothDesignLoop::DrawNewClothDesignLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!����ҷ�װ���ͼ����) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool ��ǰ�����۽� = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (��ǰ�����۽� && !�ϴ������۽�) {
        ���뷨��Ҫ���� = true;
        strcpy_s(��ʱ�����ı�, ������װ���ͼ);
    }

    if (!��ǰ�����۽� && �ϴ������۽�) {
        strcpy_s(������װ���ͼ, ��ʱ�����ı�);
    }

    �ϴ������۽� = ��ǰ�����۽�;

    if (ImGui::Begin((const char*)u8"��װ���ͼ���ع���", &����ҷ�װ���ͼ����, 0))
    {
        if (���뷨��Ҫ����) {
            if (ImGui::InputTextWithHint((const char*)u8"������װ���ͼ", (const char*)u8"�����װ���ͼ��������...",
                ��ʱ�����ı�, IM_ARRAYSIZE(��ʱ�����ı�))) {
                strcpy_s(������װ���ͼ, ��ʱ�����ı�);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"������װ���ͼ", (const char*)u8"�����װ���ͼ��������...",
                ������װ���ͼ, IM_ARRAYSIZE(������װ���ͼ))) {
                // ��������
            }
        }

        ImGui::BeginGroup();

        if (!��װ���ͼ������ && !��װ���ͼ������� && ��ǰ�������� == 0 && !��װ���ͼ����� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ʼ��ȡ", ImVec2(100, 25))) {
                ��װ���ͼ������ = true;
                ��װ���ͼ������� = false;
                ��ǰ�������� = 0;
                ���صķ�װ���ͼ�б�.clear();
                ��ǰѡ�з�װ���ͼ = -1;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if ((!��װ���ͼ������ && !��װ���ͼ������� && !��װ���ͼ����� && ��ǰ�������� > 0) || ���ش���) {
            if (ImGui::Button((const char*)u8"��������", ImVec2(100, 25))) {
                ��װ���ͼ������ = true;
                ��װ���ͼ������� = false;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (��װ���ͼ������ && !���ش���) {
            if (ImGui::Button((const char*)u8"��ͣ����", ImVec2(100, 25))) {
                ��װ���ͼ������ = false;
            }
        }

        if ((!��װ���ͼ������ && !��װ���ͼ����� && ��װ���ͼ�������) || (!��װ���ͼ������ && !��װ���ͼ����� && ���ش���)) {
            if (ImGui::Button((const char*)u8"������м���", ImVec2(125, 25))) {
                ��װ���ͼ����� = true;
                �����ͣ�� = false;
                ��װ���ͼ������� = false;
                ��ǰ������� = 0;
                ��ʼ��װ���ͼ���� = ���صķ�װ���ͼ�б�.size();
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (��װ���ͼ����� && !�����ͣ��) {
            if (ImGui::Button((const char*)u8"��ͣ���", ImVec2(100, 25))) {
                �����ͣ�� = true;
            }
        }
        else if (��װ���ͼ����� && �����ͣ��) {
            if (ImGui::Button((const char*)u8"�������", ImVec2(100, 25))) {
                �����ͣ�� = false;
            }
        }

        if ((!��װ���ͼ������ && !��װ���ͼ����� && ��װ���ͼ�������) || (!��װ���ͼ������ && !��װ���ͼ����� && ���ش���)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"���¼���", ImVec2(100, 25))) {
                ��װ���ͼ������ = true;
                ��װ���ͼ������� = false;
                ��ǰ�������� = 0;
                ���صķ�װ���ͼ�б�.clear();
                ��ǰѡ�з�װ���ͼ = -1;
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

        if (��װ���ͼ������ || ��ǰ�������� > 0) {
            const size_t totalActions = sizeof(AllCloseDesignItemName) / sizeof(AllCloseDesignItemName[0]);
            float progress = (float)��ǰ�������� / (float)totalActions;

            if (��װ���ͼ������)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (���ش���)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (��װ���ͼ������)
                ImGui::Text((const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ����װ���ͼ)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (���ش���)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"��������ͣ: %.1f%% (�Ѽ��� %zu/%zu ����װ���ͼ)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (!��װ���ͼ�������)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ����װ���ͼ)",
                    progress * 100, ��ǰ��������, totalActions);

            ImGui::Spacing();

            if (��װ���ͼ������ && ��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                const char* currentActionName = AllCloseDesignItemNameShow[��ǰ�������� - 1];
                ImGui::Text((const char*)u8"��ǰ����: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!��װ���ͼ������ && !��װ���ͼ����� && !���ش��� && ��ǰ�������� > 0 && !��װ���ͼ�������) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"��������ͣ�������������");

                if (��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                    const char* currentActionName = AllCloseDesignItemNameShow[��ǰ�������� - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"��ǰ���ص�: %s (λ��: %zu/%zu)",
                        currentActionName, ��ǰ��������, totalActions);
                }
            }
            else if (��װ���ͼ�������) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"�Ѽ���ȫ�� %zu ����װ���ͼ", totalActions);
            }
        }

        if (��װ���ͼ�����) {
            float clearProgress = (float)��ǰ������� / (float)��ʼ��װ���ͼ����;
            size_t actionsRemoved = ��ǰ�������;

            if (!�����ͣ��)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!�����ͣ��)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"�������: %.1f%% (��ɾ�� %zu/%zu ����װ���ͼ)",
                    clearProgress * 100, actionsRemoved, ��ʼ��װ���ͼ����);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"�������ͣ: %.1f%% (��ɾ�� %zu/%zu ����װ���ͼ)",
                    clearProgress * 100, actionsRemoved, ��ʼ��װ���ͼ����);

            ImGui::Spacing();

            if (!���صķ�װ���ͼ�б�.empty()) {
                size_t currentActionIndex = ���صķ�װ���ͼ�б�.size() - 1;
                if (currentActionIndex < sizeof(AllCloseDesignItemNameShow) / sizeof(AllCloseDesignItemNameShow[0])) {
                    const char* currentActionName = AllCloseDesignItemNameShow[currentActionIndex];
                    size_t originalPosition = ��ʼ��װ���ͼ���� - ��ǰ�������;

                    if (!�����ͣ��)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"����ɾ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ��װ���ͼ����);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"�������ͣ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ��װ���ͼ����);
                }
            }
        }

        ImGui::Separator();

        if ((!���صķ�װ���ͼ�б�.empty() && (!��װ���ͼ����� || �����ͣ��)) || ��װ���ͼ�������) {
            const size_t totalActions = ���صķ�װ���ͼ�б�.size();

            if (��ǰѡ�з�װ���ͼ >= 0 && ��ǰѡ�з�װ���ͼ < totalActions) {
                size_t selectedItemIndex = ��ǰѡ�з�װ���ͼ;
                if (selectedItemIndex < sizeof(AllCloseDesignItemNameShow) / sizeof(AllCloseDesignItemNameShow[0]) &&
                    selectedItemIndex < sizeof(AllCloseDesignItemName) / sizeof(AllCloseDesignItemName[0])) {
                    const char* displayName = AllCloseDesignItemNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"��ǰѡ��: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"��װ���ͼ�б�", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllCloseDesignItemNameShow[i];
                if (������װ���ͼ[0] != '\0' && strstr(displayName, ������װ���ͼ) == nullptr) {
                    continue;
                }

                bool is_selected = (��ǰѡ�з�װ���ͼ == i);
                if (ImGui::Selectable(displayName, is_selected))
                    ��ǰѡ�з�װ���ͼ = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"��ӷ�װ���ͼ", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (��ǰѡ�з�װ���ͼ >= 0 && ��ǰѡ�з�װ���ͼ < totalActions) {
                    size_t actionIndex = ��ǰѡ�з�װ���ͼ;
                    if (actionIndex < sizeof(AllCloseDesignItemName) / sizeof(AllCloseDesignItemName[0])) {
                        const char* actionInternalName = AllCloseDesignItemName[actionIndex];
                        NameForAction = actionInternalName;
                        ��ʾʹ����ʲô��װ���ͼ = true;
                        UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
                        FName Name = lib->Conv_StringToName(FString(charToWchar(NameForAction)));
                        SBCheatManager->SBPlayerItemBucketItemAdd(Name,1,1,true);
                    }
                }
            }

        }
        else if (!��װ���ͼ������ && !��װ���ͼ������� && !��װ���ͼ�����) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"���ȼ��ط�װ���ͼ");
        }

        ImGui::End();
    }
}
inline void ClothDesignLoop::FixUseAction(float deltaTime)
{
    if (!��װ���ͼ������ && (!��װ���ͼ����� || �����ͣ��)) return;

    static float ��ʱ�� = 0.0f;
    ��ʱ�� += deltaTime;

    if (��ʱ�� >= 0.2f) {
        ��ʱ�� = 0.0f;

        if (��װ���ͼ������ && !���ش���) {
            const size_t totalActions = sizeof(AllCloseDesignItemName) / sizeof(AllCloseDesignItemName[0]);

            if (��ǰ�������� < totalActions) {
                if (AllCloseDesignItemNameShow[��ǰ��������] == nullptr ||
                    AllCloseDesignItemNameShow[��ǰ��������][0] == '\0') {
                    ��װ���ͼ������ = false;
                    ���ش��� = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "��װ���ͼ���ݴ������� %zu ���� AllCloseDesignItemNameShow Ϊ null ���ֵ",
                        ��ǰ��������);
                    ������Ϣ = errorMsg;
                    ��װ���ͼ������� = true;
                    printf("����: %s\n", errorMsg);
                    return;
                }

                ���صķ�װ���ͼ�б�.push_back(AllCloseDesignItemNameShow[��ǰ��������]);
                ��ǰ��������++;
                ��װ���ͼ���ؽ��� = (float)��ǰ�������� / totalActions;
            }
            else {
                ��װ���ͼ������ = false;
                ��װ���ͼ������� = true;
            }
        }

        if (��װ���ͼ����� && !�����ͣ��) {
            if (!���صķ�װ���ͼ�б�.empty()) {
                size_t lastIndex = ���صķ�װ���ͼ�б�.size() - 1;
                const char* removedAction = ���صķ�װ���ͼ�б�[lastIndex];
                ���صķ�װ���ͼ�б�.pop_back();
                ��ǰ�������++;

                if (��ǰѡ�з�װ���ͼ >= 0 && ��ǰѡ�з�װ���ͼ >= ���صķ�װ���ͼ�б�.size()) {
                    ��ǰѡ�з�װ���ͼ = -1;
                }
            }
            else {
                ��װ���ͼ����� = false;
                �����ͣ�� = false;
                ��ǰ�������� = 0;
                ��ǰѡ�з�װ���ͼ = -1;
            }
        }
    }
}