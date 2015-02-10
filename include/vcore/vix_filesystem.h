#ifndef VIX_FILESYSTEM_H
#define VIX_FILESYSTEM_H

#include <vix_platform.h>
#include <vix_containers.h>

namespace Vixen {

	enum FSMode
	{
		FS_READ,
		FS_WRITE,
		FS_APPEND
	};

	class VIX_API FileSystem
	{
	public:
		FileSystem(void);

		~FileSystem(void);
	};

}

#endif
