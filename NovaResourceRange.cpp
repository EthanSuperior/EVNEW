
#include "NovaResourceRange.h"
#include "Workspace.h"

// Iterator Through Workspace's Plugins
NovaResourceRange::Iterator NovaResourceRange::begin() const {
	auto& plugins = Workspace::GetPlugins();
	for (size_t pi = 0; pi < plugins.size(); ++pi) {
		auto& resources = plugins[pi]->m_vResources[rezType];
		if (resources.empty()) continue;
		return Iterator(&resources[0], rezType, 0, true, 0, pi);
	}
	auto& data = Workspace::GetData();
	for (size_t pi = 0; pi < data.size(); ++pi) {
		auto& resources = data[pi]->m_vResources[rezType];
		if (resources.empty()) continue;
		return Iterator(&resources[0], rezType, 0, false, 0, pi);
	}
	return Iterator(NULL, rezType, 0, true, 0, 0);
}

NovaResourceRange::Iterator NovaResourceRange::end() const {
	int total = 0;
	for (auto* p : Workspace::GetPlugins()) total += p->m_vResources[rezType].size();
	auto& data = Workspace::GetData();
	for (auto* p : data) total += p->m_vResources[rezType].size();
	int i = 0;
	if (data.size() != 0) i = data.back()->m_vResources[rezType].size();
	return Iterator(NULL, rezType, total, false, 0, data.size());
}


NovaResourceRange::Iterator& NovaResourceRange::Iterator::operator++()
{
	while (true) {
		auto& vecs = onPlugins ? Workspace::GetPlugins(): Workspace::GetData();

		if (pluginIdx >= vecs.size()) {
			if (onPlugins) {
				onPlugins = false;
				pluginIdx = 0;
				i = -1;
				continue;
			}
			else {
				ptr = nullptr;
				break;
			}
		}

		if (++i < vecs[pluginIdx]->m_vResources[rezType].size()) {
			ptr = &vecs[pluginIdx]->m_vResources[rezType][i];
			break;
		}

		++pluginIdx;
		i = -1;
	}

	++idx;
	return *this;
}

NovaResourceRange::Iterator& NovaResourceRange::Iterator::operator--()
{
	while (true) {
		auto& vecs = onPlugins ? Workspace::GetPlugins(): Workspace::GetData();

		if (i > 0) {
			ptr = &vecs[pluginIdx]->m_vResources[rezType][--i];
			break;
		}

		if (pluginIdx > 0) {
			i = vecs[--pluginIdx]->m_vResources[rezType].size();
			if (i > 0) {
				ptr = &vecs[pluginIdx]->m_vResources[rezType][--i];
				break;
			}
		}
		else {
			if (!onPlugins) {
				onPlugins = true;
				pluginIdx = Workspace::GetPlugins().size();
				i = 0;
				continue;
			}

			ptr = nullptr;
			break;
		}
	}

	--idx;
	return *this;
}

std::string NovaResourceRange::Iterator::PluginFilename()
{
	return std::filesystem::path((onPlugins ? Workspace::GetPlugins() : Workspace::GetData())[pluginIdx]->GetFilename()).filename().string();
}