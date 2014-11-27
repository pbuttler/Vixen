#include <vix_gameconfig.h>
#include <vix_stringutil.h>
#include <vix_debugutil.h>

namespace Vixen {

	GameConfig::GameConfig(const UString& path)
	{
		LoadConfig(path);
	}

	ErrCode GameConfig::LoadConfig(const UString& path)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		using namespace tinyxml2;
		/*Load config file*/
		XMLDOC document;
		XMLError err = document.LoadFile(path.c_str());
		UString errMsg;
		if (XMLErrCheck(err, errMsg)) {
			DebugPrintF(VTEXT("GameConfig file failed to load: %s\n"),
				errMsg.c_str());
			return ErrCode::ERR_XML_LOAD_FAIL;
		}

		/*Parse config file*/
		error = ParseConfig(document);
		if (CheckError(error)) {
			DebugPrintF(VTEXT("GameConfig failed to parse: %s\n"),
				        ErrCodeString(error));
		}

		return error;
	}

	ErrCode GameConfig::ParseConfig(const XMLDOC& doc)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*Parse Window Attributes*/
		m_windowArgs = ParseWindow(doc);

		return error;
	}

	SDL_GW_Params GameConfig::ParseWindow(const XMLDOC& doc)
	{
		using namespace tinyxml2;

		SDL_GW_Params params;
		const XMLElement* gameElement = doc.FirstChildElement("game");
		const XMLElement* windowElement = gameElement->FirstChildElement("window");
#ifdef UNICODE /*this could change in future*/
		UConverter convert;
		params.title = convert.from_bytes(windowElement->Attribute("title"));
#else
		params.title = windowElement->Attribute("title");
#endif
		params.x = windowElement->IntAttribute("x");
		params.y = windowElement->IntAttribute("y");
		params.width = windowElement->IntAttribute("width");
		params.height = windowElement->IntAttribute("height");

		return params;
	}

	SDL_GW_Params GameConfig::WindowArgs() const
	{
		return m_windowArgs;
	}

}