#ifndef VIX_AUDIOMANAGER_H
#define VIX_AUDIOMANAGER_H

#include <vix_platform.h>
#include <vix_manager.h>
#include <vix_singleton.h>
#include <vix_fmod.h>


namespace Vixen {

	class VIX_API AudioManager : public Singleton <AudioManager>, IManager
	{
		const int MAX_CHANNELS = 100;

	public:
		/*constructor (NOTE: intialization occurs in VStartUp()*/
		AudioManager();

		/*desturctor (NOTE: destruction occurs in VShutDown()*/
		~AudioManager();

		/*Initialize AudioManager*/
		ErrCode VStartUp()  override;

		/*Destruct AudioManager*/
		ErrCode VShutDown() override;

	private:
		FMOD::System* m_system;
	};

}

#endif
