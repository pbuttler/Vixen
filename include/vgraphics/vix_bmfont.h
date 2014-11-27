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
#include <vix_rectangle.h>
#include <vector>
#include <map>


namespace Vixen {


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

		friend UOStream& operator << (UOStream& o, const BMFontChar& c);
	};

	UOStream& operator << (UOStream& o, const BMFontChar& c)
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
		UString    face;
		int            size;
		int            bold;
		int            italic;
		UString    charset;
		int            unicode;
		int            stretchH;
		int            smooth;
		int            antiAliasing;
		UString    padding;
		int            padX;
		int            padY;
		int            padW;
		int            padH;
		int            spacingX;
		int            spacingY;
		int            outline;

		friend UOStream& operator << (UOStream& o, const BMFontInfo& i);
	};

	UOStream& operator << (UOStream& o, const BMFontInfo& i)
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

		friend UOStream& operator << (UOStream& o, const BMFontCommon& c);
	};

	UOStream& operator << (UOStream& o, const BMFontCommon& c)
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
		UString     file;

		friend UOStream& operator << (UOStream& o, const BMFontPage& p);
	};

	UOStream& operator << (UOStream& o, const BMFontPage& p)
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

		friend UOStream& operator << (UOStream& o, const BMFontKerning& k);
	};

	UOStream& operator << (UOStream& o, const BMFontKerning& k)
	{
		o << "[BMFontKerning]\n"
			<< "\tFirst=" << k.first << "\n"
			<< "\tSecond=" << k.second << "\n"
			<< "\tAmount=" << k.amount << "\n";

		return o;
	}

	struct VIX_API BMFontFile
	{
		UString                     file;
		BMFontInfo                  info;
		BMFontCommon                common;
		std::vector<BMFontPage>     pages;
		std::vector<BMFontChar>     chars;
		std::vector<BMFontKerning>  kernings;

		UString ToString() const;
	};

	inline UString BMFontFile::ToString() const
	{
		USStream ss;
		ss << "---BMFontFile---" << "\n" << "\n"
			<< "File: " << file << "\n"
			<< info << "\n" << common;
		for (const BMFontPage& page : pages)
		{
			ss << page << "\n";
		}
		return ss.str();
	}


	class Texture;

	/**
	* BMFont class
	* Desc:
	* Font class used to descibe fonts created by the BMFont tool
	* created by AngelCode and avaliable at: http://www.angelcode.com/products/bmfont/
	*/
	class VIX_API BMFont
	{
		typedef std::map<UChar, BMFontChar>    BMCharMap;

	public:
		/*Constructor for BMFont*/
		BMFont(const UString& filePath);

		/*Adds a texture to the font page tex collection*/
		void AddPageTexture(Texture* texture);

		/*Getter functions*/
		const BMFontFile FontFile() const;

		const Texture*   PageTexture(int index) const;

		/*Functions*/
		Rectangle  Bounds(const UString& text);

		/*Static parse functions for reading the XML Font file*/
		static void ReadFontInfo(XMLDOC& doc, BMFontFile& file);
		static void ReadFontCommon(XMLDOC& doc, BMFontFile& file);
		static void ReadFontPages(XMLDOC& doc, BMFontFile& file);
		static void ReadFontChars(XMLDOC& doc, BMFontFile& file);

		/*Static load function for loading BMFont file*/
		static BMFontFile LoadFile(const UString& filePath);


		friend UOStream& operator << (UOStream& o, const BMFont& font);

	private:
		/*Utilities*/
		
		/*Find font character in char map*/
		bool FindChar(UChar c, BMFontChar& fc);

	private:
		std::vector<Texture*>   m_textures;
		BMCharMap               m_charMap;
		BMFontFile              m_fontFile;
	};


	inline UOStream& operator << (UOStream& o, const BMFont& font)
	{
		/*Will fail if UNICODE and outputting to console window without UTF-8 locale set*/
		o << font.FontFile().ToString();

		return o;
	}
}

#endif