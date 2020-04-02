#include "XP++/Plugins/Plugin.hpp"

// STL includes
#include <string>

// X-Plane SDK includes
#include "XPLMPlugin.h"

// XP++ includes
#include "XP++/Plugins/PluginInfo.hpp"

XP::PluginInfo XP::Plugin::GetInfo() const
{
	char* name[256]			= {""};
	char* filePath[256]		= {""};
	char* signature[256]	= {""};
	char* description[256]	= {""};

	XPLMGetPluginInfo(m_id, name[0], filePath[0], signature[0], description[0]);

	return PluginInfo(
		std::string(name[0]),
		std::string(filePath[0]),
		std::string(signature[0]),
		std::string(description[0])
		);
}

bool XP::Plugin::IsEnabled() const
{
	return static_cast<bool>(XPLMIsPluginEnabled(m_id));
}

void XP::Plugin::Enable()
{
	XPLMEnablePlugin(m_id);
}

void XP::Plugin::Disable()
{
	XPLMDisablePlugin(m_id);
}
