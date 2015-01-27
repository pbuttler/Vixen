#ifndef VIX_VERTEX_DEFS_H
#define VIX_VERTEX_DEFS_H

#include <vix_platform.h>
#include <vix_gl.h>
#include <vix_glbuffers.h>

namespace Vixen {

	struct VertexPositionColor
	{
		float x, y, z;
		float r, g, b, a;

		VertexPositionColor() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			r = 0.0f; g = 0.0f; b = 0.0f; a = 1.0f;
		}

		VertexPositionColor(float _x, float _y, float _z,
			                float _r, float _g, float _b, float _a)
		{
			x = _x; y = _y; z = _z;
			r = _r; g = _g; b = _b; a = _a;
		}

		static void Enable(bool flag)
		{
			if(flag) {
				glEnableVertexAttribArray(0); //position
				glEnableVertexAttribArray(1); //color
			} else {
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
			}
		}

		static void Render(GLsizei index_cnt)
		{
			size_t stride = sizeof(VertexPositionColor);
			int    offset = 0;
			
			/*POSITION*/
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*COLOR*/
			offset += sizeof(float) * 2; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(GL_TRIANGLES, index_cnt, GL_UNSIGNED_SHORT, NULL);
		}
	};


	/*USEFULL TYPEDEFS FOR VERTEX TYPES*/
	typedef GLVertexBuffer<VertexPositionColor> VertexPosColorBuffer;

}

#endif