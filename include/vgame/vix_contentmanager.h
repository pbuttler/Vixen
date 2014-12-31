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
#include <vix_manager.h>
#include <vix_paths.h>
#include <map>

namespace Vixen {

	class IContent;

	class VIX_API ContentManager : public Singleton < ContentManager >, IManager
	{
		friend class Singleton < ContentManager >;

		typedef std::map<UString, IContent*> ContentMap;
	public:
		ContentManager();

		~ContentManager();

		template <typename T>
		T* Load(const UString& path);

		template <>
		BMFont* Load(const UString& path);

		template <>
		Texture* Load(const UString& path);

		void DumpTextures();

		ErrCode VStartUp()   override;

		ErrCode VShutDown()  override;

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

		UString _path = os_path(FONT_FOLDER_PATH + path);
		UString _texPath = os_path(FONT_FOLDER_PATH + TEX_FOLDER_PATH);

		ContentMap::iterator it = m_fonts.find(_path);
		if (it != m_fonts.end()) {
			return (BMFont*)it->second;
		}
		else {
			/*create new font*/
			BMFont* font = new BMFont(_path);
			/*load textures for font*/
			for (auto& page : font->FontFile().pages) {
				Texture* tex = Load<Texture>(_texPath + page.file);
				if (tex)
					font->AddPageTexture(tex);
			}
			m_fonts[_path] = (IContent*)font;
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

		UString _path = os_path(path);

		ContentMap::iterator it = m_textures.find(_path);
		if (it != m_textures.end()) {
			return (Texture*)it->second;
		}
		else {
			/*create new texture*/
			Texture* texture = new GLTexture(_path);
			m_textures[_path] = (IContent*)texture;
			return texture;
		}

		return NULL;
	}

	extern ContentManager&  g_ContentManager;
}

#endif