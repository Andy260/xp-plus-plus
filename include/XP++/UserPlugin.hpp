#pragma once

// STL includes
#include <string>

// XP++ includes
#include "XP++/Message.hpp"
#include "XP++/Plugins/Plugin.hpp"

namespace XP
{
	/// <summary>
	/// Base classes for the OOP method of 
	/// creating X-Plane Plugins in XP++
	/// </summary>
	/// <remarks>
	/// This class allows you to keep an OOP coding style for writing plug-ins
	/// in XP++. <see cref="OnStart(std::string&, std::string&, std::string&)"/> 
	/// is a required function to implement, and using the 
	/// <see cref="REGISTER_PLUGIN(UserPlugin)"/> after your class definition
	/// of your plug-in class, is also required allowing XP++ to interface your
	/// plug-in with X-Plane.
	/// </remarks>
	class UserPlugin : public Plugin
	{
	public:
		~UserPlugin() = default;

		/// <summary>
		/// Called by X-Plane right after the plug-in's DLL is loaded
		/// </summary>
		/// <remarks>
		/// <para>
		/// This function is called right after your plug-in's DLL is loaded. 
		/// So do any initialisation necessary for your plugin in this function. 
		/// This includes creating user interfaces, installing registered callbacks, 
		/// allocating resources, etc. Set the name/signature/description for your 
		/// plug-in from the passed arguments.
		/// </para>
		/// <para>
		/// By convention, fill <see cref="outSignature"/> with the organisation name
		/// first, then the name of your plugin (E.g. organisation.pluginName).
		/// During initialisation failure for your plug-in, it's good practise to fill 
		/// <see cref="outDescription"/> with a description of what went wrong. 
		/// </para>
		/// </remarks>
		/// <param name="outName">Set this to the human readable name of the plug-in</param>
		/// <param name="outSignature">Set this to the plug-in's (globally unique) signature.</param>
		/// <param name="outDescription">Set this to the description of your plug-in, 
		/// or what went wrong during a load failure</param>
		/// <returns>
		/// Return true to tell X-Plane your plug-in loaded successfully and to receive additional 
		/// callbacks from X-Plane,  otherwise return false when the plug-in failed to load for 
		/// whatever reason. The plug-in will be unloaded immediately with no further callbacks, 
		/// and will be in the disabled state after this call.
		/// </returns>
		virtual bool OnStart(std::string& outName,
							 std::string& outSignature,
							 std::string& outDescription) = 0;
		/// <summary>
		/// Called right before the plug-in is unloaded.
		/// </summary>
		/// <remarks>
		/// Your Plug-in will be disabled (if it was enabled) 
		/// right before this method is called. Make sure to
		/// un-register any callbacks, dispose of any objects 
		/// or resources, and clean up all allocations done by 
		/// your plug-in. After returning from this method, your 
		/// plug-in will be unloaded from X-Plane.
		/// </remarks>
		virtual void OnStop() {}
		/// <summary>
		/// Called right before the plug-in is enabled
		/// </summary>
		/// <remarks>
		/// <para>
		/// Until your plug-in is enabled, it will not receive any other callbacks
		/// and its UI will be hidden and/or disabled. 
		/// </para>
		/// <para>
		/// The plugin will be enabled after all plug-ins are loaded unless the plug-in 
		/// was disabled during the last X-Plane run (and this information was saved 
		/// in preferences) or all plug-ins were disabled by the user on start-up. 
		/// If the user manually enables the plug-in, this callback is also called. 
		/// <see cref="OnEnabled"/> will not be called twice in a row without 
		/// <see cref="OnDisabled"/> being called.
		/// </para>
		/// <para>
		/// This callback should be used to allocate any resources that your plug-in 
		/// maintains while enabled. If your plug-in launches threads, start the threads. 
		/// If your plugin uses the network, begin network communications.
		/// </para>
		/// <para>
		/// You should structure the resource usage of your plug-in so that your plugin has 
		/// minimal costs for running while it is disabled by allocating expensive 
		/// resources when enabled instead of when loaded.
		/// </para>
		/// </remarks>
		/// <returns>Return true if the plug-in started successfully, otherwise false</returns>
		virtual bool OnEnable() 
		{
			return true;
		}
		/// <summary>
		/// Called right before the plug-in is disabled
		/// </summary>
		/// <remarks>
		/// <para>
		/// When your plug-in is disabled, it will not receive any other callbacks 
		/// and its UI will be hidden and/or disabled.
		/// </para>
		/// <para>
		/// Your plugin will be disabled either before it is unloaded or after the 
		/// user disables it. It will not be unloaded until after it is disabled.
		/// </para>
		/// <para>
		/// Deallocate any significant resources and prepare to not receive any 
		/// callbacks for a potentially long duration.
		/// </para>
		/// </remarks>
		virtual void OnDisable() {}
		/// <summary>
		/// Called by the X-Plane plug-in manager when a message is sent to the plugin
		/// </summary>
		/// <remarks>
		/// <para>
		/// Your plug-in will receive both messages that are specifically routed to 
		/// your plug-in and messages that are broadcast to all plug-ins.
		/// </para>
		/// <para>
		/// Specific messages are sent from X-Plane and can be determined by <see cref="XPLMMessageType"/> 
		/// and the accompanying documentation for <see cref="Message"/>.
		/// The parameter passed varies depending on the 
		/// message. Plug-ins may also define their own private messages to send. 
		/// If you receive a message you do not recognise, you should just ignore it.
		/// </para>
		/// </remarks>
		/// <param name="from"></param>
		/// <param name="message"></param>
		/// <param name="param"></param>
		virtual void OnReceiveMessage(Plugin from,
									  Message message,
									  void* param) {}

	protected:
		/// <summary>
		/// Default constructor for creating plug-ins in XP++ the OOP way
		/// </summary>
		UserPlugin();

	};
}

/// <summary>
/// Use this define within the header of your plugin's class definition
/// in order for XP++ to begin using it within X-Plane
/// </summary>
/// <param name="UserPlugin">Type of your derived User Plugin class</param>
#define REGISTER_PLUGIN(UserPlugin)																	\
UserPlugin* g_userPlugin;																			\
extern "C" __declspec(dllexport) int XPluginStart(char* outName, char* outSig, char* outDesc)		\
{																									\
	g_userPlugin = new UserPlugin();																\
																									\
	std::string name, signature, description;														\
	bool status = g_userPlugin->OnStart(name, signature, description);								\
																									\
	strcpy(outName, name.c_str());																	\
	strcpy(outSig, signature.c_str());																\
	strcpy(outDesc, description.c_str());															\
																									\
	return status;																					\
}																									\
																									\
extern "C" __declspec(dllexport) void XPluginStop()													\
{																									\
	g_userPlugin->OnStop();																			\
}																									\
																									\
extern "C" __declspec(dllexport) void XPluginDisable()												\
{																									\
	g_userPlugin->Disable();																		\
}																									\
																									\
extern "C" __declspec(dllexport) int XPluginEnable()												\
{																									\
	return static_cast<int>(g_userPlugin->OnEnable());												\
}																									\
																									\
extern "C" __declspec(dllexport) void XPluginReceiveMessage(int inFrom, int inMsg, void* inParam)	\
{																									\
	g_userPlugin->OnReceiveMessage(XP::Plugin(inFrom), XP::Message(inMsg, inParam), inParam);		\
}
																									
