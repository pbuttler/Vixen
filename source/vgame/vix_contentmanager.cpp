#include <vix_contentmanager.h>

namespace Vixen {
	
	ContentManager& g_ContentManager = ContentManager::instance();

	ContentManager::ContentManager()
	{

	}

	ContentManager::~ContentManager()
	{

	}

	void ContentManager::DumpTextures()
	{
		for (auto& tex : m_textures)
		{
			Texture* _tex = (Texture*)tex.second;
			DebugPrintF(VTEXT("Texture [%s]\n"), _tex->name().c_str());
		}
	}
}