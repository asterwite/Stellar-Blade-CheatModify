#include "PlayerTalk.h"
#include "NameForLoop/QuickItem.h"
#include "..\..\ConfigSet\KeySet.h"
class QuickItemUseLoop
{
public:
    bool 打开玩家快捷物品窗口 = false;
    int WaitTime = 0;
    int UseKey = 0;
    void DrawQuickItemUseLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void DrawNewQuickItemUseLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib);
    void FixUseAction(float deltaTime);
    char  使用快捷物品的名称[255];
    int 当前选中快捷物品 = -1;
    bool 快捷物品加载中 = false;
    bool 快捷物品加载完成 = false;
    float 快捷物品加载进度 = 0.0f;
    size_t 当前加载索引 = 0;
    std::vector<const char*> 加载的快捷物品列表;
    char 搜索快捷物品[256] = { 0 };
    bool 快捷物品清除中 = false;
    size_t 当前清除索引 = 0;
    size_t 初始快捷物品数量 = 0;
    bool 清除暂停中 = false;
    bool 输入法需要激活 = false;
    char 临时搜索文本[256] = { 0 };
    bool 上次输入框聚焦 = false;
    bool 加载错误 = false;
    const char* 错误信息 = "";
    const char* NameForAction = "";
    bool  显示使用了什么快捷物品 = false;
};
inline QuickItemUseLoop QuickItemUse;


inline bool TheUseKey = false; // 热键设置状态

inline KeyBind G_TheUseKey(KeyBind::KeyCode::F2); // 默认热键为INSERT

inline KeyBind TheUseKeyLastKey;

