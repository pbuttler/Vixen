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

#ifndef VIX_SHADERPROGRAM_H
#define VIX_SHADERPROGRAM_H

#include <vix_platform.h>
#include <vix_shader.h>
#include <array>

namespace Vixen {

	typedef std::array<ShaderInfo, 4> ShaderArgs;

	class VIX_API ShaderProgram
	{
	public:
		virtual ~ShaderProgram() { };

	protected:

		virtual ErrCode VCreateShadersFromArgs() = 0;

	protected:
		ShaderArgs m_args;     /*collection of shader info*/
		Shader*    m_vShader;  /*vertex shader*/
		Shader*    m_fShader;  /*fragment shader*/
		Shader*    m_gShader;  /*geometry shader*/
		Shader*    m_tShader;  /*tess control shader*/
	};

}

#endif