#include "ClothDesignSpawn.h"
#include "ItemSpawnName.h"
class ItemLoopCheat
{
public:
    int  ��ӽ����� = 1;
    void DrawItemUI();
    void DrawLoadItemUI();
    void FixLoadItem(float deltaTime);
    void AddItem(USBCheatManager* data, const char* itemName, int count, int level);
    void CreatItem(USBCheatManager* data, const char* itemName, int count, int level);
    char  �����Ʒ������[255];
    int  �����Ʒ���� = 1;
    int  �����Ʒ�ȼ� = 1;
    bool ��ʾ��Ʒ���� = false;
    int ��ǰѡ����Ʒ = -1;
    int ��Ʒ���� = 1;
    int ��Ʒ�ȼ� = 1;
    int �����ж� = 1;
};
inline ItemLoopCheat ItemLoop;

inline bool ��Ʒ������ = false;
inline bool ��Ʒ������� = false;
inline float ��Ʒ���ؽ��� = 0.0f;
inline size_t ��ǰ�������� = 0;
inline std::vector<const char*> ���ص���Ʒ�б�;
inline char ������Ʒ[256] = { 0 };
inline bool ��Ʒ����� = false;
inline size_t ��ǰ������� = 0;
inline size_t ��ʼ��Ʒ���� = 0;
inline bool �����ͣ�� = false;
inline bool ���뷨��Ҫ���� = false;
inline char ��ʱ�����ı�[256] = { 0 };
inline bool �ϴ������۽� = false;
inline bool ���ش��� = false;
inline const char* ������Ϣ = "";
inline const char* NameForItem = "";
inline bool  ��ʾ������ʲô��Ʒ = false;

