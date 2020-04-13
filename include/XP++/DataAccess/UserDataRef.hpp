#pragma once

// STL includes
#include <string>

// XP++ includes
#include "XP++/DataAccess/DataRef.hpp"

namespace XP
{
	/// <summary>
	/// A <see cref="DataRef"/> created by the user
	/// </summary>
	class UserDataRef final : public DataRef
	{
	public:
		/// <summary>
		/// Creates a new item of data that can be read and written
		/// </summary>
		/// <remarks>
		/// After registering your data ref, you should set the behaviour for
		/// getting and setting data for your data ref
		/// </remarks>
		/// <param name="name">Full name for searching this DataRef</param>
		/// <param name="type">Type of DataRef to register</param>
		/// <returns>Pointer to created DataRef</returns>
		static std::shared_ptr<UserDataRef> RegisterDataAccessor(std::string name, DataRefType type, bool isWriteable);

		/// <summary>
		/// Gets the function used to read Integer data from this data ref
		/// </summary>
		/// <returns>Function used to read Integer data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<int()> GetOnReadInt() const
		{
			return m_onReadInt;
		}
		/// <summary>
		/// Sets the function used to read Integer data from this data ref
		/// </summary>
		/// <param name="value">Function used to read Integer data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnReadInt(std::function<int()> value)
		{
			m_onReadInt = value;
		}

		/// <summary>
		/// Gets the function used to write Integer data from this data ref
		/// </summary>
		/// <returns>Function used to write Integer data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<void(int)> GetOnWriteInt() const
		{
			return m_onWriteInt;
		}
		/// <summary>
		/// Sets the function used to write Integer data from this data ref
		/// </summary>
		/// <param name="value">Function used to write Integer data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnWriteInt(std::function<void(int)> value)
		{
			m_onWriteInt = value;
		}

		/// <summary>
		/// Gets the function used to read Floating Point data from this data ref
		/// </summary>
		/// <returns>Function used to read Floating Point data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<float()> GetOnReadFloat() const
		{
			return m_onReadFloat;
		}
		/// <summary>
		/// Sets the function used to read Floating Point data from this data ref
		/// </summary>
		/// <param name="value">Function used to read Floating Point data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnReadFloat(std::function<float()> value)
		{
			m_onReadFloat = value;
		}

		/// <summary>
		/// Gets the function used to write Floating Point data from this data ref
		/// </summary>
		/// <returns>Function used to write Floating Point data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<void(float)> GetOnWriteFloat() const
		{
			return m_onWriteFloat;
		}
		/// <summary>
		/// Sets the function used to write Floating Point data from this data ref
		/// </summary>
		/// <param name="value">Function used to write Floating Point data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnWriteFloat(std::function<void(float)> value)
		{
			m_onWriteFloat = value;
		}

		/// <summary>
		/// Gets the function used to read Double Precision Floating Point data from this data ref
		/// </summary>
		/// <returns>Function used to read Double Precision Floating Point data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<double()> GetOnReadDouble() const
		{
			return m_onReadDouble;
		}
		/// <summary>
		/// Sets the function used to read Double Precision Floating Point data from this data ref
		/// </summary>
		/// <param name="value">Function used to read Double Precision Floating Point data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnReadDouble(std::function<double()> value)
		{
			m_onReadDouble = value;
		}

		/// <summary>
		/// Gets the function used to write Double Precision Floating Point data from this data ref
		/// </summary>
		/// <returns>Function used to write Double Precision Floating Point data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<void(double)> GetOnWriteDouble() const
		{
			return m_onWriteDouble;
		}
		/// <summary>
		/// Sets the function used to write Double Precision Floating Point data from this data ref
		/// </summary>
		/// <param name="value">Function used to write Double Precision Floating Point data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnWriteDouble(std::function<void(double)> value)
		{
			m_onWriteDouble = value;
		}

		/// <summary>
		/// Gets the function used to read Integer Array data from this data ref
		/// </summary>
		/// <returns>Function used to read Integer Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<int(int*, int, int)> GetOnReadIntArray() const
		{
			return m_onReadIntArray;
		}
		/// <summary>
		/// Sets the function used to read Integer Array data from this data ref
		/// </summary>
		/// <param name="value">Function used to read Integer Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnReadIntArray(std::function<int(int*, int, int)> value)
		{
			m_onReadIntArray = value;
		}

		/// <summary>
		/// Gets the function used to write Integer Array data from this data ref
		/// </summary>
		/// <returns>Function used to write Integer Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<void(int*, int, int)> GetOnWriteIntArray() const
		{
			return m_onWriteIntArray;
		}
		/// <summary>
		/// Sets the function used to write Integer Array data from this data ref
		/// </summary>
		/// <param name="value">Function used to write Integer Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnWriteIntArray(std::function<void(int*, int, int)> value)
		{
			m_onWriteIntArray = value;
		}

