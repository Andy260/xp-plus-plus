#pragma once

// STL includes
#include <exception>
#include <string>

namespace XP
{
	/// <summary>
	/// Thrown when an error was encountered while calling X-Plane SDK functions
	/// </summary>
	class XPException : public std::exception
	{
	public:
		/// <summary>
		/// Constructs new a XPException
		/// </summary>
		/// <param name="message">Message to give to this exception</param>
		XPException(std::string message) : std::exception(), m_message(message) { }

		/// <summary>
		/// Returns the explanatory string.
		/// </summary>
		/// <returns>Pointer to a null-terminated string with explanatory information. 
		/// The pointer is guaranteed to be valid at least until the exception object 
		/// from which it is obtained is destroyed, or until a non-const member function 
		/// on the exception object is called.</returns>
		virtual const char* what() const noexcept override
		{
			return m_message.c_str();
		}

	private:
		// Message of this exception
		std::string m_message;
	};
}
