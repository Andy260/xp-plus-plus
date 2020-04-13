#include "XP++/DataAccess/DataRefType.hpp"

XP::DataRefType::DataRefType(bool unknown, bool integer, bool floatingPoint, bool doubleFloat, bool floatArray, bool intArray, bool data) :
	m_bitFlag(0)
{
	// Set 'Unknown' bit
	if (unknown)
	{
		m_bitFlag = m_bitFlag | static_cast<int>(DataType::Unknown);
	}
	// Set 'Integer' bit
	if (integer)
	{
		m_bitFlag = m_bitFlag | static_cast<int>(DataType::Int);
	}
	// Set 'Float' bit
	if (floatingPoint)
	{
		m_bitFlag = m_bitFlag | static_cast<int>(DataType::Float);
	}
	// Set 'Double' bit
	if (doubleFloat)
	{
		m_bitFlag = m_bitFlag | static_cast<int>(DataType::Double);
	}
	// Set 'Float' bit
	if (floatArray)
	{
		m_bitFlag = m_bitFlag | static_cast<int>(DataType::FloatArray);
	}
	// Set 'Int' bit
	if (intArray)
	{
		m_bitFlag = m_bitFlag | static_cast<int>(DataType::IntArray);
	}
	// Set 'Data' bit
	if (data)
	{
		m_bitFlag = m_bitFlag | static_cast<int>(DataType::Data);
	}
}

XP::DataRefType::DataRefType(DataType supportedType) :
	m_bitFlag(static_cast<int>(supportedType))
{

}

XP::DataRefType::DataRefType(int bitFlag)
	: m_bitFlag(bitFlag)
{

}
