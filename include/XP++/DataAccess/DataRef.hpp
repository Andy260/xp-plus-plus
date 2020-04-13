#pragma once

// STL includes
#include <memory>
#include <functional>
#include <string>
#include <list>

namespace XP
{
	// Pre-declarations
	enum class DataType;
	class DataRefType;

	/// <summary>
	/// Data reference provides generic, flexible, high 
	/// performance way to read and write data to and 
	/// from X-Plane and other plug-ins
	/// </summary>
	class DataRef
	{
	public:
		DataRef(const DataRef&)				= delete;
		DataRef& operator=(const DataRef&)	= delete;

		/// <summary>
		/// Finds a data ref
		/// </summary>
		/// <param name="name">Name of the data ref to find</param>
		/// <returns>Found data ref, or NULL if none found</returns>
		static std::weak_ptr<DataRef> FindDataRef(std::string name);

		/// <summary>
		/// Checks if this Data Ref hasn't been orphaned
		/// </summary>
		/// <remarks>
		/// There is normally no need to call this function; datarefs returned by 
		/// <see cref="FindDataRef"/> remain valid (but possibly orphaned) unless there is a 
		/// complete plugin reload (in which case your plugin is reloaded anyway). 
		/// Orphaned datarefs can be safely read and return 0. Therefore you never 
		/// need to call <see cref="IsGood"/> to ‘check’ the safety of a dataref. 
		/// (<see cref="IsGood"/> performs some slow checking of the handle validity, 
		/// so it has a performance cost.)
		/// </remarks>
		/// <returns>True if Data Ref is not orphaned</returns>
		bool IsGood() const;

		/// <summary>
		/// What are the type(s) of data this data ref supports?
		/// </summary>
		/// <returns>Object representing Data type(s) supported by this data ref</returns>
		DataRefType GetType() const;

		/// <summary>
		/// Reads Integer data from this data ref
		/// </summary>
		/// <returns>Integer data from this data ref</returns>
		int GetIntData() const;
		/// <summary>
		/// Writes Integer data from to this data ref
		/// </summary>
		/// <param name="value">Integer data to write to this data ref</param>
		void SetIntData(int value);

		/// <summary>
		/// Reads Floating Point data from this data ref
		/// </summary>
		/// <returns>Float Point data from this data ref</returns>
		float GetFloatData() const;
		/// <summary>
		/// Writes Floating Point data from to this data ref
		/// </summary>
		/// <param name="value">Floating Point data to write to this data ref</param>
		void SetFloatData(float value);

		/// <summary>
		/// Reads Double Precision Floating Point data from this data ref
		/// </summary>
		/// <returns>Double Precision Float Point data from this data ref</returns>
		double GetDoubleData() const;
		/// <summary>
		/// Writes Double Precision Floating Point data from to this data ref
		/// </summary>
		/// <param name="value">Double Precision Floating Point data to write to this data ref</param>
		void SetDoubleData(double value);

		/// <summary>
		/// Reads integer array data from this data ref
		/// </summary>
		/// <remarks>
		/// <para>
		/// If outValues is not NULL, then up to inMax values are copied from the dataref 
		/// into outValues, starting at inOffset in the dataref. If inMax + inOffset is 
		/// larger than the size of the dataref, less than inMax values will be copied. 
		/// The number of values copied is returned.
		/// </para>
	    /// <para>
	    /// Note: the semantics of array datarefs are entirely implemented by the plugin 
	    /// (or X-Plane) that provides the dataref, not the SDK itself; the above description 
	    /// is how these datarefs are intended to work, but a rogue plugin may have different 
	    /// behaviour.
	    /// </para>
		/// </remarks>
		/// <param name="outValues">Pointer to array to write to (can be NULL so the function 
		/// will return the size of the array)</param>
		/// <param name="offset">Offset from index 0 in the array of the data ref</param>
		/// <param name="max">Maximum number of elements to copy from the offset</param>
		/// <returns>If <see cref="outValues"/> is NULL, the size of the array is returned</returns>
		int GetIntArrayData(int* outValues, int offset, int max);
		/// <summary>
		/// Writes integer data array data to this data ref
		/// </summary>
		/// <remarks>
		/// <para>
		/// Write part or all of an integer array dataref. The values passed by inValues 
		/// are written into the dataref starting at inOffset. Up to inCount values are written; 
		/// however if the values would write “off the end” of the dataref array, then fewer 
		/// values are written.
		/// </para>
		/// <para>
		/// Note: the semantics of array datarefs are entirely implemented by the plugin (or X-Plane) 
		/// that provides the dataref, not the SDK itself; the above description is how these datarefs 
		/// are intended to work, but a rogue plugin may have different behaviour.
		/// </para>
		/// </remarks>
		/// <param name="inValues">Pointer to data to copy from</param>
		/// <param name="offset">Offset from <see cref="inValues"/> to copy from</param>
		/// <param name="count">Number of elements to copy from the given offset and pointer</param>
		void SetIntArrayData(int* inValues, int offset, int count);

