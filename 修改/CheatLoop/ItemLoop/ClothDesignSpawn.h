#include "..\遍历.h"
#include "ClothDesignName.h"
class ClothDesignLoop
{
public:
    bool 打开玩家服装设计图窗口 = false;
    void DrawClothDesignLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void DrawNewClothDesignLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  使用服装设计图的名称[255];
    int 当前选中服装设计图 = -1;
    bool 服装设计图加载中 = false;
    bool 服装设计图加载完成 = false;
    float 服装设计图加载进度 = 0.0f;
    size_t 当前加载索引 = 0;
    std::vector<const char*> 加载的服装设计图列表;
    char 搜索服装设计图[256] = { 0 };
    bool 服装设计图清除中 = false;
    size_t 当前清除索引 = 0;
    size_t 初始服装设计图数量 = 0;
    bool 清除暂停中 = false;
    bool 输入法需要激活 = false;
    char 临时搜索文本[256] = { 0 };
    bool 上次输入框聚焦 = false;
    bool 加载错误 = false;
    const char* 错误信息 = "";
    const char* NameForAction = "";
    bool  显示使用了什么服装设计图 = false;
};
inline ClothDesignLoop ClothDesignSpawn;



inline void ClothDesignLoop::DrawClothDesignLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    ImGui::Checkbox((const char*)u8"打开玩家服装设计图窗口", &打开玩家服装设计图窗口);
    if (打开玩家服装设计图窗口)
    {
        DrawNewClothDesignLoopUI(CheatManager, lib);
        FixUseAction(1.f);
    }

}

