#include <vix_primitive_sphere.h>
#include <vix_color.h>
#include <vix_math.h>

#define S_X .525731112119133606 
#define S_Z .850650808352039932

namespace Vixen {

	PrimitiveSphere::PrimitiveSphere()
	{
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
		m_rotationZ = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VertPosColBuffer(SPHERE_VERTEX_COUNT);
		m_iBuffer = new GLIndexBuffer(SPHERE_INDEX_COUNT);


		init_shader_program();
		init_color_vi_buffers();
	}

	PrimitiveSphere::~PrimitiveSphere()
	{

	}

	void PrimitiveSphere::RotateX(float dt)
	{
		m_rotationX += dt * 50.0f;
	}

	void PrimitiveSphere::RotateY(float dt)
	{
		m_rotationY += dt * 50.0f;
	}

	void PrimitiveSphere::RotateZ(float dt)
	{
		m_rotationZ += dt * 50.0f;
	}

	void PrimitiveSphere::SetPosition(float x, float y, float z)
	{
		m_position = Vec3(x, y, z);
	}


	void PrimitiveSphere::init_color_vi_buffers()
	{
		
#pragma region ICOSAHEDRON
		std::array<VertexPositionColor, SPHERE_VERTEX_COUNT> vTemp =
		{
			VertexPositionColor(-S_X, 0.0f, S_Z, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( S_X, 0.0f, S_Z, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor(-S_X, 0.0f, -S_Z, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( S_X, 0.0f, -S_Z, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( 0.0f, S_Z, S_X, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( 0.0f, S_Z, -S_X, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( 0.0f, -S_Z, S_X, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( 0.0f, -S_Z, -S_X, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( S_Z, S_X, 0.0f, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( -S_Z, S_X, 0.0f, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( S_Z, -S_X, 0.0f, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a),
			VertexPositionColor( -S_Z, -S_X, 0.0f, Colors::Red.r, Colors::Red.g, Colors::Red.b, Colors::Red.a)
		};
		std::array<unsigned short, SPHERE_INDEX_COUNT> iTemp = 
		{
			0, 4, 1,
			0, 9, 4,
			9, 5, 4,
			4, 5, 8,
			4, 8, 1,
			8, 10, 1,
			8, 3, 10,
			5, 3, 8, 
			5, 2, 3,
			2, 7, 3,
			7, 10, 3,
			7, 6, 10,
			7, 11, 6,
			11, 0, 6,
			0, 1, 6,
			6, 1, 10,
			9, 0, 11,
			9, 11, 2,
			9, 2, 5,
			7, 2, 11
		};
		m_iBuffer->set(0, SPHERE_INDEX_COUNT, iTemp.data());

		
		m_vBuffer->set(0, SPHERE_VERTEX_COUNT, vTemp.data());

#pragma endregion
		
	}

	void PrimitiveSphere::init_shader_program()
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

	void PrimitiveSphere::applyTransform(GLCamera3D* camera)
	{
		GLuint projLoc;
		GLuint worldLoc;
		GLuint viewLoc;
		GLuint tessiloc;
		GLuint tessoloc;

		m_program->GetUniformLoc("Projection", projLoc);
		m_program->GetUniformLoc("View", viewLoc);
		m_program->GetUniformLoc("World", worldLoc);
		m_program->GetUniformLoc("TessLevelInner", tessiloc);
		m_program->GetUniformLoc("TessLevelOutter", tessoloc);

		Mat4 world = Mat4(0.0f);
		world =
			glm::translate(Mat4(1.0f), m_position) * //apply position
			glm::rotate(Mat4(1.0f), m_rotationX, Vec3(1, 0, 0)) *
			glm::rotate(Mat4(1.0f), m_rotationY, Vec3(0, 1, 0)) *
			glm::rotate(Mat4(1.0f), m_rotationZ, Vec3(0, 0, 1));

		/*apply value from camera*/
		glUniform1f(tessiloc, 1.0f);
		glUniform1f(tessoloc, 1.0f);
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(camera->Projection()));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(camera->View()));
		glUniformMatrix4fv(worldLoc, 1, GL_FALSE, glm::value_ptr(world));
	}

	void PrimitiveSphere::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		m_iBuffer->bind();
		m_program->Bind();

		applyTransform(camera);

		VertexPositionColor::Enable(true);
		glPatchParameteri(GL_PATCH_VERTICES, 3);
		VertexPositionColor::Render(SPHERE_INDEX_COUNT, GL_PATCHES);
		VertexPositionColor::Enable(false);

		m_vBuffer->unbind();
		m_iBuffer->unbind();
		m_program->Unbind();
	}

}