#ifndef VIX_CONSOLE_H
#define VIX_CONSOLE_H

#include <vix_platform.h>
#include <vix_noncopy.h>
#include <vix_renderer.h>
#include <vix_bmfont.h>
#include <vix_texture.h>

namespace Vixen {

	class VIX_API IConsole : public INonCopy
	{
	public: 
		virtual ~IConsole() { }

		virtual bool    IsActive(void) = 0;
		virtual void    Toggle(void) = 0;
		virtual void    Show(void) = 0;
		virtual void    Hide(void) = 0;
		virtual UString Buffer(void) = 0;
		virtual void	Write(const char* text, size_t len) = 0;
		virtual void	Erase(size_t len) = 0;
		virtual void    Render(IRenderer* renderer, int x, int y) = 0;
		virtual void    SetFont(BMFont* font) = 0;
		virtual void    SetTexture(Texture* tex) = 0;
		
	protected:
		USStream  m_buffer;
		int       m_offset;
		bool      m_visible;
		BMFont*   m_font;
		Texture*  m_texture;
	};
}

#endif