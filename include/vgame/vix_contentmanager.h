/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#ifndef VIX_CONTENTMANAGER_H
#define VIX_CONTENTMANAGER_H

#include <vix_platform.h>
#include <vix_singleton.h>
#include <vix_stringutil.h>
#include <vix_texture.h>
#include <vix_debugutil.h>
#include <vix_gltexture.h>
#include <vix_bmfont.h>
#include <map>

namespace Vixen {

	class IContent;

	class VIX_API ContentManager : public Singleton < ContentManager >
	{
		typedef std::map<UString, IContent*> ContentMap;
	public:
		ContentManager();

		~ContentManager();

		template <typename T>
		T* Load(const UString& path);

		void DumpTextures();

	private:
		ContentMap  m_textures;
		ContentMap  m_fonts;
		ContentMap  m_sounds;
	};

	template <>
	inline VIX_API BMFont* ContentManager::Load<BMFont>(const UString& path)
	{
		if (path.empty()) {
			DebugPrintF(VTEXT("Error Loading [BMFont]: %s\n"),
				ErrCodeString(ErrCode::ERR_NULL_PATH));
			return NULL;
		}

		ContentMap::iterator it = m_fonts.find(path);
		if (it != m_fonts.end()) {
			return (BMFont*)it->second;
		}
		else {
			/*create new texture*/
			BMFont* font = new BMFont(path);
			m_fonts[path] = (IContent*)font;
			return font;
		}

		return NULL;
	}

	template <>
	inline VIX_API Texture* ContentManager::Load<Texture>(const UString& path)
	{
		if (path.empty()) {
			DebugPrintF(VTEXT("Error Loading [Texture]: %s\n"),
				ErrCodeString(ErrCode::ERR_NULL_PATH));
			return NULL;
		}

		ContentMap::iterator it = m_textures.find(path);
		if (it != m_textures.end()) {
			return (Texture*)it->second;
		}
		else {
			/*create new texture*/
			Texture* texture = new GLTexture(path);
			m_textures[path] = (IContent*)texture;
			return texture;
		}

		return NULL;
	}

	extern ContentManager& g_ContentManager;
}

#endif