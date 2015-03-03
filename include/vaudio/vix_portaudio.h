#ifndef VIX_PORTAUDIO_H
#define VIX_PORTAUDIO_H

#include <vix_platform.h>
#include <portaudio.h>


/*
*	PAUDIO_Error
*	Checks for PortAudio error and outputs
*   error string.
*   returns true if error
*   return false if no error
*/
VIX_API
bool PAUDIO_Error(PaError err);

/*
*	PAUDIO_Init
*	Initializes PortAudio
*
*	Called on application startup
*/
VIX_API
void PAUDIO_Init();

/*
*	PAUDIO_Term
*	Terminates PortAudio
*
*	Called on application exit
*/
VIX_API
void PAUDIO_Term();

/*
*	PAUDIO_QueryDevices
*	Queries physical audio devices and outputs
*   information for each device.
*	
*/
VIX_API
void PAUDIO_QueryDevices();

/*
*	PAUDIO_PrintDevice
*	Prints information about specified device
*	
*/
VIX_API
void PAUDIO_PrintDevice(const PaDeviceInfo* dInfo, size_t i);

VIX_API
void PAUDIO_CloseStream(PaStream* stream);

#endif
