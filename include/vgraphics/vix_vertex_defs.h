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

		static void RenderElements(GLsizei index_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(VertexPositionColor);
			int    offset = 0;
			
			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*COLOR*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(render_mode, index_cnt, GL_UNSIGNED_SHORT, NULL);
			
		}

		static void RenderArrays(GLsizei vertex_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(VertexPositionColor);
			int    offset = 0;
			
			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*COLOR*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawArrays(render_mode, 0, vertex_cnt);
		}
	};

	struct VertexPositionTexture
	{
		float x, y, z;
		float u, v;

		VertexPositionTexture() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			u = 0.0f; v = 0.0f;
		}

		VertexPositionTexture(float _x, float _y, float _z,
			                  float _u, float _v)
		{
			x = _x; y = _y; z = _z;
			u = _u; v = _v;
		}

		static void Enable(bool flag)
		{
			if (flag) {
				glEnableVertexAttribArray(0); //position
				glEnableVertexAttribArray(1); //texture
			}
			else {
				glDisableVertexAttribArray(0); //position
				glDisableVertexAttribArray(1); //texture
			}
		}

		static void Render(GLsizei index_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(VertexPositionTexture);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TEXTURE*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(render_mode, index_cnt, GL_UNSIGNED_SHORT, NULL);
		}
	};

	struct VertexPositionColorTexture
	{
		float x, y, z;
		float r, g, b, a;
		float u, v;

		VertexPositionColorTexture() {
			x = 0.0f; y = 0.0f; z = 0.0f;
			r = 0.0f; g = 0.0f; b = 0.0f; a = 1.0f;
			u = 0.0f; v = 0.0f;
		}

		VertexPositionColorTexture(float _x, float _y, float _z,
			float _r, float _g, float _b, float _a,
			float _u, float _v)
		{
			x = _x; y = _y; z = _z;
			r = _r; g = _g; b = _b; a = _a;
			u = _u; v = _v;
		}

		static void Enable(bool flag)
		{
			if (flag) {
				glEnableVertexAttribArray(0); //position
				glEnableVertexAttribArray(1); //color
				glEnableVertexAttribArray(2); //texture
			}
			else {
				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
				glDisableVertexAttribArray(2);
			}
		}

		static void Render(GLsizei index_cnt, GLenum render_mode)
		{
			size_t stride = sizeof(VertexPositionColorTexture);
			int    offset = 0;

			/*POSITION*/
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*COLOR*/
			offset += sizeof(float) * 3; //update offset
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);
			/*TEXTURE*/
			offset += sizeof(float) * 4;
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (const GLvoid*)offset);

			/*RENDER*/
			glDrawElements(render_mode, index_cnt, GL_UNSIGNED_SHORT, NULL);
		}
	};

	/*USEFULL TYPEDEFS FOR VERTEX TYPES*/
	typedef GLVertexBuffer<VertexPositionColor>			VertPosColBuffer;
	typedef GLVertexBuffer<VertexPositionTexture>		VertPosTexBuffer;
	typedef GLVertexBuffer<VertexPositionColorTexture>	VertPosColTexBuffer;

}

#endif