#ifndef VIX_INTERFACES_H
#define VIX_INTERFACES_H

#include <vix_platform.h>
#include <vix_stringutil.h>
#include <vix_errglobals.h>

namespace Vixen {

	class Rect;
	class Point;

	class VIX_API INonCopyable
	{
	protected:
		INonCopyable() { }
		~INonCopyable() { }

	private:
		INonCopyable(const INonCopyable&);
		const INonCopyable& operator= (const INonCopyable&);
	};

	class VIX_API IApplication : INonCopyable
	{
	public:
		virtual ~IApplication() { }

		virtual ErrCode VInit()     = 0; //application init
		virtual int     VRun()      = 0; //application loop

	};


	class VIX_API IGameWindow : INonCopyable
	{

	public:
		virtual ~IGameWindow() { }
		
		virtual ErrCode            VInit() = 0;
		virtual void               VSetFullscreen(bool flag,
			                                      bool keep_res = false) = 0;
		virtual void               VSetVisible(bool flag) = 0;
		virtual const std::string& VGetTitle() = 0;
		virtual const Rect&        VGetClientBounds() = 0;
	
		static const size_t DEF_WINDOW_WIDTH  = 800;
		static const size_t DEF_WINDOW_HEIGHT = 600;
	};

	class VIX_API IManager
	{
	public:
		virtual void VStartUp() = 0;
		virtual void VShutDown() = 0;
	};

	class VIX_API IContent
	{
	public:
		//methods
	};

	class VIX_API IShader
	{
	protected:
		virtual bool VLoadFromFile(const std::string& filePath) = 0;
		virtual bool VLoadFromString(const std::string& shaderString) = 0;
	};

	class VIX_API IKeyboardHandler
	{
	public:
		virtual bool VOnKeyDown(const byte c) = 0;
		virtual bool VOnKeyUp(const byte c) = 0;
	};

	class VIX_API IRenderer
	{
	public:

		virtual void VShutdown() = 0;
		virtual void VSetClearColor(byte r, byte g, byte b, byte a) = 0;
		virtual void VSwapBuffers() = 0;
	};

}

#endif