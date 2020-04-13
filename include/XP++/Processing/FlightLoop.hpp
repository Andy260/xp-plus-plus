#pragma once

// STL includes
#include <functional>
#include <memory>
#include <list>

namespace XP
{
	/// <summary>
	/// Defines when your callback will be executed by X-Plane
	/// </summary>
	enum class FlightLoopPhaseType : int
	{
		/// <summary>
		/// Your callback runs before X-Plane integrates the flight model
		/// </summary>
		BeforeFlightModel	= 0,
		/// <summary>
		/// Your callback runs after X-Plane integrates the flight model
		/// </summary>
		AfterFlightModel	= 1
	};

	/// <summary>
	/// A callback called by X-Plane as part of the flight loop
	/// </summary>
	/// <remarks>
	/// <para>
	/// This API allows you to get regular callbacks during the flight loop, 
	/// the part of X-Plane where the plane’s position calculates the physics 
	/// of flight, etc. Use these APIs to accomplish periodic tasks like logging 
	/// data and performing I/O.
	/// </para>
	/// <para>
	/// You can receive a callback either just before or just after the per-frame 
	/// physics calculations happen - you can use post-FM callbacks to “patch” the 
	/// flight model after it has run.
	/// </para>
	/// <para>
	/// If the user has set the number of flight model iterations per frame greater 
	/// than one your plugin will not see this; these integrations run on the 
	/// sub-section of the flight model where iterations improve responsiveness 
	/// (e.g. physical integration, not simple systems tracking) and are thus opaque 
	/// to plugins.
	/// </para>
	/// <para>
	/// Flight loop scheduling, when scheduled by time, is scheduled by a “first 
	/// callback after the deadline” schedule, e.g. your callbacks will always be 
	/// slightly late to ensure that we don’t run faster than your deadline.
	/// </para>
	/// <para>
	/// WARNING: Do NOT use these callbacks to draw! You cannot draw during flight 
	/// loop callbacks. Use the drawing callbacks for graphics. (One exception: 
	/// you can use a post-flight loop callback to update your own off-screen FBOs.)
	/// </para>
	/// </remarks>
	class FlightLoop
	{
	public:
		/// <summary>
		/// Registers a new flight loop callback
		/// </summary>
		/// <param name="phase">Phase to execute the callback</param>
		/// <param name="callback">Callback function to execute</param>
		/// <returns>Created flight loop callback</returns>
		static std::shared_ptr<FlightLoop> CreateFlightLoop(FlightLoopPhaseType phase, 
															std::function<float(float, float, int)> callback);

		/// <summary>
		/// Schedules the flight loop callback for future execution
		/// </summary>
		/// <param name="interval">Interval to execute the callback</param>
		/// <param name="relativeToNow">How to resolve ties with execution time</param>
		/// <remarks>
		/// <para>
		/// If <see cref="interval"/> is negative, it is run in a certain number 
		/// of frames based on the absolute value of the input. If the interval 
		/// is positive, it is a duration in seconds.
		/// </para>
		/// <para>
		/// If <see cref="relativeToNow"/> is positive, ties are interpreted 
		/// relative to the time this function was called; otherwise they are 
		/// relative to the last call time or the time the flight loop was 
		/// registered (if never called).
		/// </para>
		/// </remarks>
		void Schedule(float interval, int relativeToNow);
		/// <summary>
		/// Sets when the callback will be called
		/// </summary>
		/// <remarks>
		/// <para>
		/// Do NOT call this function from your callback; use the return value 
		/// of the callback to change your callback interval from inside your callback.
		/// </para>
		/// <para>
		/// A positive <see cref="interval"/> value will specify seconds from 
		/// registration time to the next callback. A negative value will indicate 
		/// when you will be called (e.g. pass -1 to be called at the next cycle).
		/// Pass 0 to <see cref="interval"/> to not be called; your callback will 
		/// be inactive.
		/// </para>
		/// <para>
		/// If <see cref="relativeToNow"/> is positive, ties are interpreted 
		/// relative to the time this function was called; otherwise they are 
		/// relative to the last call time or the time the flight loop was 
		/// registered (if never called).
		/// </para>
		/// </remarks>
		/// <param name="interval">Interval at which the callback should be executed</param>
		/// <param name="relativeToNow">How to resolve ties with execution time</param>
		void SetCallbackInterval(float interval, int relativeToNow);

	private:
		FlightLoop(void* id, std::function<float(float, float, int)> callback);
		~FlightLoop();

		FlightLoop(const FlightLoop&)				= delete;
		FlightLoop& operator=(const FlightLoop&)	= delete;

		// X-Plane ID of this FlightLoop
		void* m_id;
		// Function to be called by this FlightLoop
		std::function<float(float, float, int)> m_callback;
	};
}
