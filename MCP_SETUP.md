# 算法题 MCP 配置

本仓库通过 [`.codex/config.toml`](.codex/config.toml) 配置了两个项目级 MCP：

| MCP | 当前版本 | 拉取题目 | 每日一题 | 运行/提交评测 |
| --- | --- | --- | --- | --- |
| `luogu` | `luogu-mcp-server@0.2.0` | 支持 | 无专用工具 | **不支持**，上游目前只读 |
| `leetcode` | `@jinzcdev/leetcode-mcp-server@1.4.0` | 支持 | 支持 | 登录后支持 |

依赖由 `npx` 首次启动时下载，不需要把两个 MCP 源码复制进本仓库。版本已固定，避免某次自动更新突然改变工具行为。

## 首次启用

1. 用桌面浏览器登录 [LeetCode 中国站](https://leetcode.cn/)。
2. 在浏览器开发者工具的 Cookies 中复制 `LEETCODE_SESSION` 的**值**。它等同于账号凭证，不要发进聊天、截图或提交到 Git。
3. 在 PowerShell 中运行：

   ```powershell
   .\scripts\set-leetcode-session.ps1
   ```

   脚本使用隐藏输入，并把 Cookie 保存到当前 Windows 用户的环境变量中。Windows 用户环境变量本身不是加密保险箱；这台电脑应当只由可信用户使用。

4. 完全退出并重新打开 ChatGPT/Codex，重新打开并信任本项目。
5. 在 Codex 中输入 `/mcp`，确认 `luogu` 和 `leetcode` 均已连接。可以先让 Codex 调用 `get_user_status` 验证 LeetCode 登录状态。

Cookie 失效后重复上述步骤即可。需要清除凭证时运行：

```powershell
.\scripts\set-leetcode-session.ps1 -Clear
```

## 使用方式

可以从手机上的 Codex Remote 继续控制连接的 Windows 电脑，例如：

- “拉取 LeetCode 今日每日一题，按仓库规则建立题面文件，先不要讲答案。”
- “找一道洛谷的最短路练习，保存题面；只和我讨论思路。”
- “把我确认过的思路实现为 C++，本地检查后用 LeetCode `run_code` 测试。”
- “我确认提交这份代码，调用 `submit_solution` 并告诉我评测结果。”

项目规则仍然生效：没有明确要求时，不公布答案；从网上找题时顺手保存题面；题目、代码和题解按 `AGENTS.md` 约定落盘。`run_code`、`submit_solution` 以及在线笔记写入被配置为需要确认。

## 站点与能力边界

LeetCode 默认使用中国站。若账号在全球站，把 `.codex/config.toml` 中的 `LEETCODE_SITE = "cn"` 改成 `"global"`，重新设置对应站点的 Cookie 后重启 Codex。

洛谷 MCP 当前只提供题目搜索、题面、题单、相关推荐和公开用户资料。它没有登录、运行代码或提交评测工具，所以不能借此直接向洛谷提交。若以后上游加入安全的认证与提交工具，再更新固定版本并重新检查工具权限。

手机只负责远程发指令；MCP、源码文件和评测请求实际仍在连接的电脑上执行。因此电脑需要保持开机、联网，ChatGPT/Codex 桌面端也要保持可远程连接。
