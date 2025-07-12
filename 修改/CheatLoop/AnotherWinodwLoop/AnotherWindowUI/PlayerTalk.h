#include "SpecialEffectsShow.h"
#include "NameForLoop/TalkName.h"
class PlayerTalkLoop
{
public:
    bool 打开玩家对话窗口 = false;
    int WaitTime = 0;
    void DrawPlayerTalkLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void DrawNewPlayerTalkLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  使用对话的名称[255];
    int 当前选中对话 = -1;
    bool 对话加载中 = false;
    bool 对话加载完成 = false;
    float 对话加载进度 = 0.0f;
    size_t 当前加载索引 = 0;
    std::vector<const char*> 加载的对话列表;
    char 搜索对话[256] = { 0 };
    bool 对话清除中 = false;
    size_t 当前清除索引 = 0;
    size_t 初始对话数量 = 0;
    bool 清除暂停中 = false;
    bool 输入法需要激活 = false;
    char 临时搜索文本[256] = { 0 };
    bool 上次输入框聚焦 = false;
    bool 加载错误 = false;
    const char* 错误信息 = "";
    const char* NameForAction = "";
    bool  显示使用了什么对话 = false;
};
inline PlayerTalkLoop PlayerTalk;



inline void PlayerTalkLoop::DrawPlayerTalkLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    PlayerSpecialEffectsShow.DrawPlayerSpecialEffectsUI(CheatManager, lib);
    ImGui::Checkbox((const char*)u8"打开玩家对话窗口", &打开玩家对话窗口);
    if (打开玩家对话窗口)
    {
        DrawNewPlayerTalkLoopUI(CheatManager, lib);
        FixUseAction(1.f);
    }

}

