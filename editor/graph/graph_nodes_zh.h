#ifndef VOXEL_GRAPH_NODES_ZH_H
#define VOXEL_GRAPH_NODES_ZH_H

// ════════════════════════════════════════════════════════════════════════════
//  godot_voxel 节点「名字 + 参数」中文对照表（本项目维护）
// ════════════════════════════════════════════════════════════════════════════
//
//  ## 与 `graph_nodes_doc_zh.h` 的分工
//   · `graph_nodes_doc_zh.h`  → **节点描述**（创建对话框右下角那块文字）
//   · 本文件                → **节点名** + **参数名** + **参数描述**（悬停提示）
//
//  ## ⚠️⚠️ 最重要的一条：本表只用于「显示」，绝不参与逻辑
//  官方代码里有两处名字是**标识符**，改了会直接坏掉：
//   1. `NodeType::name`（如 "SdfSphere"）—— 是**图的序列化键**
//      （`voxel_graph_function.cpp:1152/1954` 的 `try_get_type_id_from_name`），
//      `.tres` 的 graph_data 里存的就是它。**改了所有已有图都加载不了。**
//   2. `PropertyInfo::name`（如 "radius"）—— 是**属性键**
//      （`voxel_graph_node_inspector_wrapper.cpp:253/311` 靠它 `get_node_param_index_by_name` 反查索引）。
//      **改了改参数会直接失效。**
//  ⇒ 所以本文件只被「显示层」调用：
//      · `voxel_graph_node_dialog.cpp`     —— 节点列表的文字
//      · `voxel_graph_editor_node.cpp`     —— 图上节点的标题
//      · `voxel_graph_editor_inspector_plugin.cpp` —— Inspector 的 label + tooltip
//  显示格式统一为 **`中文 (English)`** ⇒ 中文可读 + 英文可搜索 + 能对照官方文档。
//
//  ## ⚠️ 参数描述：官方没有这份数据
//  `doc/graph_nodes.xml` 里 `<parameter>` 只有 name/type/default_value，**没有任何描述文字**。
//  ⇒ 本文件的参数描述是**本项目原创**（依据节点源码语义 + 实测踩过的坑），不保证与官方措辞一致。
//
//  ## ⚠️ 编码
//  本文件含中文，**必须以 UTF-8 保存**（本补丁已带 BOM，MSVC 见了 BOM 一定按 UTF-8 处理）。
//  ⚠️ 必须用 `String::utf8()` 包装，否则 Godot 的 `String(const char*)` 按 Latin-1 解释会乱码。
//
//  统计数据来源：commit 045ff93（2026-10-01）· 节点 59 · 端口/参数去重 65
// ════════════════════════════════════════════════════════════════════════════

#include "../../util/godot/core/string.h"

