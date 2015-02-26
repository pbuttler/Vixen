#ifndef VIX_LIBARCHIVE_H
#define VIX_LIBARCHIVE_H

#include <vix_platform.h>
#include <archive.h>
#include <archive_entry.h>

#define LARGE_BUFSIZE 300000

#define _FILE_OFFSET_BITS 64

VIX_API
void ARCHIVE_Extract(char* zip, char* file, BYTE* buffer);


VIX_API
BYTE*  ARCHIVE_CopyData(archive* ar);

#endif