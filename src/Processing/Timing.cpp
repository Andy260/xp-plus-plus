#include "XP++/Processing/Timing.hpp"

// XP++ includes
#include "XP++/Exceptions/NotImplementedException.hpp"

// X-Plane SDK includes
#include "XPLMProcessing.h"

float XP::GetElapsedTime()
{
	return XPLMGetElapsedTime();
}

int XP::GetCycleNumber()
{
	return XPLMGetCycleNumber();
}