inline bool UseHandleKeySetting() {
    // 取消设置（ESC）
    if (ImGui::IsKeyPressed(ImGuiKey_Escape)) {
        if (TheUseKeyLastKey != G_TheUseKey)
            G_TheUseKey = KeyBind(KeyBind::KeyCode::INSERT); // 恢复默认
        G_TheUseKey = TheUseKeyLastKey;
        return true;
    }

    // 遍历所有按键
    for (int i = 0; i < IM_ARRAYSIZE(ImGui::GetIO().KeysDown); ++i) {
        if (ImGui::IsKeyPressed(static_cast<ImGuiKey>(i))) {
            // 查找keyMap（使用data()比较）
            auto it = std::find_if(keyMap.begin(), keyMap.end(),
                [i](const Key& k) { return k.code == i; });

            if (it != keyMap.end() && it->name != "NONE") {
                // 更新热键（使用data()获取字符串）
                G_TheUseKey = KeyBind(it->name.data()); // 注意：KeyBind构造函数需接受const char*
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
    ImGui::Checkbox((const char*)u8"打开玩家快捷物品窗口", &打开玩家快捷物品窗口);
    if (打开玩家快捷物品窗口)
    {
        DrawNewQuickItemUseLoopUI(CheatManager, lib);
        FixUseAction(1.f);
    }
}

inline void QuickItemUseLoop::DrawNewQuickItemUseLoopUI(USBCheatManager* CheatManager, UKismetStringLibrary* lib)
{
    if (!打开玩家快捷物品窗口) return;

    ImVec2 minSize(300, 200);
    ImVec2 maxSize(1920, 1080);
    ImGui::SetNextWindowSizeConstraints(minSize, maxSize);
    ImGui::SetNextWindowSize(ImVec2(500, 450), ImGuiCond_FirstUseEver);

    bool 当前输入框聚焦 = ImGui::IsWindowFocused() && ImGui::IsItemActive();
    if (当前输入框聚焦 && !上次输入框聚焦) {
        输入法需要激活 = true;
        strcpy_s(临时搜索文本, 搜索快捷物品);
    }

    if (!当前输入框聚焦 && 上次输入框聚焦) {
        strcpy_s(搜索快捷物品, 临时搜索文本);
    }

    上次输入框聚焦 = 当前输入框聚焦;

    if (ImGui::Begin((const char*)u8"快捷物品状态加载管理", &打开玩家快捷物品窗口, 0))
    {

            ImGui::Text((const char*)u8"当前快捷使用物品按键: %s", G_TheUseKey.toString());

            // 热键设置按钮
            if (ImGui::Button((const char*)u8"修改快捷使用物品按键", ImVec2(150, 25))) {
                TheUseKey = true; // 进入设置模式
            }

            // 热键设置逻辑
            if (TheUseKey) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"按下新按键");
                ImGui::TextColored(ImVec4(1, 1, 1, 1), (const char*)u8"(按ESC取消，按任意键确认，按下后会关闭窗口，重新按你设置的按键即可)");

                // 处理按键输入
                if (UseHandleKeySetting())
                {
                    UseKey = G_TheUseKey.toInt();
                    TheUseKey = false; // 完成设置后退出模式
                    printf(G_TheUseKey.toString());
                }
            }

        if (输入法需要激活) {
            if (ImGui::InputTextWithHint((const char*)u8"搜索快捷物品状态", (const char*)u8"输入快捷物品状态名称搜索...",
                临时搜索文本, IM_ARRAYSIZE(临时搜索文本))) {
                strcpy_s(搜索快捷物品, 临时搜索文本);
            }
        }
        else {
            if (ImGui::InputTextWithHint((const char*)u8"搜索快捷物品状态", (const char*)u8"输入快捷物品状态名称搜索...",
                搜索快捷物品, IM_ARRAYSIZE(搜索快捷物品))) {
                // 正常处理
            }
        }

        ImGui::BeginGroup();

        if (!快捷物品加载中 && !快捷物品加载完成 && 当前加载索引 == 0 && !快捷物品清除中 && !加载错误) {
            if (ImGui::Button((const char*)u8"开始读取", ImVec2(100, 25))) {
                快捷物品加载中 = true;
                快捷物品加载完成 = false;
                当前加载索引 = 0;
                加载的快捷物品列表.clear();
                当前选中快捷物品 = -1;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if ((!快捷物品加载中 && !快捷物品加载完成 && !快捷物品清除中 && 当前加载索引 > 0) || 加载错误) {
            if (ImGui::Button((const char*)u8"继续加载", ImVec2(100, 25))) {
                快捷物品加载中 = true;
                快捷物品加载完成 = false;
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (快捷物品加载中 && !加载错误) {
            if (ImGui::Button((const char*)u8"暂停加载", ImVec2(100, 25))) {
                快捷物品加载中 = false;
            }
        }

        if ((!快捷物品加载中 && !快捷物品清除中 && 快捷物品加载完成) || (!快捷物品加载中 && !快捷物品清除中 && 加载错误)) {
            if (ImGui::Button((const char*)u8"清除所有加载", ImVec2(125, 25))) {
                快捷物品清除中 = true;
                清除暂停中 = false;
                快捷物品加载完成 = false;
                当前清除索引 = 0;
                初始快捷物品数量 = 加载的快捷物品列表.size();
                加载错误 = false;
                错误信息 = "";
            }
        }
        else if (快捷物品清除中 && !清除暂停中) {
            if (ImGui::Button((const char*)u8"暂停清除", ImVec2(100, 25))) {
                清除暂停中 = true;
            }
        }
        else if (快捷物品清除中 && 清除暂停中) {
            if (ImGui::Button((const char*)u8"继续清除", ImVec2(100, 25))) {
                清除暂停中 = false;
            }
        }

        if ((!快捷物品加载中 && !快捷物品清除中 && 快捷物品加载完成) || (!快捷物品加载中 && !快捷物品清除中 && 加载错误)) {
            ImGui::SameLine();
            if (ImGui::Button((const char*)u8"重新加载", ImVec2(100, 25))) {
                快捷物品加载中 = true;
                快捷物品加载完成 = false;
                当前加载索引 = 0;
                加载的快捷物品列表.clear();
                当前选中快捷物品 = -1;
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

        if (快捷物品加载中 || 当前加载索引 > 0) {
            const size_t totalActions = sizeof(AllQuickItemUseLoopName) / sizeof(AllQuickItemUseLoopName[0]);
            float progress = (float)当前加载索引 / (float)totalActions;

            if (快捷物品加载中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0, 0.7f, 1, 1));
            else if (加载错误)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1, 0, 0, 1));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.7f, 0.7f, 0.7f, 1));

            ImGui::ProgressBar(progress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (快捷物品加载中)
                ImGui::Text((const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个快捷物品状态)",
                    progress * 100, 当前加载索引, totalActions);
            else if (加载错误)
                ImGui::TextColored(ImVec4(1, 0, 0, 1),
                    (const char*)u8"加载已暂停: %.1f%% (已加载 %zu/%zu 个快捷物品状态)",
                    progress * 100, 当前加载索引, totalActions);
            else if (!快捷物品加载完成)
                ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1),
                    (const char*)u8"加载进度: %.1f%% (已加载 %zu/%zu 个快捷物品状态)",
                    progress * 100, 当前加载索引, totalActions);

            ImGui::Spacing();

            if (快捷物品加载中 && 当前加载索引 > 0 && 当前加载索引 <= totalActions) {
                const char* currentActionName = AllQuickItemUseLoopNameShow[当前加载索引 - 1];
                ImGui::Text((const char*)u8"当前加载: %s", currentActionName);
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0, 0.7f, 1, 1));
                ImGui::Text(currentActionName);
                ImGui::PopStyleColor();
            }
            else if (!快捷物品加载中 && !快捷物品清除中 && !加载错误 && 当前加载索引 > 0 && !快捷物品加载完成) {
                ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"加载已暂停，点击继续加载");

                if (当前加载索引 > 0 && 当前加载索引 <= totalActions) {
                    const char* currentActionName = AllQuickItemUseLoopNameShow[当前加载索引 - 1];
                    ImGui::TextColored(ImVec4(1, 0.7f, 0, 1),
                        (const char*)u8"当前加载到: %s (位置: %zu/%zu)",
                        currentActionName, 当前加载索引, totalActions);
                }
            }
            else if (快捷物品加载完成) {
                ImGui::TextColored(ImVec4(0, 1, 0, 1), (const char*)u8"已加载全部 %zu 个快捷物品状态", totalActions);
            }
        }

        if (快捷物品清除中) {
            float clearProgress = (float)当前清除索引 / (float)初始快捷物品数量;
            size_t actionsRemoved = 当前清除索引;

            if (!清除暂停中)
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.3f, 0.3f, 1.0f));
            else
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(1.0f, 0.7f, 0.3f, 1.0f));

            ImGui::ProgressBar(clearProgress, ImVec2(-1, 20));
            ImGui::PopStyleColor();

            if (!清除暂停中)
                ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                    (const char*)u8"清除进度: %.1f%% (已删除 %zu/%zu 个快捷物品状态)",
                    clearProgress * 100, actionsRemoved, 初始快捷物品数量);
            else
                ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                    (const char*)u8"清除已暂停: %.1f%% (已删除 %zu/%zu 个快捷物品状态)",
                    clearProgress * 100, actionsRemoved, 初始快捷物品数量);

            ImGui::Spacing();

            if (!加载的快捷物品列表.empty()) {
                size_t currentActionIndex = 加载的快捷物品列表.size() - 1;
                if (currentActionIndex < sizeof(AllQuickItemUseLoopNameShow) / sizeof(AllQuickItemUseLoopNameShow[0])) {
                    const char* currentActionName = AllQuickItemUseLoopNameShow[currentActionIndex];
                    size_t originalPosition = 初始快捷物品数量 - 当前清除索引;

                    if (!清除暂停中)
                        ImGui::TextColored(ImVec4(1.0f, 0.3f, 0.3f, 1.0f),
                            (const char*)u8"正在删除: %s (位置: %zu/%zu)",
                            currentActionName, originalPosition, 初始快捷物品数量);
                    else
                        ImGui::TextColored(ImVec4(1.0f, 0.7f, 0.3f, 1.0f),
                            (const char*)u8"清除已暂停在: %s (位置: %zu/%zu)",
                            currentActionName, originalPosition, 初始快捷物品数量);
                }
            }
        }

        ImGui::Separator();

        if ((!加载的快捷物品列表.empty() && (!快捷物品清除中 || 清除暂停中)) || 快捷物品加载完成) {
            const size_t totalActions = 加载的快捷物品列表.size();

            if (当前选中快捷物品 >= 0 && 当前选中快捷物品 < totalActions) {
                size_t selectedItemIndex = 当前选中快捷物品;
                if (selectedItemIndex < sizeof(AllQuickItemUseLoopNameShow) / sizeof(AllQuickItemUseLoopNameShow[0]) &&
                    selectedItemIndex < sizeof(AllQuickItemUseLoopName) / sizeof(AllQuickItemUseLoopName[0])) {
                    const char* displayName = AllQuickItemUseLoopNameShow[selectedItemIndex];
                    ImGui::TextColored(ImVec4(1, 1, 0, 1),
                        (const char*)u8"当前选中: %s\t",
                        displayName);
                }
                ImGui::Separator();
            }

            ImGui::BeginChild((const char*)u8"快捷物品状态列表", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 4), true);

            for (size_t i = 0; i < totalActions; i++)
            {
                const char* displayName = AllQuickItemUseLoopNameShow[i];
                if (搜索快捷物品[0] != '\0' && strstr(displayName, 搜索快捷物品) == nullptr) {
                    continue;
                }

                bool is_selected = (当前选中快捷物品 == i);
                if (ImGui::Selectable(displayName, is_selected))
                    当前选中快捷物品 = i;

                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }

            ImGui::EndChild();

            if (当前选中快捷物品 >= 0 && 当前选中快捷物品 < totalActions) 
            {
                size_t actionIndex = 当前选中快捷物品;
                if (actionIndex < sizeof(AllQuickItemUseLoopName) / sizeof(AllQuickItemUseLoopName[0])) {
                    const char* actionInternalName = AllQuickItemUseLoopName[actionIndex];
                    NameForAction = actionInternalName;
                }
            }
            
        }
        else if (!快捷物品加载中 && !快捷物品加载完成 && !快捷物品清除中) {
            ImGui::TextColored(ImVec4(1, 0.5f, 0, 1), (const char*)u8"请先加载快捷物品状态");
        }

        ImGui::End();
    }
}
inline void QuickItemUseLoop::FixUseAction(float deltaTime)
{
    if (!快捷物品加载中 && (!快捷物品清除中 || 清除暂停中)) return;

    static float 计时器 = 0.0f;
    计时器 += deltaTime;

    if (计时器 >= 0.2f) {
        计时器 = 0.0f;

        if (快捷物品加载中 && !加载错误) {
            const size_t totalActions = sizeof(AllQuickItemUseLoopName) / sizeof(AllQuickItemUseLoopName[0]);

            if (当前加载索引 < totalActions) {
                if (AllQuickItemUseLoopNameShow[当前加载索引] == nullptr ||
                    AllQuickItemUseLoopNameShow[当前加载索引][0] == '\0') {
                    快捷物品加载中 = false;
                    加载错误 = true;
                    char errorMsg[256];
                    sprintf_s(errorMsg, "快捷物品数据错误：索引 %zu 处的 AllQuickItemUseLoopNameShow 为 null 或空值",
                        当前加载索引);
                    错误信息 = errorMsg;
                    快捷物品加载完成 = true;
                    printf("错误: %s\n", errorMsg);
                    return;
                }

                加载的快捷物品列表.push_back(AllQuickItemUseLoopNameShow[当前加载索引]);
                当前加载索引++;
                快捷物品加载进度 = (float)当前加载索引 / totalActions;
            }
            else {
                快捷物品加载中 = false;
                快捷物品加载完成 = true;
            }
        }

        if (快捷物品清除中 && !清除暂停中) {
            if (!加载的快捷物品列表.empty()) {
                size_t lastIndex = 加载的快捷物品列表.size() - 1;
                const char* removedAction = 加载的快捷物品列表[lastIndex];
                加载的快捷物品列表.pop_back();
                当前清除索引++;

                if (当前选中快捷物品 >= 0 && 当前选中快捷物品 >= 加载的快捷物品列表.size()) {
                    当前选中快捷物品 = -1;
                }
            }
            else {
                快捷物品清除中 = false;
                清除暂停中 = false;
                当前加载索引 = 0;
                当前选中快捷物品 = -1;
            }
        }
    }
}