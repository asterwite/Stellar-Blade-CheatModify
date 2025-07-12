#include "ClothDesignSpawn.h"
#include "ItemSpawnName.h"
class ItemLoopCheat
{
public:
    int  添加金方数量 = 1;
    void DrawItemUI();
    void DrawLoadItemUI();
    void FixLoadItem(float deltaTime);
    void AddItem(USBCheatManager* data, const char* itemName, int count, int level);
    void CreatItem(USBCheatManager* data, const char* itemName, int count, int level);
    char  添加物品的名称[255];
    int  添加物品数量 = 1;
    int  添加物品等级 = 1;
    bool 显示物品窗口 = false;
    int 当前选中物品 = -1;
    int 物品数量 = 1;
    int 物品等级 = 1;
    int 生成判断 = 1;
};
inline ItemLoopCheat ItemLoop;

inline bool 物品加载中 = false;
inline bool 物品加载完成 = false;
inline float 物品加载进度 = 0.0f;
inline size_t 当前加载索引 = 0;
inline std::vector<const char*> 加载的物品列表;
inline char 搜索物品[256] = { 0 };
inline bool 物品清除中 = false;
inline size_t 当前清除索引 = 0;
inline size_t 初始物品数量 = 0;
inline bool 清除暂停中 = false;
inline bool 输入法需要激活 = false;
inline char 临时搜索文本[256] = { 0 };
inline bool 上次输入框聚焦 = false;
inline bool 加载错误 = false;
inline const char* 错误信息 = "";
inline const char* NameForItem = "";
inline bool  显示生成了什么物品 = false;

