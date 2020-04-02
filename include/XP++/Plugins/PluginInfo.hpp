#pragma once

// STL includes
#include <string>

namespace XP
{
	/// <summary>
	/// Information relating to a plug-in
	/// </summary>
	class PluginInfo
	{
	public:
		/// <summary>
		/// Constructs a new PluginInfo object
		/// (Not to be used by client code)
		/// </summary>
		/// <param name="name">Human-readable name of the plug-in</param>
		/// <param name="filePath">Absolute file path to the file that contains the plug-in</param>
		/// <param name="signature">Unique string that identifies the plug-in</param>
		/// <param name="description">Human-readable description of the plug-in</param>
		PluginInfo(std::string name, std::string filePath, std::string signature, std::string description);
		~PluginInfo() = default;

		/// <summary>
		/// Human-readable description of the plug-in
		/// </summary>
		/// <returns>String containing the name</returns>
		inline std::string GetName() const
		{
			return m_name;
		}

		/// <summary>
		/// Absolute file path to the file that contains the plug-in
		/// </summary>
		/// <returns>String containing the file path to the plug-in</returns>
		inline std::string GetFilePath() const
		{
			return m_filePath;
		}

		/// <summary>
		/// Unique string that identifies the plug-in
		/// </summary>
		/// <returns>String containing the plug-in signature</returns>
		inline std::string GetSignature() const
		{
			return m_signature;
		}

		/// <summary>
		/// Human-readable description of the plug-in
		/// </summary>
		/// <returns>String containing the plug-in's description</returns>
		inline std::string GetDescription() const
		{
			return m_description;
		}

	private:
		// Human-readable name of the plug-in
		std::string m_name;
		// Absolute file path to the file that contains the plug-in
		std::string m_filePath;
		// Unique string that identifies the plug-in
		std::string m_signature;
		// Human-readable description of the plug-in
		std::string m_description;
	};
}