inline void PlayerTalkLoop::DrawNewPlayerTalkLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!打开玩家对话窗口) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool 当前输入框聚焦 = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (当前输入框聚焦 && !上次输入框聚焦) {
        输入法需要激活 = true;
        strcpy_s(临时搜索文本, 搜索对话);
    }

    if (!当前输入框聚焦 && 上次输入框聚焦) {
        strcpy_s(搜索对话, 临时搜索文本);
    }

    上次输入框聚焦 = 当前输入框聚焦;

    if (ImGui::Begin((const char*)u8"对话状态加载管理", &打开玩家对话窗口, 0))
    {
        if (输入法需要激活) {
            if (ImGui::InputTextWithHint((const char*)u8"搜索对话状态", (const char*)u8"输入对话状态名称搜索...",
                临时搜索文本, IM_ARRAYSIZE(临时搜索文本))) {
                strcpy_s(搜索对话, 临时搜索文本);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"搜索对话状态", (const char*)u8"输入对话状态名称搜索...",
                搜索对话, IM_ARRAYSIZE(搜索对话))) {
                // 正常处理
            }
        }

        ImGui::BeginGroup();

        if (!对话加载中 && !对话加载完成 && 当前加载索引 == 0 && !对话清除中 && !加载错误) {
            if (ImGui::Button((const char*)u8"开始读取", ImVec2(100, 25))) {
                对话加载中 = true;
                对话加载完成 = false;
                当前加载索引 = 0;
                加载的对话列表.clear();
                当前选中对话 = -1;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if ((!对话加载中 && !对话加载完成 && !对话清除中 && 当前加载索引 > 0) || 加载错误) {
            if (ImGui::Button((const char*)u8"继续加载", ImVec2(100, 25))) {
                对话加载中 = true;
                对话加载完成 = false;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (对话加载中 && !加载错误) {
            if (ImGui::Button((const char*)u8"暂停加载", ImVec2(100, 25))) {
                对话加载中 = false;
            }
        }

        if ((!对话加载中 && !对话清除中 && 对话加载完成) || (!对话加载中 && !对话清除中 && 加载错误)) {
            if (ImGui::Button((const char*)u8"清除所有加载", ImVec2(125, 25))) {
                对话清除中 = true;
                清除暂停中 = false;
                对话加载完成 = false;
                当前清除索引 = 0;
                初始对话数量 = 加载的对话列表.size();
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (对话清除中 && !清除暂停中) {
            if (ImGui::Button((const char*)u8"暂停清除", ImVec2(100, 25))) {
                清除暂停中 = true;
            }
        }
        else if (对话清除中 && 清除暂停中) {
            if (ImGui::Button((const char*)u8"继续清除", ImVec2(100, 25))) {
                清除暂停中 = false;
            }
        }

        if ((!对话加载中 && !对话清除中 && 对话加载完成) || (!对话加载中 && !对话清除中 && 加载错误)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"重新加载", ImVec2(100, 25))) {
                对话加载中 = true;
                对话加载完成 = false;
                当前加载索引 = 0;
                加载的对话列表.clear();
                当前选中对话 = -1;
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

        if (对话加载中 || 当前加载索引 > 0) {
            const size_t totalActions = sizeof(AllPlayerTalkLoopName) / sizeof(AllPlayerTalkLoopName[0]);
            float progress = (float)当前加载索引 / (float)totalActions;

            if (对话加载中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (加载错误)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (对话加载中)
                ImGui::Text((const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个对话状态)",
                    progress * 100, 当前加载索引, totalActions);
            else if (加载错误)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"加载已暂停: %.1f%% (已加载 %zu/%zu 个对话状态)",
                    progress * 100, 当前加载索引, totalActions);
            else if (!对话加载完成)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个对话状态)",
                    progress * 100, 当前加载索引, totalActions);

            ImGui::Spacing();

            if (对话加载中 && 当前加载索引 > 0 && 当前加载索引 <= totalActions) {
                const char* currentActionName = AllPlayerTalkLoopNameShow[当前加载索引 - 1];
                ImGui::Text((const char*)u8"当前加载: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!对话加载中 && !对话清除中 && !加载错误 && 当前加载索引 > 0 && !对话加载完成) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"加载已暂停，点击继续加载");

                if (当前加载索引 > 0 && 当前加载索引 <= totalActions) {
                    const char* currentActionName = AllPlayerTalkLoopNameShow[当前加载索引 - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"当前加载到: %s (位置: %zu/%zu)",
                        currentActionName, 当前加载索引, totalActions);
                }
            }
            else if (对话加载完成) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"已加载全部 %zu 个对话状态", totalActions);
            }
        }

        if (对话清除中) {
            float clearProgress = (float)当前清除索引 / (float)初始对话数量;
            size_t actionsRemoved = 当前清除索引;

            if (!清除暂停中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!清除暂停中)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"清除进度: %.1f%% (已删除 %zu/%zu 个对话状态)",
                    clearProgress * 100, actionsRemoved, 初始对话数量);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"清除已暂停: %.1f%% (已删除 %zu/%zu 个对话状态)",
                    clearProgress * 100, actionsRemoved, 初始对话数量);

            ImGui::Spacing();

            if (!加载的对话列表.empty()) {
                size_t currentActionIndex = 加载的对话列表.size() - 1;
                if (currentActionIndex < sizeof(AllPlayerTalkLoopNameShow) / sizeof(AllPlayerTalkLoopNameShow[0])) {
                    const char* currentActionName = AllPlayerTalkLoopNameShow[currentActionIndex];
                    size_t originalPosition = 初始对话数量 - 当前清除索引;

                    if (!清除暂停中)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"正在删除: %s (位置: %zu/%zu)",
                            currentActionName, originalPosition, 初始对话数量);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"清除已暂停在: %s (位置: %zu/%zu)",
                            currentActionName, originalPosition, 初始对话数量);
                }
            }
        }

        ImGui::Separator();

        if ((!加载的对话列表.empty() && (!对话清除中 || 清除暂停中)) || 对话加载完成) {
            const size_t totalActions = 加载的对话列表.size();

            if (当前选中对话 >= 0 && 当前选中对话 < totalActions) {
                size_t selectedItemIndex = 当前选中对话;
                if (selectedItemIndex < sizeof(AllPlayerTalkLoopNameShow) / sizeof(AllPlayerTalkLoopNameShow[0]) &&
                    selectedItemIndex < sizeof(AllPlayerTalkLoopName) / sizeof(AllPlayerTalkLoopName[0])) {
                    const char* displayName = AllPlayerTalkLoopNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"当前选中: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"对话状态列表", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllPlayerTalkLoopNameShow[i];
                if (搜索对话[0] != '\0' && strstr(displayName, 搜索对话) == nullptr) {
                    continue;
                }

                bool is_selected = (当前选中对话 == i);
                if (ImGui::Selectable(displayName, is_selected))
                    当前选中对话 = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"使用对话状态", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (当前选中对话 >= 0 && 当前选中对话 < totalActions) {
                    size_t actionIndex = 当前选中对话;
                    if (actionIndex < sizeof(AllPlayerTalkLoopName) / sizeof(AllPlayerTalkLoopName[0])) {
                        const char* actionInternalName = AllPlayerTalkLoopName[actionIndex];
                        NameForAction = actionInternalName;
                        显示使用了什么对话 = true;
                        UKismetStringLibrary* lib = UKismetStringLibrary::GetDefaultObj();
                        USBCheatManager* SBCheatManager = USBCheatManager::GetDefaultObj();
                        FName Name = lib->Conv_StringToName(FString(charToWchar(NameForAction)));
                        SBCheatManager->SBApplyEffectMe(Name);
                    }
                }
            }

        }
        else if (!对话加载中 && !对话加载完成 && !对话清除中) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"请先加载对话状态");
        }

        ImGui::End();
    }
}
inline void PlayerTalkLoop::FixUseAction(float deltaTime)
{
    if (!对话加载中 && (!对话清除中 || 清除暂停中)) return;

    static float 计时器 = 0.0f;
    计时器 += deltaTime;

    if (计时器 >= 0.2f) {
        计时器 = 0.0f;

        if (对话加载中 && !加载错误) {
            const size_t totalActions = sizeof(AllPlayerTalkLoopName) / sizeof(AllPlayerTalkLoopName[0]);

            if (当前加载索引 < totalActions) {
                if (AllPlayerTalkLoopNameShow[当前加载索引] == nullptr ||
                    AllPlayerTalkLoopNameShow[当前加载索引][0] == '\0') {
                    对话加载中 = false;
                    加载错误 = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "对话数据错误：索引 %zu 处的 AllPlayerTalkLoopNameShow 为 null 或空值",
                        当前加载索引);
                    错误信息 = errorMsg;
                    对话加载完成 = true;
                    printf("错误: %s\n", errorMsg);
                    return;
                }

                加载的对话列表.push_back(AllPlayerTalkLoopNameShow[当前加载索引]);
                当前加载索引++;
                对话加载进度 = (float)当前加载索引 / totalActions;
            }
            else {
                对话加载中 = false;
                对话加载完成 = true;
            }
        }

        if (对话清除中 && !清除暂停中) {
            if (!加载的对话列表.empty()) {
                size_t lastIndex = 加载的对话列表.size() - 1;
                const char* removedAction = 加载的对话列表[lastIndex];
                加载的对话列表.pop_back();
                当前清除索引++;

                if (当前选中对话 >= 0 && 当前选中对话 >= 加载的对话列表.size()) {
                    当前选中对话 = -1;
                }
            }
            else {
                对话清除中 = false;
                清除暂停中 = false;
                当前加载索引 = 0;
                当前选中对话 = -1;
            }
        }
    }
}