inline void ItemLoopCheat::DrawItemUI()
{
     USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
     UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
    ImGui::Text((const char*)u8"添加物品和移除物品的区别就是输入的数量是正还是负");
    ImGui::InputInt((const char*)u8"添加金方数量", &添加金方数量);
    ImGui::SameLine();
    if (ImGui::Button((const char*)u8"添加金方"))
    {

        AddItem(SBCheatManager, "BetaCrystal", 添加金方数量, 1);
    };		
    ImGui::SameLine();
    ImGuiHelpMarker((const char*)u8"刷钱刷钱");

    if (ImGui::CollapsingHeader((const char*)u8"通过物品名称添加物品"))
    {
        ImGui::InputText((const char*)u8"物品名称", 添加物品的名称, sizeof(添加物品的名称));
        ImGui::InputInt((const char*)u8"添加物品数量", &添加物品数量);
        ImGui::InputInt((const char*)u8"添加物品等级", &添加物品等级);
        if (ImGui::Button((const char*)u8"添加物品", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
        {
            USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
            if (!SBCheatManager)
                printf("没有找到SBCheatManager");
            if (SBCheatManager && 添加物品的名称[0] != '\0')
            {
                AddItem(SBCheatManager, 添加物品的名称, 添加物品数量, 添加物品等级);
            }
            else
                printf("没有添加物品");
        }
        if (ImGui::Button((const char*)u8"创建物品", ImVec2(ImGui::GetContentRegionAvail().x - 3, 20)))
        {
            USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
            if (!SBCheatManager)
                printf("没有找到SBCheatManager");
            if (SBCheatManager && 添加物品的名称[0] != '\0')
            {
                CreatItem(SBCheatManager, 添加物品的名称, 添加物品数量, 添加物品等级);
            }
            else
                printf("没有创建物品");
        }
    }
    ImGui::Checkbox((const char*)u8"添加物品窗口", &显示物品窗口);
    if (显示物品窗口)
    {
        DrawLoadItemUI();
        FixLoadItem(1.f);
    }
    ClothDesignSpawn.DrawClothDesignLoopUI(SBCheatManager, lib);
}

#pragma region 绘制加载物品
inline void ItemLoopCheat::DrawLoadItemUI()
{
    if (!显示物品窗口) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool 当前输入框聚焦 = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (当前输入框聚焦 && !上次输入框聚焦) {
        输入法需要激活 = true;
        strcpy_s(临时搜索文本, 搜索物品);
    }

    if (!当前输入框聚焦 && 上次输入框聚焦) {
        strcpy_s(搜索物品, 临时搜索文本);
    }

    上次输入框聚焦 = 当前输入框聚焦;

    if (ImGui::Begin((const char*)u8"物品加载管理", &显示物品窗口, 0)) 
    {
        ImGui::Text((const char*)u8"非全物品，并且有些无法添加");
        ImGui::RadioButton((const char*)u8"生成在背包", &生成判断, 1); ImGui::SameLine();
        ImGui::RadioButton((const char*)u8"生成在附近", &生成判断, 2);
        if (输入法需要激活) {
            if (ImGui::InputTextWithHint((const char*)u8"搜索物品", (const char*)u8"输入物品名称搜索...",
                临时搜索文本, IM_ARRAYSIZE(临时搜索文本))) {
                strcpy_s(搜索物品, 临时搜索文本);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"搜索物品", (const char*)u8"输入物品名称搜索...",
                搜索物品, IM_ARRAYSIZE(搜索物品))) {
                // 正常处理
            }
        }

        ImGui::InputInt((const char*)u8"物品数量", &物品数量);
        ImGui::InputInt((const char*)u8"物品等级", &物品等级);

        ImGui::BeginGroup();

        if (!物品加载中 && !物品加载完成 && 当前加载索引 == 0 && !物品清除中 && !加载错误) {
            if (ImGui::Button((const char*)u8"开始读取", ImVec2(100, 25))) {
                物品加载中 = true;
                物品加载完成 = false;
                当前加载索引 = 0;
                加载的物品列表.clear();
                当前选中物品 = -1;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if ((!物品加载中 && !物品加载完成 && !物品清除中 && 当前加载索引 > 0) || 加载错误) {
            if (ImGui::Button((const char*)u8"继续加载", ImVec2(100, 25))) {
                物品加载中 = true;
                物品加载完成 = false;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (物品加载中 && !加载错误) {
            if (ImGui::Button((const char*)u8"暂停加载", ImVec2(100, 25))) {
                物品加载中 = false;
            }
        }

        if ((!物品加载中 && !物品清除中 && 物品加载完成) || (!物品加载中 && !物品清除中 && 加载错误)) {
            if (ImGui::Button((const char*)u8"清除所有加载", ImVec2(125, 25))) {
                物品清除中 = true;
                清除暂停中 = false;
                物品加载完成 = false;
                当前清除索引 = 0;
                初始物品数量 = 加载的物品列表.size();
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (物品清除中 && !清除暂停中) {
            if (ImGui::Button((const char*)u8"暂停清除", ImVec2(100, 25))) {
                清除暂停中 = true;
            }
        }
        else if (物品清除中 && 清除暂停中) {
            if (ImGui::Button((const char*)u8"继续清除", ImVec2(100, 25))) {
                清除暂停中 = false;
            }
        }

        if ((!物品加载中 && !物品清除中 && 物品加载完成) || (!物品加载中 && !物品清除中 && 加载错误)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"重新加载", ImVec2(100, 25))) {
                物品加载中 = true;
                物品加载完成 = false;
                当前加载索引 = 0;
                加载的物品列表.clear();
                当前选中物品 = -1;
                加载错误 = false;
                错误信息 = "";
            }
        }

        ImGui::EndGroup();
        ImGui::Separator();

        if (加载错误 && 错误信息[0] != '\0') {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), (const char*)u8"加载错误: %s", 错误信息);
            ImGui::Separator();
        }

        if (物品加载中 || 当前加载索引 > 0) {
            const size_t totalItems = sizeof(AllItemName) / sizeof(AllItemName[0]);
            float progress = (float)当前加载索引 / (float)totalItems;

            if (物品加载中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (加载错误)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (物品加载中)
                ImGui::Text((const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个物品)",
                    progress * 100, 当前加载索引, totalItems);
            else if (加载错误)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"加载已暂停: %.1f%% (已加载 %zu/%zu 个物品)",
                    progress * 100, 当前加载索引, totalItems);
            else if (!物品加载完成)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个物品)",
                    progress * 100, 当前加载索引, totalItems);

            ImGui::Spacing();

            if (物品加载中 && 当前加载索引 > 0 && 当前加载索引 <= totalItems) {
                const char* currentItemName = ItemNameShow[当前加载索引 - 1];
                ImGui::Text((const char*)u8"当前加载: %s", currentItemName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentItemName);
                ImGui::PopStyleColor();
            }
            else if (!物品加载中 && !物品清除中 && !加载错误 && 当前加载索引 > 0 && !物品加载完成) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"加载已暂停，点击继续加载");

                if (当前加载索引 > 0 && 当前加载索引 <= totalItems) {
                    const char* currentItemName = ItemNameShow[当前加载索引 - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"当前加载到: %s (位置: %zu/%zu)",
                        currentItemName, 当前加载索引, totalItems);
                }
            }
            else if (物品加载完成) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"已加载全部 %zu 个物品", totalItems);
            }
        }

        if (物品清除中) {
            float clearProgress = (float)当前清除索引 / (float)初始物品数量;
            size_t itemsRemoved = 当前清除索引;

            if (!清除暂停中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!清除暂停中)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"清除进度: %.1f%% (已删除 %zu/%zu 个物品)",
                    clearProgress * 100, itemsRemoved, 初始物品数量);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"清除已暂停: %.1f%% (已删除 %zu/%zu 个物品)",
                    clearProgress * 100, itemsRemoved, 初始物品数量);

            ImGui::Spacing();

            if (!加载的物品列表.empty()) {
                size_t currentItemIndex = 加载的物品列表.size() - 1;
                if (currentItemIndex < sizeof(ItemNameShow) / sizeof(ItemNameShow[0])) {
                    const char* currentItemName = ItemNameShow[currentItemIndex];
                    size_t originalPosition = 初始物品数量 - 当前清除索引;

                    if (!清除暂停中)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"正在删除: %s (位置: %zu/%zu)",
                            currentItemName, originalPosition, 初始物品数量);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"清除已暂停在: %s (位置: %zu/%zu)",
                            currentItemName, originalPosition, 初始物品数量);
                }
            }
        }

        ImGui::Separator();

        if ((!加载的物品列表.empty() && (!物品清除中 || 清除暂停中)) || 物品加载完成) {
            const size_t totalItems = 加载的物品列表.size();

            if (当前选中物品 >= 0 && 当前选中物品 < totalItems) {
                size_t selectedItemIndex = 当前选中物品;
                if (selectedItemIndex < sizeof(ItemNameShow) / sizeof(ItemNameShow[0]) &&
                    selectedItemIndex < sizeof(AllItemName) / sizeof(AllItemName[0])) {
                    const char* displayName = ItemNameShow[selectedItemIndex];
                    const char* internalName = AllItemName[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"当前选中: %s\t\t%s",
                        displayName, internalName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"物品列表", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalItems; i++)
            {
                const char* displayName = ItemNameShow[i];
                if (搜索物品[0] != '\0' && strstr(displayName, 搜索物品) == nullptr) {
                    continue;
                }

                bool is_selected = (当前选中物品 == i);
                if (ImGui::Selectable(displayName, is_selected))
                    当前选中物品 = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"创建物品", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25))) {
                if (当前选中物品 >= 0 && 当前选中物品 < totalItems) {
                    size_t itemIndex = 当前选中物品;
                    if (itemIndex < sizeof(AllItemName) / sizeof(AllItemName[0])) {
                        const char* itemInternalName = AllItemName[itemIndex];
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
                        if(生成判断==1)
                        AddItem(SBCheatManager, itemInternalName, 物品数量, 物品等级);
                        if(生成判断 == 2)
                        CreatItem(SBCheatManager, itemInternalName, 物品数量, 物品等级);
                        const char* itemDisplayName = ItemNameShow[itemIndex];
                        显示生成了什么物品 = true;
                        NameForItem = itemDisplayName;
                    }
                    if(显示生成了什么物品)
                    ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"已创建物品: %s", NameForItem);
                }
            }
        }
        else if (!物品加载中 && !物品加载完成 && !物品清除中) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"请先加载物品");
        }

        ImGui::End();
    }
}
#pragma endregion

