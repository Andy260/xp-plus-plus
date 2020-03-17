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
		~Plugin()											= default;
		Plugin(const Plugin&)								= default;
		Plugin& Plugin::operator=(const Plugin&)			= default;

		PluginInfo GetInfo() const;

		bool IsEnabled() const;
		void Enable();
		void Disable();

	protected:
		Plugin()											= default;

		virtual bool OnStart(std::string& outName, 
							 std::string& outSignature, 
							 std::string& outDescription)	= 0;
		virtual void OnStop()								= 0;
		virtual bool OnEnable()								= 0;
		virtual void OnDisable()							= 0;
		virtual void OnReceiveMessage()						= 0;

	private:
		// Internal X-Plane ID of this plugin
		int m_id;
	};
}
