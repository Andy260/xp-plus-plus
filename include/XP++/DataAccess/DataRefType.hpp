#pragma once

// XP++ includes
#include "XP++/Exceptions/NotImplementedException.hpp"

namespace XP
{
	/// <summary>
	/// Defines the type of data behind a data reference
	/// </summary>
	/// <remarks>
	/// This allows you to sanity check that the data type matches what you expect. 
	/// But for the most part, you will know the type of data you are expecting from 
	/// the online documentation. Data types each take a bit field; it is legal to 
	/// have a single dataref be more than one type of data. When this happens, 
	/// you can pick any matching get / set API.
	/// </remarks>
	enum class DataType : int
	{
		/// <summary>
		/// Data of a type the current XPLM/XP++ doesn't do.
		/// </summary>
		Unknown = 0,
		/// <summary>
		/// A single 4-byte integer, native endian.
		/// </summary>
		Int = 1,
		/// <summary>
		/// A single 4-byte float, native endian.
		/// </summary>
		Float = 2,
		/// <summary>
		/// A single 8-byte double, native endian.
		/// </summary>
		Double = 4,
		/// <summary>
		/// An array of 4-byte floats, native endian.
		/// </summary>
		FloatArray = 8,
		/// <summary>
		/// An array of 4-byte integers, native endian.
		/// </summary>
		IntArray = 16,
		/// <summary>
		/// A variable block of data.
		/// </summary>
		Data = 32
	};

	/// <summary>
	/// Representation of Data Types a <see cref="DataRef"/> supports
	/// </summary>
	class DataRefType
	{
	public:
		/// <summary>
		/// Constructs an object representation of data a <see cref="DataRef"/> supports
		/// </summary>
		/// <param name="unknown">True if supports <see cref="DataType::Unknown"/> data</param>
		/// <param name="integer">True if supports <see cref="DataType::Int"/> data</param>
		/// <param name="floatingPoint">True if supports <see cref="DataType::Float"/> data</param>
		/// <param name="doubleFloat">True if supports <see cref="DataType::Double"/> data</param>
		/// <param name="floatArray">True if supports <see cref="DataType::FloatArray"/> data</param>
		/// <param name="intArray">True if supports <see cref="DataType::IntArray"/> data</param>
		/// <param name="data">True multiple data types are supported</param>
		DataRefType(bool unknown, 
					bool integer, 
					bool floatingPoint, 
					bool doubleFloat, 
					bool floatArray, 
					bool intArray, 
					bool data);
		/// <summary>
		/// Constructs an object representation of data a <see cref="DataRef"/> supports
		/// </summary>
		/// <param name="supportedType">Supported Data type</param>
		DataRefType(DataType supportedType);
		/// <summary>
		/// Constructs an object representation of data a <see cref="DataRef"/> supports
		/// </summary>
		/// <param name="bitFlag">Bit flag of data supported</param>
		DataRefType(int bitFlag);

		~DataRefType()								= default;
		DataRefType(const DataRefType&)				= default;
		DataRefType& operator=(const DataRefType&)	= default;

		/// <summary>
		/// Supports <see cref="DataType::Unknown"/> data
		/// </summary>
		/// <returns>True if data type is supported</returns>
		inline bool SupportsUnknown() const
		{
			return static_cast<bool>(m_bitFlag & static_cast<int>(DataType::Unknown));
		}

		/// <summary>
		/// Supports <see cref="DataType::Int"/> data
		/// </summary>
		/// <returns>True if data type is supported</returns>
		inline bool SupportsInteger() const
		{
			return static_cast<bool>(m_bitFlag & static_cast<int>(DataType::Int));
		}

		/// <summary>
		/// Supports <see cref="DataType::Float"/> data
		/// </summary>
		/// <returns>True if data type is supported</returns>
		inline bool SupportsFloat() const
		{
			return static_cast<bool>(m_bitFlag & static_cast<int>(DataType::Float));
		}

		/// <summary>
		/// Supports <see cref="DataType::Double"/> data
		/// </summary>
		/// <returns>True if data type is supported</returns>
		inline bool SupportsDouble() const
		{
			return static_cast<bool>(m_bitFlag & static_cast<int>(DataType::Double));
		}

		/// <summary>
		/// Supports <see cref="DataType::FloatArray"/> data
		/// </summary>
		/// <returns>True if data type is supported</returns>
		inline bool SupportsFloatArray() const
		{
			return static_cast<bool>(m_bitFlag & static_cast<int>(DataType::FloatArray));
		}

		/// <summary>
		/// Supports <see cref="DataType::IntArray"/> data
		/// </summary>
		/// <returns>True if data type is supported</returns>
		inline bool SupportsIntArray() const
		{
			return static_cast<bool>(m_bitFlag & static_cast<int>(DataType::IntArray));
		}

		/// <summary>
		/// Is a variable block of data supporting multiple types of data
		/// </summary>
		/// <returns>True if multiple data types are supported</returns>
		inline bool IsVariableBlock() const
		{
			return static_cast<bool>(m_bitFlag & static_cast<int>(DataType::Data));
		}

		/// <summary>
		/// Casts this object to an Integer bit-flag
		/// </summary>
		/// <returns>Bit Flag representation of this object</returns>
		inline explicit operator int() const
		{
			return m_bitFlag;
		}

	private:
		// Bit flag of supported data types
		int m_bitFlag;
	};
}