#pragma region 更新加载物品
inline void ItemLoopCheat::FixLoadItem(float deltaTime) {
    if (!物品加载中 && (!物品清除中 || 清除暂停中)) return;

    static float 计时器 = 0.0f;
    计时器 += deltaTime;

    if (计时器 >= 0.2f) {
        计时器 = 0.0f;

        if (物品加载中 && !加载错误) {
            const size_t totalItems = sizeof(AllItemName) / sizeof(AllItemName[0]);

            if (当前加载索引 < totalItems) {
                if (ItemNameShow[当前加载索引] == nullptr ||
                    ItemNameShow[当前加载索引][0] == '\0') {
                    物品加载中 = false;
                    加载错误 = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "物品数据错误：索引 %zu 处的 ItemNameShow 为 null 或空值",
                        当前加载索引);
                    错误信息 = errorMsg;
                    物品加载完成 = true;
                    printf("错误: %s\n", errorMsg);
                    return;
                }

                加载的物品列表.push_back(ItemNameShow[当前加载索引]);
                当前加载索引++;
                物品加载进度 = (float)当前加载索引 / totalItems;
            }
            else {
                物品加载中 = false;
                物品加载完成 = true;
            }
        }

        if (物品清除中 && !清除暂停中) {
            if (!加载的物品列表.empty()) {
                size_t lastIndex = 加载的物品列表.size() - 1;
                const char* removedItem = 加载的物品列表[lastIndex];
                加载的物品列表.pop_back();
                当前清除索引++;

                if (当前选中物品 >= 0 && 当前选中物品 >= 加载的物品列表.size()) {
                    当前选中物品 = -1;
                }
            }
            else {
                物品清除中 = false;
                清除暂停中 = false;
                当前加载索引 = 0;
                当前选中物品 = -1;
            }
        }
    }
}
#pragma endregion

#pragma region 通过物品名称添加物品至背包
inline void ItemLoopCheat::AddItem(USBCheatManager* data, const char* itemName, int count, int level)
{
    static UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
    wchar_t  ws[255];
    swprintf(ws, 255, L"%hs", itemName);
    FName Name = lib->Conv_StringToName(FString(ws));

    data->SBPlayerItemBucketItemAdd(Name, count, level, true);
}
#pragma endregion

#pragma region 通过物品名称创建物品至世界
inline void ItemLoopCheat::CreatItem(USBCheatManager* data, const char* itemName, int count, int level)
{
    static UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
    wchar_t  ws[255];
    swprintf(ws, 255, L"%hs", itemName);
    FName Name = lib->Conv_StringToName(FString(ws));

    data->SBCreateItemRange(Name, count, level, 0, 0, 0, 0);
}
#pragma endregion    

