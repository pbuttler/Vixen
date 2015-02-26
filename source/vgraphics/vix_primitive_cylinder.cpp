#include <vix_primitive_cylinder.h>
#include <vix_math.h>

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
		int sides = 10;
		const float height = 1.0f;
		const float radius = 1;
		const float angle = 2 * PI / (float)sides;
		const float c = cos(angle);
		const float s = sin(angle);
		
		std::vector<VertexPositionColor> verts;
		float x2 = radius;
		float z2 = radius;
		for(int i = 0; i <= sides; i++)
		{
			verts.push_back(VertexPositionColor(0.0f + x2, 0.0f, 0.0f + z2, 1.0f, 0.0f, 0.0f, 1.0f));
			verts.push_back(VertexPositionColor(0.0f + x2, 0.0f + height, 0.0f + z2, 1.0f, 0.0f, 0.0f, 1.0f));

			const float x3 = x2;
			x2 = c * x2 - s * z2;
			z2 = s * x3 + c * z2;
		}
		m_vBuffer->set(0, verts.size(), verts.data());
	}

	void PrimitiveCylinder::init_shader_program()
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

	void PrimitiveCylinder::Render(GLCamera3D* camera)
	{
		m_vBuffer->bind();
		//m_iBuffer->bind();
		m_program->Bind();

		applyTransform(camera);

		VertexPositionColor::Enable(true);
		VertexPositionColor::RenderArrays(m_vertCnt, GL_TRIANGLE_STRIP);
		VertexPositionColor::Enable(false);

		m_vBuffer->unbind();
		//m_iBuffer->unbind();
		m_program->Unbind();
	}

}