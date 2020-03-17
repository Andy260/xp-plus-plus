#pragma once

namespace XP
{
	/// <summary>
	/// ID of a plugin
	/// </summary>
	/// <remarks>
	/// <para>
	/// A plug-in ID is unique within the currently running instance of X-Plane
	/// unless plug-ins are reloaded. Plug-ins may receive a different unique
	/// ID each time they are loaded. This includes the unloading and reloading
	/// of plugins that are part of the user's aircraft.
	/// </para>
	/// <para>
	/// For persistent identification of plug-ins, use <see cref="Plugin::FindBySignature"/>
	/// </para>
	/// </remarks>
	class PluginID
	{
	public:
		PluginID(int id);
		~PluginID();

		static PluginID GetNullID()
		{
			return PluginID(-1);
		}

		inline int GetIndex() const;

		inline bool PluginID::operator==(const PluginID& rhs);
		inline bool PluginID::operator!=(const PluginID& rhs)
		{
			return !((*this) == rhs);
		}

	private:
		// Internal X-Plane ID of a plugin
		int m_id;
	};
}
