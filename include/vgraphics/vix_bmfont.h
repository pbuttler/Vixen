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
#include <vix_tinyxml.h>
#include <vector>
#include <map>

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

		friend std::ostream& operator << (std::ostream& o, const BMFontChar& c);
	};

	std::ostream& operator << (std::ostream& o, const BMFontChar& c)
	{
		o << "[BMFontChar]\n"
			<< "\tID=" << c.id << "\n"
			<< "\tX=" << c.x << "\n"
			<< "\tY=" << c.y << "\n"
			<< "\tW=" << c.width << "\n"
			<< "\tH=" << c.height << "\n"
			<< "\tXOFF=" << c.xOffset << "\n"
			<< "\tYOFF=" << c.yOffset << "\n"
			<< "\tXADV=" << c.xAdvance << "\n"
			<< "\tPage=" << c.page << "\n"
			<< "\tChannel=" << c.channel << "\n";

		return o;
	}


	struct VIX_API BMFontInfo
	{
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

		friend std::ostream& operator << (std::ostream& o, const BMFontInfo& i);
	};

	std::ostream& operator << (std::ostream& o, const BMFontInfo& i)
	{
		o << "[BMFontInfo]\n"
			<< "\tFace=" << i.face << "\n"
			<< "\tSize=" << i.size << "\n"
			<< "\tBold=" << i.bold << "\n"
			<< "\tItalic=" << i.italic << "\n"
			<< "\tCharSet=" << i.charset << "\n"
			<< "\tUnicode=" << i.unicode << "\n"
			<< "\tStretchH=" << i.stretchH << "\n"
			<< "\tSmooth=" << i.smooth << "\n"
			<< "\tAA=" << i.antiAliasing << "\n"
			<< "\tPadding=" << i.padding << "\n"
			<< "\tPadX=" << i.padX << "\n"
			<< "\tPadY=" << i.padY << "\n"
			<< "\tPadW=" << i.padW << "\n"
			<< "\tPadH=" << i.padH << "\n"
			<< "\tSpacingX=" << i.spacingX << "\n"
			<< "\tSpacingY=" << i.spacingY << "\n"
			<< "\tOutline=" << i.outline << "\n";

		return o;
	}

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

		friend std::ostream& operator << (std::ostream& o, const BMFontCommon& c);
	};

	std::ostream& operator << (std::ostream& o, const BMFontCommon& c)
	{
		o << "[BMFontCommon]\n"
			<< "\tLineHeight=" << c.lineHeight << "\n"
			<< "\tBase=" << c.base << "\n"
			<< "\tScaleW=" << c.scaleW << "\n"
			<< "\tScaleH=" << c.scaleH << "\n"
			<< "\tPages=" << c.pages << "\n"
			<< "\tPacked=" << c.packed << "\n"
			<< "\tAlpha=" << c.alphaChannel << "\n"
			<< "\tRed=" << c.redChannel << "\n"
			<< "\tGreen=" << c.greenChannel << "\n"
			<< "\tBlue=" << c.blueChannel << "\n";

		return o;
	}

	struct VIX_API BMFontPage
	{
		int         id;
		std::string file;

		friend std::ostream& operator << (std::ostream& o, const BMFontPage& p);
	};

	std::ostream& operator << (std::ostream& o, const BMFontPage& p)
	{
		o << "[BMFontPage]\n"
			<< "\tID=" << p.id << "\n"
			<< "\tFile=" << p.file << "\n";

		return o;
	}

	struct VIX_API BMFontKerning
	{
		int  first;
		int  second;
		int  amount;

		friend std::ostream& operator << (std::ostream& o, const BMFontKerning& k);
	};

	std::ostream& operator << (std::ostream& o, const BMFontKerning& k)
	{
		o << "[BMFontKerning]\n"
			<< "\tFirst=" << k.first << "\n"
			<< "\tSecond=" << k.second << "\n"
			<< "\tAmount=" << k.amount << "\n";

		return o;
	}

	struct VIX_API BMFontFile
	{
		std::string                 file;
		BMFontInfo                  info;
		BMFontCommon                common;
		std::vector<BMFontPage>     pages;
		std::vector<BMFontChar>     chars;
		std::vector<BMFontKerning>  kernings;

		std::string ToString() const;
	};

	inline std::string BMFontFile::ToString() const
	{
		std::stringstream ss;
		ss << "---BMFontFile---" << "\n" << "\n"
			<< "File: " << file << "\n"
			<< info << "\n" << common;
		for (const BMFontPage& page : pages)
		{
			ss << page << "\n";
		}
		return ss.str();
	}


	/**
	* BMFont class
	* Desc:
	* Font class used to descibe fonts created by the BMFont tool
	* created by AngelCode and avaliable at: http://www.angelcode.com/products/bmfont/
	*/
	class VIX_API BMFont
	{
		typedef std::map<char, BMFontChar> BMCharMap;

	public:
		BMFont(const std::string& filePath);

		/*Getter functions*/
		const BMFontFile FontFile() const;

		/*Static parse functions for reading the XML Font file*/
		static void ReadFontInfo(XMLDOC& doc, BMFontFile& file);
		static void ReadFontCommon(XMLDOC& doc, BMFontFile& file);
		static void ReadFontPages(XMLDOC& doc, BMFontFile& file);
		static void ReadFontChars(XMLDOC& doc, BMFontFile& file);

		/*Static load function for loading BMFont file*/
		static BMFontFile LoadFile(const std::string& filePath);


		friend std::ostream& operator << (std::ostream& o, const BMFont& font);

	private:
		BMCharMap     m_charMap;
		BMFontFile    m_fontFile;
	};


	inline std::ostream& operator << (std::ostream& o, const BMFont& font)
	{
		o << font.FontFile().ToString();

		return o;
	}
}

#endif