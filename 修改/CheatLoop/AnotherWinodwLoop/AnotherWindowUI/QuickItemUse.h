#include "PlayerTalk.h"
#include "NameForLoop/QuickItem.h"
#include "..\..\ConfigSet\KeySet.h"
class QuickItemUseLoop
{
public:
    bool ����ҿ����Ʒ���� = false;
    int WaitTime = 0;
    int UseKey = 0;
    void DrawQuickItemUseLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void DrawNewQuickItemUseLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  ʹ�ÿ����Ʒ������[255];
    int ��ǰѡ�п����Ʒ = -1;
    bool �����Ʒ������ = false;
    bool �����Ʒ������� = false;
    float �����Ʒ���ؽ��� = 0.0f;
    size_t ��ǰ�������� = 0;
    std::vector<const char*> ���صĿ����Ʒ�б�;
    char ���������Ʒ[256] = { 0 };
    bool �����Ʒ����� = false;
    size_t ��ǰ������� = 0;
    size_t ��ʼ�����Ʒ���� = 0;
    bool �����ͣ�� = false;
    bool ���뷨��Ҫ���� = false;
    char ��ʱ�����ı�[256] = { 0 };
    bool �ϴ������۽� = false;
    bool ���ش��� = false;
    const char* ������Ϣ = "";
    const char* NameForAction = "";
    bool  ��ʾʹ����ʲô�����Ʒ = false;
};
inline QuickItemUseLoop QuickItemUse;


inline bool TheUseKey = false; // �ȼ�����״̬

inline KeyBind G_TheUseKey(KeyBind::KeyCode::F2); // Ĭ���ȼ�ΪINSERT

inline KeyBind TheUseKeyLastKey;

inline bool UseHandleKeySetting() {
    // ȡ�����ã�ESC��
    if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
        if (TheUseKeyLastKey != G_TheUseKey)
            G_TheUseKey = KeyBind(KeyBind::KeyCode::INSERT); // �ָ�Ĭ��
        G_TheUseKey = TheUseKeyLastKey;
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
                G_TheUseKey = KeyBind(it->name.data()); // ע�⣺KeyBind���캯�������const char*
                TheUseKeyLastKey = KeyBind(it->name.data());
                return true;
            }
        }
    }
    return false;
}


inline void QuickItemUseLoop::DrawQuickItemUseLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    PlayerTalk.DrawPlayerTalkLoopUI(CheatManager, lib);
    ImGui::Checkbox((const char*)u8"����ҿ����Ʒ����", &����ҿ����Ʒ����);
    if (����ҿ����Ʒ����)
    {
        DrawNewQuickItemUseLoopUI(CheatManager, lib);
        FixUseAction(1.f);
    }
}

