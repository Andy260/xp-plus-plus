#include "XP++/DataAccess/UserDataRef.hpp"

// XP++ includes
#include "XP++/DataAccess/DataRefType.hpp"
#include "XP++/Exceptions/XPException.hpp"

// X-Plane SDK includes
#include "XPLMDataAccess.h"

XP::UserDataRef::UserDataRef(std::string name, int type, bool isWriteable) :
	DataRef(name, XPLMRegisterDataAccessor(name.c_str(), type, isWriteable, 
										   &UserDataRef::GetDatai,  &UserDataRef::SetDatai, 
										   &UserDataRef::GetDataf,  &UserDataRef::SetDataf, 
										   &UserDataRef::GetDatad,  &UserDataRef::SetDatad, 
										   &UserDataRef::GetDatavi, &UserDataRef::SetDatavi, 
										   &UserDataRef::GetDatavf, &UserDataRef::SetDatavf,
										   &UserDataRef::GetDatab,  &UserDataRef::SetDatab, 
										   this, this))
{
	// Ensure DataRef registration succeeded
	if (GetID() == nullptr)
	{
		throw XPException("Failed to register DataRef: " + name);
	}
}

XP::UserDataRef::~UserDataRef()
{
	// Unregister DataRef
	XPLMUnregisterDataAccessor(GetID());
}

std::shared_ptr<XP::UserDataRef> XP::UserDataRef::RegisterDataAccessor(std::string name, DataRefType type, bool isWriteable)
{
	std::shared_ptr<UserDataRef> dataRef(new UserDataRef(name, static_cast<int>(type), isWriteable), [](UserDataRef* userDataRef)
	{
		DataRef* dataRefToDelete = reinterpret_cast<DataRef*>(userDataRef);

		// Remove DataRef from master list
		auto foundDataRef = std::remove_if(m_dataRefs.begin(), m_dataRefs.end(), [dataRefToDelete](const std::weak_ptr<DataRef>& dataRefToRemove)
		{
			if (dataRefToRemove.expired())
			{
				return false;
			}

			std::shared_ptr<DataRef> lockedDataRef = dataRefToRemove.lock();
			return lockedDataRef.get() == dataRefToDelete;
		});
		if (foundDataRef == m_dataRefs.end())
		{
			throw XPException("Unable to destroy DataRef: Wasn't found in master list");
		}

		// Destroy DataRef
		delete userDataRef;
	});

	m_dataRefs.push_back(dataRef);

	return dataRef;
}

int XP::UserDataRef::GetDatai(void* inRefCon)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	if (dataRef->m_onReadInt == nullptr)
	{
		// No function assigned, return default value
		return 0;
	}
	else
	{
		// Return DataRef data
		return dataRef->m_onReadInt();
	}
}

void XP::UserDataRef::SetDatai(void* inRefCon, int inValue)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	if (dataRef->m_onWriteInt == nullptr)
	{
		// No function assigned
		return;
	}

	// Set DataRef data
	dataRef->m_onWriteInt(inValue);
}

float XP::UserDataRef::GetDataf(void* inRefCon)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	if (dataRef->m_onReadFloat == nullptr)
	{
		// No function assigned, return default value
		return 0.0f;
	}
	else
	{
		// Return DataRef data
		return dataRef->m_onReadFloat();
	}
}

void XP::UserDataRef::SetDataf(void* inRefCon, float inValue)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	if (dataRef->m_onWriteFloat == nullptr)
	{
		// No function assigned
		return;
	}

	// Set DataRef data
	dataRef->m_onWriteFloat(inValue);
}

double XP::UserDataRef::GetDatad(void* inRefCon)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	if (dataRef->m_onReadDouble == nullptr)
	{
		// No function assigned, return default value
		return 0.0;
	}
	else
	{
		// Return DataRef data
		return dataRef->m_onReadDouble();
	}
}

void XP::UserDataRef::SetDatad(void* inRefCon, double inValue)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	if (dataRef->m_onWriteDouble == nullptr)
	{
		// No function given
		return;
	}

	// Set DataRef data
	dataRef->m_onWriteDouble(inValue);
}

int XP::UserDataRef::GetDatavi(void* inRefCon, int* outValues, int inOffset, int inMax)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	outValues = nullptr;
	if (dataRef->m_onReadIntArray == nullptr)
	{
		// No function assigned
		return static_cast<int>(false);
	}
	else
	{
		// Get array data
		return dataRef->m_onReadIntArray(outValues, inOffset, inMax);
	}
}

void XP::UserDataRef::SetDatavi(void* inRefCon, int* inValues, int inOffset, int inCount)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	// Ensure inValues isn't a NULL pointer
	if (inValues == nullptr)
	{
		throw std::invalid_argument("inValues is NULL");
	}

	if (dataRef->m_onWriteIntArray == nullptr)
	{
		// No function assigned
		return;
	}

	// Set array data
	dataRef->m_onWriteIntArray(inValues, inOffset, inCount);
}

int XP::UserDataRef::GetDatavf(void* inRefCon, float* outValues, int inOffset, int inMax)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	outValues = nullptr;
	if (dataRef->m_onReadFloatArray == nullptr)
	{
		// No function assigned
		return static_cast<int>(false);
	}
	else
	{
		// Get array data
		return dataRef->m_onReadFloatArray(outValues, inOffset, inMax);
	}
}

void XP::UserDataRef::SetDatavf(void* inRefCon, float* inValues, int inOffset, int inCount)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	// Ensure inValues isn't a NULL pointer
	if (inValues == nullptr)
	{
		throw std::invalid_argument("inValues is NULL");
	}

	if (dataRef->m_onWriteFloatArray == nullptr)
	{
		// No function assigned
		return;
	}

	// Set array data
	dataRef->m_onWriteFloatArray(inValues, inOffset, inCount);
}

int XP::UserDataRef::GetDatab(void* inRefCon, void* outValue, int inOffset, int inMaxLength)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	outValue = nullptr;
	if (dataRef->m_onReadDataArray == nullptr)
	{
		// No function assigned
		return static_cast<int>(false);
	}
	else
	{
		// Get array data
		return dataRef->m_onReadDataArray(outValue, inOffset, inMaxLength);
	}
}

void XP::UserDataRef::SetDatab(void* inRefCon, void* inValue, int inOffset, int inLength)
{
	// Get pointer to DataRef
	UserDataRef* dataRef = static_cast<UserDataRef*>(inRefCon);

	// Ensure inValues isn't a NULL pointer
	if (inValue == nullptr)
	{
		throw std::invalid_argument("inValues is NULL");
	}

	if (dataRef->m_onWriteDataArray == nullptr)
	{
		// No function assigned
		return;
	}

	// Set array data
	dataRef->m_onWriteDataArray(inValue, inOffset, inLength);
}