namespace GraphNodesZh {

struct Entry {
	const char *en;
	const char *zh;
};

// ── 节点名（59 条，按官方 XML 字母序）──────────────────────────────
static const Entry NODE_NAMES[] = {
		{ "Abs", "绝对值" },
		{ "Add", "加法" },
		{ "Clamp", "钳制" },
		{ "ClampC", "常量钳制" },
		{ "Comment", "注释框" },
		{ "Constant", "常量" },
		{ "Curve", "曲线映射" },
		{ "CustomInput", "自定义输入" },
		{ "CustomOutput", "自定义输出" },
		{ "Distance2D", "2D 距离" },
		{ "Distance3D", "3D 距离" },
		{ "Divide", "除法" },
		{ "Expression", "表达式" },
		{ "FastNoise2D", "快速 2D 噪声" },
		{ "FastNoise2_2D", "2D SIMD 噪声" },
		{ "FastNoise2_3D", "3D SIMD 噪声" },
		{ "FastNoise3D", "快速 3D 噪声" },
		{ "FastNoiseGradient2D", "2D 噪声梯度" },
		{ "FastNoiseGradient3D", "3D 噪声梯度" },
		{ "Floor", "向下取整" },
		{ "Fract", "取小数" },
		{ "Function", "子图函数" },
		{ "Image", "贴图采样" },
		{ "InputSDF", "输入 SDF" },
		{ "InputX", "X 坐标" },
		{ "InputY", "Y 坐标" },
		{ "InputZ", "Z 坐标" },
		{ "Max", "取大" },
		{ "Min", "取小" },
		{ "Mix", "线性插值" },
		{ "Multiply", "乘法" },
		{ "Noise2D", "2D 噪声" },
		{ "Noise3D", "3D 噪声" },
		{ "Normalize", "归一化" },
		{ "OutputSDF", "输出 SDF" },
		{ "OutputSingleTexture", "输出单纹理" },
		{ "OutputType", "输出类型" },
		{ "OutputWeight", "输出纹理权重" },
		{ "Pow", "幂" },
		{ "Powi", "整数幂" },
		{ "Relay", "中继" },
		{ "Remap", "区间映射" },
		{ "SdfBox", "SDF 盒" },
		{ "SdfPlane", "SDF 平面" },
		{ "SdfPreview", "SDF 预览" },
		{ "SdfSmoothSubtract", "SDF 平滑差集" },
		{ "SdfSmoothUnion", "SDF 平滑并集" },
		{ "SdfSphere", "SDF 球" },
		{ "SdfSphereHeightmap", "SDF 球面高度图" },
		{ "SdfTorus", "SDF 圆环" },
		{ "Select", "选择" },
		{ "Sin", "正弦" },
		{ "Smoothstep", "平滑阶跃" },
		{ "Spots2D", "2D 斑点" },
		{ "Spots3D", "3D 斑点" },
		{ "Sqrt", "平方根" },
		{ "Stepify", "阶梯化" },
		{ "Subtract", "减法" },
		{ "Wrap", "环绕" },
};

// ── 端口名 / 参数名（65 条，去重后，按出现频次排）─────────────────
static const Entry PORT_NAMES[] = {
		{ "out", "输出" },
		{ "x", "X" },
		{ "y", "Y" },
		{ "z", "Z" },
		{ "a", "A" },
		{ "b", "B" },
		{ "sdf", "距离场" },
		{ "noise", "噪声资源" },
		{ "value", "值" },
		{ "min", "下限" },
		{ "max", "上限" },
		{ "x0", "起点 X" },
		{ "y0", "起点 Y" },
		{ "z0", "起点 Z" },
		{ "x1", "终点 X" },
		{ "y1", "终点 Y" },
		{ "z1", "终点 Z" },
		{ "spot_radius", "斑点半径" },
		{ "image", "图像" },
		{ "smoothness", "平滑度" },
		{ "radius", "半径" },
		{ "seed", "随机种子" },
		{ "cell_size", "格子尺寸" },
		{ "jitter", "抖动" },
		{ "out_x", "输出 X" },
		{ "out_y", "输出 Y" },
		{ "out_z", "输出 Z" },
		{ "nx", "归一化 X" },
		{ "ny", "归一化 Y" },
		{ "nz", "归一化 Z" },
		{ "len", "原向量长度" },
		{ "ratio", "插值比例" },
		{ "index", "索引" },
		{ "type", "类型" },
		{ "weight", "权重" },
		{ "p", "指数" },
		{ "power", "幂次" },
		{ "in", "输入" },
		{ "height", "高度" },
		{ "t", "判断值" },
		{ "threshold", "阈值" },
		{ "step", "步长" },
		{ "length", "长度" },
		{ "text", "文本" },
		{ "curve", "曲线资源" },
		{ "expression", "表达式" },
		{ "_function", "子图资源" },
		{ "filter", "过滤模式" },
		{ "layer", "纹理层" },
		{ "min0", "源区间下限" },
		{ "max0", "源区间上限" },
		{ "min1", "目标区间下限" },
		{ "max1", "目标区间上限" },
		{ "size_x", "X 尺寸" },
		{ "size_y", "Y 尺寸" },
		{ "size_z", "Z 尺寸" },
		{ "min_value", "显示下限" },
		{ "max_value", "显示上限" },
		{ "fraction_period", "网格周期" },
		{ "mode", "显示模式" },
		{ "factor", "高度缩放" },
		{ "radius1", "环半径" },
		{ "radius2", "管粗" },
		{ "edge0", "边界起点" },
		{ "edge1", "边界终点" },
};

// ── 参数描述（65 条，本项目原创；鼠标悬停时显示）────────────────
//  ⚠️ 官方无此数据，内容依据节点源码语义 + 实测经验撰写。
static const Entry PORT_DESCS[] = {
		{ "out", "本节点的计算结果输出。" },
		{ "x", "输入坐标 X（通常来自 InputX 或上游节点）。" },
		{ "y", "输入坐标 Y（通常来自 InputY 或上游节点）。" },
		{ "z", "输入坐标 Z（通常来自 InputZ 或上游节点）。" },
		{ "a", "第一个操作数。⚠️ 顺序有意义：Subtract 是 a − b，Divide 是 a ÷ b，别接反。" },
		{ "b", "第二个操作数。⚠️ 在 SdfSmoothSubtract 里它是「被减掉的那个」，要挖洞必须让它变小。" },
		{ "sdf", "有符号距离场值：< 0 表示实心内部，> 0 表示空气，= 0 是表面。" },
		{ "noise", "噪声资源对象（ZN_FastNoiseLite 或 Godot 的 Noise 子类）。" },
		{ "value", "要输出/写入的数值。" },
		{ "min", "下限。x 小于它时返回该值。" },
		{ "max", "上限。x 大于它时返回该值。" },
		{ "x0", "第一个点的 X 坐标。" },
		{ "y0", "第一个点的 Y 坐标。" },
		{ "z0", "第一个点的 Z 坐标。" },
		{ "x1", "第二个点的 X 坐标。" },
		{ "y1", "第二个点的 Y 坐标。" },
		{ "z1", "第二个点的 Z 坐标。" },
		{ "spot_radius", "斑点半径（坐标单位）。⚠️ 它也是「做陨石坑」时最关键的输入口，可动态变。" },
		{ "image", "图像资源。⚠️ 必须是**未压缩格式**（如 FORMAT_RGB8），否则读不到像素。" },
		{ "smoothness", "平滑过渡宽度：0 = 硬边；越大两个形状之间的「焊接」越宽。官方行星图用 5。" },
		{ "radius", "半径（坐标单位）。⚠️ SdfSphere 的球心固定在原点，要移动球心得给 x/y/z 做偏移。" },
		{ "seed", "随机种子。⚠️ 每颗星球要用不同种子，否则全场长得一模一样。" },
		{ "cell_size", "格子边长（坐标单位）：斑点网格的疏密，越小斑点越密。" },
		{ "jitter", "斑点在各自格子内的随机偏移程度。⚠️ 过大时斑会越出格子边界（官方说这是有意的）。" },
		{ "out_x", "扭曲后的 X 坐标输出。" },
		{ "out_y", "扭曲后的 Y 坐标输出。" },
		{ "out_z", "扭曲后的 Z 坐标输出。" },
		{ "nx", "归一化后的 X 分量（输出向量长度为 1）。" },
		{ "ny", "归一化后的 Y 分量。" },
		{ "nz", "归一化后的 Z 分量。" },
		{ "len", "原始向量的长度（**不是**归一化结果）。⚠️ 官方行星图正是拿它当「到球心的距离」用。" },
		{ "ratio", "插值比例：0 = 取 a，1 = 取 b。超出 [0,1] 会外推。" },
		{ "index", "输出用的索引值。" },
		{ "type", "体素类型索引（配合 VoxelMesherBlocky 使用）。" },
		{ "weight", "该纹理层的权重。" },
		{ "p", "指数（幂运算的次数）。" },
		{ "power", "幂次（常数正整数）。用 Powi 比 Pow 更快。" },
		{ "in", "直通输入。" },
		{ "height", "平面的高度位置（沿 Y 轴）。" },
		{ "t", "用于判断的值：小于 threshold 取 a，否则取 b。" },
		{ "threshold", "判断阈值。⚠️ Select 是硬切换（不连续），做地形过渡建议改用 Mix 或 Smoothstep。" },
		{ "step", "阶梯步长：把 x 吸附到它的整数倍。" },
		{ "length", "环绕区间长度。⚠️ 为 0 时该节点会返回 NaN。" },
		{ "text", "注释文本内容。" },
		{ "curve", "曲线资源（Godot 的 Curve）。" },
		{ "expression", "数学表达式。写入的变量名会自动成为该节点的输入口。⚠️ 可用函数：sin/floor/abs/sqrt/fract/stepify/wrap/min/max/clamp/lerp（**没有 pow**）。" },
		{ "_function", "引用的子图资源（VoxelGraphFunction）。其后的参数由子图暴露。" },
		{ "filter", "图像采样过滤模式。" },
		{ "layer", "纹理层索引。⚠️ 同一个 layer 只能有一个 OutputWeight 节点。" },
		{ "min0", "源区间下限。" },
		{ "max0", "源区间上限。" },
		{ "min1", "目标区间下限。" },
		{ "max1", "目标区间上限。" },
		{ "size_x", "盒子在 X 方向的尺寸（以原点为中心）。" },
		{ "size_y", "盒子在 Y 方向的尺寸。" },
		{ "size_z", "盒子在 Z 方向的尺寸。" },
		{ "min_value", "预览显示的下限（仅供查看，不影响结果）。" },
		{ "max_value", "预览显示的上限。" },
		{ "fraction_period", "预览网格的周期。" },
		{ "mode", "预览切片模式。" },
		{ "factor", "高度图的高度缩放系数。" },
		{ "radius1", "圆环的环半径。" },
		{ "radius2", "圆环的管粗（截面半径）。" },
		{ "edge0", "边界的起点。⚠️⚠️ 当 edge0 > edge1 时 Smoothstep 会**反向**：x 接近 0 处输出 1。官方行星图正是靠 edge0=0.002/edge1=0.0 做出「山谷/沟壑」的。" },
		{ "edge1", "边界的终点。⚠️ 见 edge0 的说明。" },
};

static const unsigned int NODE_NAME_COUNT = sizeof(NODE_NAMES) / sizeof(NODE_NAMES[0]);
static const unsigned int PORT_NAME_COUNT = sizeof(PORT_NAMES) / sizeof(PORT_NAMES[0]);
static const unsigned int PORT_DESC_COUNT = sizeof(PORT_DESCS) / sizeof(PORT_DESCS[0]);


// ── 内部：在表里查中文（ASCII 键，逐字节比较安全）────────────────
inline const char *lookup(const Entry *table, unsigned int count, const String &key) {
	for (unsigned int i = 0; i < count; ++i) {
		if (key == table[i].en) {
			return table[i].zh;
		}
	}
	return nullptr;
}

// 节点名的中文（查不到返回空）
inline String node_name_zh(const String &en) {
	const char *zh = lookup(NODE_NAMES, NODE_NAME_COUNT, en);
	return zh != nullptr ? String::utf8(zh) : String();
}

// 端口/参数名的中文（查不到返回空）
inline String port_name_zh(const String &en) {
	const char *zh = lookup(PORT_NAMES, PORT_NAME_COUNT, en);
	return zh != nullptr ? String::utf8(zh) : String();
}

// 参数描述（查不到返回空）
inline String port_desc_zh(const String &en) {
	const char *zh = lookup(PORT_DESCS, PORT_DESC_COUNT, en);
	return zh != nullptr ? String::utf8(zh) : String();
}

// ⭐ 统一的中英对照格式：`中文 (English)`；查不到中文就原样返回英文。
inline String bilingual_name(const String &en) {
	const String zh = node_name_zh(en);
	if (zh.is_empty()) {
		return en;
	}
	return String("{0} ({1})").format(varray(zh, en));
}

// ⭐ 参数用同款格式：`中文 (english)`。
// ⚠️ 对 x/y/z/a/b 这类单字母数学符号，中文名与英文名只差大小写 ⇒ 不重复显示，直接用英文。
inline String bilingual_port(const String &en) {
	const String zh = port_name_zh(en);
	if (zh.is_empty() || zh.to_lower().strip_edges() == en.to_lower().strip_edges()) {
		return en;
	}
	return String("{0} ({1})").format(varray(zh, en));
}

// ⭐⭐ 把「参数显示名 → 中文描述」逐条喂给回调。
// 用途：`voxel_graph_editor_inspector_plugin.cpp` 用它把 65 条描述注册进 `EditorInspector`，
// 鼠标悬停在参数上时 Godot 就会显示这段中文。
// ⚠️ 用回调而不是直接写 `EditorInspector*`，是为了让本头文件**不依赖任何引擎头**
//    （本模块同时支持 `ZN_GODOT` 与 `ZN_GODOT_EXTENSION` 两种编译方式）。
// ⚠️ 喂出去的键必须是 `bilingual_port()` 的**输出**（显示名），不能是英文原名：
//    Inspector 里的属性名已经被我们改成显示名了，Godot 是拿显示名去查这张表的。
template <typename F>
inline void for_each_param_description(F p_callback) {
	for (unsigned int i = 0; i < PORT_DESC_COUNT; ++i) {
		const Entry &e = PORT_DESCS[i];
		p_callback(bilingual_port(String::utf8(e.en)), String::utf8(e.zh));
	}
}

// ⭐⭐ 「反查」：从显示名 `中文 (english)` 还原出 english。
// **这是保持逻辑安全的关键** —— `_set`/`_get` 拿到的属性名是显示名（中文），
// 而 `get_node_param_index_by_name` 需要英文原名，所以必须在这里还原回去。
// 端口/参数名都是纯 ASCII 标识符（不含圆括号），所以取最后一段 `(...)` 即可。
inline String strip_bilingual(const String &display) {
	const int p = display.rfind("(");
	if (p >= 0 && display.ends_with(")")) {
		return display.substr(p + 1, display.length() - p - 2);
	}
	return display;
}

} // namespace GraphNodesZh

#endif // VOXEL_GRAPH_NODES_ZH_H
