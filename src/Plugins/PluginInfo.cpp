#include "XP++/Plugins/PluginInfo.hpp"

XP::PluginInfo::PluginInfo(std::string name, 
						   std::string filePath, 
						   std::string signature, 
						   std::string description)
	: m_name(name), m_filePath(filePath), 
	m_signature(signature), m_description(description)
{

}
