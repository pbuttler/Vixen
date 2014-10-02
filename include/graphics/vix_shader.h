#ifndef VIX_SHADER_H
#define VIX_SHADER_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_stringutil.h>

namespace Vixen {

	namespace Graphics {

		class VIX_API Shader
		{

			GLuint m_program;	//opengl shader program handle
		public:
			
			Shader(void);
	
			~Shader(void);
			
			void initFromString(const std::string& vShaderStr, const std::string& fShaderStr);
			
			void initFromFile(const std::string& vShaderPath, const std::string& fShaderPath);
			
			void bind();
			
			void unbind();
			
			const GLuint getProgramID() const;
			
			const GLuint getUniformLoc(const GLchar* name) const;
		private:
		
			static const GLchar* readShader(const std::string& fileName);
		
			void loadShader(GLenum shaderType, const GLchar* source);
		
			void loadShaderStr(GLenum shaderType, const char* source);
		
			static bool checkCompiled(GLuint shader);
			
			static bool checkLinked(GLuint program);
		
		};

	}
}

#endif