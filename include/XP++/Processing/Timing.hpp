#pragma once

namespace XP
{
	/// <summary>
	/// Returns the elapsed time since the sim started up
	/// in decimal seconds
	/// </summary>
	/// <remarks>
	/// <para>
	/// This is a wall timer; it keeps counting upward even if the sim is paused.
	/// </para>
	/// <para>
	/// This is not a very good timer! It lacks precision in both its data type
	/// and its source. Do not attempt to use it for timing critical applications
	/// like network multiplayer.
	/// </para>
	/// </remarks>
	/// <returns>
	/// 
	/// </returns>
	float GetElapsedTime();

	/// <summary>
	/// Returns a counter starting at zero for each sim 
	/// cycle computed/video frame rendered
	/// </summary>
	/// <returns>
	/// Amount of computed/video frames rendered
	/// </returns>
	int GetCycleNumber();
}
