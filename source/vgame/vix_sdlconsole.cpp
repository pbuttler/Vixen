#include <vix_sdlconsole.h>

namespace Vixen{
	
	SDLConsole::SDLConsole()
	{
		m_offset = 0;
	}

	SDLConsole::~SDLConsole()
	{
		
	}

	UString SDLConsole::Buffer()
	{
		return m_buffer.str();
	}

	void SDLConsole::Write(const char* text, size_t len)
	{
		/*limit buffer write to MAX_COMMAND_LEN*/
		if (m_offset + len < 64)
		{
			m_buffer << text;
			m_offset += len;
		}
	}

	void SDLConsole::Erase(size_t len)
	{
		/*erase everything*/
		if (len == -1) {
			m_buffer.str(VTEXT(""));
			m_buffer.clear();
			m_offset = 0;
			return;
		}

		/*kinda gross, a lot of copying but o well....*/
		UString temp = m_buffer.str();
		size_t end = temp.length();
		if (end != 0)
			temp = temp.erase(end - len);
		else
			return;
		m_buffer.str(VTEXT(""));
		m_buffer.clear();
		m_buffer << temp;
		m_offset = 0;
		m_offset = m_buffer.str().length();
	}
}