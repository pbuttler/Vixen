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


#ifndef VIX_BMFONT_H
#define VIX_BMFONT_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vector>
#include <map>

#include <tinyxml2.h>

namespace Vixen {

	typedef tinyxml2::XMLDocument XMLDOC;

	struct VIX_API BMFontChar
	{
		int id;
		int x;
		int y;
		int width;
		int height;
		int xOffset;
		int yOffset;
		int xAdvance;
		int page;
		int channel;
	};

	struct VIX_API BMFontInfo
	{
		std::string    file;
		std::string    face;
		int            size;
		int            bold;
		int            italic;
		std::string    charset;
		int            unicode;
		int            stretchH;
		int            smooth;
		int            antiAliasing;
		std::string    padding;
		int            padX;
		int            padY;
		int            padW;
		int            padH;
		int            spacingX;
		int            spacingY;
		int            outline;
	};

	struct VIX_API BMFontCommon
	{
		int lineHeight;
		int base;
		int scaleW;
		int scaleH;
		int pages;
		int packed;
		int alphaChannel;
		int redChannel;
		int greenChannel;
		int blueChannel;
	};

	struct VIX_API BMFontPage
	{
		int         id;
		std::string file;
	};

	struct VIX_API BMFontKerning
	{
		int  first;
		int  second;
		int  amount;
	};

	struct VIX_API BMFontFile
	{
		BMFontInfo                  info;
		BMFontCommon                common;
		std::vector<BMFontPage>     pages;
		std::vector<BMFontChar>     chars;
		std::vector<BMFontKerning>  kernings;
	};


	class VIX_API BMFont
	{
		typedef std::map<char, BMFontChar> BMCharMap;

	public:
		BMFont();


		/*Static parse functions for reading the XML Font file*/
		static void ReadFontInfo(XMLDOC& doc, BMFontFile& file);
		static void ReadFontCommon(XMLDOC& doc, BMFontFile& file);
		static void ReadFontPages(XMLDOC& doc, BMFontFile& file);
		static void ReadFontChars(XMLDOC& doc, BMFontFile& file);

	private:
		BMCharMap     m_charMap;
		BMFontFile    m_fontFile;
	};
}

#endif