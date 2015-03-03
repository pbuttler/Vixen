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

bool
PAUDIO_Init()
{
	PaError err;
	err = Pa_Initialize();
	return PAUDIO_Error(err); //check error
}

bool
PAUDIO_Term()
{
	PaError err;
	err = Pa_Terminate();
	return PAUDIO_Error(err); //check error
}

void PAUDIO_QueryDevices()
{
	using namespace Vixen;

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

bool
PAUDIO_OpenStreamDef(PaStream*          stream,
                     int                inChannels,
                     int                outChannels,
                     PaSampleFormat     sampleFormat,
                     double             sampleRate,
                     unsigned long      framesPerBuffer,
                     PaStreamCallback*  callback,
                     void*              data)
{
    PaError err;
    err = Pa_OpenDefaultStream(&stream,
                               inChannels,
                               outChannels,
                               sampleFormat,
                               sampleRate,
                               framesPerBuffer,
                               callback,
                               &data);
    return PAUDIO_Error(err);
}

bool
PAUDIO_OpenStreamDef(PaStream*          stream,
                     int                inChannels,
                     int                outChannels,
                     PaSampleFormat     sampleFormat,
                     unsigned long      framesPerBuffer,
                     PaStreamCallback*  callback,
                     void*              data)
{
    PaError err;
    err = Pa_OpenDefaultStream(&stream,
                               inChannels,
                               outChannels,
                               sampleFormat,
                               PAUDIO_SAMPLERATE,
                               framesPerBuffer,
                               callback,
                               &data);
    return PAUDIO_Error(err);
}

bool
PAUDIO_CloseStream(PaStream* stream)
{
    PaError err;
    err = Pa_CloseStream(stream);
    return PAUDIO_Error(err);
}

void
PAUDIO_Sleep()
{
    Pa_Sleep(PAUDIO_SLEEPSECONDS * 1000);
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