inline void ClothDesignLoop::DrawNewClothDesignLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!打开玩家服装设计图窗口) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool 当前输入框聚焦 = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (当前输入框聚焦 && !上次输入框聚焦) {
        输入法需要激活 = true;
        strcpy_s(临时搜索文本, 搜索服装设计图);
    }

    if (!当前输入框聚焦 && 上次输入框聚焦) {
        strcpy_s(搜索服装设计图, 临时搜索文本);
    }

    上次输入框聚焦 = 当前输入框聚焦;

    if (ImGui::Begin((const char*)u8"服装设计图加载管理", &打开玩家服装设计图窗口, 0))
    {
        if (输入法需要激活) {
            if (ImGui::InputTextWithHint((const char*)u8"搜索服装设计图", (const char*)u8"输入服装设计图名称搜索...",
                临时搜索文本, IM_ARRAYSIZE(临时搜索文本))) {
                strcpy_s(搜索服装设计图, 临时搜索文本);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"搜索服装设计图", (const char*)u8"输入服装设计图名称搜索...",
                搜索服装设计图, IM_ARRAYSIZE(搜索服装设计图))) {
                // 正常处理
            }
        }

        ImGui::BeginGroup();

        if (!服装设计图加载中 && !服装设计图加载完成 && 当前加载索引 == 0 && !服装设计图清除中 && !加载错误) {
            if (ImGui::Button((const char*)u8"开始读取", ImVec2(100, 25))) {
                服装设计图加载中 = true;
                服装设计图加载完成 = false;
                当前加载索引 = 0;
                加载的服装设计图列表.clear();
                当前选中服装设计图 = -1;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if ((!服装设计图加载中 && !服装设计图加载完成 && !服装设计图清除中 && 当前加载索引 > 0) || 加载错误) {
            if (ImGui::Button((const char*)u8"继续加载", ImVec2(100, 25))) {
                服装设计图加载中 = true;
                服装设计图加载完成 = false;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (服装设计图加载中 && !加载错误) {
            if (ImGui::Button((const char*)u8"暂停加载", ImVec2(100, 25))) {
                服装设计图加载中 = false;
            }
        }

        if ((!服装设计图加载中 && !服装设计图清除中 && 服装设计图加载完成) || (!服装设计图加载中 && !服装设计图清除中 && 加载错误)) {
            if (ImGui::Button((const char*)u8"清除所有加载", ImVec2(125, 25))) {
                服装设计图清除中 = true;
                清除暂停中 = false;
                服装设计图加载完成 = false;
                当前清除索引 = 0;
                初始服装设计图数量 = 加载的服装设计图列表.size();
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (服装设计图清除中 && !清除暂停中) {
            if (ImGui::Button((const char*)u8"暂停清除", ImVec2(100, 25))) {
                清除暂停中 = true;
            }
        }
        else if (服装设计图清除中 && 清除暂停中) {
            if (ImGui::Button((const char*)u8"继续清除", ImVec2(100, 25))) {
                清除暂停中 = false;
            }
        }

        if ((!服装设计图加载中 && !服装设计图清除中 && 服装设计图加载完成) || (!服装设计图加载中 && !服装设计图清除中 && 加载错误)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"重新加载", ImVec2(100, 25))) {
                服装设计图加载中 = true;
                服装设计图加载完成 = false;
                当前加载索引 = 0;
                加载的服装设计图列表.clear();
                当前选中服装设计图 = -1;
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

        if (服装设计图加载中 || 当前加载索引 > 0) {
            const size_t totalActions = sizeof(AllCloseDesignItemName) / sizeof(AllCloseDesignItemName[0]);
            float progress = (float)当前加载索引 / (float)totalActions;

            if (服装设计图加载中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (加载错误)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (服装设计图加载中)
                ImGui::Text((const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个服装设计图)",
                    progress * 100, 当前加载索引, totalActions);
            else if (加载错误)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"加载已暂停: %.1f%% (已加载 %zu/%zu 个服装设计图)",
                    progress * 100, 当前加载索引, totalActions);
            else if (!服装设计图加载完成)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个服装设计图)",
                    progress * 100, 当前加载索引, totalActions);

            ImGui::Spacing();

            if (服装设计图加载中 && 当前加载索引 > 0 && 当前加载索引 <= totalActions) {
                const char* currentActionName = AllCloseDesignItemNameShow[当前加载索引 - 1];
                ImGui::Text((const char*)u8"当前加载: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!服装设计图加载中 && !服装设计图清除中 && !加载错误 && 当前加载索引 > 0 && !服装设计图加载完成) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"加载已暂停，点击继续加载");

                if (当前加载索引 > 0 && 当前加载索引 <= totalActions) {
                    const char* currentActionName = AllCloseDesignItemNameShow[当前加载索引 - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"当前加载到: %s (位置: %zu/%zu)",
                        currentActionName, 当前加载索引, totalActions);
                }
            }
            else if (服装设计图加载完成) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"已加载全部 %zu 个服装设计图", totalActions);
            }
        }

        if (服装设计图清除中) {
            float clearProgress = (float)当前清除索引 / (float)初始服装设计图数量;
            size_t actionsRemoved = 当前清除索引;

            if (!清除暂停中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!清除暂停中)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"清除进度: %.1f%% (已删除 %zu/%zu 个服装设计图)",
                    clearProgress * 100, actionsRemoved, 初始服装设计图数量);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"清除已暂停: %.1f%% (已删除 %zu/%zu 个服装设计图)",
                    clearProgress * 100, actionsRemoved, 初始服装设计图数量);

            ImGui::Spacing();

            if (!加载的服装设计图列表.empty()) {
                size_t currentActionIndex = 加载的服装设计图列表.size() - 1;
                if (currentActionIndex < sizeof(AllCloseDesignItemNameShow) / sizeof(AllCloseDesignItemNameShow[0])) {
                    const char* currentActionName = AllCloseDesignItemNameShow[currentActionIndex];
                    size_t originalPosition = 初始服装设计图数量 - 当前清除索引;

                    if (!清除暂停中)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"正在删除: %s (位置: %zu/%zu)",
                            currentActionName, originalPosition, 初始服装设计图数量);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"清除已暂停在: %s (位置: %zu/%zu)",
                            currentActionName, originalPosition, 初始服装设计图数量);
                }
            }
        }

        ImGui::Separator();

        if ((!加载的服装设计图列表.empty() && (!服装设计图清除中 || 清除暂停中)) || 服装设计图加载完成) {
            const size_t totalActions = 加载的服装设计图列表.size();

            if (当前选中服装设计图 >= 0 && 当前选中服装设计图 < totalActions) {
                size_t selectedItemIndex = 当前选中服装设计图;
                if (selectedItemIndex < sizeof(AllCloseDesignItemNameShow) / sizeof(AllCloseDesignItemNameShow[0]) &&
                    selectedItemIndex < sizeof(AllCloseDesignItemName) / sizeof(AllCloseDesignItemName[0])) {
                    const char* displayName = AllCloseDesignItemNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"当前选中: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"服装设计图列表", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllCloseDesignItemNameShow[i];
                if (搜索服装设计图[0] != '\0' && strstr(displayName, 搜索服装设计图) == nullptr) {
                    continue;
                }

                bool is_selected = (当前选中服装设计图 == i);
                if (ImGui::Selectable(displayName, is_selected))
                    当前选中服装设计图 = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"添加服装设计图", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (当前选中服装设计图 >= 0 && 当前选中服装设计图 < totalActions) {
                    size_t actionIndex = 当前选中服装设计图;
                    if (actionIndex < sizeof(AllCloseDesignItemName) / sizeof(AllCloseDesignItemName[0])) {
                        const char* actionInternalName = AllCloseDesignItemName[actionIndex];
                        NameForAction = actionInternalName;
                        显示使用了什么服装设计图 = true;
                        UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
                        FName Name = lib->Conv_StringToName(FString(charToWchar(NameForAction)));
                        SBCheatManager->SBPlayerItemBucketItemAdd(Name,1,1,true);
                    }
                }
            }

        }
        else if (!服装设计图加载中 && !服装设计图加载完成 && !服装设计图清除中) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"请先加载服装设计图");
        }

        ImGui::End();
    }
}
inline void ClothDesignLoop::FixUseAction(float deltaTime)
{
    if (!服装设计图加载中 && (!服装设计图清除中 || 清除暂停中)) return;

    static float 计时器 = 0.0f;
    计时器 += deltaTime;

    if (计时器 >= 0.2f) {
        计时器 = 0.0f;

        if (服装设计图加载中 && !加载错误) {
            const size_t totalActions = sizeof(AllCloseDesignItemName) / sizeof(AllCloseDesignItemName[0]);

            if (当前加载索引 < totalActions) {
                if (AllCloseDesignItemNameShow[当前加载索引] == nullptr ||
                    AllCloseDesignItemNameShow[当前加载索引][0] == '\0') {
                    服装设计图加载中 = false;
                    加载错误 = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "服装设计图数据错误：索引 %zu 处的 AllCloseDesignItemNameShow 为 null 或空值",
                        当前加载索引);
                    错误信息 = errorMsg;
                    服装设计图加载完成 = true;
                    printf("错误: %s\n", errorMsg);
                    return;
                }

                加载的服装设计图列表.push_back(AllCloseDesignItemNameShow[当前加载索引]);
                当前加载索引++;
                服装设计图加载进度 = (float)当前加载索引 / totalActions;
            }
            else {
                服装设计图加载中 = false;
                服装设计图加载完成 = true;
            }
        }

        if (服装设计图清除中 && !清除暂停中) {
            if (!加载的服装设计图列表.empty()) {
                size_t lastIndex = 加载的服装设计图列表.size() - 1;
                const char* removedAction = 加载的服装设计图列表[lastIndex];
                加载的服装设计图列表.pop_back();
                当前清除索引++;

                if (当前选中服装设计图 >= 0 && 当前选中服装设计图 >= 加载的服装设计图列表.size()) {
                    当前选中服装设计图 = -1;
                }
            }
            else {
                服装设计图清除中 = false;
                清除暂停中 = false;
                当前加载索引 = 0;
                当前选中服装设计图 = -1;
            }
        }
    }
}