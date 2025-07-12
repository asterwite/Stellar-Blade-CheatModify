#include "..\..\Config\CofigLoodNeed.h"
#include "..\..\Cheat\Cheat.h"
#include "..\ModleName.h"
class PlayerActionCheat
{
public:
	int 当前选中= -1;
	bool 打开玩家动作窗口 = false;
    bool 循环执行 = false;
    int 几帧执行一次 = 30;
    int WaitTime = 0;
	const char* ActionName = "";
	void DrawPlayerActonUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
	void DrawNewPlayerActionUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  使用动作的名称[255];
    int 当前选中动作 = -1;
    bool 动作加载中 = false;
    bool 动作加载完成 = false;
    float 动作加载进度 = 0.0f;
    size_t 当前加载索引 = 0;
    std::vector<const char*> 加载的动作列表;
    char 搜索动作[256] = { 0 };
    bool 动作清除中 = false;
    size_t 当前清除索引 = 0;
    size_t 初始动作数量 = 0;
    bool 清除暂停中 = false;
    bool 输入法需要激活 = false;
    char 临时搜索文本[256] = { 0 };
    bool 上次输入框聚焦 = false;
    bool 加载错误 = false;
    const char* 错误信息 = "";
    const char* NameForAction = "";
    bool  显示使用了什么动作 = false;
};
inline PlayerActionCheat PlayerAction;




inline void PlayerActionCheat::DrawPlayerActonUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
	ImGui::Checkbox((const char*)u8"打开玩家动作窗口", &打开玩家动作窗口);
    if (打开玩家动作窗口)
    {
        DrawNewPlayerActionUI(CheatManager, lib);
        FixUseAction(1.f);
    }


}

