#ifndef ZOXEL_ZH_TRANSLATIONS_H
#define ZOXEL_ZH_TRANSLATIONS_H

#include "../../util/godot/classes/editor_plugin.h"

namespace zylann::godot {

// 把编译进来的中文译文注入编辑器的两个翻译域：
//   · 属性名 / 分组名        →  godot.properties
//   · 悬停说明 / 帮助文档正文 →  godot.documentation
//
// ⭐ 时机：必须在 `EditorSettings::setup_language()` **之后**。
// 那个函数里的 `load_editor_translations()` / `load_doc_translations()`
// 会先 `domain->clear()`，比它更早注入的内容会被清掉。
// `EditorPlugin::_enter_tree()` 由编辑器在 UI 建好、插件挂上时才调用，时机正好。
class VoxelZhTranslationsPlugin : public ZN_EditorPlugin {
	GDCLASS(VoxelZhTranslationsPlugin, ZN_EditorPlugin)
public:
	VoxelZhTranslationsPlugin() {}

protected:
	String _zn_get_plugin_name() const override;
	void _enter_tree() override;

private:
	void _inject() const;

	// When compiling with GodotCpp, `_bind_methods` is not optional
	static void _bind_methods() {}
};

} // namespace zylann::godot

#endif // ZOXEL_ZH_TRANSLATIONS_H