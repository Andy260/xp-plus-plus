#pragma once

// STL includes
#include <string>

namespace XP
{
	class PluginInfo
	{
	public:
		PluginInfo();
		~PluginInfo();

		inline std::string GetName() const
		{
			return m_name;
		}

		inline std::string GetFilePath() const
		{
			return m_filePath;
		}

		inline std::string GetSignature() const
		{
			return m_signature;
		}

		inline std::string GetDescription() const
		{
			return m_description;
		}

	private:
		std::string m_name;
		std::string m_filePath;
		std::string m_signature;
		std::string m_description;
	};
}
