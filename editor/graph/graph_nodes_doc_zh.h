#ifndef VOXEL_GRAPH_NODES_DOC_ZH_H
#define VOXEL_GRAPH_NODES_DOC_ZH_H

// ════════════════════════════════════════════════════════════════════════════
//  godot_voxel 节点描述 · 中文表（本项目维护）
// ════════════════════════════════════════════════════════════════════════════
//
//  ## 为什么单独一个文件
//  官方 `graph_nodes_doc_data.h` 是 <GENERATED> 的（由 `doc/graph_nodes.xml`
//  经 `doc/tools/graph_nodes_doc.py` 生成）。直接改它，官方更新时会冲突。
//  ⇒ 本文件与官方数据**完全分离**：官方那份保持原样，中文独立维护。
//
//  ## 怎么用（只改 `voxel_graph_node_dialog.cpp` 两处）
//  1) 在 `#include "graph_nodes_doc_data.h"` 后面加一行：
//         #include "graph_nodes_doc_zh.h"
//  2) 把该文件里 `description = doc->description;` 改成：
//         description = GraphNodesDocDataZh::translated_description(type.name, doc->description);
//
//  ## ⚠️ 编码要求（重要）
//  本文件含中文，**必须以 UTF-8 保存**。若 MSVC 报编码警告（如 C4819），
//  有两个办法（任选）：
//    a) 把本文件另存为「UTF-8 with BOM」（MSVC 见到 BOM 一定按 UTF-8 处理）；
//    b) 编译命令带 `/utf-8`（Godot 的 SCons 对 MSVC 通常默认已带）。
//  ⚠️ 另外：CI 的编译参数含 `voxel_werror=yes`（警告即错误）⇒ 见汉化说明里的处理建议。
//
//  ## ⚠️ 为什么用 String::utf8() 而不是直接返回 const char*
//  Godot 的 `String(const char*)` 是按 **Latin-1（逐字节）** 解释的，
//  直接用它包中文会**乱码**。必须显式 `String::utf8(...)` 才能正确解码 UTF-8。
//
//  ## 数据来源
//  官方英文原文：`doc/graph_nodes.xml` @ commit 045ff93（2026-10-01，59 个节点）
//  中文说明另见：`体素系统/节点对照库.md`（含注意事项与实测坑）
// ════════════════════════════════════════════════════════════════════════════

#include "../../util/godot/core/string.h"

