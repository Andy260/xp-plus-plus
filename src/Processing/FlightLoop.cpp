#include "XP++/Processing/FlightLoop.hpp"

// XP++ includes
#include "XP++/Exceptions/NotImplementedException.hpp"

// X-Plane SDK includes
#include "XPLMProcessing.h"

XP::FlightLoop::FlightLoop(void* id, std::function<float(float, float, int)> callback) :
	m_id(id), m_callback(callback)
{
	
}

XP::FlightLoop::~FlightLoop()
{
	XPLMDestroyFlightLoop(m_id);
}

std::shared_ptr<XP::FlightLoop> XP::FlightLoop::CreateFlightLoop(FlightLoopPhaseType phase, std::function<float(float, float, int)> callback)
{
	// Create wrapper object
	std::shared_ptr<FlightLoop> flightLoop(new FlightLoop(nullptr, callback), [](FlightLoop* flightLoop)
	{
		delete flightLoop;
	});

	// Create FlightLoop X-Plane structure
	XPLMCreateFlightLoop_t flightLoopOptions;
	flightLoopOptions.structSize = sizeof(flightLoopOptions);
	
	// Set phase type
	switch (phase)
	{
	case XP::FlightLoopPhaseType::BeforeFlightModel:
		flightLoopOptions.phase = xplm_FlightLoop_Phase_BeforeFlightModel;
		break;

	case XP::FlightLoopPhaseType::AfterFlightModel:
		flightLoopOptions.phase = xplm_FlightLoop_Phase_AfterFlightModel;
		break;

	default:
		throw NotImplementedException();
	}
	// Set refcon and callback function
	flightLoopOptions.refcon		= flightLoop.get();
	flightLoopOptions.callbackFunc	= callback.target;

	// Create X-Plane flight loop
	flightLoop->m_id = XPLMCreateFlightLoop(&flightLoopOptions);

	return flightLoop;
}

void XP::FlightLoop::Schedule(float interval, int relativeToNow)
{
	XPLMScheduleFlightLoop(m_id, interval, relativeToNow);
}

void XP::FlightLoop::SetCallbackInterval(float interval, int relativeToNow)
{
	XPLMSetFlightLoopCallbackInterval(m_callback.target, interval, relativeToNow, this);
}
