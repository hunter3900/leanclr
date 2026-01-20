# LeanCLR

语言: [中文](./README.md) | [English](./README_EN.md)

[![GitHub](https://img.shields.io/badge/GitHub-Repository-181717?logo=github)](https://github.com/focus-creative-games/leanclr) [![Gitee](https://img.shields.io/badge/Gitee-Repository-C71D23?logo=gitee)](https://gitee.com/focus-creative-games/leanclr)

[![license](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/focus-creative-games/leanclr/blob/main/LICENSE) [![DeepWiki](https://deepwiki.com/badge.svg)](https://deepwiki.com/focus-creative-games/leanclr) [![Discord](https://img.shields.io/badge/Discord-Join-7289DA?logo=discord&logoColor=white)](https://discord.gg/esAYcM6RDQ)

LeanCLR 是一个面向全平台的精练的 CLR（Common Language Runtime）实现。LeanCLR 的设计目标是在高度符合 ECMA-335 规范的前提下，提供更紧凑、易嵌入、低内存占用的运行时，实现对移动端、H5 与小游戏等资源受限平台的友好支持。

## 为什么选择 LeanCLR

业界已有 CoreCLR、Mono、IL2CPP 等成熟的 CLR 实现，为什么还需要 LeanCLR？

### 现有方案的局限性

| 运行时 | 主要问题 |
|--------|----------|
| **CoreCLR** | 体积庞大（数十 MB），代码复杂度高，难以裁剪和嵌入；不适合资源受限场景 |
| **Mono** | 历史包袱重，架构复杂；虽可裁剪但仍偏大；维护和定制成本高 |
| **IL2CPP** | 闭源，仅支持 AOT；ECMA-335 完整度有限；wasm 体积和内存占用偏高 |

### LeanCLR 的设计理念

LeanCLR 从零设计，专注于以下核心目标：

- **极致精简** — 单线程版本在 Win64/WebAssembly 平台仅约 **600 KB**，裁剪后可低至 **300 KB**
- **易于嵌入** — 纯 C++17 实现，无外部依赖，可轻松集成到任何 C++ 项目
- **跨平台一致性** — AOT + Interpreter 混合模式，放弃 JIT，确保全平台行为一致
- **可维护性** — 代码结构清晰，便于理解、定制和二次开发

LeanCLR 特别适合以下场景：

- 📱 移动端游戏和应用（iOS/Android）
- 🌐 H5 游戏和小游戏平台（微信小游戏、抖音小游戏等）
- 🎮 需要热更新能力的游戏客户端
- 🔧 嵌入式系统和 IoT 设备

## 特性与优势

### 标准兼容性

- **高度兼容 ECMA-335** — 几乎完整实现 CLI 规范，覆盖范围高于 `IL2CPP + HybridCLR`
- **支持现代 C# 特性** — 泛型、异常处理、反射、委托、LINQ 等核心特性完整支持
- **CoreCLR 扩展支持**（规划中）— 接口静态虚方法（.NET 7+）等扩展特性
- **精简设计** — 仅移除已废弃的过时特性（如 `arglist`、`jmp` 指令）

### 极致轻量

- **超小体积** — 单线程版本约 **600 KB**；裁剪 IR 解释器和非必要 icall 后可缩至 **300 KB** 甚至更小
- **低内存占用** — 优化的元数据表示，支持方法体元数据按需回收
- **精细化对齐** — 按元数据/托管对象的实际对齐需求使用独立分配池，避免统一 8 字节对齐的内存浪费
- **紧凑对象头** — 单线程版本对象头仅占一个指针大小

### 执行模式

- **AOT + Interpreter 混合执行** — 兼顾启动速度和运行效率，跨平台行为一致
- **双解释器架构** — IL 解释器处理冷路径，IR 解释器优化热点函数，平衡编译开销与执行性能
- **函数粒度 AOT** — 支持按函数选择 AOT 或解释执行，精细化权衡包体与性能
- **异常路径兜底** — 异常处理由解释器统一兜底，显著简化 AOT 代码体积

### 跨平台能力

- **纯 C++ 实现** — 基于 C++17 标准，零平台特定依赖
- **无异常机制依赖** — 不依赖 C++ 异常，可在禁用异常的环境下编译运行
- **零移植成本** — 可直接编译到任何支持 C++17 的平台（Windows、Linux、macOS、iOS、Android、WebAssembly 等）

### 代码质量

- **结构清晰** — 模块化设计，职责分明，易于理解和导航
- **易于定制** — 简洁的代码库便于根据需求裁剪和扩展
- **便于优化** — 清晰的执行路径，性能瓶颈易于定位和优化

## 版本说明

LeanCLR 提供两个版本，以满足不同场景的需求：

| 特性 | Universal 版本 | Standard 版本 |
|------|---------------|---------------|
| **线程模型** | 单线程 | 多线程 |
| **执行模式** | AOT + Interpreter | AOT + Interpreter |
| **P/Invoke** | 仅支持 AOT 函数 | 仅支持 AOT 函数 |
| **垃圾回收** | 精确协助式 GC | 保守式 GC |
| **平台 icall** | 未实现 | 完整实现 |
| **平台依赖** | 无 | 需适配平台接口 |
| **移植成本** | 零成本 | 需处理平台相关接口 |
| **适用场景** | WebAssembly、嵌入式、跨平台一致性要求高 | 桌面/移动端、需要完整系统功能 |

### Universal 版本

**设计目标**：极致的跨平台能力和可移植性

- **单线程执行** — 简化内存模型，无需考虑线程同步
- **AOT + Interpreter 混合执行** — 灵活的执行策略
- **精确协助式 GC** — 精确追踪托管引用，内存回收高效
- **零平台依赖** — 不依赖任何操作系统或平台特定函数
- **标准 C++17 实现** — 可直接编译运行于任何支持 C++17 标准的平台
- **未实现平台相关 icall** — 如 `System.IO.File` 等需自行桥接或使用纯托管实现

**最佳适用场景**：WebAssembly、嵌入式系统、IoT 设备、对跨平台一致性要求极高的项目

### Standard 版本

**设计目标**：功能完整的生产级运行时

- **多线程支持** — 完整的线程模型和同步原语
- **AOT + Interpreter 混合执行** — 灵活的执行策略
- **保守式 GC** — 兼容性更好，适合复杂应用场景
- **完整平台 icall** — 实现 `System.IO`、`System.Net` 等平台相关功能
- **标准 C++17 实现** — 移植到新平台时需要适配少量平台相关接口

**最佳适用场景**：桌面应用、移动端游戏、需要完整 .NET 基础库功能的项目

## 项目状态

### 当前进度

| 模块 | 状态 | 说明 |
|------|------|------|
| **元数据解析** | ✅ 完成 | 完整支持 PE/COFF 格式和 CLI 元数据表 |
| **类型系统** | ✅ 完成 | 类、接口、泛型、数组、值类型等 |
| **IL 解释器** | 🔶 开发中 | 覆盖几乎所有 ECMA-335 IL 指令 |
| **IR 解释器** | ✅ 完成 | 热点函数优化执行 |
| **异常处理** | ✅ 完成 | try/catch/finally、嵌套异常等 |
| **反射** | ✅ 完成 | Type、MethodInfo、FieldInfo 等核心 API |
| **委托** | ✅ 完成 | 单播/多播委托、泛型委托 |
| **内部调用** | 🔶 进行中 | 核心 icall 已实现，平台相关 icall 持续补充 |
| **垃圾回收** | 🔶 开发中 | 基础框架已就绪 |
| **AOT 编译器** | 📋 规划中 | IL → C++ 转译 |
| **P/Invoke** | � 部分完成 | 已支持手动注册，自动化支持依赖 AOT 编译器 |
| **多线程** | 📋 规划中 | 线程、同步原语等 |

### ECMA-335 兼容性

- 完整度高于 `IL2CPP + HybridCLR` 组合
- 完整度略低于 Mono（主要差距在平台相关 icall）
- CoreCLR 扩展特性（如接口静态虚方法）将在后续版本实现

### 稳定性

目前版本版本已经达到**非常高**的稳定性水平。

- 与Unity 2019.4.x - 6000.3.x LTS il2cpp的 BCL 完全兼容，通过全部（数千个）测试用例。
- 与mono 4.8的 BCL 99.95%兼容，仅一个测试用例失败。

### 路线图

**近期目标：**

- 完善垃圾回收器实现
- 实现 AOT 编译器（IL → C++）
- 完善 P/Invoke 自动化支持（依赖 AOT 编译器）
- 支持 CoreCLR 扩展特性
- 提供更完整的示例和文档

**中期目标：**

- 补充更多平台相关的内部调用（如 `System.IO`）
- 多线程支持

**长期目标：**

- 性能持续优化
- 更广泛的平台支持

## 项目结构

详细的项目结构说明请参阅 [项目结构文档](./docs/project_structure.md)。

```
leanclr/
├── src/
│   ├── runtime/      # LeanCLR 运行时核心
│   ├── libraries/    # 基础类库
│   ├── tools/        # 命令行工具
│   ├── samples/      # 示例项目
│   └── tests/        # 单元测试
├── docs/             # 文档
└── tools/            # 构建辅助工具
```

## 文档

详细文档位于 [docs](./docs) 目录：

- [文档概览](./docs/README.md) - 文档结构和导航
- [构建文档](./docs/build/README.md) - 构建相关文档概述
- [构建运行时](./docs/build/build_runtime.md) - 如何构建 LeanCLR 运行时
- [嵌入 LeanCLR](./docs/build/embed_leanclr.md) - 如何将 LeanCLR 集成到您的项目
- [测试框架](./src/tests/README.md) - 单元测试框架和测试用例编写指南

## 快速构建

### Windows (Visual Studio)

```cmd
cd src/runtime
build.bat Release
```

### WebAssembly

```cmd
# 1. 准备 Emscripten SDK 环境
emsdk_env.bat

# 2. 构建
cd src/samples/lean-wasm
build-wasm.bat
```

更多详细说明请参阅 [构建文档](./docs/build/build_runtime.md)。

## Demo

[leanclr-demo](https://github.com/focus-creative-games/leanclr-demo) 提供两个平台的示例用于快速体验 LeanCLR 的功能：

| 示例 | 说明 |
|------|------|
| **win64** | Windows x64 平台示例，运行 `run.bat` 即可执行 |
| **h5** | WebAssembly 浏览器示例，通过 HTTP 服务器访问 `index.html` |

## 联系方式

- 邮箱：leanclr#code-philosophy.com
- discord 频道： <https://discord.gg/esAYcM6RDQ>
- QQ群：1047250380
