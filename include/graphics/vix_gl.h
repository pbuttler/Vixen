#ifndef VIX_GL_H
#define VIX_GL_H

//////////////////////////////////////////////////////////////////////////
// Checks to see if glew should be supported
// *This is checked first because GLEW must be included before
// the OpenGL (GL and GLU) headers
//////////////////////////////////////////////////////////////////////////
#ifndef VIX_NO_GLEW
#include <gl/glew.h>
#endif

//////////////////////////////////////////////////////////////////////////
// This file includes operating specific paths for OpenGL (GL and GLU)
// headers, which depending on operating system may have different paths
//////////////////////////////////////////////////////////////////////////
#if defined(VIX_SYS_WINDOWS)
	//Visual C++ version of gl.h using WINGDIAPI and APIENTRY but doesn't define them
	//so window.h must be included
	#ifdef _MSC_VER
	#define _CRT_SECURE_NO_WARNINGS //disable warnings for safe function versions
	#include <windows.h>
	#endif

	#include <gl/gl.h>
	#include <gl/glu.h>
#elif defined(VIX_SYS_LINUX) //Linux
	#include <gl/gl.h>
	#include <gl/glu.h>
#elif defined(VIX_SYS_MACOS) //Mac OS
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
#endif

#endif