#include <vix_primitive_cube.h>
#include <vix_color.h>

namespace Vixen {

	PrimitiveCube::PrimitiveCube()
	{
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
		m_rotationZ = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VertPosColBuffer(COLOR_VERT_COUNT);
		m_iBuffer = new GLIndexBuffer(COLOR_INDEX_COUNT);


		init_shader_program();
		init_color_vi_buffers();
	}

	PrimitiveCube::~PrimitiveCube()
	{

	}

	void PrimitiveCube::RotateX(float dt)
	{
		m_rotationX += dt * 50.0f;
	}

	void PrimitiveCube::RotateY(float dt)
	{
		m_rotationY += dt * 50.0f;
	}

	void PrimitiveCube::RotateZ(float dt)
	{
		m_rotationZ += dt * 50.0f;
	}

	void PrimitiveCube::SetPosition(float x, float y, float z)
	{
		m_position = Vec3(x, y, z);
	}

	void PrimitiveCube::init_color_vi_buffers()
	{
		const std::array<VertexPositionColor, COLOR_VERT_COUNT> vTemp =
		{
			VertexPositionColor(-1.0f, 1.0f, 1.0f,
			   Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor(1.0f, 1.0f, 1.0f, 
			   Colors::Blue.r, Colors::Blue.g, Colors::Blue.b, Colors::Blue.a),
			VertexPositionColor(-1.0f, -1.0f, 1.0f,
			   Colors::Yellow.r, Colors::Yellow.g, Colors::Yellow.b, Colors::Yellow.a),
			VertexPositionColor(1.0f, -1.0f, 1.0f,
			   Colors::Pink.r, Colors::Pink.g, Colors::Pink.b, Colors::Pink.a),

			VertexPositionColor(1.0f, 1.0f, -1.0f,
			   Colors::Green.r, Colors::Green.g, Colors::Green.b, Colors::Green.a),
			VertexPositionColor(-1.0f, 1.0f, -1.0f,
			   Colors::Orange.r, Colors::Orange.g, Colors::Orange.b, Colors::Orange.a),
			VertexPositionColor(1.0, -1.0f, -1.0f,
			   Colors::Aqua.r, Colors::Aqua.g, Colors::Aqua.b, Colors::Aqua.a),
			VertexPositionColor(-1.0f, -1.0f, -1.0f,
			   Colors::Purple.r, Colors::Purple.g, Colors::Purple.b, Colors::Purple.a)
		};
		m_vBuffer->set(0, COLOR_VERT_COUNT, vTemp.data());

		const std::array<unsigned short, COLOR_INDEX_COUNT> iTemp =
		{
			//FRONT FACE
			0, 1, 2,
			2, 1, 3,

			//BACK FACE
			4, 5, 6,
			6, 5, 7,

			//LEFT FACE
			5, 0, 7,
			7, 0, 2,

			//RIGHT FACE
			1, 4, 3,
			3, 4, 6,

			//TOP FACE
			5, 4, 0,
			0, 4, 1,

			//BOTTOM FACE
			6, 7, 3, 
			3, 7, 2
		};
		m_iBuffer->set(0, COLOR_INDEX_COUNT, iTemp.data());
	}

	void PrimitiveCube::init_shader_program()
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

	void PrimitiveCube::applyTransform(GLCamera3D* camera)
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
			glm::rotate(Mat4(1.0f), m_rotationX, Vec3(1, 0, 0)) *
			glm::rotate(Mat4(1.0f), m_rotationY, Vec3(0, 1, 0)) *
			glm::rotate(Mat4(1.0f), m_rotationZ, Vec3(0, 0, 1));

		/*apply value from camera*/
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
	}

	void PrimitiveCube::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		m_iBuffer->bind();
		m_program->Bind();

		applyTransform(camera);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		VertexPositionColor::Enable(true);
		VertexPositionColor::RenderElements(COLOR_INDEX_COUNT, GL_TRIANGLES);
		VertexPositionColor::Enable(false);

		m_vBuffer->unbind();
		m_iBuffer->unbind();
		m_program->Unbind();
	}

}