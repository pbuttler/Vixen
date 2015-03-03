#include <vix_libarchive.h>
#include <vix_debugutil.h>
#include <cstring>

void
ARCHIVE_Extract(char* zip, char* file, BYTE* buffer)
{
	archive* a;
	archive* ext;
	archive_entry* entry;
	int ret;
	a = archive_read_new();
	archive_read_support_format_zip(a);
	ext = archive_write_disk_new();
	archive_write_disk_set_options(ext, ARCHIVE_EXTRACT_PERM);
	
	if ((ret = archive_read_open_filename(a, zip, LARGE_BUFSIZE)))
		Vixen::DebugPrintF(VTEXT("err: archive_read_open_filename %s \n"),
		        archive_error_string(a));
	for (;;) {
		ret = archive_read_next_header(a, &entry);
		if (ret == ARCHIVE_EOF)
			break;
		/*look for requested file*/
		const char* entryName = archive_entry_pathname(entry);
		if (strcmp(file, entryName) == 0)
			break; /*if found, break*/
	}
	
	BYTE* buff = ARCHIVE_CopyData(a);
	memcpy(buffer, buff, LARGE_BUFSIZE);
	delete[] buff;
	buff = NULL;

	archive_read_close(a);
	archive_read_free(a);
}

BYTE*
ARCHIVE_CopyData(archive* ar)
{
	BYTE* buff = new BYTE[LARGE_BUFSIZE];

	archive_read_data(ar, (void*)buff, LARGE_BUFSIZE);

	return buff;
}
