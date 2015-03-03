#include <vix_primitive_cone.h>
#include <vix_math.h>

namespace Vixen {


	PrimitiveCone::PrimitiveCone()
	{
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
		m_rotationZ = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VertPosColBuffer(32);
		m_iBuffer = new GLIndexBuffer(SPHERE_INDEX_COUNT);
		m_subdivisions = 10.0f;
		m_radius = 1.0f;

		init_shader_program();
		init_color_vi_buffers();
	}

	PrimitiveCone::PrimitiveCone(float radius, float height, float subdivisions, Color c)
	{
		m_rotationX = 0.0f;
		m_rotationY = 0.0f;
		m_rotationZ = 0.0f;
		m_position = Vec3(0.0f, 0.0f, -5);
		m_vBuffer = new VertPosColBuffer(32);
		m_iBuffer = new GLIndexBuffer(SPHERE_INDEX_COUNT);
		m_subdivisions = subdivisions;
		m_radius = radius;
		m_height = height;
		m_color = c;

		init_shader_program();
		init_color_vi_buffers();
	}

	PrimitiveCone::~PrimitiveCone()
	{
        delete m_program;
	}

	void PrimitiveCone::SetSubdivisions(size_t sub)
	{
		m_subdivisions = sub;
		init_color_vi_buffers();
	}

	size_t PrimitiveCone::GetMaxSubdivisions()
	{
		return SUBDIVISIONS;
	}

	void PrimitiveCone::RotateX(float dt)
	{
		m_rotationX += dt * 50.0f;
	}

	void PrimitiveCone::RotateY(float dt)
	{
		m_rotationY += dt * 50.0f;
	}

	void PrimitiveCone::RotateZ(float dt)
	{
		m_rotationZ += dt * 50.0f;
	}

	void PrimitiveCone::SetPosition(float x, float y, float z)
	{
		m_position = Vec3(x, y, z);
	}

	size_t PrimitiveCone::GetSubdivisions()
	{
		return m_subdivisions;
	}


	void PrimitiveCone::init_color_vi_buffers()
	{
		m_botVerts.clear();
		m_bodyVerts.clear();

		const float r = 1.0f;
		const float h = 1.0f;
		const float min_sub = 3;
		const float max_sub = 12;
		const float a = TWO_PI / (m_subdivisions + (min_sub-1));

		//BOTTOM CAP VERTS
		m_botVerts.push_back(VertexPositionColor(0, -h, 0, 1.0f, 0.0f, 0.0f, 1.0f));
		for(float i = 0; i <= TWO_PI; i += a)
		{
			m_botVerts.push_back(VertexPositionColor(r*cos(i), -h, r*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
		}
		m_botVerts.push_back(VertexPositionColor(r, -h, 0, 1.0f, 0.0f, 0.0f, 1.0f));

		//MIDDLE
		m_bodyVerts.push_back(VertexPositionColor(0, h, 0, 1.0f, 0.0f, 0.0f, 1.0f));
		for(float i = 0; i <= TWO_PI; i += a)
		{
			m_bodyVerts.push_back(VertexPositionColor(r*cos(i), -h, r*sin(i), 1.0f, 0.0f, 0.0f, 1.0f));
		}

	}

	void PrimitiveCone::init_shader_program()
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

	void PrimitiveCone::applyTransform(GLCamera3D* camera)
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

	void PrimitiveCone::Render(GLCamera3D* camera)
	{
		m_program->Bind();

		applyTransform(camera);


		//RENDER BOTTOM
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		m_vBuffer->set(0, m_botVerts.size(), m_botVerts.data());
		m_vBuffer->bind();
		VertexPositionColor::Enable(true);
		VertexPositionColor::RenderArrays(m_botVerts.size(), GL_TRIANGLE_FAN);
		VertexPositionColor::Enable(false);
		m_vBuffer->unbind();

		//RENDER BOTTOM
		m_vBuffer->set(0, m_bodyVerts.size(), m_bodyVerts.data());
		m_vBuffer->bind();
		VertexPositionColor::Enable(true);
		VertexPositionColor::RenderArrays(m_bodyVerts.size(), GL_TRIANGLE_FAN);
		VertexPositionColor::Enable(false);
		m_vBuffer->unbind();

		//m_iBuffer->unbind();
		m_program->Unbind();
	}
}
