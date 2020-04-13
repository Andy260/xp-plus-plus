#include "XP++/DataAccess/DataRef.hpp"

// STL includes
#include <algorithm>
#include <stdexcept>

// XP++ includes
#include "XP++/DataAccess/DataRefType.hpp"
#include "XP++/Exceptions/XPException.hpp"

// X-Plane SDK includes
#include "XPLMDataAccess.h"

std::list<std::weak_ptr<XP::DataRef>> XP::DataRef::m_dataRefs;

XP::DataRef::DataRef(std::string name, void* id) :
	m_id(id), m_name(name)
{

}

XP::DataRef::~DataRef()
{
	// Destroy X-Plane Data Ref
	XPLMUnregisterDataAccessor(m_id);
}

std::weak_ptr<XP::DataRef> XP::DataRef::FindDataRef(std::string name)
{
	// Attempt to find created data ref
	auto foundDataRefItr = std::find_if(m_dataRefs.begin(), m_dataRefs.end(), [&name](const std::weak_ptr<DataRef>& dataRef)
	{
		if (dataRef.expired())
		{
			return false;
		}
		else
		{
			std::shared_ptr<DataRef> lockedDataRef = dataRef.lock();
			return lockedDataRef->GetName() == name;
		}
	});

	if (foundDataRefItr != m_dataRefs.end())
	{
		// Found requested DataRef
		return (*foundDataRefItr);
	}
	else
	{
		// Requested DataRef not found, create it
		void* foundDataRef = XPLMFindDataRef(name.c_str());
		if (foundDataRef == nullptr)
		{
			// Requested DataRef doesn't exist
			return std::shared_ptr<DataRef>(nullptr);
		}

		// Create wrapper object
		std::shared_ptr<DataRef> dataRef(new DataRef(name, foundDataRef), [](DataRef* dataRefToDelete)
		{
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
			delete dataRefToDelete;
		});
		m_dataRefs.push_back(dataRef);

		return dataRef;
	}
}

bool XP::DataRef::IsGood() const
{
	return XPLMIsDataRefGood(m_id);
}

XP::DataRefType XP::DataRef::GetType() const
{
	// Get X-Plane Data Ref type
	XPLMDataTypeID xplmType = XPLMGetDataRefTypes(m_id);

	// Return wrapped type object
	return DataRefType(static_cast<int>(xplmType));
}

int XP::DataRef::GetIntData() const
{
	return XPLMGetDatai(m_id);
}

void XP::DataRef::SetIntData(int value)
{
	XPLMSetDatai(m_id, value);
}

float XP::DataRef::GetFloatData() const
{
	return XPLMGetDataf(m_id);
}

void XP::DataRef::SetFloatData(float value)
{
	XPLMSetDataf(m_id, value);
}

double XP::DataRef::GetDoubleData() const
{
	return XPLMGetDatad(m_id);
}

void XP::DataRef::SetDoubleData(double value)
{
	XPLMSetDatad(m_id, value);
}

int XP::DataRef::GetIntArrayData(int* outValues, int offset, int max)
{
	return XPLMGetDatavi(m_id, outValues, offset, max);
}

void XP::DataRef::SetIntArrayData(int* inValues, int offset, int count)
{
	XPLMSetDatavi(m_id, inValues, offset, count);
}

int XP::DataRef::GetFloatArrayData(float* outValues, int offset, int max)
{
	return XPLMGetDatavf(m_id, outValues, offset, max);
}

void XP::DataRef::SetFloatArrayData(float* inValues, int offset, int count)
{
	XPLMSetDatavf(m_id, inValues, offset, count);
}

int XP::DataRef::GetByteArrayData(void* outValues, int offset, int max)
{
	return XPLMGetDatab(m_id, outValues, offset, max);
}

void XP::DataRef::SetByteArrayData(void* inValues, int offset, int count)
{
	XPLMSetDatab(m_id, inValues, offset, count);
}
