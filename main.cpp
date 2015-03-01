#include <vix_game.h>
#include <vix_primitive_cube.h>
#include <vix_primitive_sphere.h>
#include <vix_primitive_cone.h>
#include <vix_primitive_cylinder.h>

using namespace Vixen;

class TestGame : public IGame
{
public:
  TestGame(void);
  ~TestGame(void);

  virtual void VOnStartup(void);
  virtual void VOnUpdate(float dt);
  virtual void VOnRender(float dt);
  virtual void VOnShutdown(void);

private:
  BMFont*            font;
  size_t             subdivisions;
  PrimitiveCube*     cube;
  PrimitiveSphere*   sphere;
  PrimitiveCone*     cone;
  PrimitiveCylinder* cylinder;
  bool               render_cube;
  bool               render_sphere;
  bool               render_cone;
  bool               render_cylinder;
};

TestGame::TestGame(void)
  :IGame()
{

}

TestGame::~TestGame(void)
{

}

void TestGame::VOnStartup(void)
{
  render_cube = true;
  render_sphere = false;
  render_cone = false;
  render_cylinder = false;
  subdivisions = 12;
  cylinder = new PrimitiveCylinder(1, 1, subdivisions, Colors::Red);
  cone = new PrimitiveCone(1, 1, subdivisions, Colors::Red);
  cube = new PrimitiveCube;
  sphere = new PrimitiveSphere(1, 12, Colors::Red);
  font = m_content.LoadFont(VTEXT("Consolas_24.fnt"));
}

void TestGame::VOnUpdate(float dt)
{
  cube->RotateY(0.001f);
  sphere->RotateY(0.001f);
  cylinder->RotateY(0.001f);
  cone->RotateY(0.001f);

  //HANDLE KEYBOARD
  
  if(m_keyboard->KeyPress(IKEY::S)) {
    cylinder->RotateX(0.001f);
    cone->RotateX(0.001f);
    cube->RotateX(0.001f);
    sphere->RotateX(0.001f);
  }

  if(m_keyboard->KeyPress(IKEY::W)) {
    cylinder->RotateX(-0.001f);
    cone->RotateX(-0.001f);
    cube->RotateX(-0.001f);
    sphere->RotateX(-0.001f);
  }

  if(m_keyboard->SingleKeyPress(IKEY::F1)) {
    render_cube = true;
    render_cylinder = false;
    render_cone = false;
    render_sphere = false;
  }

  if(m_keyboard->SingleKeyPress(IKEY::F2)) {
    render_cylinder = true;
    render_cube = false;
    render_cone = false;
    render_sphere = false;

    if(subdivisions > cylinder->GetMaxSubdivisions()) {
      subdivisions = cylinder->GetMaxSubdivisions();
      cylinder->SetSubdivisions(subdivisions);
    }
  }

  if(m_keyboard->SingleKeyPress(IKEY::F3)) {
    render_cone = true;
    render_cylinder = false;
    render_cube = false;
    render_sphere = false;

    if(subdivisions > cone->GetMaxSubdivisions()) {
      subdivisions = cone->GetMaxSubdivisions();
      cone->SetSubdivisions(subdivisions);
    }
  }

  if(m_keyboard->SingleKeyPress(IKEY::F4)) {
    render_sphere = true;
    render_cone = false;
    render_cylinder = false;
    render_cube = false;
  }

  if(m_keyboard->SingleKeyPress(IKEY::A) && !render_cube) {
    subdivisions--;
    if(subdivisions <= 0)
      subdivisions = 1;
    cylinder->SetSubdivisions(subdivisions);
    cone->SetSubdivisions(subdivisions);
    sphere->SetSubdivisions(subdivisions);
  }

  if(m_keyboard->SingleKeyPress(IKEY::D) && !render_cube) {
    subdivisions++;
    if(render_cylinder)
      if(subdivisions > cylinder->GetMaxSubdivisions())
	subdivisions = cylinder->GetMaxSubdivisions();
    if(render_cone)
      if(subdivisions > cone->GetMaxSubdivisions())
	subdivisions = cone->GetMaxSubdivisions();
    sphere->SetSubdivisions(subdivisions);
    cone->SetSubdivisions(subdivisions);
    cylinder->SetSubdivisions(subdivisions);
  }
  
}


void TestGame::VOnRender(float dt)
{
  if(render_cube) {
    cube->Render(((GLRenderer*)m_renderer)->Camera3D());
    ((GLRenderer*)m_renderer)->Render2DText(font, UString(VTEXT("CUBE")), Vector2(-1, 20), Colors::White);
  }
  if(render_sphere) {
    sphere->Render(((GLRenderer*)m_renderer)->Camera3D());
    ((GLRenderer*)m_renderer)->Render2DText(font, UString(VTEXT("SPHERE (ICOSAHEDRON)")), Vector2(-1, 20), Colors::White);
  }
  if(render_cone) {
    cone->Render(((GLRenderer*)m_renderer)->Camera3D());
    ((GLRenderer*)m_renderer)->Render2DText(font, UString(VTEXT("CONE")), Vector2(-1, 20), Colors::White);
  }
  if(render_cylinder) {
    cylinder->Render(((GLRenderer*)m_renderer)->Camera3D());
    ((GLRenderer*)m_renderer)->Render2DText(font, UString(VTEXT("CYLINDER")), Vector2(-1, 20), Colors::White);
  }
  
  
}

void TestGame::VOnShutdown(void)
{

}

int main(int argc, char* argv[])
{
  TestGame game;

  return game.Run();
}
