﻿/*
	The MIT License(MIT)

	Copyright(c) 2014 Matt Guerrette

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files(the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions :
	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include <vix_sdlwindow.h>
#include <vix_debugutil.h>
#include <vix_glrenderer.h>
#include <vix_glshaderprogram.h>
#include <vix_gltexturebatcher.h>
//#include <vix_audiomanager.h>
#include <vix_contentmanager.h>
#include <vix_math.h>

namespace Vixen {

	SDLGameWindow::SDLGameWindow(const SDL_GW_Params& params)
	{
		m_params = params;
		m_running = false;
		m_hidden = false;
		m_paused = false;
	}

	SDLGameWindow::~SDLGameWindow()
	{
		delete m_renderer;
	}

	ErrCode SDLGameWindow::VInit()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/* Initialize SDL
		*/
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			DebugPrintF(VTEXT("SDL Failed to Initialize: %s\n"),
				        ErrCodeString(ErrCode::ERR_SDL_INIT_FAIL));
			return ErrCode::ERR_SDL_INIT_FAIL;
		}

		/*Create the SDL_Window handle*/
#ifdef UNICODE
		UConverter convert;
		std::string title = convert.to_bytes(m_params.title); 
#else
		std::string title = m_params.title;
#endif
		m_windowHandle = SDL_CreateWindow(title.c_str(),
											m_params.x <= 0 ? SDL_WINDOWPOS_CENTERED : m_params.x,
											m_params.y <= 0 ? SDL_WINDOWPOS_CENTERED : m_params.y,
											m_params.width,
											m_params.height,
											SDL_WINDOW_OPENGL);
		if (!m_windowHandle) {
			SDL_Quit();
			DebugPrintF(VTEXT("Failed to created SDL_Window handle: %s\n"),
				ErrCodeString(ErrCode::ERR_SDL_CREATE_FAIL));
			return ErrCode::ERR_SDL_CREATE_FAIL;
		}

		/*create OpenGL context*/
		m_context = SDL_GL_CreateContext(m_windowHandle);
		if (!m_context) {
			SDL_Quit();
			DebugPrintF(VTEXT("Failed to create SDL_GL_Context handle: %s\n"),
				ErrCodeString(ErrCode::ERR_SDL_CREATE_FAIL));
			return ErrCode::ERR_SDL_CREATE_FAIL;
		}

		m_renderer = new GLRenderer;
		error = m_renderer->VInit();
		if (CheckError(error)) {
			DebugPrintF(VTEXT("Renderer failed to initialize: %s\n"),
				ErrCodeString(error));
			return error;
		}




		return error;
	}

	ErrCode SDLGameWindow::VRun()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*try and initialize window*/
		error = VInit();
		if (CheckError(error)) {
			DebugPrintF(VTEXT("SDLGameWindow failed to initialize: %s\n"),
				ErrCodeString(error));
			return error;
		}

		Texture* tex = g_ContentManager.Load<Texture>(TEX_FOLDER_PATH + VTEXT("stackedTileSheet.png"));
		BMFont*  font = g_ContentManager.Load<BMFont>(VTEXT("Consolas_28.fnt"));

		m_renderer->VSetClearColor(Colors::Black);

		/*run application loop*/
		m_running = true;
		while (m_running)
		{
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					VClose();
					break;

				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
					case SDLK_F5:
						VSetFullscreen(!m_fullscreen);
						break;
					}
					break;
				}
			}

			m_renderer->VClearBuffer(ClearArgs::COLOR_BUFFER);

			
			((GLRenderer*)m_renderer)->Render2DText(font, UString(VTEXT("Hello, World")),
				Vector2(20, 20),
				Colors::White);
			SDL_GL_SwapWindow(m_windowHandle);
		}

		return error;
	}

	void SDLGameWindow::VSetFullscreen(bool flag)
	{
		m_fullscreen = flag;
		if (flag) {
			SDL_SetWindowFullscreen(m_windowHandle, SDL_WINDOW_FULLSCREEN);
		}
		else {
			SDL_SetWindowFullscreen(m_windowHandle, 0);
		}
	}

	void SDLGameWindow::VSetVisible(bool flag)
	{
		

	}

	void SDLGameWindow::VSwapBuffers()
	{
		

	
	}

	const UString& SDLGameWindow::VGetTitle()
	{
		return m_title;
	}

	const Rect SDLGameWindow::VGetClientBounds()
	{
		Rect r;
		SDL_GetWindowPosition(m_windowHandle, &r.x, &r.y);
		SDL_GetWindowSize(m_windowHandle, &r.w, &r.h);
		return r;
	}

	bool SDLGameWindow::VIsPaused()
	{
		return m_paused;
	}

	bool SDLGameWindow::VIsHidden()
	{
		return m_hidden;
	}

	bool SDLGameWindow::VIsRunning()
	{
		return m_running;
	}

	void SDLGameWindow::VClose()
	{
		m_running = false;
		SDL_GL_DeleteContext(m_context);
		SDL_Quit();
	}

	void SDLGameWindow::OutputDisplayModes()
	{
		int numModes = SDL_GetNumDisplayModes(0);
		for (int i = 0; i < numModes; i++)
		{
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(0, i, &mode);
			DebugPrintF(VTEXT("DisplayMode[%i]: <W: %i, H: %i>\n"), i, mode.w, mode.h);
		}
	}

}