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