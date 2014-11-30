#ifndef VIX_GLSHADER_H
#define VIX_GLSHADER_H

#include <vix_platform.h>
#include <vix_shader.h>
#include <vix_stringutil.h>
#include <vix_gl.h>

namespace Vixen {

	class VIX_API GLShader : public Shader
	{
	public:
		GLShader(const ShaderInfo& info);

		~GLShader();

		ErrCode VInitFromFile(const UString& path)  override;
		ErrCode VInitFromString(const UString& str) override;


		GLuint ShaderHandle() const;

	private:

		ErrCode  LoadShader(const GLchar* source);

		static const GLchar* ReadShader(const UString& path);
		static GLenum        GLShaderType(ShaderType type);
		static ErrCode       ValidateCompile(GLuint shader);
	private:
		GLuint     m_shader;
		ShaderInfo m_info;
	};

}

#endif