inline void PlayerActionCheat::DrawNewPlayerActionUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!打开玩家动作窗口) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool 当前输入框聚焦 = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (当前输入框聚焦 && !上次输入框聚焦) {
        输入法需要激活 = true;
        strcpy_s(临时搜索文本, 搜索动作);
    }

    if (!当前输入框聚焦 && 上次输入框聚焦) {
        strcpy_s(搜索动作, 临时搜索文本);
    }

    上次输入框聚焦 = 当前输入框聚焦;

    if (ImGui::Begin((const char*)u8"动作加载管理", &打开玩家动作窗口, 0))
    {
        ImGui::Checkbox((const char*)u8"是否循环执行动作（开启后需要使用动作才会循环执行）", &循环执行);
        ImGui::InputInt((const char*)u8"几帧执行一次", &几帧执行一次);
        if (输入法需要激活) {
            if (ImGui::InputTextWithHint((const char*)u8"搜索动作", (const char*)u8"输入动作名称搜索...",
                临时搜索文本, IM_ARRAYSIZE(临时搜索文本))) {
                strcpy_s(搜索动作, 临时搜索文本);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"搜索动作", (const char*)u8"输入动作名称搜索...",
                搜索动作, IM_ARRAYSIZE(搜索动作))) {
                // 正常处理
            }
        }

        ImGui::BeginGroup();

        if (!动作加载中 && !动作加载完成 && 当前加载索引 == 0 && !动作清除中 && !加载错误) {
            if (ImGui::Button((const char*)u8"开始读取", ImVec2(100, 25))) {
                动作加载中 = true;
                动作加载完成 = false;
                当前加载索引 = 0;
                加载的动作列表.clear();
                当前选中动作 = -1;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if ((!动作加载中 && !动作加载完成 && !动作清除中 && 当前加载索引 > 0) || 加载错误) {
            if (ImGui::Button((const char*)u8"继续加载", ImVec2(100, 25))) {
                动作加载中 = true;
                动作加载完成 = false;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (动作加载中 && !加载错误) {
            if (ImGui::Button((const char*)u8"暂停加载", ImVec2(100, 25))) {
                动作加载中 = false;
            }
        }

        if ((!动作加载中 && !动作清除中 && 动作加载完成) || (!动作加载中 && !动作清除中 && 加载错误)) {
            if (ImGui::Button((const char*)u8"清除所有加载", ImVec2(125, 25))) {
                动作清除中 = true;
                清除暂停中 = false;
                动作加载完成 = false;
                当前清除索引 = 0;
                初始动作数量 = 加载的动作列表.size();
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (动作清除中 && !清除暂停中) {
            if (ImGui::Button((const char*)u8"暂停清除", ImVec2(100, 25))) {
                清除暂停中 = true;
            }
        }
        else if (动作清除中 && 清除暂停中) {
            if (ImGui::Button((const char*)u8"继续清除", ImVec2(100, 25))) {
                清除暂停中 = false;
            }
        }

        if ((!动作加载中 && !动作清除中 && 动作加载完成) || (!动作加载中 && !动作清除中 && 加载错误)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"重新加载", ImVec2(100, 25))) {
                动作加载中 = true;
                动作加载完成 = false;
                当前加载索引 = 0;
                加载的动作列表.clear();
                当前选中动作 = -1;
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

        if (动作加载中 || 当前加载索引 > 0) {
            const size_t totalActions = sizeof(AllPlayerActionModeName) / sizeof(AllPlayerActionModeName[0]);
            float progress = (float)当前加载索引 / (float)totalActions;

            if (动作加载中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (加载错误)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (动作加载中)
                ImGui::Text((const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个动作)",
                    progress * 100, 当前加载索引, totalActions);
            else if (加载错误)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"加载已暂停: %.1f%% (已加载 %zu/%zu 个动作)",
                    progress * 100, 当前加载索引, totalActions);
            else if (!动作加载完成)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个动作)",
                    progress * 100, 当前加载索引, totalActions);

            ImGui::Spacing();

            if (动作加载中 && 当前加载索引 > 0 && 当前加载索引 <= totalActions) {
                const char* currentActionName = AllPlayerActionModeNameShow[当前加载索引 - 1];
                ImGui::Text((const char*)u8"当前加载: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!动作加载中 && !动作清除中 && !加载错误 && 当前加载索引 > 0 && !动作加载完成) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"加载已暂停，点击继续加载");

                if (当前加载索引 > 0 && 当前加载索引 <= totalActions) {
                    const char* currentActionName = AllPlayerActionModeNameShow[当前加载索引 - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"当前加载到: %s (位置: %zu/%zu)",
                        currentActionName, 当前加载索引, totalActions);
                }
            }
            else if (动作加载完成) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"已加载全部 %zu 个动作", totalActions);
            }
        }

        if (动作清除中) {
            float clearProgress = (float)当前清除索引 / (float)初始动作数量;
            size_t actionsRemoved = 当前清除索引;

            if (!清除暂停中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!清除暂停中)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"清除进度: %.1f%% (已删除 %zu/%zu 个动作)",
                    clearProgress * 100, actionsRemoved, 初始动作数量);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"清除已暂停: %.1f%% (已删除 %zu/%zu 个动作)",
                    clearProgress * 100, actionsRemoved, 初始动作数量);

            ImGui::Spacing();

            if (!加载的动作列表.empty()) {
                size_t currentActionIndex = 加载的动作列表.size() - 1;
                if (currentActionIndex < sizeof(AllPlayerActionModeNameShow) / sizeof(AllPlayerActionModeNameShow[0])) {
                    const char* currentActionName = AllPlayerActionModeNameShow[currentActionIndex];
                    size_t originalPosition = 初始动作数量 - 当前清除索引;

                    if (!清除暂停中)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"正在删除: %s (位置: %zu/%zu)",
                            currentActionName, originalPosition, 初始动作数量);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"清除已暂停在: %s (位置: %zu/%zu)",
                            currentActionName, originalPosition, 初始动作数量);
                }
            }
        }

        ImGui::Separator();

        if ((!加载的动作列表.empty() && (!动作清除中 || 清除暂停中)) || 动作加载完成) {
            const size_t totalActions = 加载的动作列表.size();

            if (当前选中动作 >= 0 && 当前选中动作 < totalActions) {
                size_t selectedItemIndex = 当前选中动作;
                if (selectedItemIndex < sizeof(AllPlayerActionModeNameShow) / sizeof(AllPlayerActionModeNameShow[0]) &&
                    selectedItemIndex < sizeof(AllPlayerActionModeName) / sizeof(AllPlayerActionModeName[0])) {
                    const char* displayName = AllPlayerActionModeNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"当前选中: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"动作列表", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllPlayerActionModeNameShow[i];
                if (搜索动作[0] != '\0' && strstr(displayName, 搜索动作) == nullptr) {
                    continue;
                }

                bool is_selected = (当前选中动作 == i);
                if (ImGui::Selectable(displayName, is_selected))
                    当前选中动作 = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (ImGui::Button((const char*)u8"使用动作", ImVec2(ImGui::GetContentRegionAvail().x - 3, 25)))
            {
                if (当前选中动作 >= 0 && 当前选中动作 < totalActions) {
                    size_t actionIndex = 当前选中动作;
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
        else if (!动作加载中 && !动作加载完成 && !动作清除中) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"请先加载动作");
        }

        ImGui::End();
    }
}

inline void PlayerActionCheat::FixUseAction(float deltaTime)
{
    if (!动作加载中 && (!动作清除中 || 清除暂停中)) return;

    static float 计时器 = 0.0f;
    计时器 += deltaTime;

    if (计时器 >= 0.2f) {
        计时器 = 0.0f;

        if (动作加载中 && !加载错误) {
            const size_t totalActions = sizeof(AllPlayerActionModeName) / sizeof(AllPlayerActionModeName[0]);

            if (当前加载索引 < totalActions) {
                if (AllPlayerActionModeNameShow[当前加载索引] == nullptr ||
                    AllPlayerActionModeNameShow[当前加载索引][0] == '\0') {
                    动作加载中 = false;
                    加载错误 = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "动作数据错误：索引 %zu 处的 AllPlayerActionModeNameShow 为 null 或空值",
                        当前加载索引);
                    错误信息 = errorMsg;
                    动作加载完成 = true;
                    printf("错误: %s\n", errorMsg);
                    return;
                }

                加载的动作列表.push_back(AllPlayerActionModeNameShow[当前加载索引]);
                当前加载索引++;
                动作加载进度 = (float)当前加载索引 / totalActions;
            }
            else {
                动作加载中 = false;
                动作加载完成 = true;
            }
        }

        if (动作清除中 && !清除暂停中) {
            if (!加载的动作列表.empty()) {
                size_t lastIndex = 加载的动作列表.size() - 1;
                const char* removedAction = 加载的动作列表[lastIndex];
                加载的动作列表.pop_back();
                当前清除索引++;

                if (当前选中动作 >= 0 && 当前选中动作 >= 加载的动作列表.size()) {
                    当前选中动作 = -1;
                }
            }
            else {
                动作清除中 = false;
                清除暂停中 = false;
                当前加载索引 = 0;
                当前选中动作 = -1;
            }
        }
    }
}