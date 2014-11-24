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

#include <vix_bmfont.h>
#include <vix_debugutil.h>
#include <vix_errglobals.h>
#include <vix_algorithms.h>
#include <vix_texture.h>

namespace Vixen {

	BMFont::BMFont(const std::string& filePath)
	{
		m_fontFile = LoadFile(filePath);

		/*check for unicode font*/
		if (m_fontFile.info.unicode) {
			/*Create unicode character map*/
			for (BMFontChar& fontChar : m_fontFile.chars)
			{
				wchar_t c = (wchar_t)fontChar.id;
				m_wideCharMap[c] = fontChar;
			}
		}
		else {
			/*Create ansi character map*/
			for (BMFontChar& fontChar : m_fontFile.chars)
			{
				char c = (char)fontChar.id;
				m_charMap[c] = fontChar;
			}
		}
		
	}

	void BMFont::AddPageTexture(Texture* texture)
	{
		if (!texture) {
			DebugPrintF("Cannot add NULL texture");
			return;
		}

		/*Check if texture doesn't already exist in collection*/
		std::vector<Texture*>::iterator it;
		it = std::find(m_textures.begin(), m_textures.end(), texture);
		if (it == m_textures.end()) {
			/*we can safely add the texture to our collection*/
			m_textures.push_back(texture);
		}
		else {
			DebugPrintF("Texture %s already exists in BMFont collection", texture->name().c_str());
			return;
		}
	}

	const BMFontFile BMFont::FontFile() const
	{
		return m_fontFile;
	}

	/*Returns the pixel unit bounds of a string of text*/
	Rectangle BMFont::BoundsA(const std::string& text)
	{
		Rectangle bounds;
		int dx = 0;
		int lineH = m_fontFile.common.lineHeight;
		int dy = lineH;
		/*Iterate over characters in text*/
		for (const char& c : text)
		{
			if (c == '\n') {
				dx = 0;
				dy += lineH;
			}

			//Find the font character and advance the
			//pixel units based on the xAdvance value
			BMFontChar fc;
			if (FindCharA(c, fc)) {
				dx += fc.xAdvance;
			}
		}

		bounds.x = 0;
		bounds.y = 0;
		bounds.w = dx;
		bounds.h = dy;
		
		return bounds;
	}

	Rectangle BMFont::BoundsW(const std::wstring& text)
	{
		Rectangle bounds;
		int dx = 0;
		int lineH = m_fontFile.common.lineHeight;
		int dy = lineH;
		/*Iterate over characters in text*/
		for (const wchar_t& c : text)
		{
			if (c == '\n') {
				dx = 0;
				dy += lineH;
			}

			//Find the font character and advance the
			//pixel units based on the xAdvance value
			BMFontChar fc;
			if (FindCharW(c, fc)) {
				dx += fc.xAdvance;
			}
		}

		bounds.x = 0;
		bounds.y = 0;
		bounds.w = dx;
		bounds.h = dy;

		return bounds;
	}

	bool BMFont::FindCharA(char c, BMFontChar& fc)
	{
		BMACharMap::iterator it = m_charMap.find(c);
		if (it != m_charMap.end())
		{
			fc = it->second;
			return true;
		}
		else
			return false;
	}

	bool BMFont::FindCharW(wchar_t c, BMFontChar& fc)
	{
		BMWCharMap::iterator it = m_wideCharMap.find(c);
		if (it != m_wideCharMap.end())
		{
			fc = it->second;
			return true;
		}
		else
			return false;
	}

	BMFontFile BMFont::LoadFile(const std::string& filePath)
	{
		using namespace tinyxml2;

		BMFontFile file;
		if (filePath.empty()) {
			DebugPrintF("Failed to create BMFont: %s\n",
				        ErrCodeString(ErrCode::ERR_NULL_PATH).c_str());
			return file;
		}

		/*set file attribute of font file*/
		file.file = filePath;

		/*Try Parse file*/
		XMLDOC document;
		XMLError err = document.LoadFile(filePath.c_str());
		std::string errorString;
		if (XMLErrCheck(err, errorString)) {
			DebugPrintF("XMLDocument Load Failed: %s\n", errorString.c_str());
			return file;
		}

		/*Read file contents into bmfont file struct*/
		BMFont::ReadFontInfo(document, file);
		BMFont::ReadFontCommon(document, file);
		BMFont::ReadFontPages(document, file);
		BMFont::ReadFontChars(document, file);

		return file;
	}

