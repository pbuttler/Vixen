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

#ifndef VIX_TINYXML_H
#define VIX_TINYXML_H

#include <vix_platform.h>
#include <vix_stringutil.h>

/*include for TinyXML2*/
#include <tinyxml2.h>

namespace Vixen {

	inline bool VIX_API XMLErrCheck(tinyxml2::XMLError error, std::string& errorMsg)
	{
		bool fail = true;
		switch (error)
		{
		case tinyxml2::XML_NO_ERROR:
			errorMsg = "XML_NO_ERROR";
			fail = false;
			break;
		case tinyxml2::XML_NO_ATTRIBUTE:
			errorMsg = "XML_NO_ATTRIBUTE";
			break;
		case tinyxml2::XML_WRONG_ATTRIBUTE_TYPE:
			errorMsg = "XML_WRONG_ATTRIBUTE_TYPE";
			break;
		case tinyxml2::XML_ERROR_FILE_NOT_FOUND:
			errorMsg = "XML_ERROR_FILE_NOT_FOUND";
			break;
		case tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED:
			errorMsg = "XML_ERROR_FILE_COULD_NOT_BE_OPENED";
			break;
		case tinyxml2::XML_ERROR_FILE_READ_ERROR:
			errorMsg = "XML_ERROR_FILE_READ_ERROR";
			break;
		case tinyxml2::XML_ERROR_ELEMENT_MISMATCH:
			errorMsg = "XML_ERROR_ELEMENT_MISMATCH";
			break;
		case tinyxml2::XML_ERROR_PARSING_ELEMENT:
			errorMsg = "XML_ERROR_PARSING_ELEMENT";
			break;
		case tinyxml2::XML_ERROR_PARSING_ATTRIBUTE:
			errorMsg = "XML_ERROR_PARSING_ATTRIBUTE";
			break;
		case tinyxml2::XML_ERROR_IDENTIFYING_TAG:
			errorMsg = "XML_ERROR_IDENTIFYING_TAG";
			break;
		case tinyxml2::XML_ERROR_PARSING_TEXT:
			errorMsg = "XML_ERROR_PARSING_TEXT";
			break;
		case tinyxml2::XML_ERROR_PARSING_CDATA:
			errorMsg = "XML_ERROR_PARSING_CDATA";
			break;
		case tinyxml2::XML_ERROR_PARSING_COMMENT:
			errorMsg = "XML_ERROR_PARSING_COMMENT";
			break;
		case tinyxml2::XML_ERROR_PARSING_DECLARATION:
			errorMsg = "XML_ERROR_PARSING_DECLARATION";
			break;
		case tinyxml2::XML_ERROR_PARSING_UNKNOWN:
			errorMsg = "XML_ERROR_PARSING_UNKNOWN";
			break;
		case tinyxml2::XML_ERROR_EMPTY_DOCUMENT:
			errorMsg = "XML_ERROR_EMPTY_DOCUMENT";
			break;
		case tinyxml2::XML_ERROR_MISMATCHED_ELEMENT:
			errorMsg = "XML_ERROR_MISMATCHED_ELEMENT";
			break;
		case tinyxml2::XML_ERROR_PARSING:
			errorMsg = "XML_ERROR_PARSING";
			break;
		case tinyxml2::XML_CAN_NOT_CONVERT_TEXT:
			errorMsg = "XML_CAN_NOT_CONVERT_TEXT";
			break;
		case tinyxml2::XML_NO_TEXT_NODE:
			errorMsg = "XML_NO_TEXT_NODE";
			break;
		}
		
		return fail;
	}

}

#endif