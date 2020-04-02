#include "XP++/UserPlugin.hpp"

// X-Plane SDK includes
#include "XPLMPlugin.h"

XP::UserPlugin::UserPlugin() :
	XP::Plugin(XPLMGetMyID())
{

}
