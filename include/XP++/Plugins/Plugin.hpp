#pragma once

// STL includes
#include <string>

namespace XP
{
	// Pre-declarations
	class PluginInfo;

	class Plugin
	{
	public:
		/// <summary>
		/// Constructs a new plugin object
		/// (Not intended to be used for client code)
		/// </summary>
		/// <remarks>
		/// While can be created by user code of XP++, it's not intended.
		/// As the XP++ library is just an abstraction over the X-Plane SDK
		/// and as such, may cause errors and have unintended side affects 
		/// with an invalid internal plugin ID.
		/// </remarks>
		/// <param name="id">Internal X-Plane ID</param>
		Plugin(int id) : m_id(id) {}
		~Plugin()											= default;
		Plugin(const Plugin&)								= default;
		Plugin& Plugin::operator=(const Plugin&)			= default;

		PluginInfo GetInfo() const;

		bool IsEnabled() const;
		void Enable();
		void Disable();

	private:
		// Internal X-Plane ID of this plugin
		int m_id;
	};
}