		/// <summary>
		/// Reads floating point array data from this data ref
		/// </summary>
		/// <remarks>
		/// <para>
		/// Read a part of a single precision floating point array dataref. If you pass 
		/// NULL for outVaules, the routine will return the size of the array, ignoring 
		/// inOffset and inMax.
		/// </para>
		/// <para>
		/// If outValues is not NULL, then up to inMax values are copied from the dataref 
		/// into outValues, starting at inOffset in the dataref. If inMax + inOffset is 
		/// larger than the size of the dataref, less than inMax values will be copied. 
		/// The number of values copied is returned.
		/// </para>
		/// <para>
		/// Note: the semantics of array datarefs are entirely implemented by the plugin 
		/// (or X-Plane) that provides the dataref, not the SDK itself; the above description 
		/// is how these datarefs are intended to work, but a rogue plugin may have different 
		/// behaviour.
		/// </para>
		/// </remarks>
		/// <param name="outValues">Pointer to array to write to (can be NULL so the 
		/// function will return the size of the array)</param>
		/// <param name="offset">Offset from index 0 in the array of the data ref</param>
		/// <param name="max">Maximum number of elements to copy from the offset</param>
		/// <returns>If <see cref="outValues"/> is NULL, the size of the array is returned</returns>
		int GetFloatArrayData(float* outValues, int offset, int max);
		/// <summary>
		/// Writes floating point data array data to this data ref
		/// </summary>
		/// <remarks>
		/// <para>
		/// Write part or all of a single precision floating point array dataref. 
		/// The values passed by inValues are written into the dataref starting at 
		/// inOffset. Up to inCount values are written; however if the values would 
		/// write “off the end” of the dataref array, then fewer values are written.
		/// </para>
		/// <para>
		/// Note: the semantics of array datarefs are entirely implemented by the plugin 
		/// (or X-Plane) that provides the dataref, not the SDK itself; the above description 
		/// is how these datarefs are intended to work, but a rogue plugin may have different 
		/// behaviour.
		/// </para>
		/// </remarks>
		/// <param name="inValues">Pointer to data to copy from</param>
		/// <param name="offset">Offset from <see cref="inValues"/> to copy from</param>
		/// <param name="count">Number of elements to copy from the given offset and pointer</param>
		void SetFloatArrayData(float* inValues, int offset, int count);

		/// <summary>
		/// Reads byte array data from this data ref
		/// </summary>
		/// <remarks>
		/// <para>
		/// Read a part of a byte array dataref. If you pass NULL for outVaules, the routine 
		/// will return the size of the array, ignoring inOffset and inMax.
		/// </para>
		/// <para>
		/// If outValues is not NULL, then up to inMax values are copied from the dataref into outValues, 
		/// starting at inOffset in the dataref. If inMax + inOffset is larger than the size of the dataref, 
		/// less than inMax values will be copied. The number of values copied is returned.
		/// </para>
		/// <para>
		/// Note: the semantics of array datarefs are entirely implemented by the plugin (or X-Plane) that 
		/// provides the dataref, not the SDK itself; the above description is how these datarefs are 
		/// intended to work, but a rogue plugin may have different behaviour.
		/// </para>
		/// </remarks>
		/// <param name="outValues">Pointer to array to write to (can be NULL so the function will return the size of the array)</param>
		/// <param name="offset">Offset from index 0 in the array of the data ref</param>
		/// <param name="max">Maximum number of elements to copy from the offset</param>
		/// <returns>If <see cref="outValues"/> is NULL, the size of the array is returned</returns>
		int GetByteArrayData(void* outValues, int offset, int max);
		/// <summary>
		/// Writes byte data array data to this data ref
		/// </summary>
		/// <remarks>
		/// <para>
		/// Write part or all of a byte array dataref. The values passed by inValues 
		/// are written into the dataref starting at inOffset. Up to inCount values 
		/// are written; however if the values would write “off the end” of the 
		/// dataref array, then fewer values are written.
		/// </para>
		/// <para>
		/// Note: the semantics of array datarefs are entirely implemented by the plugin 
		/// (or X-Plane) that provides the dataref, not the SDK itself; the above description 
		/// is how these datarefs are intended to work, but a rogue plugin may have different 
		/// behaviour.
		/// </para>
		/// </remarks>
		/// <param name="inValues">Pointer to data to copy from</param>
		/// <param name="offset">Offset from <see cref="inValues"/> to copy from</param>
		/// <param name="count">Number of elements to copy from the given offset and pointer</param>
		void SetByteArrayData(void* inValues, int offset, int count);

		/// <summary>
		/// Name of this DataRef
		/// </summary>
		/// <returns>String representing the name of this DataRef</returns>
		inline std::string GetName() const
		{
			return m_name;
		}

	protected:
		// Used for creating DataRefs externally managed and/or created by the consuming plug-in
		DataRef(std::string name, void* id);
		~DataRef();

		inline void* GetID() const
		{
			return m_id;
		}

		// Created DataRefs
		static std::list<std::weak_ptr<DataRef>> m_dataRefs;

	private:
		// Name/Path to this DataRef
		std::string m_name;

		// Internal X-Plane DataRef ID
		void* m_id;
	};
}