	void BMFont::ReadFontInfo(XMLDOC& doc, BMFontFile& file)
	{
		using namespace tinyxml2;
		XMLElement* fontElement = doc.FirstChildElement("font");
		XMLElement* infoElement = fontElement->FirstChildElement("info");

		/*Populate font info struct of file with parsed info*/
		BMFontInfo& info = file.info;
		info.face = infoElement->Attribute("face");
		info.size = infoElement->IntAttribute("size");
		info.bold = infoElement->IntAttribute("bold");
		info.italic = infoElement->IntAttribute("italic");
		info.charset = infoElement->Attribute("charset");
		info.unicode = infoElement->IntAttribute("unicode");
		info.stretchH = infoElement->IntAttribute("stretchH");
		info.smooth = infoElement->IntAttribute("smooth");
		info.antiAliasing = infoElement->IntAttribute("aa");
		info.padding = infoElement->Attribute("padding");
		/*Need to parse the padding values*/
		std::vector<int> paddingValues = parse<int>(info.padding, ',');
		info.padX = paddingValues[0];
		info.padY = paddingValues[1];
		info.padW = paddingValues[2];
		info.padH = paddingValues[3];
		/*Need to parse the spacing values*/
		std::string spacing = infoElement->Attribute("spacing");
		std::vector<int> spacingValues = parse<int>(spacing, ',');
		info.spacingX = spacingValues[0];
		info.spacingY = spacingValues[1];
		info.outline = infoElement->IntAttribute("outline");
	}

	void BMFont::ReadFontCommon(XMLDOC& doc, BMFontFile& file)
	{
		using namespace tinyxml2;
		XMLElement* fontElement = doc.FirstChildElement("font");
		XMLElement* commonElement = fontElement->FirstChildElement("common");

		/*Populate font common struct of file*/
		BMFontCommon& common = file.common;
		common.lineHeight = commonElement->IntAttribute("lineHeight");
		common.base = commonElement->IntAttribute("base");
		common.scaleW = commonElement->IntAttribute("scaleW");
		common.scaleH = commonElement->IntAttribute("scaleH");
		common.pages = commonElement->IntAttribute("pages");
		common.packed = commonElement->IntAttribute("packed");
		common.alphaChannel = commonElement->IntAttribute("alphaChnl");
		common.redChannel = commonElement->IntAttribute("redChnl");
		common.greenChannel = commonElement->IntAttribute("greenChnl");
		common.blueChannel = commonElement->IntAttribute("blueChnl");
	}

	void BMFont::ReadFontChars(XMLDOC& doc, BMFontFile& file)
	{
		using namespace tinyxml2;
		XMLElement* fontElement = doc.FirstChildElement("font");
		XMLElement* charsElement = fontElement->FirstChildElement("chars");
		int count = charsElement->IntAttribute("count");

		/*Populate font file chars collection*/
		std::vector<BMFontChar>& chars = file.chars;
		XMLElement* charElement = charsElement->FirstChildElement("char");
		for (int i = 0; i < count; i++)
		{
			
			BMFontChar c;
			c.id = charElement->IntAttribute("id");
			c.x = charElement->IntAttribute("x");
			c.y = charElement->IntAttribute("y");
			c.width = charElement->IntAttribute("width");
			c.height = charElement->IntAttribute("height");
			c.xOffset = charElement->IntAttribute("xoffset");
			c.yOffset = charElement->IntAttribute("yoffset");
			c.xAdvance = charElement->IntAttribute("xadvance");
			c.page = charElement->IntAttribute("page");
			c.channel = charElement->IntAttribute("chnl");
			chars.push_back(c);

			/*move to next char element*/
			charElement = charElement->NextSiblingElement("char");
		}
	}

	void BMFont::ReadFontPages(XMLDOC& doc, BMFontFile& file)
	{
		using namespace tinyxml2;
		XMLElement* fontElement = doc.FirstChildElement("font");
		XMLElement* pagesElement = fontElement->FirstChildElement("pages");

		/*Populate font file pages collection*/
		std::vector<BMFontPage>& pages = file.pages;
		XMLElement* pageElement = pagesElement->FirstChildElement("page");
		while (pageElement)
		{
			BMFontPage p;
			p.id = pageElement->IntAttribute("id");
			p.file = pageElement->Attribute("file");
			pages.push_back(p);
			
			/*Try and move to next page element*/
			pageElement = pageElement->NextSiblingElement("page");
		}
	}
}