inline void QuickItemUseLoop::DrawNewQuickItemUseLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!����ҿ����Ʒ����) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool ��ǰ�����۽� = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (��ǰ�����۽� && !�ϴ������۽�) {
        ���뷨��Ҫ���� = true;
        strcpy_s(��ʱ�����ı�, ���������Ʒ);
    }

    if (!��ǰ�����۽� && �ϴ������۽�) {
        strcpy_s(���������Ʒ, ��ʱ�����ı�);
    }

    �ϴ������۽� = ��ǰ�����۽�;

    if (ImGui::Begin((const char*)u8"�����Ʒ״̬���ع���", &����ҿ����Ʒ����, 0))
    {

            ImGui::Text((const char*)u8"��ǰ���ʹ����Ʒ����: %s", G_TheUseKey.toString());

            // �ȼ����ð�ť
            if (ImGui::Button((const char*)u8"�޸Ŀ��ʹ����Ʒ����", ImVec2(150, 25))) {
                TheUseKey = true; // ��������ģʽ
            }

            // �ȼ������߼�
            if (TheUseKey) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"�����°���");
                ImGui::TextColored(ImVec4(1, 1, 1, 1), (const char*)u8"(��ESCȡ�����������ȷ�ϣ����º��رմ��ڣ����°������õİ�������)");

                // ����������
                if (UseHandleKeySetting())
                {
                    UseKey = G_TheUseKey.toInt();
                    TheUseKey = false; // ������ú��˳�ģʽ
                    printf(G_TheUseKey.toString());
                }
            }

        if (���뷨��Ҫ����) {
            if (ImGui::InputTextWithHint((const char*)u8"���������Ʒ״̬", (const char*)u8"��������Ʒ״̬��������...",
                ��ʱ�����ı�, IM_ARRAYSIZE(��ʱ�����ı�))) {
                strcpy_s(���������Ʒ, ��ʱ�����ı�);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"���������Ʒ״̬", (const char*)u8"��������Ʒ״̬��������...",
                ���������Ʒ, IM_ARRAYSIZE(���������Ʒ))) {
                // ��������
            }
        }

        ImGui::BeginGroup();

        if (!�����Ʒ������ && !�����Ʒ������� && ��ǰ�������� == 0 && !�����Ʒ����� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ʼ��ȡ", ImVec2(100, 25))) {
                �����Ʒ������ = true;
                �����Ʒ������� = false;
                ��ǰ�������� = 0;
                ���صĿ����Ʒ�б�.clear();
                ��ǰѡ�п����Ʒ = -1;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if ((!�����Ʒ������ && !�����Ʒ������� && !�����Ʒ����� && ��ǰ�������� > 0) || ���ش���) {
            if (ImGui::Button((const char*)u8"��������", ImVec2(100, 25))) {
                �����Ʒ������ = true;
                �����Ʒ������� = false;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (�����Ʒ������ && !���ش���) {
            if (ImGui::Button((const char*)u8"��ͣ����", ImVec2(100, 25))) {
                �����Ʒ������ = false;
            }
        }

        if ((!�����Ʒ������ && !�����Ʒ����� && �����Ʒ�������) || (!�����Ʒ������ && !�����Ʒ����� && ���ش���)) {
            if (ImGui::Button((const char*)u8"������м���", ImVec2(125, 25))) {
                �����Ʒ����� = true;
                �����ͣ�� = false;
                �����Ʒ������� = false;
                ��ǰ������� = 0;
                ��ʼ�����Ʒ���� = ���صĿ����Ʒ�б�.size();
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (�����Ʒ����� && !�����ͣ��) {
            if (ImGui::Button((const char*)u8"��ͣ���", ImVec2(100, 25))) {
                �����ͣ�� = true;
            }
        }
        else if (�����Ʒ����� && �����ͣ��) {
            if (ImGui::Button((const char*)u8"�������", ImVec2(100, 25))) {
                �����ͣ�� = false;
            }
        }

        if ((!�����Ʒ������ && !�����Ʒ����� && �����Ʒ�������) || (!�����Ʒ������ && !�����Ʒ����� && ���ش���)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"���¼���", ImVec2(100, 25))) {
                �����Ʒ������ = true;
                �����Ʒ������� = false;
                ��ǰ�������� = 0;
                ���صĿ����Ʒ�б�.clear();
                ��ǰѡ�п����Ʒ = -1;
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

        if (�����Ʒ������ || ��ǰ�������� > 0) {
            const size_t totalActions = sizeof(AllQuickItemUseLoopName) / sizeof(AllQuickItemUseLoopName[0]);
            float progress = (float)��ǰ�������� / (float)totalActions;

            if (�����Ʒ������)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (���ش���)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (�����Ʒ������)
                ImGui::Text((const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu �������Ʒ״̬)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (���ش���)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"��������ͣ: %.1f%% (�Ѽ��� %zu/%zu �������Ʒ״̬)",
                    progress * 100, ��ǰ��������, totalActions);
            else if (!�����Ʒ�������)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu �������Ʒ״̬)",
                    progress * 100, ��ǰ��������, totalActions);

            ImGui::Spacing();

            if (�����Ʒ������ && ��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                const char* currentActionName = AllQuickItemUseLoopNameShow[��ǰ�������� - 1];
                ImGui::Text((const char*)u8"��ǰ����: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!�����Ʒ������ && !�����Ʒ����� && !���ش��� && ��ǰ�������� > 0 && !�����Ʒ�������) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"��������ͣ�������������");

                if (��ǰ�������� > 0 && ��ǰ�������� <= totalActions) {
                    const char* currentActionName = AllQuickItemUseLoopNameShow[��ǰ�������� - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"��ǰ���ص�: %s (λ��: %zu/%zu)",
                        currentActionName, ��ǰ��������, totalActions);
                }
            }
            else if (�����Ʒ�������) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"�Ѽ���ȫ�� %zu �������Ʒ״̬", totalActions);
            }
        }

        if (�����Ʒ�����) {
            float clearProgress = (float)��ǰ������� / (float)��ʼ�����Ʒ����;
            size_t actionsRemoved = ��ǰ�������;

            if (!�����ͣ��)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!�����ͣ��)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"�������: %.1f%% (��ɾ�� %zu/%zu �������Ʒ״̬)",
                    clearProgress * 100, actionsRemoved, ��ʼ�����Ʒ����);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"�������ͣ: %.1f%% (��ɾ�� %zu/%zu �������Ʒ״̬)",
                    clearProgress * 100, actionsRemoved, ��ʼ�����Ʒ����);

            ImGui::Spacing();

            if (!���صĿ����Ʒ�б�.empty()) {
                size_t currentActionIndex = ���صĿ����Ʒ�б�.size() - 1;
                if (currentActionIndex < sizeof(AllQuickItemUseLoopNameShow) / sizeof(AllQuickItemUseLoopNameShow[0])) {
                    const char* currentActionName = AllQuickItemUseLoopNameShow[currentActionIndex];
                    size_t originalPosition = ��ʼ�����Ʒ���� - ��ǰ�������;

                    if (!�����ͣ��)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"����ɾ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ�����Ʒ����);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"�������ͣ��: %s (λ��: %zu/%zu)",
                            currentActionName, originalPosition, ��ʼ�����Ʒ����);
                }
            }
        }

        ImGui::Separator();

        if ((!���صĿ����Ʒ�б�.empty() && (!�����Ʒ����� || �����ͣ��)) || �����Ʒ�������) {
            const size_t totalActions = ���صĿ����Ʒ�б�.size();

            if (��ǰѡ�п����Ʒ >= 0 && ��ǰѡ�п����Ʒ < totalActions) {
                size_t selectedItemIndex = ��ǰѡ�п����Ʒ;
                if (selectedItemIndex < sizeof(AllQuickItemUseLoopNameShow) / sizeof(AllQuickItemUseLoopNameShow[0]) &&
                    selectedItemIndex < sizeof(AllQuickItemUseLoopName) / sizeof(AllQuickItemUseLoopName[0])) {
                    const char* displayName = AllQuickItemUseLoopNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"��ǰѡ��: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"�����Ʒ״̬�б�", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllQuickItemUseLoopNameShow[i];
                if (���������Ʒ[0] != '\0' && strstr(displayName, ���������Ʒ) == nullptr) {
                    continue;
                }

                bool is_selected = (��ǰѡ�п����Ʒ == i);
                if (ImGui::Selectable(displayName, is_selected))
                    ��ǰѡ�п����Ʒ = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (��ǰѡ�п����Ʒ >= 0 && ��ǰѡ�п����Ʒ < totalActions) 
            {
                size_t actionIndex = ��ǰѡ�п����Ʒ;
                if (actionIndex < sizeof(AllQuickItemUseLoopName) / sizeof(AllQuickItemUseLoopName[0])) {
                    const char* actionInternalName = AllQuickItemUseLoopName[actionIndex];
                    NameForAction = actionInternalName;
                }
            }
            
        }
        else if (!�����Ʒ������ && !�����Ʒ������� && !�����Ʒ�����) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"���ȼ��ؿ����Ʒ״̬");
        }

        ImGui::End();
    }
}
inline void QuickItemUseLoop::FixUseAction(float deltaTime)
{
    if (!�����Ʒ������ && (!�����Ʒ����� || �����ͣ��)) return;

    static float ��ʱ�� = 0.0f;
    ��ʱ�� += deltaTime;

    if (��ʱ�� >= 0.2f) {
        ��ʱ�� = 0.0f;

        if (�����Ʒ������ && !���ش���) {
            const size_t totalActions = sizeof(AllQuickItemUseLoopName) / sizeof(AllQuickItemUseLoopName[0]);

            if (��ǰ�������� < totalActions) {
                if (AllQuickItemUseLoopNameShow[��ǰ��������] == nullptr ||
                    AllQuickItemUseLoopNameShow[��ǰ��������][0] == '\0') {
                    �����Ʒ������ = false;
                    ���ش��� = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "�����Ʒ���ݴ������� %zu ���� AllQuickItemUseLoopNameShow Ϊ null ���ֵ",
                        ��ǰ��������);
                    ������Ϣ = errorMsg;
                    �����Ʒ������� = true;
                    printf("����: %s\n", errorMsg);
                    return;
                }

                ���صĿ����Ʒ�б�.push_back(AllQuickItemUseLoopNameShow[��ǰ��������]);
                ��ǰ��������++;
                �����Ʒ���ؽ��� = (float)��ǰ�������� / totalActions;
            }
            else {
                �����Ʒ������ = false;
                �����Ʒ������� = true;
            }
        }

        if (�����Ʒ����� && !�����ͣ��) {
            if (!���صĿ����Ʒ�б�.empty()) {
                size_t lastIndex = ���صĿ����Ʒ�б�.size() - 1;
                const char* removedAction = ���صĿ����Ʒ�б�[lastIndex];
                ���صĿ����Ʒ�б�.pop_back();
                ��ǰ�������++;

                if (��ǰѡ�п����Ʒ >= 0 && ��ǰѡ�п����Ʒ >= ���صĿ����Ʒ�б�.size()) {
                    ��ǰѡ�п����Ʒ = -1;
                }
            }
            else {
                �����Ʒ����� = false;
                �����ͣ�� = false;
                ��ǰ�������� = 0;
                ��ǰѡ�п����Ʒ = -1;
            }
        }
    }
}