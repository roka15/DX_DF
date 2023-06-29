#pragma once
#include "../External/PngLib/include/png.h"
#ifdef _DEBUG
#pragma comment(lib,"..\\External\\PngLib\\lib\\Debug\\Zlib.lib")
#pragma comment(lib,"..\\External\\PngLib\\lib\\Debug\\Pnglib.lib")
#else
#pragma comment(lib,"..\\External\\PngLib\\lib\\Release\\Zlib.lib")
#pragma comment(lib,"..\\External\\PngLib\\lib\\Release\\Pnglib.lib")
#endif

namespace roka
{
	/*struct IHDRInfo
	{
		unsigned int length;
		unsigned int width;
		unsigned int height;
		char bit_depth;
		char color_type;
		char compression;
		char filter;
		char interlace;
	};
	struct PngInfo
	{
		IHDRInfo ihdr;
		char* idat_pixel;
	};
	
	class PngReader
	{
	public:
		static IHDRInfo Read(const unsigned char* data);
		
	private:

	};*/
}


