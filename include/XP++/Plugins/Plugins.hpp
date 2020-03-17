#pragma once

// STL includes
#include <functional>
#include <string>

namespace XP
{
	// Pre-declarations
	class PluginID;
	class Message;

	/// <summary>
	/// Provides facilities to find and work with other plugins
	/// and manage other plugins.
	/// </summary>
	class Plugins final
	{
	public:
		/// <summary>
		/// Returns the total number of plug-ins that are loaded,
		/// both disabled and enabled.
		/// </summary>
		/// <returns>Number of plug-ins loaded, disabled and enabled</returns>
		static int Count();
		/// <summary>
		/// Returns a plugin by index
		/// </summary>
		/// <remarks>
		/// Index of a plugin is based from 0 to <see cref="Count"/>-1, inclusive.
		/// Plugins may be returned in any arbitrary order.
		/// </remarks>
		/// <returns>
		/// ID of the plugin at the given index, 
		/// or NULL if none exist at such an index
		/// </returns>
		static PluginID GetNth(int index);
		/// <summary>
		/// Returns the plug-in ID of the plug-in whose file exists at 
		/// the passed in absolute file system path. NULL is returned 
		/// if the path does not point to a currently loaded plug-in.
		/// </summary>
		/// <param name="path">Absolute system path to the plugin</param>
		/// <returns>Plug-in found at the given path, or NULL if none exist</returns>
		static PluginID FindByPath(std::string path);
		/// <summary>
		/// Returns the plug-in ID of the plug-in whose signature matches what is passed in
		/// or NULL if no running plug-in has this signature.
		/// </summary>
		/// <remarks>
		/// Signatures are the best way to identify another plug-in as they are independent 
		/// of the file system path of a plug-in or the human-readable plug-in name, and 
		/// should be unique for all plug-ins. Use this routine to locate another plugin 
		/// that your plugin interoperates with.
		/// </remarks>
		/// <param name="signature">Signature of the plug-in to find</param>
		/// <returns>Plug-in with the given signature, or NULL if none exist</returns>
		static PluginID FindBySignature(std::string signature);

		/// <summary>
		/// Reloads all plug-ins.
		/// </summary>
		/// <remarks>
		/// Once this routine is called and you return from the callback
		/// you were within (e.g. a menu select callback) you will receive
		/// your <see cref="Plugin::Disable"/> and <see cref="Plugin::Stop"/>
		/// callbacks and your DLL will be unloaded, then the start process 
		/// happens as if the sim was starting up.
		/// </remarks>
		static void Reload();

		/// <summary>
		/// Sends a message to another plug-in or X-Plane.
		/// </summary>
		/// <remarks>
		/// Pass <see cref="PluginID::GetNullID"/> to broadcast to all plug-ins.
		/// Only enabled plug-ins with a message receive function receive the function.
		/// </remarks>
		/// <param name="plugin">Plug-in to see message to, or NULL to send to all plug-ins</param>
		/// <param name="message">Message to send</param>
		/// <param name="param">Pointer of the data to send with the message</param>
		static void SendMessageToPlugin(PluginID& plugin, Message message, void* param);

		/// <summary>
		/// Checks if the given installation of X-Plane supports a given feature
		/// </summary>
		/// <param name="feature">Feature to check</param>
		/// <returns>
		/// Returns true if the given installation of X-Plane supports 
		/// the given feature, or false if it does not
		/// </returns>
		static bool HasFeature(std::string feature);
		/// <summary>
		/// Checks if a given feature is currently enabled
		/// </summary>
		/// <remarks>
		/// It is an error to call this routine with an unsupported feature.
		/// </remarks>
		/// <param name="feature">Feature to check</param>
		/// <returns>
		/// Returns true if the given feature is currently enabled for your 
		/// plugin, or false if it is not enabled.
		/// </returns>
		static bool IsFeatureEnabled(std::string feature);
		/// <summary>
		/// Enabled or disables a feature for your plug-in.
		/// </summary>
		/// <remarks>
		/// This will change the running behaviour of X-Plane and your 
		/// plugin in some way, depending on the feature.
		/// </remarks>
		/// <param name="feature">Feature to enable/disable</param>
		/// <param name="enable">True to enable feature, false to disable</param>
		static void EnableFeature(std::string feature, bool enable);
		/// <summary>
		/// Enumerates through every feature that this running version of X-Plane supports.
		/// </summary>
		/// <remarks>
		/// Use this routine to determine all of the features that X-Plane can support.
		/// </remarks>
		/// <param name="enumerator">Callback for the enumeration</param>
		/// <param name="ref">(undocumented)</param>
		static void EnumerateFeatures(std::function<void(std::string feature, void* ref)> enumerator, void* ref);

	protected:
		Plugins()									= delete;
		~Plugins()									= delete;
		Plugins(const Plugins&)						= delete;
		Plugins& Plugins::operator=(const Plugins&) = delete;
	};
}
