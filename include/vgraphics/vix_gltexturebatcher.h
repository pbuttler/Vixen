#ifndef VIX_GLTEXTUREBATCHER_H
#define VIX_GLTEXTUREBATCHER_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_glshader.h>

namespace Vixen {

	//////////////////////////////////////////////////////////////////////////
	// DEFAULT VERTEX / FRAGMENT SHADERS
	//////////////////////////////////////////////////////////////////////////

	static const UString UNIFORM_PROJECTION = UString(VTEXT("gProjection"));
	static const UString UNIFORM_SAMPLER = UString(VTEXT("gSampler"));
	static const UString OUT_TEXCOORD = UString(VTEXT("TexCoord0"));
	static const UString OUT_COLOR = UString(VTEXT("Color"));
	static const UString DEF_VERT_SHADER = UString(VTEXT("#version ")) + VTEXT("330\n\n\n") +
		VTEXT("layout(location = 0) in vec2 vPosition;\n") +
		VTEXT("layout(location = 1) in vec4 vColor;\n") +
		VTEXT("layout(location = 2) in vec2 vTexCoord;\n") +
		VTEXT("out vec2 ") + OUT_TEXCOORD + VTEXT(";\n") +
		VTEXT("out vec4 ") + OUT_COLOR + VTEXT(";\n") +
		VTEXT("uniform mat4 ") + UNIFORM_PROJECTION + VTEXT(";\n") +
		VTEXT("void main()\n") +
		VTEXT("{\n") +
		VTEXT("gl_Position = ") + UNIFORM_PROJECTION +
		VTEXT(" * ") + VTEXT("vec4(vPosition, 0.0, 1.0);\n") + OUT_TEXCOORD + VTEXT(" = ") +
		VTEXT("vTexCoord;\n") + OUT_COLOR + VTEXT(" = ") + VTEXT("vColor;\n") + VTEXT("}\n");

	static const UString DEF_FRAG_SHADER = UString(VTEXT("#version ")) + VTEXT("330\n\n\n") +
		VTEXT("in vec2 ") + OUT_TEXCOORD + VTEXT(";\n") +
		VTEXT("in vec4 ") + OUT_COLOR + VTEXT(";\n") +
		VTEXT("uniform sampler2D ") + UNIFORM_SAMPLER + VTEXT(";\n\n") +
		VTEXT("void main()\n") + VTEXT("{\n\n") +
		VTEXT("gl_FragColor = ") + VTEXT("texture2D(") + UNIFORM_SAMPLER + VTEXT(",") + OUT_TEXCOORD +
		VTEXT(".st) * ") + OUT_COLOR + VTEXT(";\n") +
		VTEXT("}\n");

	class VIX_API GLTextureBatcher
	{
	public:
		GLTextureBatcher();

		~GLTextureBatcher();

	};

}

#endif