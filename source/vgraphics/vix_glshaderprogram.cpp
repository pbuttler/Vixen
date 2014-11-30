#include <vix_glshaderprogram.h>
#include <vix_debugutil.h>

namespace Vixen {

	GLShaderProgram::GLShaderProgram(const ShaderArgs args)
	{
		m_args = args;
		m_program = glCreateProgram();

		/*load and create shaders from args*/
		ErrCode error = VCreateShadersFromArgs();
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Failed to create shader program: %s\n"),
				ErrCodeString(error));
		}
		else {
			DebugPrintF(VTEXT("Created shader program"));
		}
	}

	GLShaderProgram::~GLShaderProgram()
	{
		glDeleteProgram(m_program);
	}

	ErrCode GLShaderProgram::VCreateShadersFromArgs()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*iterate over shader info objects*/
		for (auto& info : m_args) {
			switch (info.type)
			{
			case ShaderType::VERTEX_SHADER:
				if (!m_vShader) {
					m_vShader = new GLShader(info);
					AttachShader(m_vShader);
					LinkShader(m_vShader);
				}
				break;

			case ShaderType::FRAGMENT_SHADER:
				if (!m_fShader) {
					m_fShader = new GLShader(info);
					AttachShader(m_fShader);
					LinkShader(m_fShader);
				}
				break;
			default:
				break;
			}
		}

		return error;
	}

	void GLShaderProgram::AttachShader(Shader* shader)
	{
		if (shader) {
			glAttachShader(m_program, ((GLShader*)shader)->ShaderHandle());
		}
	}

	ErrCode GLShaderProgram::LinkShader(Shader* shader)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*link program to shader*/
		glLinkProgram(m_program);
		error = ValidateCompile(m_program);
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Failed to link shader to program: %s\n"),
				ErrCodeString(error));
			delete shader;
		}

		return error;
	}

	ErrCode GLShaderProgram::ValidateCompile(GLuint program)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		GLint linked;
		glGetProgramiv(program, GL_LINK_STATUS, &linked);
		if (!linked) {
			error = ErrCode::ERR_FAILURE;

			GLsizei length;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
			GLchar* log = new GLchar[length + 1];
			glGetProgramInfoLog(program, length, &length, log);
			DebugPrintF(VTEXT("Program Log: %s\n%s\n"),
				log, ErrCodeString(error));
			delete[] log;
		}

		return error;
	}
}