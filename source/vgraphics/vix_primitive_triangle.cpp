#include <vix_primitive_triangle.h>
#include <vix_color.h>
#include <array>

namespace Vixen {

	PrimitiveTriangle::PrimitiveTriangle()
	{
		m_rotation = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VertPosColBuffer(VERTEX_COUNT);
		m_iBuffer = new GLIndexBuffer(INDEX_COUNT);

		const std::array<VertexPositionColor, VERTEX_COUNT> vTemp =
		{
			VertexPositionColor(0.0f, 1.0f, 0.0f,
								Colors::Red.r, Colors::Red.g, Colors::Red.b, 1.0f),
			VertexPositionColor(1.0f, -1.0f, 0.0f,
			                    Colors::Blue.r, Colors::Blue.g, Colors::Blue.b, 1.0f),
			VertexPositionColor(-1.0f, -1.0f, 0.0f,
			                    Colors::Green.r, Colors::Green.g, Colors::Green.b, 1.0f)
		};
		m_vBuffer->set(0, VERTEX_COUNT, vTemp.data());

		const std::array<unsigned short, INDEX_COUNT> iTemp =
		{
			0, 1, 2
		};
		m_iBuffer->set(0, INDEX_COUNT, iTemp.data());

		init_shader_program();

	}

	PrimitiveTriangle::~PrimitiveTriangle()
	{
		delete m_vBuffer;
		delete m_iBuffer;
	}

	void PrimitiveTriangle::SetPosition(float x, float y, float z)
	{
		m_position = Vec3(x, y, z);
	}

	void PrimitiveTriangle::Rotate(float dt)
	{
		m_rotation += dt * 5.0f;
	}

	void PrimitiveTriangle::init_shader_program()
	{
		/*vertex shader info*/
		ShaderInfo vshader_info;
		vshader_info.filePath = VTEXT("Basic.vs");
		vshader_info.raw = VTEXT("");
		vshader_info.type = ShaderType::VERTEX_SHADER;

		/*fragment shader info*/
		ShaderInfo fshader_info;
		fshader_info.filePath = VTEXT("Basic.fs");
		fshader_info.raw = VTEXT("");
		fshader_info.type = ShaderType::FRAGMENT_SHADER;

		/*populate shader args*/
		ShaderArgs args;
		args[0] = vshader_info;
		args[1] = fshader_info;

		/*create shader program*/
		m_program = new GLShaderProgram(args);
	}

	void PrimitiveTriangle::applyTransform(GLCamera3D* camera)
	{
		GLuint projLoc;
		GLuint worldLoc;
		GLuint viewLoc;

		m_program->GetUniformLoc(SHADER_GLOBAL_PROJECTION, projLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_VIEW, viewLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_WORLD, worldLoc);

		Mat4 world = Mat4(0.0f);
		world =
			glm::translate(Mat4(1.0f), m_position) * //apply position
			glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 1, 0));

		/*apply value from camera*/
		glUniformMatrix4fv(projLoc,  1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc,  1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
	}

	void PrimitiveTriangle::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		m_iBuffer->bind();
		m_program->Bind();

		applyTransform(camera);

		VertexPositionColor::Enable(true);
		VertexPositionColor::RenderElements(INDEX_COUNT, GL_TRIANGLES);
		VertexPositionColor::Enable(false);

		m_vBuffer->unbind();
		m_iBuffer->unbind();
		m_program->Unbind();
	}

}