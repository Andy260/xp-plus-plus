#include "XP++/Plugins/Plugins.hpp"

// XP++ includes
#include "XP++/Exceptions/NotImplementedException.hpp"
#include "XP++/Message.hpp"
#include "XP++/Plugins/PluginID.hpp"

int XP::Plugins::Count()
{
	throw NotImplementedException();
}

XP::PluginID XP::Plugins::GetNth(int index)
{
	throw NotImplementedException();
}

XP::PluginID XP::Plugins::FindByPath(std::string path)
{
	throw NotImplementedException();
}

XP::PluginID XP::Plugins::FindBySignature(std::string signature)
{
	throw NotImplementedException();
}

void XP::Plugins::Reload()
{
	throw NotImplementedException();
}

void XP::Plugins::SendMessageToPlugin(PluginID& plugin, Message message, void* param)
{
	throw NotImplementedException();
}

bool XP::Plugins::HasFeature(std::string feature)
{
	throw NotImplementedException();
}

bool XP::Plugins::IsFeatureEnabled(std::string feature)
{
	throw NotImplementedException();
}

void XP::Plugins::EnableFeature(std::string feature, bool enable)
{
	throw NotImplementedException();
}

void XP::Plugins::EnumerateFeatures(std::function<void(std::string feature, void* ref)> enumerator, void* ref)
{
	throw NotImplementedException();
}
