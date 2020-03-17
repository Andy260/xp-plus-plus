#pragma once

namespace XP
{
	class PluginID;

	class Planes final
	{
	public:
		static void Count(int& totalAircraft, int& activeAircraft, PluginID controller);

	private:
		Planes()									= delete;
		~Planes()									= delete;
		Planes(const Planes&)						= delete;
		Planes& Planes::operator=(const Planes&)	= delete;
	};
}
