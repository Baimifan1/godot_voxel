#include "voxel_graph_editor_inspector_plugin.h"
#include "editor_property_text_change_on_submit.h"
#include "graph_nodes_zh.h"
#include "voxel_graph_node_inspector_wrapper.h"

#if defined(ZN_GODOT)
#include "../../util/godot/classes/editor_inspector.h"
#include "../../util/godot/classes/editor_interface.h"
#endif

namespace zylann::voxel {

#if defined(ZN_GODOT)

// 本项目汉化（v2）：把 65 条参数中文描述注册进检查器，鼠标悬停参数时显示。
//
// 原理（查过 4.7.2 源码，走的是 Godot 自己的公开通路，没有造轮子）：
//   `EditorInspector::update_tree()` 给每个属性设的 tooltip 内容其实是 doc 符号
//   `property|<object->get_class_name()>|<pi.name>`；
//   悬停时 `EditorProperty::make_custom_tooltip()` 拿这个符号去问
//   `EditorInspector::get_custom_property_description()`（**公开 API**），把结果拼进 prologue 显示。
// ⇒ 只要在这里注册一次即可，**不需要改任何一个控件的 tooltip**，
//   也就能覆盖所有类型（float / int / enum / string / resource …）。
//
// ⚠️ 键的第 2 段必须是 `object->get_class_name()`，第 3 段必须是**显示名**
//    （`pi.name` 已被 `voxel_graph_node_inspector_wrapper.cpp` 改成 `中文 (english)`），否则查不中。
// ⚠️ 必须**迟到这里**才注册：`EditorInterface::get_inspector()` 内部直接解引用
//    `InspectorDock::singleton`，检查器坞还没建好时调用会崩。
//    本函数是「检查器正在为本对象构造属性」时被调到的，此时一定已就绪。
static void ensure_param_descriptions_registered(const Object *p_object) {
	static bool done = false;
	if (done || p_object == nullptr) {
		return;
	}
	EditorInterface *ei = EditorInterface::get_singleton();
	if (ei == nullptr) {
		return;
	}
	EditorInspector *inspector = ei->get_inspector();
	if (inspector == nullptr) {
		return;
	}
	done = true;

	const String class_name = p_object->get_class_name();
	GraphNodesZh::for_each_param_description(
			[inspector, &class_name](const String &p_display_name, const String &p_description) {
				inspector->add_custom_property_description(class_name, p_display_name, p_description);
			}
	);
}

#endif // ZN_GODOT

bool VoxelGraphEditorInspectorPlugin::_zn_can_handle(const Object *obj) const {
	return obj != nullptr && Object::cast_to<VoxelGraphNodeInspectorWrapper>(obj) != nullptr;
}

bool VoxelGraphEditorInspectorPlugin::_zn_parse_property(Object *p_object, const Variant::Type p_type,
		const String &p_path, const PropertyHint p_hint, const String &p_hint_text,
		const BitField<PropertyUsageFlags> p_usage, const bool p_wide) {
#if defined(ZN_GODOT)
	ensure_param_descriptions_registered(p_object);
#endif

	if (p_type == Variant::STRING && p_hint != PROPERTY_HINT_MULTILINE_TEXT) {
		add_property_editor(p_path, memnew(ZN_EditorPropertyTextChangeOnSubmit));
		return true;
	}
	return false;
}

} // namespace zylann::voxel
