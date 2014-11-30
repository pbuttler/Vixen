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