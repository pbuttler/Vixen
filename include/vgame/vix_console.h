#ifndef VIX_CONSOLE_H
#define VIX_CONSOLE_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_renderer.h>

namespace Vixen {

	class VIX_API IConsole : public INonCopy
	{
	public: 
		virtual ~IConsole() { }

		virtual UString Buffer(void) = 0;
		virtual void	Write(const char* text, size_t len) = 0;
		virtual void	Erase(size_t len) = 0;

		
	protected:
		USStream  m_buffer;
		int       m_offset;

	};
}

#endif