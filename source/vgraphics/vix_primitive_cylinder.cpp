#include <vix_primitive_cylinder.h>


namespace Vixen {

	PrimitiveCylinder::PrimitiveCylinder()
	{
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
		m_rotationZ = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VertPosColBuffer(SPHERE_VERTEX_COUNT);
		m_iBuffer = new GLIndexBuffer(SPHERE_INDEX_COUNT);
		m_subdivisions = 4.0f;
		m_radius = 1.0f;

		init_shader_program();
		init_color_vi_buffers();
	}

	PrimitiveCylinder::PrimitiveCylinder(float radius, float height, float subdivisions, Color c)
	{
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
		m_rotationZ = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VertPosColBuffer(SPHERE_VERTEX_COUNT);
		m_iBuffer = new GLIndexBuffer(SPHERE_INDEX_COUNT);
		m_subdivisions = subdivisions;
		m_radius = radius;
		m_height = height;
		m_color = c;

		init_shader_program();
		init_color_vi_buffers();
	}

	PrimitiveCylinder::~PrimitiveCylinder()
	{

	}

	void PrimitiveCylinder::RotateX(float dt)
	{
		m_rotationX += dt * 50.0f;
	}

	void PrimitiveCylinder::RotateY(float dt)
	{
		m_rotationY += dt * 50.0f;
	}

	void PrimitiveCylinder::RotateZ(float dt)
	{
		m_rotationZ += dt * 50.0f;
	}

	void PrimitiveCylinder::SetPosition(float x, float y, float z)
	{
		m_position = Vec3(x, y, z);
	}


	void PrimitiveCylinder::init_color_vi_buffers()
	{
		
		const std::array<VertexPositionColor, 8> vTemp =
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
		m_vBuffer->set(0, 8, vTemp.data());

		const std::array<unsigned short, 36> iTemp =
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
		m_iBuffer->set(0, 36, iTemp.data());
		
		
	}

	void PrimitiveCylinder::init_shader_program()
	{
		/*vertex shader info*/
		ShaderInfo vshader_info;
		vshader_info.filePath = VTEXT("Tess.vs");
		vshader_info.raw = VTEXT("");
		vshader_info.type = ShaderType::VERTEX_SHADER;

		/*tesselation control shader info*/
		ShaderInfo tcontrol_info;
		tcontrol_info.filePath = VTEXT("Tess.tc");
		tcontrol_info.raw = VTEXT("");
		tcontrol_info.type = ShaderType::TESSELATION_CONTROL_SHADER;

		ShaderInfo teval_info;
		teval_info.filePath = VTEXT("Tess.te");
		teval_info.raw = VTEXT("");
		teval_info.type = ShaderType::TESSELATION_EVAL_SHADER;


		/*fragment shader info*/
		ShaderInfo fshader_info;
		fshader_info.filePath = VTEXT("Tess.fs");
		fshader_info.raw = VTEXT("");
		fshader_info.type = ShaderType::FRAGMENT_SHADER;

		/*ShaderInfo gshader_info;
		gshader_info.filePath = VTEXT("Tess.go");
		gshader_info.raw = VTEXT("");
		gshader_info.type = ShaderType::GEOMETRY_SHADER;*/

		/*populate shader args*/
		ShaderArgs args;
		args[0] = vshader_info;
		args[1] = tcontrol_info;
		args[2] = teval_info;
		//args[3] = gshader_info;
		args[3] = fshader_info;

		/*create shader program*/
		m_program = new GLShaderProgram(args);
	}

	void PrimitiveCylinder::applyTransform(GLCamera3D* camera)
	{
		GLuint projLoc;
		GLuint worldLoc;
		GLuint viewLoc;
		GLuint tessiloc;
		GLuint tessoloc;
		GLuint colorloc;

		m_program->GetUniformLoc(SHADER_GLOBAL_PROJECTION, projLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_VIEW, viewLoc);
		m_program->GetUniformLoc(SHADER_GLOBAL_WORLD, worldLoc);
	    m_program->GetUniformLoc("TessLevelInner", tessiloc);
		m_program->GetUniformLoc("TessLevelOuter", tessoloc);
		m_program->GetUniformLoc("gFragColor", colorloc);

		Mat4 world = Mat4(0.0f);
		world =
			glm::translate(Mat4(1.0f), m_position) * //apply position
			glm::rotate(Mat4(1.0f), m_rotationX, Vec3(1, 0, 0)) *
			glm::rotate(Mat4(1.0f), m_rotationY, Vec3(0, 1, 0)) *
			glm::rotate(Mat4(1.0f), m_rotationZ, Vec3(0, 0, 1)) *
			glm::scale(Mat4(1.0f), glm::vec3(m_radius));

		/*apply value from camera*/
		glUniform1f(tessiloc, 2);
		glUniform1f(tessoloc, 2);
		glUniform4f(colorloc, m_color.r, m_color.g, m_color.b, m_color.a);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
	}

	void PrimitiveCylinder::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		m_iBuffer->bind();
		m_program->Bind();

		applyTransform(camera);

		VertexPositionColor::Enable(true);
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		VertexPositionColor::Render(36, GL_PATCHES);
		VertexPositionColor::Enable(false);

		m_vBuffer->unbind();
		m_iBuffer->unbind();
		m_program->Unbind();
	}

}