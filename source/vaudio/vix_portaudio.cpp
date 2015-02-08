#include <vix_portaudio.h>
#include <vix_debugutil.h>


bool
PAUDIO_Error(PaError err)
{
	using namespace Vixen;

	if (err != paNoError) {
		const char* errText = Pa_GetErrorText(err);
#ifdef UNICODE
		UConverter cv;
		UString text = cv.from_bytes(errText);
		DebugPrintF(VTEXT("PortAudio Error: %s\n"), text.c_str());
#else
		DebugPrintF(VTEXT("PortAudio Error: %s\n"), errText);

#endif
		return true;
	}
	else {
		return false;
	}
}

void
PAUDIO_Init()
{
	PaError err;
	err = Pa_Initialize();
	PAUDIO_Error(err); //check error
}

void
PAUDIO_Term()
{
	PaError err;
	err = Pa_Terminate();
	PAUDIO_Error(err); //check error
}

void PAUDIO_QueryDevices()
{
	using namespace Vixen;

	PaError err;
	int numDevices;
	numDevices = Pa_GetDeviceCount();
	if (numDevices < 0) {
		PAUDIO_Error(numDevices);
		return;
	}

	const PaDeviceInfo* deviceInfo;
	for (int i = 0; i < numDevices; i++)
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		PAUDIO_PrintDevice(deviceInfo, i);
	}
}

void
PAUDIO_PrintDevice(const PaDeviceInfo* dInfo, size_t i)
{
	using namespace Vixen;

	if (!dInfo)
		return;


#ifdef UNICODE
	UConverter cv;
	UString name = cv.from_bytes(dInfo->name);
#else
	UString name(dInfo->name);
#endif

	
	DebugPrintF(VTEXT("AUDIO DEVICE [%d]\n"), i);
	DebugPrintF(VTEXT("\tNAME: %s\n"), name.c_str());
	DebugPrintF(VTEXT("\tMAX_ICHANNELS: %d\n"), dInfo->maxInputChannels);
	DebugPrintF(VTEXT("\tMAX_OCHANNELS: %d\n"), dInfo->maxOutputChannels);

}