#ifndef VIX_GLSHADERPROGRAM_H
#define VIX_GLSHADERPROGRAM_H

#include <vix_platform.h>
#include <vix_shaderprogram.h>
#include <vix_glshader.h>

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

	protected:
		ErrCode VCreateShadersFromArgs() override;
	    
		void    AttachShader(Shader* shader);
		ErrCode LinkShader(Shader* shader);
		
	private:
		GLuint m_program;


		static ErrCode  ValidateCompile(GLuint program);
	};
}

#endif