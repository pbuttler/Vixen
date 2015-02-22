#ifndef VIX_FILESYSTEM_H
#define VIX_FILESYSTEM_H

#include <vix_platform.h>
#include <vix_containers.h>
#include <vix_stringutil.h>

namespace Vixen {

	enum FSMode
	{
		FS_READ,
		FS_WRITE,
		FS_APPEND
	};

	class VIX_API FileList
	{
		typedef std::vector<UString> UStringList;
	public:
		FileList(void);

		UString				GetBasePath(void);
		int					GetNumFiles(void);
		UString				GetFile(size_t index);
		const UStringList&  GetList(void) const;

	private:
		UString		 m_basePath;
		UStringList  m_list;
	};

	class VIX_API FileSystem
	{
		typedef std::vector<UString> FileList;
	public:
		FileSystem(void);

		~FileSystem(void);

		void Init(void);
		void Restart(void);
		void Shutdown(void);
		
	private:
		size_t	m_readCnt; //bytes read
		size_t	m_loadCnt; //files read
		UString	m_folder;  //game folder

	};

}

#endif
