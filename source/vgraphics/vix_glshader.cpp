#include <vix_glshader.h>
#include <vix_debugutil.h>
#include <vix_errglobals.h>

namespace Vixen {
	
	GLShader::GLShader(const ShaderInfo& info)
	{
		m_info = info;

		ErrCode error = ErrCode::ERR_SUCCESS;
		if (m_info.filePath.empty() && m_info.raw.empty()) {
			/*no file or raw contents avaliable for loading*/
			DebugPrintF(VTEXT("Shader creation failed: %s\n%s\n"),
				        VTEXT("No shader path or raw contents avaliable"),
						ErrCodeString(ErrCode::ERR_NULL_PATH));
		}

		/*determine if shader should load from file or raw contents*/
		if (!m_info.filePath.empty()) {
			error = VInitFromFile(m_info.filePath);
		}
		else {
			error = VInitFromString(m_info.raw);
		}

		if (CheckError(error)) {
			DebugPrintF(VTEXT("Shader creation failed: %s\n"),
				        ErrCodeString(error));
		}
	}

	GLShader::~GLShader()
	{
		glDeleteShader(m_shader);
	}

	ErrCode GLShader::VInitFromFile(const UString& path)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*grab source from file*/
		const GLchar* source = ReadShader(path);
		if (!source) {
			error = ErrCode::ERR_FAILURE;
			DebugPrintF(VTEXT("Failed to parse shader source: %s\n"),
				ErrCodeString(error));
			return error;
		}

		error = LoadShader(source);
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Failed to init shader from file: %s\n"),
				ErrCodeString(error));
			return error;
		}

		return error;
	}

	ErrCode GLShader::VInitFromString(const UString& path)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

#if defined UNICODE && defined VIX_SYS_WINDOWS
		UConverter cv;
		std::string _source = cv.to_bytes(m_info.raw.c_str());
		const GLchar* source = _source.c_str();
#else
		const GLchar* source = m_info.raw.c_str();
#endif
		error = LoadShader(source);
		if (CheckError(error)) {
			if (CheckError(error)) {
				DebugPrintF(VTEXT("Failed to init shader from source: %s\n"),
					ErrCodeString(error));
				return error;
			}
		}

		return error;
	}

	ErrCode GLShader::LoadShader(const GLchar* source)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		GLenum type = GLShaderType(m_info.type);
		if (type == GL_NONE) {
			error = ErrCode::ERR_FAILURE;
			DebugPrintF(VTEXT("Failed to Load Shader due to invalid type: %s\n"),
						ErrCodeString(error));
			return error;
		}

		/*create shader object*/
		m_shader = glCreateShader(type);

		/*put shader source into memory*/
		glShaderSource(m_shader, 1, &source, NULL);
		/*cleanup allocated source*/

		/*compile shader*/
		glCompileShader(m_shader);
		error = ValidateCompile(m_shader);

		return error;
	}

	ErrCode GLShader::ValidateCompile(GLuint shader)
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			error = ErrCode::ERR_FAILURE;
			GLsizei length;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

			/*output shader log info*/
			GLchar* log = new GLchar[length + 1];
			glGetShaderInfoLog(shader, length, &length, log);
			DebugPrintF(VTEXT("Shader Log: %s\n%s\n"),
						log, ErrCodeString(error));
			delete[] log;

			return error;
		}
		

		return error;
	}

	const GLchar* GLShader::ReadShader(const UString& path)
	{
		FILE* file;
#if defined VIX_SYS_WINDOWS && defined UNICODE
		_wfopen_s(&file, path.c_str(), VTEXT("rb"));
#else
		file = fopen(path.c_str(), VTEXT("rb"));
#endif
		if (!file) {
			DebugPrintF(VTEXT("Unabled to read shader: %s\n"),
				ErrCodeString(ErrCode::ERR_FAILURE));
			return NULL;
		}

		/*seek end of file*/
		fseek(file, 0, SEEK_END);
		/*cache length*/
		size_t len = ftell(file);
		/*seek beg of file*/
		fseek(file, 0, SEEK_SET);

		/*buffer source*/
		GLchar* src = new GLchar[len + 1];
		
		/*read file contents into buffer*/
		fread(src, 1, len, file);
		/*close file after read*/
		fclose(file);
		/*null terminate*/
		src[len] = 0;

		return src;
	}

	GLenum GLShader::GLShaderType(ShaderType type)
	{
		switch (type)
		{
		case Vixen::ShaderType::VERTEX_SHADER:
			return GL_VERTEX_SHADER;
			break;
		case Vixen::ShaderType::GEOMETRY_SHADER:
			return GL_GEOMETRY_SHADER;
			break;
		case Vixen::ShaderType::TESSELATION_SHADER:
			return GL_TESS_CONTROL_SHADER;
			break;
		case Vixen::ShaderType::FRAGMENT_SHADER:
			return GL_FRAGMENT_SHADER;
			break;
		}

		return GL_NONE;
	}

	GLuint GLShader::ShaderHandle() const
	{
		return m_shader;
	}
}