		/// <summary>
		/// Gets the function used to read Floating Point Array data from this data ref
		/// </summary>
		/// <returns>Function used to read Floating Point Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<int(float*, int, int)> GetOnReadFloatArray() const
		{
			return m_onReadFloatArray;
		}
		/// <summary>
		/// Sets the function used to read Floating Point Array data from this data ref
		/// </summary>
		/// <param name="value">Function used to read Floating Point Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnReadFloatArray(std::function<int(float*, int, int)> value)
		{
			m_onReadFloatArray = value;
		}

		/// <summary>
		/// Gets the function used to write Floating Point Array data from this data ref
		/// </summary>
		/// <returns>Function used to write Floating Point Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<void(float*, int, int)> GetOnWriteFloatArray() const
		{
			return m_onWriteFloatArray;
		}
		/// <summary>
		/// Sets the function used to write Floating Point Array data from this data ref
		/// </summary>
		/// <param name="value">Function used to write Floating Point Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnWriteFloatArray(std::function<void(float*, int, int)> value)
		{
			m_onWriteFloatArray = value;
		}

		/// <summary>
		/// Gets the function used to read Byte Array data from this data ref
		/// </summary>
		/// <returns>Function used to read Byte Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<int(void*, int, int)> GetOnReadDataArray() const
		{
			return m_onReadDataArray;
		}
		/// <summary>
		/// Sets the function used to read Byte Array data from this data ref
		/// </summary>
		/// <param name="value">Function used to read Byte Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnReadDataArray(std::function<int(void*, int, int)> value)
		{
			m_onReadDataArray = value;
		}

		/// <summary>
		/// Gets the function used to write Byte Array data from this data ref
		/// </summary>
		/// <returns>Function used to write Byte Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</returns>
		inline std::function<void(void*, int, int)> GetOnWriteDataArray() const
		{
			return m_onWriteDataArray;
		}
		/// <summary>
		/// Sets the function used to write Byte Array data from this data ref
		/// </summary>
		/// <param name="value">Function used to write Byte Array data from this data ref, 
		/// or NULL if not supported by this data ref, or data ref is created 
		/// and managed externally from this plug-in</param>
		inline void SetOnWriteDataArray(std::function<void(void*, int, int)> value)
		{
			m_onWriteDataArray = value;
		}

	private:
		UserDataRef(std::string name, int type, bool isWriteable);
		~UserDataRef();

		UserDataRef(const UserDataRef&)				= delete;
		UserDataRef& operator=(const UserDataRef&)	= delete;

		// Function for reading Integer data
		std::function<int()> m_onReadInt;
		// Function for writing Integer data
		std::function<void(int)> m_onWriteInt;

		// Function for reading Floating Point data
		std::function<float()> m_onReadFloat;
		// Function for writing Floating Point data
		std::function<void(float)> m_onWriteFloat;

		// Function for reading Double Precision Floating Point data
		std::function<double()> m_onReadDouble;
		// Function for writing Double Precision Floating Point data
		std::function<void(double)> m_onWriteDouble;

		// Function for reading Integer Array data
		std::function<int(int*, int, int)> m_onReadIntArray;
		// Function for writing Integer Array data
		std::function<void(int*, int, int)> m_onWriteIntArray;

		// Function for reading Floating Point Array data
		std::function<int(float*, int, int)> m_onReadFloatArray;
		// Function for writing Floating Point Array data
		std::function<void(float*, int, int)> m_onWriteFloatArray;

		// Function for reading Byte Array data
		std::function<int(void*, int, int)> m_onReadDataArray;
		// Function for writing Byte Array data
		std::function<void(void*, int, int)> m_onWriteDataArray;

		// Integer Data Getter function handler
		static int GetDatai(void* inRefCon);
		// Integer Data Setter function handler
		static void SetDatai(void* inRefCon, int inValue);
		// Floating Point Data Getter function handler
		static float GetDataf(void* inRefCon);
		// Floating Point Data Setter function handler
		static void SetDataf(void* inRefCon, float inValue);
		// Double Precision Floating Point Data Getter function handler
		static double GetDatad(void* inRefCon);
		// Double Precision Floating Point Data Setter function handler
		static void SetDatad(void* inRefCon, double inValue);
		// Integer Array Data Getter function handler
		static int GetDatavi(void* inRefCon, int* outValues, int inOffset, int inMax);
		// Integer Array Data Setter function handler
		static void SetDatavi(void* inRefCon, int* inValues, int inOffset, int inCount);
		// Floating Point Array Data Getter function handler
		static int GetDatavf(void* inRefCon, float* outValues, int inOffset, int inMax);
		// Floating Point Array Data Setter function handler
		static void SetDatavf(void* inRefCon, float* inValues, int inOffset, int inCount);
		// Byte Array Data Getter function handler
		static int GetDatab(void* inRefCon, void* outValue, int inOffset, int inMaxLength);
		// Byte Array Data Setter function handler
		static void SetDatab(void* inRefCon, void* inValue, int inOffset, int inLength);
	};
}
