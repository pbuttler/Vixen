#ifndef VIX_CPP_REST_H
#define VIX_CPP_REST_H

#include <vix_platform.h>
#include <vix_debugutil.h>
#include <cpprest/filestream.h>
#include <cpprest/interopstream.h>
#include <cpprest/interopstream.h>
#include <cpprest/filestream.h>
#include <cpprest/containerstream.h>
#include <cpprest/producerconsumerstream.h>
#include <iostream>

using namespace concurrency;
using namespace concurrency::streams;

inline task<void> cppWriteFileAsync(const std::string path, std::stringstream& ss)
{
	stdio_istream<char> astream(ss);

	auto fileStream = std::make_shared<ostream>();
	utility::string_t _path;
	_path.assign(path.begin(), path.end());

	task<void> file_task = fstream::open_ostream(_path).then([=](ostream outFile)
	{
		*fileStream = outFile;

		return astream.read_to_end(fileStream->streambuf());
	}).then([=](size_t bytesWritten)
	{
		return fileStream->close();
	});

	return file_task;

}

inline void vixWriteFileAsync(const std::string path, std::stringstream& ss)
{
	try
	{
		cppWriteFileAsync(path, ss).wait();
	}
	catch (const std::exception& e)
	{
		Vixen::vixOutputDebugString(e.what());
	}
}

inline void vixWriteFileSync(const std::string path, std::stringstream& ss)
{
	std::fstream outFile(path);
	outFile.write(ss.str().c_str(), ss.str().size());
	outFile.close();
}

#endif