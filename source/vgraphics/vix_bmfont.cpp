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

namespace Vixen {

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
		info.spacingY = spacingValues[2];
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