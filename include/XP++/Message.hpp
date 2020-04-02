#pragma once

// STL includes
#include <memory>
#include <string>

namespace XP
{
	/// <summary>
	/// Defines a type of X-Plane message
	/// </summary>
	enum class XPLMMessageType : int
	{
		/// <summary>
		/// User's plane has crashed
		/// </summary>
		PlaneCrashed			= 101,
		/// <summary>
		/// New plane is loaded
		/// </summary>
		/// <remarks>
		/// Message data contains the index number of 
		/// the plane being loaded; 0 indicates the user's plane.
		/// </remarks>
		PlaneLoaded				= 102,
		/// <summary>
		/// User's plane was positioned at a new airport
		/// </summary>
		AirportLoaded			= 103,
		/// <summary>
		/// New scenery is loaded
		/// </summary>
		/// <remarks>
		/// Use datarefs to determine the new scenery files that were loaded.
		/// </remarks>
		SceneryLoaded			= 104,
		/// <summary>
		/// User has adjusted the number of X-Plane
		/// aircraft models
		/// </summary>
		/// <remarks>
		/// You must use <see cref="Planes::Count"/> to 
		/// find out how many planes are now available.
		/// </remarks>
		AirplaneCountChanged	= 105,
		/// <summary>
		/// A plane was unloaded
		/// </summary>
		/// <remarks>
		/// Message data contains the index number of the plane being unloaded;
		/// 0 indicates the user's plane. 
		/// </remarks>
		PlaneUnloaded			= 106,
		/// <summary>
		/// X-Plane is about to write to its preferences file
		/// </summary>
		/// <remarks>
		/// You can use this for two purposes: to write your own preferences,
		/// and to modify any datarefs to influence preferences output. For example, 
		/// if your plugin temporarily modifies saved preferences, you can put them 
		/// back to their default values here to avoid having the tweaks be persisted 
		/// if your plugin is not loaded on the next invocation of X-Plane.
		/// </remarks>
		WillWritePrefs			= 107,
		/// <summary>
		/// Livery for an airplane has been loaded
		/// </summary>
		/// <remarks>
		/// Message send right after a livery is loaded for an airplane.
		/// You can use this to check the new livery (via datarefs) and 
		/// react accordingly. The parameter contains the index number 
		/// of the aircraft whose livery is changing.
		/// </remarks>
		LiveryLoaded			= 108,
		/// <summary>
		/// About to enter virtual reality mode
		/// </summary>
		/// <remarks>
		/// Sent right before X-Plane enters virtual reality mode
		/// (at which time any windows that are not positioned in
		/// VR mode will no longer be visible to the user).
		/// </remarks>
		EnteredVR				= 109,
		/// <summary>
		/// About to exit virtual reality mode
		/// </summary>
		/// <remarks>
		/// Sent right before X-Plane leaves virtual reality mode
		/// (at which time you may want to clean up windows that
		/// are positioned in VR mode).
		/// </remarks>
		ExitingVR				= 110,
		/// <summary>
		/// Plugin message
		/// </summary>
		Unknown					= 0x8000000
	};

	class Message final
	{
	public:
		Message(int id, void* data);
		~Message()									= default;
		Message(const Message&)						= default;
		Message& Message::operator=(const Message&) = default;

		inline int GetID() const
		{
			return m_id;
		}
		inline void* GetData() const
		{
			return m_data;
		}

		XPLMMessageType GetType() const;

	private:
		// ID of the message
		int m_id;
		// Pointer to data given with this message
		void* m_data;
	};
}
