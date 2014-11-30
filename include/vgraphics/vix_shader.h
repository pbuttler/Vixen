#ifndef VIX_SHADER_H
#define VIX_SHADER_H

#include <vix_platform.h>
#include <vix_content.h>
#include <vix_stringutil.h>
#include <vix_errglobals.h>

namespace Vixen {

	enum class ShaderType
	{
		VERTEX_SHADER,
		GEOMETRY_SHADER,
		TESSELATION_SHADER,
		FRAGMENT_SHADER /*DX: PIXEL_SHADER */
	};

	struct ShaderInfo
	{
		ShaderType type;       /*type of shader*/
		UString    filePath;   /*path to shader*/
		UString    raw;        /*raw contents of shader*/
	};

	class VIX_API Shader : IContent
	{
	public:
		virtual ~Shader() { };

	protected:
		/*Virtual functions*/
		virtual ErrCode VInitFromFile(const UString& path) = 0;
		virtual ErrCode VInitFromString(const UString& path) = 0;
	};

}

#endif