inline void ItemLoopCheat::DrawItemUI()
{
     USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
     UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
    ImGui::Text((const char*)u8"�����Ʒ���Ƴ���Ʒ�������������������������Ǹ�");
    ImGui::InputInt((const char*)u8"��ӽ�����", &��ӽ�����);
    ImGui::SameLine();
    if (ImGui::Button((const char*)u8"��ӽ�"))
    {

        AddItem(SBCheatManager, "BetaCrystal", ��ӽ�����, 1);
    };		
    ImGui::SameLine();
    ImGuiHelpMarker((const char*)u8"ˢǮˢǮ");

    if (ImGui::CollapsingHeader((const char*)u8"ͨ����Ʒ���������Ʒ"))
    {
        ImGui::InputText((const char*)u8"��Ʒ����", �����Ʒ������, sizeof(�����Ʒ������));
        ImGui::InputInt((const char*)u8"�����Ʒ����", &�����Ʒ����);
        ImGui::InputInt((const char*)u8"�����Ʒ�ȼ�", &�����Ʒ�ȼ�);
        if (ImGui::Button((const char*)u8"�����Ʒ", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
        {
            USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
            if (!SBCheatManager)
                printf("û���ҵ�SBCheatManager");
            if (SBCheatManager && �����Ʒ������[0] != '\0')
            {
                AddItem(SBCheatManager, �����Ʒ������, �����Ʒ����, �����Ʒ�ȼ�);
            }
            else
                printf("û�������Ʒ");
        }
        if (ImGui::Button((const char*)u8"������Ʒ", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
        {
            USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
            if (!SBCheatManager)
                printf("û���ҵ�SBCheatManager");
            if (SBCheatManager && �����Ʒ������[0] != '\0')
            {
                CreatItem(SBCheatManager, �����Ʒ������, �����Ʒ����, �����Ʒ�ȼ�);
            }
            else
                printf("û�д�����Ʒ");
        }
    }
    ImGui::Checkbox((const char*)u8"�����Ʒ����", &��ʾ��Ʒ����);
    if (��ʾ��Ʒ����)
    {
        DrawLoadItemUI();
        FixLoadItem(1.f);
    }
    ClothDesignSpawn.DrawClothDesignLoopUI(SBCheatManager, lib);
}

#pragma region ���Ƽ�����Ʒ
inline void ItemLoopCheat::DrawLoadItemUI()
{
    if (!��ʾ��Ʒ����) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool ��ǰ�����۽� = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (��ǰ�����۽� && !�ϴ������۽�) {
        ���뷨��Ҫ���� = true;
        strcpy_s(��ʱ�����ı�, ������Ʒ);
    }

    if (!��ǰ�����۽� && �ϴ������۽�) {
        strcpy_s(������Ʒ, ��ʱ�����ı�);
    }

    �ϴ������۽� = ��ǰ�����۽�;

    if (ImGui::Begin((const char*)u8"��Ʒ���ع���", &��ʾ��Ʒ����, 0)) 
    {
        ImGui::Text((const char*)u8"��ȫ��Ʒ��������Щ�޷����");
        ImGui::RadioButton((const char*)u8"�����ڱ���", &�����ж�, 1); ImGui::SameLine();
        ImGui::RadioButton((const char*)u8"�����ڸ���", &�����ж�, 2);
        if (���뷨��Ҫ����) {
            if (ImGui::InputTextWithHint((const char*)u8"������Ʒ", (const char*)u8"������Ʒ��������...",
                ��ʱ�����ı�, IM_ARRAYSIZE(��ʱ�����ı�))) {
                strcpy_s(������Ʒ, ��ʱ�����ı�);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"������Ʒ", (const char*)u8"������Ʒ��������...",
                ������Ʒ, IM_ARRAYSIZE(������Ʒ))) {
                // ��������
            }
        }

        ImGui::InputInt((const char*)u8"��Ʒ����", &��Ʒ����);
        ImGui::InputInt((const char*)u8"��Ʒ�ȼ�", &��Ʒ�ȼ�);

        ImGui::BeginGroup();

        if (!��Ʒ������ && !��Ʒ������� && ��ǰ�������� == 0 && !��Ʒ����� && !���ش���) {
            if (ImGui::Button((const char*)u8"��ʼ��ȡ", ImVec2(100, 25))) {
                ��Ʒ������ = true;
                ��Ʒ������� = false;
                ��ǰ�������� = 0;
                ���ص���Ʒ�б�.clear();
                ��ǰѡ����Ʒ = -1;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if ((!��Ʒ������ && !��Ʒ������� && !��Ʒ����� && ��ǰ�������� > 0) || ���ش���) {
            if (ImGui::Button((const char*)u8"��������", ImVec2(100, 25))) {
                ��Ʒ������ = true;
                ��Ʒ������� = false;
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (��Ʒ������ && !���ش���) {
            if (ImGui::Button((const char*)u8"��ͣ����", ImVec2(100, 25))) {
                ��Ʒ������ = false;
            }
        }

        if ((!��Ʒ������ && !��Ʒ����� && ��Ʒ�������) || (!��Ʒ������ && !��Ʒ����� && ���ش���)) {
            if (ImGui::Button((const char*)u8"������м���", ImVec2(125, 25))) {
                ��Ʒ����� = true;
                �����ͣ�� = false;
                ��Ʒ������� = false;
                ��ǰ������� = 0;
                ��ʼ��Ʒ���� = ���ص���Ʒ�б�.size();
                ���ش��� = false;
                ������Ϣ = "";
            }
        }
        else if (��Ʒ����� && !�����ͣ��) {
            if (ImGui::Button((const char*)u8"��ͣ���", ImVec2(100, 25))) {
                �����ͣ�� = true;
            }
        }
        else if (��Ʒ����� && �����ͣ��) {
            if (ImGui::Button((const char*)u8"�������", ImVec2(100, 25))) {
                �����ͣ�� = false;
            }
        }

        if ((!��Ʒ������ && !��Ʒ����� && ��Ʒ�������) || (!��Ʒ������ && !��Ʒ����� && ���ش���)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"���¼���", ImVec2(100, 25))) {
                ��Ʒ������ = true;
                ��Ʒ������� = false;
                ��ǰ�������� = 0;
                ���ص���Ʒ�б�.clear();
                ��ǰѡ����Ʒ = -1;
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

        if (��Ʒ������ || ��ǰ�������� > 0) {
            const size_t totalItems = sizeof(AllItemName) / sizeof(AllItemName[0]);
            float progress = (float)��ǰ�������� / (float)totalItems;

            if (��Ʒ������)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (���ش���)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (��Ʒ������)
                ImGui::Text((const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ����Ʒ)",
                    progress * 100, ��ǰ��������, totalItems);
            else if (���ش���)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"��������ͣ: %.1f%% (�Ѽ��� %zu/%zu ����Ʒ)",
                    progress * 100, ��ǰ��������, totalItems);
            else if (!��Ʒ�������)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"���ؽ���: %.1f%% (�Ѽ��� %zu/%zu ����Ʒ)",
                    progress * 100, ��ǰ��������, totalItems);

            ImGui::Spacing();

            if (��Ʒ������ && ��ǰ�������� > 0 && ��ǰ�������� <= totalItems) {
                const char* currentItemName = ItemNameShow[��ǰ�������� - 1];
                ImGui::Text((const char*)u8"��ǰ����: %s", currentItemName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentItemName);
                ImGui::PopStyleColor();
            }
            else if (!��Ʒ������ && !��Ʒ����� && !���ش��� && ��ǰ�������� > 0 && !��Ʒ�������) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"��������ͣ�������������");

                if (��ǰ�������� > 0 && ��ǰ�������� <= totalItems) {
                    const char* currentItemName = ItemNameShow[��ǰ�������� - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"��ǰ���ص�: %s (λ��: %zu/%zu)",
                        currentItemName, ��ǰ��������, totalItems);
                }
            }
            else if (��Ʒ�������) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"�Ѽ���ȫ�� %zu ����Ʒ", totalItems);
            }
        }

        if (��Ʒ�����) {
            float clearProgress = (float)��ǰ������� / (float)��ʼ��Ʒ����;
            size_t itemsRemoved = ��ǰ�������;

            if (!�����ͣ��)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!�����ͣ��)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"�������: %.1f%% (��ɾ�� %zu/%zu ����Ʒ)",
                    clearProgress * 100, itemsRemoved, ��ʼ��Ʒ����);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"�������ͣ: %.1f%% (��ɾ�� %zu/%zu ����Ʒ)",
                    clearProgress * 100, itemsRemoved, ��ʼ��Ʒ����);

            ImGui::Spacing();

            if (!���ص���Ʒ�б�.empty()) {
                size_t currentItemIndex = ���ص���Ʒ�б�.size() - 1;
                if (currentItemIndex < sizeof(ItemNameShow) / sizeof(ItemNameShow[0])) {
                    const char* currentItemName = ItemNameShow[currentItemIndex];
                    size_t originalPosition = ��ʼ��Ʒ���� - ��ǰ�������;

                    if (!�����ͣ��)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"����ɾ��: %s (λ��: %zu/%zu)",
                            currentItemName, originalPosition, ��ʼ��Ʒ����);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"�������ͣ��: %s (λ��: %zu/%zu)",
                            currentItemName, originalPosition, ��ʼ��Ʒ����);
                }
            }
        }

        ImGui::Separator();

        if ((!���ص���Ʒ�б�.empty() && (!��Ʒ����� || �����ͣ��)) || ��Ʒ�������) {
            const size_t totalItems = ���ص���Ʒ�б�.size();

            if (��ǰѡ����Ʒ >= 0 && ��ǰѡ����Ʒ < totalItems) {
                size_t selectedItemIndex = ��ǰѡ����Ʒ;
                if (selectedItemIndex < sizeof(ItemNameShow) / sizeof(ItemNameShow[0]) &&
                    selectedItemIndex < sizeof(AllItemName) / sizeof(AllItemName[0])) {
                    const char* displayName = ItemNameShow[selectedItemIndex];
                    const char* internalName = AllItemName[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"��ǰѡ��: %s\t\t%s",
                        displayName, internalName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"��Ʒ�б�", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalItems; i++)
            {
                const char* displayName = ItemNameShow[i];
                if (������Ʒ[0] != '\0' && strstr(displayName, ������Ʒ) == nullptr) {
                    continue;
                }

                bool is_selected = (��ǰѡ����Ʒ == i);
                if (ImGui::Selectable(displayName, is_selected))
                    ��ǰѡ����Ʒ = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"������Ʒ", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) {
                if (��ǰѡ����Ʒ >= 0 && ��ǰѡ����Ʒ < totalItems) {
                    size_t itemIndex = ��ǰѡ����Ʒ;
                    if (itemIndex < sizeof(AllItemName) / sizeof(AllItemName[0])) {
                        const char* itemInternalName = AllItemName[itemIndex];
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
                        if(�����ж�==1)
                        AddItem(SBCheatManager, itemInternalName, ��Ʒ����, ��Ʒ�ȼ�);
                        if(�����ж� == 2)
                        CreatItem(SBCheatManager, itemInternalName, ��Ʒ����, ��Ʒ�ȼ�);
                        const char* itemDisplayName = ItemNameShow[itemIndex];
                        ��ʾ������ʲô��Ʒ = true;
                        NameForItem = itemDisplayName;
                    }
                    if(��ʾ������ʲô��Ʒ)
                    ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"�Ѵ�����Ʒ: %s", NameForItem);
                }
            }
        }
        else if (!��Ʒ������ && !��Ʒ������� && !��Ʒ�����) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"���ȼ�����Ʒ");
        }

        ImGui::End();
    }
}
#pragma endregion

