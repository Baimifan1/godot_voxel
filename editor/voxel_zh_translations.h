#ifndef VOXEL_ZH_TRANSLATIONS_H
#define VOXEL_ZH_TRANSLATIONS_H

#include "../util/godot/classes/editor_plugin.h"

namespace zylann::godot {

// 把编译进来的中文译文注入编辑器的两个翻译域：
//   · 属性名 / 分组名        →  godot.properties
//   · 悬停说明 / 帮助文档正文 →  godot.documentation
//
// ⭐ 时机：必须在 `EditorSettings::setup_language()` **之后**。
// 那个函数里的 `load_editor_translations()` / `load_doc_translations()`
// 会先 `domain->clear()`，比它更早注入的内容会被清掉。
// 用 `NOTIFICATION_ENTER_TREE` 触发，时机正好（与 `VoxelBlockyLibraryEditorPlugin` 同一套路）。
//
// ⚠️ 不要给 `_notification` 加 `override`：4.7 里 `Node::_enter_tree()` 之类是用
// `GDVIRTUAL0()` 声明的（scene/main/node.h:435），不是普通 virtual，加了会报 C3668。
class VoxelZhTranslationsPlugin : public ZN_EditorPlugin {
	GDCLASS(VoxelZhTranslationsPlugin, ZN_EditorPlugin)
public:
	VoxelZhTranslationsPlugin();

protected:
	String _zn_get_plugin_name() const override;

private:
	void _inject() const;
	void _notification(int p_what);

	// When compiling with GodotCpp, `_bind_methods` is not optional
	static void _bind_methods() {}
};

} // namespace zylann::godot

#endif // VOXEL_ZH_TRANSLATIONS_H