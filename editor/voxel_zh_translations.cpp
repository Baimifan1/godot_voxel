#include "voxel_zh_translations.h"
#include "voxel_zh_data.h"

#if defined(ZN_GODOT)
#include <core/string/translation.h>
#include <core/string/translation_domain.h>
#include <core/string/translation_server.h>
#endif

namespace zylann::godot {

namespace {
	// 把一张表灌进某个翻译域。
	// ⚠️ 只在「该域里还没有我们的译文」时才灌，避免重复叠加
	//（切换编辑器语言时域会被 clear，需要重新灌 —— 那次 translate 会返回原文，正好触发重灌）。
	void add_table(const Ref<TranslationDomain> &p_domain, const String &p_locale,
			const VoxelZhData::Entry *p_entries, unsigned int p_count) {
		if (p_domain.is_null() || p_count == 0 || p_entries == nullptr) {
			return;
		}
		// 哨兵：第一条若已经查得到译文，说明本插件已灌过。
		// ⚠️ TranslationDomain::translate() 的 context 参数**没有默认值**，必须显式传。
		const String probe_key = String::utf8(p_entries[0].msgid);
		const String probe_val = String::utf8(p_entries[0].zh);
		if (p_domain->translate(probe_key, StringName()) == probe_val) {
			return;
		}

		Ref<Translation> tr;
		tr.instantiate();
		tr->set_locale(p_locale);
		for (unsigned int i = 0; i < p_count; i++) {
			tr->add_message(String::utf8(p_entries[i].msgid), String::utf8(p_entries[i].zh));
		}
		p_domain->add_translation(tr);
	}
} // namespace

String VoxelZhTranslationsPlugin::_zn_get_plugin_name() const {
	return "Voxel 中文汉化";
}

VoxelZhTranslationsPlugin::VoxelZhTranslationsPlugin() {}

void VoxelZhTranslationsPlugin::_notification(int p_what) {
	if (p_what == NOTIFICATION_ENTER_TREE) {
		_inject();
	}
}

void VoxelZhTranslationsPlugin::_inject() const {
	TranslationServer *ts = TranslationServer::get_singleton();
	if (ts == nullptr) {
		return;
	}
	const String locale = ts->get_locale();
	// 只在非英文界面下注入：编辑器语言就是中文时才需要，英文界面塞中文只会帮倒忙。
	if (locale.is_empty() || locale == "en") {
		return;
	}

	Ref<TranslationDomain> prop_domain = ts->get_or_add_domain("godot.properties");
	Ref<TranslationDomain> doc_domain = ts->get_or_add_domain("godot.documentation");

	add_table(prop_domain, locale, VoxelZhData::PROPERTY_NAMES, VoxelZhData::PROPERTY_COUNT);
	add_table(prop_domain, locale, VoxelZhData::GROUP_NAMES, VoxelZhData::GROUP_COUNT);
	add_table(doc_domain, locale, VoxelZhData::DOCS, VoxelZhData::DOC_COUNT);
}

} // namespace zylann::godot