#pragma region ���¼�����Ʒ
inline void ItemLoopCheat::FixLoadItem(float deltaTime) {
    if (!��Ʒ������ && (!��Ʒ����� || �����ͣ��)) return;

    static float ��ʱ�� = 0.0f;
    ��ʱ�� += deltaTime;

    if (��ʱ�� >= 0.2f) {
        ��ʱ�� = 0.0f;

        if (��Ʒ������ && !���ش���) {
            const size_t totalItems = sizeof(AllItemName) / sizeof(AllItemName[0]);

            if (��ǰ�������� < totalItems) {
                if (ItemNameShow[��ǰ��������] == nullptr ||
                    ItemNameShow[��ǰ��������][0] == '\0') {
                    ��Ʒ������ = false;
                    ���ش��� = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "��Ʒ���ݴ������� %zu ���� ItemNameShow Ϊ null ���ֵ",
                        ��ǰ��������);
                    ������Ϣ = errorMsg;
                    ��Ʒ������� = true;
                    printf("����: %s\n", errorMsg);
                    return;
                }

                ���ص���Ʒ�б�.push_back(ItemNameShow[��ǰ��������]);
                ��ǰ��������++;
                ��Ʒ���ؽ��� = (float)��ǰ�������� / totalItems;
            }
            else {
                ��Ʒ������ = false;
                ��Ʒ������� = true;
            }
        }

        if (��Ʒ����� && !�����ͣ��) {
            if (!���ص���Ʒ�б�.empty()) {
                size_t lastIndex = ���ص���Ʒ�б�.size() - 1;
                const char* removedItem = ���ص���Ʒ�б�[lastIndex];
                ���ص���Ʒ�б�.pop_back();
                ��ǰ�������++;

                if (��ǰѡ����Ʒ >= 0 && ��ǰѡ����Ʒ >= ���ص���Ʒ�б�.size()) {
                    ��ǰѡ����Ʒ = -1;
                }
            }
            else {
                ��Ʒ����� = false;
                �����ͣ�� = false;
                ��ǰ�������� = 0;
                ��ǰѡ����Ʒ = -1;
            }
        }
    }
}
#pragma endregion

#pragma region ͨ����Ʒ���������Ʒ������
inline void ItemLoopCheat::AddItem(USBCheatManager* data, const char* itemName, int count, int level)
{
    static UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
    wchar_t  ws[255];
    swprintf(ws, 255, L"%hs", itemName);
    FName Name = lib->Conv_StringToName(FString(ws));

    data->SBPlayerItemBucketItemAdd(Name, count, level, true);
}
#pragma endregion

#pragma region ͨ����Ʒ���ƴ�����Ʒ������
inline void ItemLoopCheat::CreatItem(USBCheatManager* data, const char* itemName, int count, int level)
{
    static UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
    wchar_t  ws[255];
    swprintf(ws, 255, L"%hs", itemName);
    FName Name = lib->Conv_StringToName(FString(ws));

    data->SBCreateItemRange(Name, count, level, 0, 0, 0, 0);
}
#pragma endregion    