namespace GraphNodesDocDataZh {

struct Entry {
	const char *name;
	const char *description;
};

static const Entry ZH_ENTRIES[] = {
		{ "Abs", "若 x 为负，返回其相反数；否则原样返回。" },
		{ "Add", "返回 a + b。" },
		{ "Clamp", "x 小于 min 返回 min；大于 max 返回 max；否则返回 x。" },
		{ "ClampC", "同 Clamp，但上下限为常量参数（引擎内部优化用）。" },
		{ "Comment", "带文字的矩形注释框，用于整理图结构。" },
		{ "Constant", "输出一个固定数值。" },
		{ "Curve", "返回自定义 Curve 资源在 x 处的值（x 范围见曲线 domain，4.3 及更早固定为 [0,1]）。" },
		{ "CustomInput", "输出同名「自定义输入」的值（仅 VoxelGraphFunction 子图可用）。" },
		{ "CustomOutput", "设置同名「自定义输出」的值（仅 VoxelGraphFunction 子图可用）。" },
		{ "Distance2D", "返回 2D 两点 (x0,y0) 与 (x1,y1) 之间的距离。" },
		{ "Distance3D", "返回 3D 两点 (x0,y0,z0) 与 (x1,y1,z1) 之间的距离。" },
		{ "Divide", "返回 a / b。注意：除零会输出 NaN，可能导致结果异常，尽量改用 Multiply。" },
		{ "Expression",
				"求值一段数学表达式；变量名会成为节点输入。可用函数：sin、floor、abs、sqrt、fract、stepify、wrap、min、max、clamp、lerp。" },
		{ "FastNoise2D",
				"用 FastNoiseLite 库计算 (x,y) 处的 2D 噪声（noise 参数为 ZN_FastNoiseLite 资源）。比 Noise2D 略快。" },
		{ "FastNoise2_2D",
				"用 FastNoise2 库计算 2D SIMD 噪声（noise 参数为 FastNoise2 资源）。目前支持的最快噪声。" },
		{ "FastNoise2_3D",
				"用 FastNoise2 库计算 (x,y,z) 处的 3D SIMD 噪声（noise 参数为 FastNoise2 资源）。目前支持的最快噪声。" },
		{ "FastNoise3D",
				"用 FastNoiseLite 库计算 (x,y,z) 处的 3D 噪声（noise 参数为 ZN_FastNoiseLite 资源）。比 Noise3D 略快。" },
		{ "FastNoiseGradient2D", "用 FastNoiseLite 的噪声梯度扭曲 2D 坐标 (x,y)。" },
		{ "FastNoiseGradient3D", "用 FastNoiseLite 的噪声梯度扭曲 3D 坐标 (x,y,z)。" },
		{ "Floor", "返回 floor(x)，即不大于 x 的最大整数。" },
		{ "Fract", "返回 x 的小数部分，结果恒为正。" },
		{ "Function",
				"运行一个自定义函数（可复用子图）；参数 0 是子图引用，其后为该子图暴露的参数。" },
		{ "Image",
				"返回 image 在像素坐标 (x,y) 处 R 通道的值（[0..1]）；越界会环绕，不做过滤，需未压缩格式。" },
		{ "InputSDF", "输出当前体素已有的有符号距离（仅特定场景可用，如程序化笔刷）。" },
		{ "InputX", "输出当前体素的 X 坐标。" },
		{ "InputY", "输出当前体素的 Y 坐标。" },
		{ "InputZ", "输出当前体素的 Z 坐标。" },
		{ "Max", "返回 a 与 b 中较大的值。" },
		{ "Min", "返回 a 与 b 中较小的值。" },
		{ "Mix",
				"按 ratio 在 a 与 b 之间插值；ratio=0 返回 a，ratio=1 返回 b，超出 [0,1] 会外推。" },
		{ "Multiply", "返回 a * b。" },
		{ "Noise2D", "用 Godot 的某个 Noise 子类计算 (x,y) 处的 2D 噪声。" },
		{ "Noise3D", "用 Godot 的某个 Noise 子类计算 (x,y,z) 处的 3D 噪声。" },
		{ "Normalize",
				"返回 (x,y,z) 的归一化坐标（长度 1）；第 4 个输出 len 是原向量长度。" },
		{ "OutputSDF", "设置当前体素的有符号距离值（最终输出）。" },
		{ "OutputSingleTexture",
				"设置当前体素的纹理索引；仅单纹理时比 OutputWeight 简单，两者不可混用。" },
		{ "OutputType",
				"设置当前体素的 TYPE 索引，配合 VoxelMesherBlocky 使用；用它就不需要 OutputSDF。" },
		{ "OutputWeight", "设置当前体素某个纹理层的权重；同一 layer 只能有一个输出。" },
		{ "Pow", "返回 x 的 power 次幂，相对较慢。" },
		{ "Powi", "返回 x 的 power 次幂，指数为常数正整数，可能比 Pow 更快。" },
		{ "Relay", "直通节点，用于整理长连线的走向。" },
		{ "Remap",
				"把 [min0,max0] 范围内的 x 线性映射到 [min1,max1]；超出范围会外推。" },
		{ "SdfBox", "返回以原点为中心、尺寸 (size_x,size_y,size_z) 的轴对齐盒子的有符号距离场。" },
		{ "SdfPlane", "返回朝向 Y 轴、位于高度 height 的平面的有符号距离场。" },
		{ "SdfPreview", "调试节点，不参与最终结果；在编辑器中显示接入值的切片。" },
		{ "SdfSmoothSubtract", "从 a 中减去 b，带 SdfSmoothUnion 同样的平滑。" },
		{ "SdfSmoothUnion", "返回两个有符号距离场 a、b 的平滑并集；smoothness 越大过渡越宽。" },
		{ "SdfSphere", "返回以原点为球心、半径 radius 的球的有符号距离场。" },
		{ "SdfSphereHeightmap",
				"返回球形高度图近似的有符号距离场；image 为全景投影图，需未压缩格式。" },
		{ "SdfTorus",
				"返回以原点为中心、朝向 Y 轴的圆环的有符号距离场；radius1 环半径，radius2 管粗。" },
		{ "Select", "若 t 小于 threshold 返回 a，否则返回 b（硬切换）。" },
		{ "Sin", "返回 sin(x)。" },
		{ "Smoothstep",
				"在 edge0 与 edge1 之间对 x 平滑插值：x≤edge0 返回 0，x≥edge1 返回 1，中间为 S 形曲线。" },
		{ "Spots2D",
				"为矿脉生成优化的 cellular 噪声：2D 每格放一个圆形斑点，在斑内返回 1、否则 0。" },
		{ "Spots3D",
				"为矿脉生成优化的 cellular 噪声：3D 每格放一个圆形斑点，在斑内返回 1、否则 0。" },
		{ "Sqrt", "返回 sqrt(x)。注意：x 为负时返回 0 而非 NaN。" },
		{ "Stepify", "把 x 吸附到 step 的整数倍（同 GDScript 的 stepify）。" },
		{ "Subtract", "返回 a - b。" },
		{ "Wrap",
				"把 x 环绕到 [0,length]（同 GDScript 的 wrapf(x,0,max)）。注意：length 为 0 时返回 NaN。" },
};

static const unsigned int ZH_COUNT = sizeof(ZH_ENTRIES) / sizeof(ZH_ENTRIES[0]);

// 查中文描述；查不到则回落官方英文原文。
// ⚠️ 必须用 String::utf8()：Godot 的 String(const char*) 按 Latin-1 解释，直接包中文会乱码。
inline String translated_description(const String &p_node_name, const String &p_fallback) {
	for (unsigned int i = 0; i < ZH_COUNT; ++i) {
		// 节点名均为 ASCII，逐字节比较安全
		if (p_node_name == ZH_ENTRIES[i].name) {
			return String::utf8(ZH_ENTRIES[i].description);
		}
	}
	return p_fallback;
}

} // namespace GraphNodesDocDataZh

#endif // VOXEL_GRAPH_NODES_DOC_ZH_H
