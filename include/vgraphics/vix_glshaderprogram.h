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

#ifndef VIX_GLSHADERPROGRAM_H
#define VIX_GLSHADERPROGRAM_H

#include <vix_platform.h>
#include <vix_shaderprogram.h>
#include <vix_glshader.h>

#define SHADER_GLOBAL_PROJECTION "gProjection"
#define SHADER_GLOBAL_WORLD      "gWorld"
#define SHADER_GLOBAL_VIEW       "gView"

namespace Vixen {

	class VIX_API GLShaderProgram : public ShaderProgram
	{
	public:
		GLShaderProgram(const ShaderArgs args);

		~GLShaderProgram();

		/*bind gl program to render pipeline*/
		void Bind();

		/*unbind gl program from render pipeline*/
		void Unbind();

		/*retrive uniform location*/
		ErrCode GetUniformLoc(const GLchar* name, GLuint& location);

	protected:
		ErrCode VCreateShadersFromArgs() override;
	    
		/*attach OpenGL shader to program*/
		void    AttachShader(Shader* shader);

		
		/*try and OpenGL link shader to program*/
		ErrCode LinkShader(Shader* shader);

	private:
		GLuint m_program;


		static ErrCode  ValidateCompile(GLuint program);
	};
}

#endif