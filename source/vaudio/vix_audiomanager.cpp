#include <vix_audiomanager.h>

namespace Vixen {

	AudioManager::AudioManager()
	{

	}

	AudioManager::~AudioManager()
	{

	}

	ErrCode AudioManager::VStartUp()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;
		
		/*create fmod sound system*/
		error = FMOD_CheckError(FMOD::System_Create(&m_system));
		if (CheckError(error))
			return error;

		/*initialize fmod sound system*/
		error = FMOD_CheckError(m_system->init(MAX_CHANNELS, FMOD_INIT_NORMAL, NULL));
		if (CheckError(error))
			return error;

		return error;
	}

	ErrCode AudioManager::VShutDown()
	{
		ErrCode error = ErrCode::ERR_SUCCESS;

		/*close sound system*/
		error = FMOD_CheckError(m_system->close());
		/*release sound system*/
		error = FMOD_CheckError(m_system->release());

		return error;
	}

}